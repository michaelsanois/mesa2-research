# Original MESA captures recovered and reconciled

13 October 2026. This supplement resolves the missing **client-side** capture evidence under U04/U06. It supersedes earlier statements that the raw captures were guest-only or that the complete uploaded headers were unavailable. Physical firmware questions remain separate.

## Result

**Yes: there is now sufficient evidence to begin implementing the offline uploader and captured golden-vector tests.** Exact sample and single-keygroup program transcripts, full 192-byte outgoing headers, raw PCM and synthetic reply bytes are available locally and tied to file hashes. Implementation should remain offline/disabled for hardware. No new MESA experiment, VM boot, Bridge change or physical transfer was performed.

The recovered program was a blank New Program. Its four zone sample names were all blank, so these files still do not demonstrate a complete program linked to PROBE. That gap does not prevent testing codecs, scheduling, transcript replay, failure handling and source-derived slice preparation offline.

## Recovery and integrity

Source disk: `${LOCAL_HOME}/Library/Containers/com.utmapp.UTM/Data/Documents/Windows.utm/Data/1FD07E86-5695-4BC4-A72B-DA61BE76CAF5.qcow2`.

The disk is QCOW2 v3, virtual size 2 GiB, cluster size 65536, with no backing file, encryption or incompatible feature flags. Recovery used an ordinary byte copy into this chat's `work/` directory, verified against the source SHA-256. The allocated active L1/L2 mapping was read directly; the existing internal snapshot was not restored or changed. FAT32 partition type0C begins at LBA63, with512-byte sectors and eight sectors per cluster. Named allocated directory entries and FAT chains were followed read-only. No filesystem mount, target executable or guest OS was used.

[Recovery manifest](recovered-captures/recovery-manifest.json) records the source disk identity, extraction method, and every extracted file's guest path, cluster, raw directory entry, exact length and SHA-256. The hash identifies the retained disk copy; it does not authenticate historical timestamps or independently establish who ran the original experiment.

Recovered eight archives: `cap_import1`, `cap_import2`, `cap_postpcm`, `cap_program`, `cap_kg`, `cap_final`, `cap_range`, and `MESA_CAPTURE`. They contain893 capture files, including eight complete TRACE.TXT files. Six identified scratch files were recovered separately, for899 total files/416369 bytes. Scratch files are not substituted for exact trace-named payloads.

[Capture integrity](capture-integrity.json) checks1208 trace records: no duplicated sequence number within an archive, and every referenced payload file exists with exactly its recorded payload length. Archive identity plus sequence/tick is preserved. Incoming data and completion statuses are explicitly synthetic; outgoing `payload_kind` identifies the original client data. Requested length and captured length agree in the examined successful transfers. This proves logger/file consistency, not actual physical transferred-byte reporting.

## 1. Exact sample upload ordering

The complete successful POSTPCM sample transaction is C03 (`cap_postpcm`) seq62–72:

| Seq | CDB | Data / result |
|---:|---|---|
| 62 | `09 00 01 01 00 00` | Bulk MODE; no payload |
| 63 | `0C 00 00 01 88 00` |392-byte SDATA, sample identifier1, full192-byte header |
| 64 | `0D 00 00 00 00 00` | Availability bytes `00 00 07` |
| 65 | `0E 00 00 00 07 00` | `F0 47 00 16 48 00 F7`, synthetic OK |
| 66 | `0C 00 00 02 00 80` |512-byte raw PCM DATA OUT |
| 67 | `09 00 00 00 00 00` | Normal MODE |
| 68 | `09 00 01 00 00 00` | Ordinary MIDI-over-SCSI MODE |
| 69 | `0C 00 00 00 0D 00` | `F0 47 00 34 48 01 00 00 00 00 00 00 F7` |
| 70 | `0D 00 00 00 00 00` | `00 00 07` |
| 71 | `0E 00 00 00 07 00` | `F0 47 00 16 48 00 F7`, synthetic OK |
| 72 | `09 00 00 00 00 00` | Normal MODE |

All these records report SRB status1, host status0 and target status0. There is no STATUS, RECEIVE, explicit ASPACK or intermediate Akai ACK between the single PCM SEND and normal-mode restoration. The header's readiness exchange uses **ordinary control00 even while MODE is bulk**. The captured post-object command uses an explicit switch back to ordinary mode.

C08 (`MESA_CAPTURE`) seq149–159 repeats the same complete command order. C02 (`cap_import2`) seq62–69 matches through the post-object SEND, but seq70–77 returns zero availability: that fixture lacked the post-function reply. This is client-observed polling, not evidence that the real sampler refuses the command.

Lakai remains a distinct reference path: it explicitly sends ASPACK after bulk MODE. The recovered MESA transcript conclusively excludes ASPACK within these two successful **sample-creation transactions**. It does not exclude ASPACK from every MESA operation, overwriting an existing sample or resuming a transfer.

The full trace-order data, including failure and readback windows, is in [upload-order.csv](upload-order.csv) and [upload-transactions.json](upload-transactions.json). The latter preserves complete selected records and full payload hex rather than only prefixes.

## 2. Exact program/keygroup ordering

C06 (`cap_final`) seq57–71:

| Seq | CDB | Data / result |
|---:|---|---|
| 57 | `09 00 01 00 00 00` | Ordinary MODE |
| 58 | `0C 00 00 01 88 00` | PDATA07, identifier128 (`00 01`),192 decoded bytes |
| 59 | `0D 00 00 00 00 00` | `00 00 07` |
| 60 | `0E 00 00 00 07 00` | REPLY16/status0 |
| 61 | `09 00 00 00 00 00` | Normal MODE |
| 62 | `09 00 01 00 00 00` | Ordinary MODE |
| 63 | `0C 00 00 01 89 00` | KDATA09, program255 (`7F 01`), keygroup0,192 decoded bytes |
| 64 | `0D 00 00 00 00 00` | `00 00 07` |
| 65 | `0E 00 00 00 07 00` | REPLY16/status0 |
| 66 | `09 00 00 00 00 00` | Normal MODE |
| 67 | `09 00 01 00 00 00` | Ordinary MODE |
| 68 | `0C 00 00 00 0D 00` | Same post-object function1 |
| 69 | `0D 00 00 00 00 00` | `00 00 07` |
| 70 | `0E 00 00 00 07 00` | REPLY16/status0 |
| 71 | `09 00 00 00 00 00` | Normal MODE |

C08 seq69–83 repeats this exact order. The recovered traces therefore establish per-object normal-mode restoration/re-entry for this New Program action, not just one mode switch covering its entire upload. Bridge can retain bus ownership while reproducing these interface-mode changes.

C04 (`cap_program`) stops at zero-availability polling after KDATA because the fixture had no keygroup reply. C05 (`cap_kg`) acknowledges PDATA/KDATA but polls zero availability after the post-object command. Those failures corroborate which response boundaries blocked client progression; they do not validate hardware error causes.

## 3. Complete header and PCM examples

Every chosen header was decoded only after verifying exact envelope size/EOX, op/type, identifier, and every nibble's range. Its decoded body is exactly192 bytes. [Header examples](captured-header-examples.json) contains complete hex, source archive/sequence/tick and wire/body hashes; [capture-headers](capture-headers) contains the192-byte binary bodies. [Captured golden vectors](captured-golden-vectors.json) contains full outbound packets and PCM. These supplement the earlier synthetic boundary vectors.

| Object | Original source | Decoded SHA-256 |
|---|---|---|
| PROBE sample header | C03 seq63; repeated identically C08 seq150 | `e1623a9691f8dae9f374849541d21aa824f00ec22957891ece6e1a90f648a99e` |
| PROGPROBE program header | C06 seq58; repeated identically C08 seq70 | `f0b2a9aede8baaaf59a6424ef0b8914f117f8c0e550402e6552f4ba49737eb15` |
| Blank default keygroup | C06 seq63; repeated identically C08 seq75 | `1b890db35029572ba39e0c654a98848e9bd0267ab416559087d03be45dda8a7e` |
| PROBE PCM512 bytes | C02 seq66, C03 seq66, C08 seq153 | `3019b24ddc6a66f0d31f65013335b81ce8bfa0ba2de675c870e40755d0e299d5` |

PCM was independently compared on the host with frames read from the preserved PROBE.WAV using Python's WAV parser: mono,16-bit,44100Hz,256 frames. All three complete512-byte writes match exactly. This upgrades the old guest FC/B report to directly rechecked captured bytes.

The sample header has type3, bandwidth1, root60, encoded PROBE, rate-valid80, playback type3, zero tuning/location/start/loops, length256, end255, stereo-partner0, and rate44100. Thus MESA uses an inclusive last-frame end (`N−1`) in this probe, and transmits sample-length/rate fields little-endian. This is not a universal proof of every loop/end convention.

Program fields include type1, name PROGPROBE, internal first-group pointer0, MIDI program number1, polyphony byte31, priority1, low/high21/127, stereo level90, loudness90 and GROUPS1. The keygroup has type2, next-group pointer0, low/high21/127, filter90, envelope defaults and four space-filled encoded sample-name slots. Constant-pitch flags are zero; all zone sample pointers are zero. **No zone points to PROBE.**

## 4. Bridge serializer comparison

Read-only source comparison used B03/B04 plus B05 `S2000InitializationTemplate.h` and B06 `HDA_INITIALIZATION_EXPORT.md`. B05's384-byte template hashes to the existing documented `d87eb973fe8e19ba71b95e34f982e07caeeebaddc9267b319e2014fea553e988`. Its claimed origin is a user-approved hardware-saved program; this pass verified its embedded bytes/hash, not its historical physical origin.

[Byte differences](bridge-default-differences.csv) records32 common-header,30 keygroup-header and three sample-header differences. Common/group comparisons normalize names and linked-list pointers/count, apply the documented slice constant-pitch/pointer policies, and retain other template defaults. They are **source-derived comparison fixtures, not an executed Bridge snapshot**. Slice-specific playable ranges and sample names still depend on the actual upload plan; the captured MESA New Program has blank zones, whereas a slice export intentionally names its sample.

| Field | Captured MESA | Bridge source/default | Conclusion |
|---|---|---|---|
| Sample length/end/rate |256/255/44100, LE | Same for the same256-frame input | Compatible byte representation for this case. No off-by-one mismatch found. |
| Sample playback byte19 |3, documented no-loop | B04 writes2, documented loop-until-release | Confirmed behavioral/default mismatch if attempting to reproduce MESA's no-loop probe. Not evidence that Bridge's approved slice behavior should be changed. |
| Sample stereo-partner136–137 |`00 00` | B04 writes `FF FF` | Exact wire-default mismatch; acceptance/normalization unknown. |
| Zone sample pointers56/80/104/128 |`00 00` in each blank zone | B03 sets `FF FF` for each zone | Exact policy mismatch; disk-export pointer policy must not be assumed proven for SCSI upload. |
| Constant pitch zone1 byte132 |0 | B03 explicitly patches1 | Intentional slice-playback behavior; not a packet-format defect. |
| Play/keygroup low note |21 | Embedded approved template24 before per-slice patches | Valid range/default difference; actual slice notes override it. |
| Program MIDI number15 |1 | Template0, preserved by slice preparation | Default difference; neither is the resident allocation ordinal. |
| Stereo level/loudness |90/90 | Approved template99/80 | Sound-setting differences, not established incompatibility. |
| Crossfade factors/unused/internal fields | Several zero bytes | Approved template oftenFF and other retained values | Preserve approved sound defaults; determine a separate validated upload normalization policy. |

It would be incorrect to call every byte difference an incompatible S2000 setting or overwrite the user's approved opaque template with MESA's New Program defaults. The established incompatibilities are with **byte-for-byte MESA reproduction** and, for playback type, the requested no-loop behavior. Real SCSI rejection remains unproven.

The existing Bridge transport remains SysEx-only and its disk program container is multiple concatenated headers. An uploader still needs separate PDATA/KDATA messages, a raw PCM backend capability and complete transaction ownership. This comparison does not modify those implementations.

## 5. Readback and failure reconciliation

C06 seq81 is exactly the32-byte two-name program-list reply, without the scratch wildcard concatenation. Seq82/103 ask for program0; seq84/105 return the synthetic SYNTH LAB header. Seq114 is likewise program0/group0. These prove the prior “uploaded program selected” limitation was justified.

C08 does request uploaded program1 via extended byte reads at seq127/130 and208/211. Each reads only one byte: channel offset16 returns00 and MIDI program-number offset15 returns01. No complete program1/keygroup readback or zone assignment was recovered. The fixture source explains these responses; they are not independent physical evidence.

C08 seq186 requests sample1 and seq188 returns its complete392-byte SDATA envelope. The decoded header matches the outgoing seq150 header exactly, confirming full **synthetic sample metadata** round-trip. There is no bulk PCM readback request in these upload windows; captured DATA OUT equality is not sampler-resident PCM verification.

C01's failed header transaction has no readiness reply and no PCM SEND, yet it later emits the same post-object function after switching to ordinary mode. Therefore the mere presence of function1 in a trace cannot prove PCM completed. Bridge should stop after failed readiness rather than inherit this failure-side continuation.

Corrections to historical prose: C03 seq71's exact recorded tick is45574541 (not the earlier reported45574454). Its complete payload is seven bytes; root scratch ACK concatenation is unnecessary. C06 seq81 is exactly32 bytes. Root `upload.bin` is393 bytes and is not substituted for the original392-byte SDATA file. Historical reports are preserved unchanged; this supplement records the corrections.

## Remaining boundary and implementation decision

U04 is resolved for exact ordinary/bulk mode ordering and successful seven-byte fixture ACKs in these recovered runs. Real readiness variants, WAIT/NAK/CANCEL semantics and physical residual/phase behavior remain open. U06 is resolved for complete outgoing examples, inclusive probe end, PCM bytes and source-default comparison; physical internal-field normalization remains open.

Begin offline implementation using pinned recovered transcripts and full captured golden packets. Test strict codecs, synthetic inbound parsing, per-object mode scheduling, successful sample/program replay, no-reply failures, byte accounting and cancellation/restoration states. Multi-group and block-boundary cases may use explicitly synthetic fixtures informed by existing static evidence; they are not new captured results. Hardware enablement still requires allocation, linked-program/readback, field-normalization, transport and recovery validation. No additional MESA capture experiment is needed to start this bounded offline work.
