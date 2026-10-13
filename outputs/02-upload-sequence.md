# End-to-end SEND PROGRAM sequence

> **Capture reconciliation update:** Original guest files have now been recovered offline. [05-capture-reconciliation.md](05-capture-reconciliation.md) supersedes initial-pass statements about missing raw headers/traces and records the exact mode ordering, complete examples, Bridge differences and revised readiness decision.

13 October 2026. Read with [protocol findings](01-protocol-report.md) and [unresolved questions](04-unresolved-questions.md). This is a specification for future implementation; nothing in this document authorizes hardware execution.

## What is exact, and what is composed

**Confirmed static/client evidence:** MESA’s sample-import routine sends a sample header, consumes a readiness response, streams raw PCM, and restores normal mode. Its program routines send PDATA, wait for an Akai OK reply, then send keygroups sequentially, checking their replies. Existing captures show post-object function 1 after each kind of operation.

**Reasonable design composition:** upload and verify all uniquely named samples first, then upload the program common header and its complete sample-linked keygroups, then verify the program. That composition avoids creating a program referencing incomplete samples. The retained captures did not exercise one complete combined SEND PROGRAM action with verified zone assignments, so it must not be presented as MESA’s observed end-to-end behavior.

## Exact recovered sample-import subroutine

The following is analyst pseudocode of A03 `0x10001240–0x10001480`, with virtual targets resolved from its embedded vtable at `0x10005288`. It is not original source. The mono path is shown; source length comes from the file interface, so Bridge must independently check it against header frame count.

```text
runSampleImport(headerWire392, source):
    executeNoDataCDB(09 00 01 01 00 00)           // constructor's bulk MODE
    response = exchange(
        SEND = 0C 00 00 01 88 00,
        DATA_OUT = headerWire392,
        STATUS = 0D 00 00 00 00 00,
        RECEIVE = 0E 00 u24be(availableBytes) 00,
        concatenateUntilLastByteIsF7)
    if response[0] != F0: return localError(0x3EB)
    if response[3] == 7D: return localError(0x3F2)
    if response[3] == 7E: return localError(0x3F1)
    if response[3] == 7C:
        poll/read bounded six-byte response, then re-evaluate response
    // Any other opcode reaches streaming in this inspected lower-level path.
    // It is not a strict REPLY16/status0 check.
    remaining = source.lengthBytes()
    while remaining > 0:
        bytes = source.read(min(remaining, 32768))
        if bytes.count == 0: return localError(0x4D2)
        executeDataOutCDB(0C 00 u24be(bytes.count) 80, bytes)
        if commandError: return error
        remaining -= bytes.count
    executeNoDataCDB(09 00 00 00 00 00)           // virtual +44 → 10003390
    return completion
```

There is **no explicit ASPACK**, no per-PCM-block STATUS/RECEIVE loop, and no per-PCM-block Akai ACK in this inspected subroutine. These are bounded static negative findings, not a claim about all MESA paths. H02 seq63/66 corroborates SDATA followed by raw PCM; the complete intervening trace is now recovered in C03/C08. On the observed original-client continuation, H02 seq69 sends post-object function 1 and seq71 receives seven-byte REPLY16/status0 from the synthetic adapter.

The mode restore above belongs to the successful lower-level sample job. Later high-level ordinary requests may re-enter MIDI-over-SCSI mode. Recovered C03/C08 show normal MODE after PCM, ordinary MODE before function1 and normal MODE after its ACK. C06/C08 likewise restore/re-enter ordinary mode between each program/keygroup/post-function exchange. This pins captured-client order without proving a physical firmware profile.

## Exact recovered program subroutine

Two shipped paths were examined: New Program (`0x10007390`, `0x10007540`, `0x100075D0`, `0x10007720`) and copying an existing in-memory program (`0x1000A040`, `0x1000A220`, `0x1000A2B0`, `0x1000A440`).

```text
createOrCopyProgram(rawCommon192, rawKeygroups):
    encode the proposed 12-character name; reject name found in current list
    commonWire = PDATA(identifier=128, nibble(rawCommon192))
    exchange ordinary SEND/STATUS/RECEIVE until complete reply
    require operation16 and decoded status0
    for k = 0 .. lastSourceKeygroup:
        kgWire = KDATA(programIdentifier=255, keygroupIndex=k,
                       nibble(rawKeygroups[k]))
        exchange ordinary SEND/STATUS/RECEIVE until complete reply
        require operation16 and decoded status0
    invalidate MESA's local program cache/list model; notify caller
```

The copy path explicitly follows the next source keygroup; the New Program path creates one default keygroup. H02 PROGRAM_LAB seq58/63 and KG_LAB seq58/63 corroborate PDATA128 → KDATA255/group0. KG_LAB seq68 then sends post-object function1. The final function is established by captures and the common function builder/callback, not by assigning a speculative “commit” name to the last-keygroup callback.

## Proposed complete Bridge state machine

Every transition below must be one non-coalesced transaction on the existing hardware queue. A backend owner retains exclusive access across all steps, including periods when the sampler is in normal mode.

| Step | Action and exact wire shape | Required completion | Evidence class |
|---:|---|---|---|
| 0 | Prepare immutable mono PCM and 192-byte common/keygroup/sample headers; resolve names and dependencies locally. | Exact lengths, frame counts, supported profile, no unresolved assignments. | DESIGN using B03/B04 |
| 1 | Acquire exclusive backend/bus ownership; bind approved SCSI endpoint, sampler identity and generation. | Ownership and endpoint admission; approved physical-validation state. | DESIGN/H07 |
| 2 | Ordinary-mode metadata exchange: MODE `09 00 01 00 00 00`; RSTAT `F0 47 cc 00 48 F7`; RPLIST op02 and RSLIST op04. | Valid STAT and complete name lists; sufficient capacity; no encoded-name collision. | DOCUMENTARY and prior client requests; exact outer mode behavior needs U04 |
| 3 | For each sample, enter bulk MODE `09 00 01 01 00 00`. | Transport completion; no payload. | STATIC A03 |
| 4 | SEND `0C 00 00 01 88 00`, DATA OUT `SDATA(sampleCreationIdentifier, header192)`. | Ordinary-channel STATUS/RECEIVE; full recognized readiness reply. For v1 require REPLY16/status0; legitimate WAIT/readiness variants need U04. | STATIC + H02 seq63; identifier policy U01 |
| 5 | Consecutive raw PCM SENDs: `0C 00 u24be(blockBytes) 80`, each block even and ≤32768. | Exact bytes and GOOD transport status for each block; total = 2×frames. No invented MIDI ACK/checksum between chunks. | STATIC + H02 seq66 |
| 6 | Restore normal MODE `09 00 00 00 00 00`; enter ordinary mode for the next message as required by the validated profile. | Completion and known current mode, while retaining ownership. | STATIC successful sample path; U04 outer ordering |
| 7 | SEND13 `F0 47 cc 34 48 01 00 00 00 00 00 00 F7`. | Ordinary exchange; exact REPLY16/status0. | H02 seq69/71; semantic effect U03 |
| 8 | Refresh sample list; uniquely locate uploaded encoded name, obtain its actual resident ordinal; read its sample header (legacy RSDATA0A/SDATA0B or existing validated 2B/2C reader). | Header semantic fields match; no reliance on a synthetic slot, old ordinal or allocation token. | DESIGN + documentary readback |
| 9 | Verify complete sample PCM by a separately validated bulk read profile, or retain explicit “PCM not independently verified”. | Exact frame count and byte/hash match if required for verified success. | DESIGN; bulk-read units remain U08 |
| 10 | After all samples pass the profile's required checks, SEND392 PDATA identifier128 with GROUPS=K. | Ordinary REPLY16/status0. | STATIC + H02 PROGRAM_LAB seq58 |
| 11 | SEND393 KDATA255 for k=0..K−1. Zone sample names exactly match prepared/uploaded names. | Ordinary REPLY16/status0 after every group, before next group. | STATIC copy callbacks; H02 seq63 for group0 |
| 12 | SEND the same post-object function1. | Ordinary REPLY16/status0. | H02 KG_LAB seq68; effect U03 |
| 13 | Refresh program list; locate exact new name; RPDATA06 for returned ordinal and RKDATA08 for every keygroup. | Correct PDATA07/KDATA09 envelopes, lengths, name, GROUPS, ranges, zone names and validated parameter fields. | DESIGN; H02 FINAL_LAB shows later list/header traffic |
| 14 | Refresh capacity/status, restore normal interface mode and complete backend ownership cleanup. | Clean transport/mode/owner result; emit final receipt only after cleanup succeeds. | DESIGN; historical final normal MODE |

Steps 8/9/13 are verification requirements chosen for Bridge, not a claim that MESA performs a full PCM comparison. Optional multi-part selection or MIDI program change is outside this SEND function. H02’s `C0 00` is normal performance MIDI transported through SCSI; it is not an Akai upload acknowledgement and is not needed to prove residency.

The sample-creation identifier in step4 is an explicit profile decision. MESA’s static header construction uses the current sample-list count (`0x10008D0C–0x10008D39`), consistent with the historical one-existing-sample fixture sending identifier1. Whether the installed firmware treats that as a safe append token, whether sorting changes it, and what ACK/list result establishes the allocated object are U01. Do not silently substitute 255 or 128 for samples.

## Success and failure

**Verified resident success** requires a current device identity, every acknowledged object write, exact PCM transfer accounting, complete post-write program/keygroup readback, verified sample dependencies, profile-required PCM verification, normal interface mode and successful ownership cleanup. A name appearing in a list is insufficient.

Keep separate receipt flags for `writesAcknowledged`, `metadataReadbackVerified`, `pcmTransferBytesVerified`, `pcmReadbackVerified` and `cleanupVerified`. Never report the last flag as true because HTTP returned 200 or a helper process exited. A transfer that stops after PDATA can leave dummy/incomplete keygroups; a sample header accepted without full PCM can leave incomplete sample state.

On a timeout or uncertain DATA OUT completion, stop subsequent writes. Preserve stage, raw command/reply, intended byte range and whether completion is known. Do not replay the last raw block or creation header automatically; the sampler may already have consumed it. Reconnection, metadata inspection, operator-approved deletion and retry are distinct actions requiring a validated recovery policy. There is no recovered atomic rollback/commit protocol.

Normal-mode restoration is an actual sampler command, not a local unlock. Attempt it only when the transport/session remains trustworthy and the applicable validation profile permits cleanup. If hardware/helper cleanup is uncertain, retain backend uncertainty and the existing project’s recovery fence; do not automatically restart target service. No reset, autosense, delete, front-panel action or power-cycle is implicit in SEND.

## Reconciled transcript baseline

Use C03 seq62–72 and C06 seq57–71 (confirmed again by C08) as the captured offline schedule. Their exact per-command bytes and synthetic ACKs are in upload-transactions.json and upload-order.csv. Preserve normal/ordinary mode changes between PDATA, KDATA and post-object function1 while retaining exclusive ownership. Sample SDATA readiness uses ordinary STATUS/RECEIVE while MODE is bulk. No ASPACK or per-block Akai ACK appears in the recovered tiny-sample transaction. Complete192-byte examples and PCM are in captured-golden-vectors.json. Longer/multi-group and physical verification steps remain designed/static rather than captured.
