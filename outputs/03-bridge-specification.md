# Bridge SEND PROGRAM TO S2000: implementation contract

> **Capture reconciliation update:** Original guest files have now been recovered offline. [05-capture-reconciliation.md](05-capture-reconciliation.md) supersedes initial-pass statements about missing raw headers/traces and records the exact mode ordering, complete examples, Bridge differences and revised readiness decision.

13 October 2026. This contract specifies codecs and a future upload transaction. It does not change Bridge, enable hardware writes, or claim that unresolved firmware behavior has been validated.

## Implementation boundary

Use the existing `AkaiHardwareRequestQueue` (B02) for one complete upload job. It is the sole hardware transaction worker; UI/audio threads consume immutable progress/results. The entire job has a single backend owner. Uploads must not use parameter coalescing keys: dropping or replacing a queued header/group/block would invalidate the sequence.

`AkaiTransport` (B01) presently exposes complete SysEx sending, status, admission, cancellation and disconnect. Raw PCM is not a MIDI message. Introduce a conceptually separate upload transaction capability at the transport/backend boundary in a future implementation; do not pass PCM to `sendSysexAsync`, the ordinary reply parser, a UI widget or a per-block HTTP SysEx route. Transport-specific ownership/mode/actual-byte handling remains in the backend.

Existing B03/B04 disk preparation can supply validated local names, mono PCM and raw templates. Split a program file into its common header plus individual groups. Do not upload the HDA image, directory entry, disk type marker `F0`/`F3`, or file container headers. The wire type bytes are 1/2/3 inside the decoded headers.

## Typed input, result and backend capability

Suggested types, DESIGN rather than existing API declarations:

```text
UploadPlan {
  requestId, deviceSessionGeneration, targetIdentity, profileId
  programNameEncoded[12], programHeader[192]
  keygroups: array<Header192>       // length K, matches GROUPS at byte42
  samples: array<{
    nameEncoded[12], sampleHeader[192], frameCount, rateHz
    immutablePcm16LE, pcmSha256, sourceIdentity
  }>
  nameCollisionPolicy = reject
  requirePcmReadback: bool          // supported only by a validated read profile
}

ScsiCompletion {
  commandStatus, hostStatus, targetStatus
  requestedBytes, actualBytes: optional<uint64>, residual: optional<uint64>
  completionKnown: bool, rawSense: optional<bytes>
}

UploadReceipt {
  requestId, profileId, firmwareIdentity, programResidentOrdinal
  sampleNameToResidentOrdinal, perObjectSemanticReadback
  writesAcknowledged, pcmTransferBytesVerified, pcmReadbackVerified
  metadataReadbackVerified, cleanupVerified
  totalPcmBytesConfirmed, stage, error, completionUncertain
}
```

Backend must implement: exclusive transaction begin/end; no-data MODE; bounded DATA OUT and DATA IN with exact completion information; ordinary message assembly/validation; cancellation checkpoints; restoration/uncertainty reporting; durable transaction-stage evidence if process interruption can leave device state uncertain. A backend advertising only SysEx exchange or HTTP success does not meet the contract.

## Packet specification

All array indices are zero-based. Use checked integer arithmetic.

| Encoding | Rule |
|---|---|
| CDB length | n in 0..0xFFFFFF, three **8-bit**, most-significant-first bytes |
| Item identifier | n in 0..0x3FFF, two **7-bit**, least-significant-first bytes |
| Extended byte offset/count | n in 0..0x3FFF, two 7-bit low-first bytes |
| Extended frame position/count where applicable | four 7-bit low-first bytes, maximum 0x0FFFFFFF; not used to announce the recovered implicit sample-header path |
| Header payload | exactly 192 raw bytes → exactly 384 nibble bytes, low nibble first; each nibble ≤15 |
| Header integer fields | preserve validated raw template/profile; current documentary/disk representation is little-endian, distinct from CDB length |
| Name | exactly 12 Akai codes; alphabet `0123456789 ABCDEFGHIJKLMNOPQRSTUVWXYZ#+-.`, padding 10; canonicalize before collision checking |
| PCM | mono signed16 little-endian bytes for validated v1 source profile; exactly 2×frames, no WAV header or SysEx wrapping |

```text
headerWrite(op, identifier, raw192, kg=None):
  require op in {07,09,0B}; len(raw192)==192
  require raw192[0] == {07:1,09:2,0B:3}[op]
  wire = [F0,47,cc,op,48] + u14(identifier)
  if op==09: wire += [kg]           // bounded v1 K<=99 → kg0..98
  wire += concat([b&15,b>>4] for b in raw192) + [F7]
  require len(wire) == (393 if op==09 else 392)
  return wire

sendCdb(n, bulk): return [0C,00] + u24be(n) + [80 if bulk else 00]
receiveCdb(n, bulk): return [0E,00] + u24be(n) + [80 if bulk else 00]
statusCdb(bulk): return [0D,00,00,00,00,80 if bulk else 00]
postObject1(cc): return [F0,47,cc,34,48,01,00,00,00,00,00,00,F7]
```

Creation identifiers: program128 is confirmed MESA output; program255 identifies previous-created program in keygroup writes. Sample creation uses current list count in the examined MESA path. These must be selected by a separately validated firmware profile, not exposed as arbitrary user-controlled addresses. KDATA is sent immediately after successful PDATA with no intervening program creation, since 255 is context-dependent.

Header-write reply must be exactly a recognized complete envelope with matching `cc`, manufacturer47, model48, expected op16, status0 and terminalF7. Recognized documented nonzero status produces `samplerRejected`, preserving original bytes. Reject malformed/unrelated replies; no “any reply means OK” behavior. For extended readback replies, validate echoed identifier, selector, byte offset and decoded count. A physical adapter must separately report successful CDB completion and actual transfer bytes.

## Preparation and field ownership

1. Freeze selected Bridge program, keygroups, source audio and device-generation snapshot. Validate all referenced samples are available; reject missing audio and stale resident references.
2. Derive one encoded program name and unique encoded sample names. Enforce uniqueness against other planned objects and current resident lists. Decide canonicalization explicitly (e.g. uppercase ASCII); do not truncate distinct names into the same 12 bytes.
3. Require K in 1..99 for the initial documentary/MESA profile. Set program GROUPS at decoded offset42 to K. Raw type bytes must be1,2,3. Use only a template/profile whose complete 192-byte bodies and applicable parameter fields have been validated.
4. Patch key range bytes3/4 and zone name slots34+24×z as required by the frozen program. Preserve known parameter values. Leave calculated pointer fields to an explicit validated profile: host/disk addresses and resident ordinals are forbidden there. Do not infer pointer policy from the existing disk writer alone.
5. Produce exactly 2×N mono PCM bytes per sample, and set sample SLNGTH at26 consistently. Sample rate, root, tuning, loop/end semantics and reserved fields require profile-specific validation. No implicit resampling, downmixing or stereo partner creation in v1; conversions are explicit local preparation decisions outside transfer.
6. Verify lengths, hashes and arithmetic without hardware before any mutation. Recheck capacity/names/generation after transaction admission.

An existing resident sample may be reused only with validated identity, compatible metadata and audio-content policy. A matching name alone cannot prove a matching sample. V1 may instead require all sample names to be new and reject reuse, which reduces unproven equivalence decisions.

## Transaction state, progress and cancellation

Use the sequence in [02-upload-sequence.md](02-upload-sequence.md). Suggested states:

```text
prepared → admitted → inventoryChecked
  → sampleHeaderPending → sampleStreaming → samplePostFunction → sampleVerified
  → programHeaderPending → keygroupPending[k] → programPostFunction
  → programReadback → restoring → completed

any stage → rejectedBeforeWrite | failedKnown | completionUncertain
```

Record the intended transition before each mutating command. Advance only after the required exact result. Keep the next PCM byte offset locally for progress, but do not claim the sampler supports resuming at that offset. Counts are bytes at the SCSI layer and frames in sample metadata; these must remain distinct types.

Use per-command and total monotonic deadlines. Establish numeric limits by approved validation and backend capability; do not inherit Lakai's 100 ms delay or MESA's CPU-clock timing as a reliability guarantee. Availability zero means no bytes presently available, not instant failure or proof of all acknowledgements consumed. Bound message size, number of polls, total transfer bytes and unsolicited-message handling.

Cancel before the first write: release cleanly. Cancel between acknowledged objects/blocks: stop scheduling writes, classify partially resident state, and run only validated cleanup. Cancel/timeout during DATA OUT: completion is uncertain until reconciled. Never report a successful full upload after cancellation. UI progress measures confirmed bytes/objects; staged HTTP file upload progress is not SCSI progress.

## Error contract

| Error | Required response |
|---|---|
| Invalid local plan / unsupported profile | Reject before hardware admission |
| Busy / endpoint or generation changed | Reject; do not retarget automatically |
| Insufficient blocks/words or encoded-name collision | Reject before first write; no automatic deletion |
| Known sampler REPLY error | Stop; preserve reply and stage; do not invent a more specific reason |
| Unexpected readiness/WAIT variant | Stop or bounded handle only as the validated profile permits |
| Short transfer / unknown residual | Do not advance requested-length progress or claim complete PCM |
| Timeout / connection loss after mutating dispatch | Mark completionUncertain; no automatic write replay |
| Header/keygroup/PCM readback mismatch | Fail verification; retain created-object evidence; no implicit rollback |
| MODE restore or backend cleanup failure | Overall failure/uncertainty even if metadata readback passed |

Do not conflate HTTP errors, helper exit status, ASPI/SCSI statuses, availability counts and Akai REPLY statuses. Preserve these separately in diagnostics. The existing project’s recovery fences continue to govern backend cleanup; this specification does not redesign GPIO handling or grant service restart permission.

## Implementation readiness and acceptance

Ready to implement offline now: packet builders, strict parsers, immutable planning, field/name validation, byte accounting, progress/result states and transcript-driven transaction logic. [golden-vectors.json](golden-vectors.json) supplies independently specified codec fixtures; they are explicitly synthetic data, not captures or firmware defaults.

Not ready to enable against hardware: sample/program allocation profile, final function semantics, real readiness variants, target-normalized fields, actual-byte adapter reporting and recovery/PCM verification. Captured mode ordering is now pinned by supplement05. See U01–U09. A pure codec can be complete while the physical uploader remains disabled.

Meaningful offline acceptance should cover partial reply assembly, low-first vs high-first encodings, the 32768-byte boundary and final two-byte tail, wrong/colliding identities, multi-keygroup ordering, failure after PDATA, uncertain block completion, no automatic retries, cancellation and restoration failure. Playback or physical readback cannot be proven by fixture tests. No Bridge test/build changes were made in this investigation.

## Recovered capture acceptance baseline

**Sufficient evidence exists to start the offline uploader and golden-vector tests now.** Use captured-golden-vectors.json for full original-client PDATA/KDATA/SDATA/PCM bytes, and upload-transactions.json for successful and missing-reply fixtures. Retain earlier synthetic boundary vectors for uncaptured32768-byte/multi-block cases. For a MESA-equivalent PROBE fixture, sample playback byte19 is3 and partner bytes136–137 are0; B04 currently emits2/FFFF. Those are explicit comparison differences, not a direction to change approved slice defaults or a claim of physical rejection. Program/group sound defaults also differ from the approved Bridge template; preserve them unless a specifically chosen upload profile calls for conversion. See bridge-default-differences.csv.
