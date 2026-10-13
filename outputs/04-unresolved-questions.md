# Unresolved questions and evidence requirements

> **Capture reconciliation update:** Original guest files have now been recovered offline. [05-capture-reconciliation.md](05-capture-reconciliation.md) supersedes initial-pass statements about missing raw headers/traces and records the exact mode ordering, complete examples, Bridge differences and revised readiness decision.

13 October 2026. The following are focused gaps for SEND PROGRAM, not a new broad reverse-engineering plan. No hardware transfer or experiment is authorized by this document.

| ID | Question / known boundary | Evidence needed | Effect on implementation |
|---|---|---|---|
| U01 | How does this S2000 firmware allocate PDATA128 and SDATA(current sample-count), particularly at high occupancy? MESA deliberately emits those identifiers; fixture slot1 is invented. | Full original MESA control transcript with before/after lists and headers, plus separately approved real-firmware validation of new-name allocation. Check that128 cannot target an existing program in the admitted profile. | Blocks enabling creation writes; creation token cannot be used as a resident ordinal. |
| U02 | Does a complete multi-keygroup program with named sample dependencies become resident and correctly linked? Static copy callbacks iterate groups; historical New Program capture has only group0 and later UI/readback gaps. | Existing full captured common/group headers first; then a controlled sample-linked, multi-group client transcript. Physical metadata and PCM/readback verification later under separate approval. | Blocks claiming complete end-to-end success. |
| U03 | What does extended miscellaneous bank0/function1 do, and when is it necessary? Exact outgoing13 bytes and expected REPLY16/status0 are known. | Original numeric function mapping or firmware static evidence; alternatively narrowly controlled before/after state evidence under approval. D02's mention of BTSORT is not a numeric binding. | Keep command named post-object function1; do not implement speculative commit/relink/sort semantics. |
| U04 | **Client trace gap resolved:** C03/C06/C08 establish exact MODE/SEND/STATUS/RECEIVE order and seven-byte synthetic REPLY16/status0. Real WAIT/NAK/CANCEL/readiness variants remain unobserved. | Physical/documentary evidence only for those remaining variants; no repeat of completed successful client captures. Raw files are recovered and hashed. | Offline transcript scheduler can be implemented now; real firmware profile remains unvalidated. |
| U05 | Are 32768-byte blocks, final-tail handling and separate stereo-member uploads accepted by real S2000 and this adapter? Mono512 probe only is captured; large/stereo paths are static. | Existing larger client capture if available; otherwise offline client capture at32766/32768/32770 and several blocks, isolated from hardware. Stereo only if needed, with both headers and members. Physical long-transfer validation is separately approved. | Mono profile can use recovered chunk size in offline design; no proven hardware ceiling, no enabled stereo path. |
| U06 | **Complete example gap resolved:** full192-byte sample/program/keygroup headers, inclusive probe end255, sample metadata round-trip and Bridge byte differences are recovered. Firmware-owned field normalization remains unknown. | Separately approved physical before/after readback or authoritative firmware evidence for internal pointers/reserved fields. | Offline codecs and captured golden tests can be implemented; disk defaults are not automatically validated for SCSI. |
| U07 | Does the deployed/backend adapter prove actual DATA OUT bytes and support the required long-transfer phases/disconnect behavior? Prior H06 leaves residual reporting unresolved; current first-INQUIRY project does not validate long writes. | Exact retained adapter source/revision and completion contract; offline residual/short-transfer tests; separately approved physical transport validation. | Blocks claiming exact PCM transfer or reliable large uploads. |
| U08 | What is the exact S2000 bulk-read offset/count unit and PCM verification path? H06 identifies RSPACK word/byte disagreement between reference callers. Upload byte count does not solve download units. | Firmware/documentary clarification or controlled known-content read transcript. Verify full length, endian/signedness and byte accounting under an approved read plan. | Cannot claim independent PCM readback until resolved; preserve a separate verification flag. |
| U09 | What recovery is valid after timeout, partial header/PCM, target error or cleanup failure? No atomic rollback or safe write-replay algorithm is recovered. | Narrow failure/reconciliation design and offline state-machine tests first. Any real fault/retry/delete experiment needs a separate validation plan with explicit scope. | Disable automatic write retry/resume/delete/reset; retain partial/uncertain state. |

## Existing captures to retrieve before new client experiments

H01/H02 preserve guest paths `C:\cap_import1`, `C:\cap_import2`, `C:\cap_postpcm`, `C:\cap_program`, `C:\cap_kg`, `C:\cap_final`, `C:\cap_range`, and the later `C:\MESA_CAPTURE`. They are now recovered under this package's recovered-captures/ directory with exact guest-path/file-hash provenance. The VM was not launched; the disk was read from a verified offline copy.

Priority records:

| Capture / record | Why it matters |
|---|---|
| UPLOAD2 seq63,66,69 and every intervening record | Complete header readiness exchange, exact mode sequence, PCM and post-command |
| POSTPCM seq71 and its surrounding STATUS/RECEIVE | Original-client consumption of the synthetic post-function ACK |
| PROGRAM_LAB seq58,63; KG_LAB seq58,63,68 | Full192-byte common/group data and reply boundaries |
| FINAL_LAB seq81,84,103,114,115,116 | Which program was actually reread; final normal MODE; differentiate program0 from uploaded object |
| READBACK_LAB seq208,211,214,217,220,223 and preceding writes | Same-process PROGPROBE/PROBE state and later header-range accesses |

Use exact filenames, not wildcards: earlier DOS wildcard copies concatenated records (seq71 with100, seq81 with112). Preserve process/tick and archive identity because sequence numbers reset. Use binary-safe copying; previous text-mode DOS COPY truncated/expanded PCM/request scratch files. Those artifacts are not transfer bugs. Preserve complete raw files and SHA-256 before decoding; screenshots of a prefix are not complete payload evidence.

## Smallest subsequent work

Recovery and reconciliation are complete for the identified existing files. This settled the successful-client transcript and full-header questions without repeating experiments. Only if a specific gap remains should a new **isolated synthetic client** experiment target that gap (e.g. a two-keygroup linked program or a block-boundary probe). Do not repeat installer, ASPI loader, startup, effects refresh or the already-established512-byte mono import.

A later physical validation plan should bind firmware identity, endpoint, transport/backend revision, new unique names, memory limits, exact allowed commands, expected replies, required readback and failure containment. Separate milestones should establish identity/metadata, one tiny mono sample, one linked program, then multiple keygroups/large transfers and recovery. This is an outline of evidence requirements only; no plan was executed, no approval was requested, and no future command was authorized here.

The implementation can now proceed locally against the recovered pinned transcripts. Hardware-facing enablement remains contingent on the unresolved items relevant to the chosen profile. An attended one-command INQUIRY cannot by itself validate upload behavior.

## Updated readiness decision

Begin offline uploader/codec/transcript tests now. U01 allocation remains hardware-unverified; U02 remains unproven for linked/multi-group programs because the captured keygroups contain blank zones. U03 post-function semantics, U05 physical large/stereo transfers, U07 transport residuals, U08 physical PCM readback and U09 uncertain-write recovery remain open. These do not block offline implementation, but they block hardware enablement. The sample1 full synthetic metadata readback is now confirmed; program1 is only read via two one-byte range requests. See05 for source/timestamp corrections and exact sequences.
