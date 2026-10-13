# MESA II → Akai S2000: offline protocol findings

> **Capture reconciliation update:** Original guest files have now been recovered offline. [05-capture-reconciliation.md](05-capture-reconciliation.md) supersedes initial-pass statements about missing raw headers/traces and records the exact mode ordering, complete examples, Bridge differences and revised readiness decision.

13 October 2026. Objective: specify Bridge’s SEND PROGRAM TO S2000 without changing Bridge or interacting with the physical sampler.

## Result and scope

The recovered MESA II PC v1.5 code and prior original-client captures establish the outgoing program/keygroup envelopes, the sample-header-first SCSI upload path, raw PCM transport, client block sizes, and several reply checks. They support an implementation-ready **packet codec and transaction design**. They do **not** establish a hardware-validated, reliable S2000 uploader. Allocation on the installed firmware, the meaning of the final miscellaneous function, ambiguous-write recovery, and complete physical readback remain unresolved. A successful synthetic ACK must never satisfy those requirements.

MESA’s captured sample import and New Program actions were separate. No retained report demonstrates one complete, sample-linked program upload followed by physical residency verification. The end-to-end sequence in [02-upload-sequence.md](02-upload-sequence.md) deliberately identifies that composition as a proposed Bridge sequence.

Only local file reads, package materialization, hashing and static disassembly were performed in this investigation. No VM was started or altered; no original executable was launched; no Pi, SSH, SCSI, MIDI, device-control, Bridge build or deployment was used. Existing notes and source comments were treated as evidence or proposals, not instructions authorizing their suggested experiments.

## Evidence grades and reproducibility

| Grade | Meaning |
|---|---|
| STATIC | Instructions/data directly present in the identified shipped DLL; interpreted control flow is stated separately. Does not observe sampler execution. |
| HISTORICAL CLIENT | Existing analyst report of original MESA traffic against a synthetic ASPI adapter. Original guest capture files were not retrieved in the initial pass; they are now independently recovered under C01–C08 and reconciled in supplement05. |
| DOCUMENTARY | Retained transcription of Akai documentation, with its transcription and model-inheritance limitations. |
| SECONDARY | Lakai source or existing Bridge implementation; useful corroboration, not original MESA or hardware behavior. |
| DESIGN / HYPOTHESIS | Proposed Bridge policy or extrapolation requiring validation. |
| UNKNOWN | Evidence needed to resolve a material question is absent. |

`H01`–`H07`, `D01`–`D04`, `L01`, `F01`–`F02`, `B01`–`B04`, and `A01`–`A04` are **local source-register identifiers**, not REA Evidence IDs. Exact paths, sizes and SHA-256 are in [source-register.json](evidence/source-register.json). REA’s `open_binary` identified A03, but native queries reported `provider_unavailable`: Ghidra was not configured, Hopper was absent, and IDA was not configured. No analysis engine or unrelated software was installed. Native findings below use the installed LLVM objdump through `/usr/bin/objdump` and local byte parsing; they are not REA decompiler output.

| Artifact | SHA-256 / provenance |
|---|---|
| A01 MESA.ISO | `26a2b9b535d424b96c3029c3bbb30df3c0c5c0e846a166ffcc4bee3df9c857a2` |
| A02 DPSSETUP.MSI | `c40226e1fe6301ba41f8d28acfb16ad3dff7010af5ce6c9fb1dd6f9860adc8d2`; exact complete byte sequence occurs in A01 at file offset `0xF800` (63488). |
| A03 SCSIPlug.dll | `0385e9f145b97beb601a91dad18db9bdc6f6748a650fd7aa629a9c9c7fc239e8`; cabinet member `_1A0ACC18EBDA11D4B8140800460222F0` matches the existing extracted DLL. |
| A04 MESASAMPLER.dll | `4ff7d6457038c2f9035bb734ab046f8488ebb30a992b74a3c48a0a5fde4785b0`; cabinet member `_1A0ACC3FEBDA11D4B8140800460222F0`, matches H03’s prior audited identity. |

The MSI contains an `MSCF` cabinet at offset `0x5200`, size 783620 bytes. Its existing SCSIPlug member was reused. MESASAMPLER was rematerialized into this chat’s scratch directory because the previously extracted temporary copy was absent; the matching prior hash binds the recovered file to the earlier research. This was recovery of a missing artifact, not another installer investigation.

Both DLLs use preferred PE image base `0x10000000`. Addresses below are preferred virtual addresses, not addresses captured in a current process. Most inspected code/data lies in sections whose file offset equals RVA; use the excerpt’s explicit file-offset mapping, not that assumption for other sections. Function names used below are analyst labels. Linear disassembly can decode jump-table data as instructions; the report relies on selected code ranges and separately parsed tables. No compilable original source was recovered.

## Existing work reviewed and reused

| Source | Prior result retained | What this pass adds |
|---|---|---|
| H05 lab README; H04 loader audit | Installer paths, ASPI ordinals, support-info test, discovery setup. README’s “VM not created/no shim” statements are stale relative to later notes. | Artifact identity chain only; no repeated setup or loader experiment. |
| H02 MESA verification | Discovery corrections, processor-type requirement, startup handshake, sample import, New Program, keygroup and post-function captures; READBACK_LAB continuation. | Static upload-path, chunking, creation/copy callbacks and status handling. |
| H03 effects audit | Effects refresh code, fixture experiments and synthetic limitations. | Effects retrieval is excluded from the minimal uploader; no repeated FX emulation. |
| H01 consolidated upload findings | Header/PCM/PDATA/KDATA traffic and final-mode observation. | Wire layouts and static corroboration; does not upgrade synthetic results to hardware evidence. |
| F01 fixture source | Invented capacities, lab slots, bounded synthetic storage/ACKs. | Identifies which “resident” results belong to the fixture rather than firmware. |
| H06 resident PCM audit; L01 Lakai | Bulk read reference, byte/unit conflicts, adapter actual-byte reporting gaps. | Separates Lakai’s explicit ASPACK upload from MESA’s implicit sample-header path. |
| H07 PiSCSI compatibility assessment | First controlled INQUIRY is only conditionally prepared; long writes are not validated. | Carries the physical-validation boundary into the proposed uploader specification. |
| D01–D04 protocol documents/source ledger | Inheritance, name encoding, metadata structures and evidence discipline. | Full documentary field CSV, upload-relevant tables and explicit applicability limits. |
| B01–B04 existing Bridge source | SysEx transport boundary, sole hardware queue, disk/sample encoding and slice program serialization. | Read-only integration specification; no changes or tests run against Bridge. |

The relevant research directories and project documentation were searched before analysis. Build products, toolchain trees and frozen copies were excluded from repeated reading; repeated lifecycle reports do not provide new MESA wire evidence. H02’s late READBACK_LAB notes supersede H01’s earlier UI limitations in one respect: synthetic PROGPROBE and PROBE both appeared in the same process. They still do not prove linked-zone assignment or physical residency. Recovered capture files and original guest paths are in recovered-captures/recovery-manifest.json; supplement05 reconciles them.

## 1. SCSI commands and transfer framing

### Command descriptor blocks

STATIC A03 and SECONDARY L01 agree on six-byte command families. For SEND/RECEIVE, bytes 2–4 form a **24-bit big-endian byte length**, not MIDI’s 7-bit integer encoding. Byte 5 selects the ordinary or bulk data channel for those commands.

| Command | CDB bytes | Direction / payload | Basis |
|---|---|---|---|
| Normal interface mode | `09 00 00 00 00 00` | No data | A03 `0x10003390`; H01/H02 final MODE; L01 `lakai_setmode` |
| MIDI over SCSI mode | `09 00 01 00 00 00` | No data | L01 `lakai_setmode`; A03 has reference-counted mode construction at `0x10001F50`/`0x10002E30` |
| Bulk mode | `09 00 01 01 00 00` | No data | A03 upload constructor `0x100010E0–0x1000117B`; L01 |
| SEND message | `0C 00 nH nM nL 00` | DATA OUT, n bytes of MIDI/SysEx | A03 constructor `0x10002990`; H01 packets |
| SEND PCM | `0C 00 nH nM nL 80` | DATA OUT, n raw bytes | A03 `0x10001490`; H01 512-byte capture |
| STATUS ordinary | `0D 00 00 00 00 00` | DATA IN, exactly 3 availability bytes | A03 `0x10002B60` with ordinary-channel field |
| STATUS bulk | `0D 00 00 00 00 80` | DATA IN, exactly 3 availability bytes | Same A03 constructor with bulk-channel field; L01 |
| RECEIVE ordinary | `0E 00 nH nM nL 00` | DATA IN, requested n bytes | A03 `0x10002CA0`; H02 seven-byte ACK receive |
| RECEIVE bulk | `0E 00 nH nM nL 80` | DATA IN, requested n raw bytes | Same A03 field; L01 bulk read |

MODE byte 5 has its own construction: A03 `0x10002E30` derives bit 7 from a separate flag. Do not apply a universal “byte 5 always means bulk” rule to all commands.

Examples, recovered/corroborated:

```text
392-byte header SEND:  0C 00 00 01 88 00
393-byte keygroup:     0C 00 00 01 89 00
512-byte PCM SEND:     0C 00 00 02 00 80
32768-byte PCM SEND:   0C 00 00 80 00 80  (static chunk-size consequence)
13-byte function:     0C 00 00 00 0D 00
7-byte reply RECEIVE: 0E 00 00 00 07 00
```

STATIC status decoding at `0x10002C57–0x10002C82` is:

```text
availableBytes = (u8(reply[0]) << 16) | (u8(reply[1]) << 8) | u8(reply[2])
```

This availability value is distinct from the SCSI command’s completion/status byte, ASPI host-adapter status, and Akai REPLY status. Success at one layer does not prove success at the next.

### Ordinary message exchange

A03 `0x10002990` constructs SEND with bulk control determined from its channel flag. `0x10002A60` first executes SEND through `0x100035E0`, then polls STATUS through virtual slot `+0x3C`; it appends RECEIVE data through `+0x40` until the last appended byte is `F7`, or an error/timeout occurs. If STATUS reports zero, it waits using a 250 ms event wait and compares elapsed `clock()` time with the configured timeout. The elapsed conversion divides by 1000; do not copy a CPU-clock timer into Bridge as a wall-clock deadline.

The receive helper bounds accumulated response bytes to `0x8000` (32768), at `0x10002CB7`. This is an implementation buffer bound, not an S2000 protocol maximum. The default object timeout field is initialized to 1000 at `0x10003518`; some callers supply overrides. Neither 1000 nor the 250 ms polling interval is a proven physical transfer deadline.

**DESIGN:** Bridge should assemble complete bounded messages, validate expected message identity and length, preserve partial-receive state, and keep ownership until any pending reply is accounted for. MESA ending its exchange at F7 is not proof that the device’s receive queue has been drained, or that a second message is impossible. Exact unsolicited/repeated response behavior is UNKNOWN.

## 2. Program and keygroup serialization

### Envelope and payload

STATIC A04 `0x10003D10` writes `F0 47 cc op 48`. The model byte `48` is used for this inherited Akai protocol; it is not an INQUIRY identity check. `cc` is the SysEx address, distinct from SCSI target ID and performance MIDI channel.

A04 `0x10003C30` encodes a 14-bit item as low 7 bits, then high 7 bits. A04 `0x10003BA0` emits every raw header byte as low nibble then high nibble. Dispatch tables at `0x10003F2C` and `0x10003F08` select the distinct legacy program/sample and keygroup builders. See [static-data.json](evidence/static-data.json) and [MESASAMPLER excerpts](evidence/MESASAMPLER-excerpts.md).

```text
u14(v) = [v & 0x7F, (v >> 7) & 0x7F]
nibble(b) = [b & 0x0F, (b >> 4) & 0x0F]

PDATA = F0 47 cc 07 48 u14(programIdentifier)
        nibble(header[0]) ... nibble(header[191]) F7       # 392 bytes

KDATA = F0 47 cc 09 48 u14(programIdentifier) keygroupIndex
        nibble(header[0]) ... nibble(header[191]) F7       # 393 bytes

SDATA = F0 47 cc 0B 48 u14(sampleIdentifier)
        nibble(header[0]) ... nibble(header[191]) F7       # 392 bytes
```

There is no checksum or SDS packet number in these recovered header envelopes. Do not add a MIDI Sample Dump checksum to raw SCSI PCM. This is a claim about the examined builders/capture, not every possible Akai transfer method.

Headers are separate objects. A disk file containing `programHeader + keygroupHeader[]` must be split into one PDATA and one KDATA per group; the whole file is not one SEND payload. Disk directory entries, FAT chains and HDA container bytes do not belong on this wire.

### Allocation and identifiers

H01/H02 record New Program PDATA identifier `00 01` (14-bit value **128**) followed by KDATA `7F 01` (value **255**) and keygroup index `00`.

STATIC A04 confirms these are intentional constants:

- `0x10007390` checks the proposed new name against the current program-name list, copies a 192-byte initialization template, and at `0x10007489–0x1000749B` builds operation 07 with identifier `0x80`.
- After receiving operation 16/status 0, callback `0x10007540` passes `0xFF`, group 0 to virtual slot `+0x13C` at `0x10007573–0x1000757A`. The shipped vtable at `0x100578B0` resolves that slot to `0x100075D0`, the keygroup builder.
- MESA also has a program-copy path at `0x1000A040`: copy existing common header, change name, send PDATA 128. ACK callback `0x1000A220` starts KDATA to 255 at group 0 through virtual `+0x154`, resolving to `0x1000A2B0`.
- `0x1000A440` checks each KDATA ACK, increments the source keygroup index, and invokes the same builder with destination 255 until no next source keygroup exists. This supports multiple sequential keygroups in the program-copy path. It is STATIC control-flow evidence, not a captured multi-group physical upload.

DOCUMENTARY D01 says an out-of-range program identifier creates a new program, allocates one common block plus GROUPS dummy keygroups, and requires immediate replacement of their unspecified data. It also explicitly defines 255 as the previously created program for KDATA. D03 establishes only that much of the older system applies to S2000. Therefore **128 is MESA’s confirmed creation token; actual S2000 firmware treatment and resident ordinal remain UNKNOWN**. Never treat 128 as an acknowledged resident slot or use the fixture’s slot 1 as a hardware allocation result.

D01 describes duplicate program names as deleting the prior program first, and duplicate sample names as deleting/replacing the prior sample. MESA’s new-name check is consistent with avoiding that path. A reliably non-destructive v1 upload should reject existing/colliding names, including collisions after 12-character encoding, and revalidate under ownership before the first write. This is DESIGN informed by documentary behavior.

### Header layouts

All offsets below are **decoded byte offsets**, not SysEx offsets. D02 provides 192-byte S3000-family layouts; [documentary-header-fields.csv](documentary-header-fields.csv) preserves its field descriptions and applicability caveat. It is not a hardware-confirmed write allowlist. Do not copy S1000 obsolete field meanings where D02 revises them.

| Program offset | Size | Meaning / basis |
|---|---:|---|
| 0 | 1 | Type 1; MESA embedded template and fixture validation |
| 1 | 2 | Internal first-keygroup pointer; D01/D02, MESA template zero |
| 3 | 12 | Akai-encoded name on wire; MESA converts ASCII template before encoding |
| 15 | 1 | MIDI program number, not resident-list ordinal |
| 16 | 1 | Legacy MIDI channel field; S2000 Multi Mode may change applicability |
| 19,20 | 1 each | Low/high playable note range |
| 42 | 1 | GROUPS, number of keygroups; D02 and B03 both use this offset |
| 43 | 1 | Temporary program number, internal use |
| remainder | — | Parameter/reserved bytes; preserve validated template/profile rather than zero-filling |

| Keygroup offset | Size | Meaning / basis |
|---|---:|---|
| 0 | 1 | Type 2; MESA template |
| 1 | 2 | Internal next-keygroup pointer |
| 3,4 | 1 each | Key range low/high |
| 5 | 2 | Tuning word, cent/fraction then signed semitone; preserve raw bytes unless conversion validated |
| 7 | 1 | Basic filter frequency; documentary layout only here, no parameter-control experiment |
| 34 + 24×z | 12 | Sample name for zone z, z=0..3 |
| 46 + 24×z, 47 + 24×z | 1 each | Velocity low/high |
| 48 + 24×z | 2 | Zone tuning |
| 50..53 + 24×z | 1 each | Level, filter, pan and playback mode |
| 54,55 + 24×z | 1 each | Calculated velocity crossfade factors |
| 56 + 24×z | 2 | Internal sample-header pointer; not the resident sample number |
| 132 + z | 1 | Constant-pitch setting per zone, documentary/Bridge layout |

**Sample linkage is by the 12-byte zone sample name**, supported by D01/D02 and B03. Internal pointers should not be filled with host addresses, disk offsets or current resident numbers. MESA initialization templates have zero pointers; existing Bridge disk export uses `FFFF` for zone references. Their difference is not resolved as a universal upload rule. A validated wire template/profile must decide pointer initialization and which fields firmware normalizes. See U06.

STATIC MESA name conversion uses alphabet `0123456789 ABCDEFGHIJKLMNOPQRSTUVWXYZ#+-.` at `0x10056F60`; space is code 10. It converts exactly 12 characters at `0x10003CC0`. Its search loop considers up to 42 entries while the printable alphabet is 41 plus terminator; malformed/unsupported-name handling should not be copied. DESIGN: accept only the explicit 41 printable characters, pad with code 10, reject unsupported characters and encoded collisions.

## 3. PCM upload path and formats

### MESA path, not Lakai’s explicit packet-request path

STATIC A03 upload constructor `0x100010E0` builds bulk MODE `09 00 01 01 00 00`, assigns vtable `0x10005288`, and provides `0x10001240` as the run method. `0x10001240` first executes MODE, then constructs a fixed 392-byte SDATA SEND `0C 00 00 01 88 00`, receives a response, streams file bytes through raw SEND, and restores normal mode on its successful path. That routine does not construct or transmit ASPACK 0D between the header and raw PCM.

H02’s original-client import corroborates the order: UPLOAD2 seq63 SDATA, seq66 raw 512-byte PCM, seq69 the common function. Complete intervening MODE/STATUS/RECEIVE records are now recovered in C02/C03/C08; supplement05 gives their exact order.

SECONDARY L01 `lakai_put_sample`, lines 1150 onward, instead enters bulk mode, sends ASPACK 0D with sample number, start and `lenBytes/2` encoded as 7-bit words, checks bulk STATUS, delays 100 ms, sends raw blocks, then restores normal mode. Its delay has a TODO, its return value is a TODO, and its block loop ignores the send return value. `putbulkdata` returns requested bytes rather than actual transferred bytes. This reference is **not** a reliable implementation to copy and is not evidence that MESA sends ASPACK in the header-creation path.

D01 describes SDATA creation as priming subsequent sample data and separately allows ACCEPT PACKETS for flexibility. That documentary statement explains the observed implicit path, but S2000 firmware applicability remains a validation question. An existing-sample or resumed-transfer path might require ASPACK; no such variant is specified as enabled here.

### Byte format and chunking

H02 reports an original 256-frame, mono PCM16LE, 44100 Hz WAV probe. MESA’s 512-byte raw DATA OUT was compared in the guest using `FC /B` with the extracted WAV PCM and had no differences. This confirms **that probe’s outgoing client bytes**: two bytes per mono frame, little-endian signed-16 source representation, no nibble conversion, no byte swapping. It does not prove all source-file conversions, all rates or the hardware’s received representation.

STATIC A03 `0x1000141C–0x1000145A` reads mono source bytes in blocks at most `0x8000` (32768), calls the raw sender, and subtracts the returned source-read count. `0x10001490–0x100014D9` places the requested byte count into CDB bytes 2–4, uses control 80, and calls the ASPI executor. There is no per-block Akai checksum or packet sequence in this branch; each raw SEND must complete before the next block.

**DESIGN:** use even-sized blocks at most 32768 for the first MESA-compatible mono profile. For N frames, the expected raw length is exactly `2*N`. CDB length, buffer length and adapter-reported actual bytes must all agree; advance progress only by proven transferred bytes. Odd final bytes, source truncation or uncertain completion must abort. MESA’s block size is a recovered client choice, not a proved hardware limit.

STATIC stereo branch `0x100013A0–0x1000141A` reads up to 65536 source bytes, selects alternating 16-bit words according to its channel field, and sends half the source-read length. A04 `0x10008B82–0x10008B96` changes sample-name suffixes to `-L` / `-R`; `0x10008DF0` handles a second import pass. This supports separate mono-member treatment, not a stereo-interleaved S2000 wire payload. Complete stereo metadata/partner behavior remains UNKNOWN; v1 specification is mono-only until validated.

### Sample header data

| Offset | Size | Meaning / evidence |
|---|---:|---|
| 0 | 1 | Type 3 |
| 1 | 1 | Bandwidth, inherited layout |
| 2 | 1 | Original/root pitch |
| 3 | 12 | Encoded name |
| 15 | 1 | Sample-rate-valid flag, documented `80` |
| 16,17 | 1 each | Internal loop count/active-loop fields |
| 19 | 1 | Playback type |
| 20 | 2 | Raw tuning cent/fraction:semitone |
| 22 | 4 | Absolute wave-memory location, internal/device-owned |
| 26 | 4 | Sample length in sample words/mono frames, LE header representation; historical probe decodes 256 |
| 30 | 4 | Relative playback start |
| 34 | 4 | Relative playback end; boundary convention must be validated for new wire templates |
| 38 + 12×l | 12 | Loop l, l=0..7: point u32, length fractional u16 + integer u32, dwell u16 |
| 136 | 2 | Internal stereo-partner block address |
| 138 | 2 | Sample rate in Hz |

D01/D02 document the layout; B04 disk encoder corroborates little-endian field storage but is not independent wire proof. The complete historical192-byte sample header is now recovered: length256, end255, rate44100, playback3 and stereo partner0; see supplement05. Treat firmware-owned addresses, loop rounding and playback-end rules separately from the now-established PCM byte count. H06’s uncertainty about **download** RSPACK length units is not resolved by this upload finding.

## 4. Discovery and memory management

H04 and H02 already established ASPI support-info/import behavior, adapter scan corrections, and MESA’s use of SCSI peripheral device type 3 (processor). H02 cites A03 constructor `0x100038D1` and discovery `0x10001B10`. Synthetic INQUIRY and GDEV responses had to agree on type 3 for discovery to proceed. This was not repeated.

SCSI adapter number/target ID/LUN identify the bus endpoint. SysEx `cc` is a separate address. The default lab target HA0/ID2 and its reply name are fixture choices, not the physical device’s identity. Bridge should bind the approved endpoint to actual INQUIRY identity and current session generation, rather than searching all IDs during SEND. The established project’s first-INQUIRY helper uses `12 00 00 00 24 00`, expecting 36 bytes (H07); no new physical identity is claimed.

DOCUMENTARY RSTAT request is `F0 47 cc 00 48 F7`; STAT response is 21 bytes:

| Wire offsets | Field |
|---|---|
| 0..4 | `F0 47 cc 01 48` |
| 5,6 | Minor and major firmware version bytes |
| 7,8 | Maximum header blocks, low-first u14 |
| 9,10 | Free header blocks, low-first u14 |
| 11..14 | Maximum sample words, low-first u28 |
| 15..18 | Free sample words, low-first u28 |
| 19 | Current exclusive channel |
| 20 | `F7` |

Do not substitute the synthetic fixture’s capacities or S1000 published maximum memory for live S2000 capacity. H02’s fixture was intentionally version 2.0, 1024/1022 blocks, 1048576/1048560 words; those are invented values.

**DESIGN estimate:** for K new keygroups and S new mono samples, require at least `1 + K + S` free header blocks and `sum(sampleFrames)` free sample words, plus a separately validated firmware overhead/reserve policy. Dummy keygroups allocated by PDATA are included in K; do not count them a second time merely because KDATA replaces them. This estimate follows documentary allocation and is not a proved S2000 allocator formula. Refresh status/lists inside transaction ownership; front-panel or another client can invalidate earlier capacity/name checks.

Program/sample list requests are 02/04 and replies 03/05. List payload has a low-first u14 count at offsets 5–6 followed by count×12 encoded names starting at 7, ending F7. List position is an ordinal, distinct from MIDI program number and the creation token. Existing readback readers should be reused after identity validation.

## 5. Handshakes, errors and post-transfer command

### Akai reply

DOCUMENTARY D01 and STATIC A04 program/keygroup callbacks expect:

```text
F0 47 cc 16 48 status F7
status 00 = OK; 01 = documented error
```

For example A04 `0x1000755C–0x10007569`, `0x10007740–0x10007751`, `0x1000A23C–0x1000A249`, and `0x1000A466–0x1000A477` require decoded operation 16 and status 0 before continuing. A04’s common callback `0x10006570` performs the same check. Error 01 alone does not identify whether the cause is memory, name, index or unsupported behavior. Preserve raw replies; never translate all such errors into “duplicate name”.

### Sample header response path

A03 `0x100012AF–0x1000136B` requires the response to begin F0 and examines byte 3. Values 7C, 7D and 7E receive special handling: 7C follows a bounded wait/poll/read loop, 7D returns `0x3F2`, and 7E returns `0x3F1`. These opcode values are consistent with standard sample-dump WAIT/CANCEL/NAK (interpretation); the branch itself is a static observation. Other response opcodes pass on to streaming if transport status is zero. **This lower-level branch does not visibly validate Akai REPLY status 0 before sending PCM.** Bridge should add explicit operation/status validation, pending validation of any alternative legitimate readiness message. Do not inherit MESA’s permissive branch as reliable error handling.

The wait path uses a 100-count loop and 250 ms waits, checks for a six-byte message and reads it. That does not establish what the physical sampler sends, or authorize Bridge to issue retries after an ambiguous write. The raw guest records around the header ACK are needed to confirm readiness-channel behavior.

### Adapter/SCSI completion

A03 `0x100035E0` ORs ASPI flags with 40 (event notification), submits through imported `SendASPI32Command` ordinal 2, waits if SRB status is pending, maps wait timeout to local error 2 and wait failure to 3, host-adapter status to 4, and nonzero target status to 5. STATUS helper has an exception allowing host status `13` (`0x10002C36`), while the raw executor does not. This is MESA’s implementation behavior, not a recommendation to ignore adapter anomalies.

The inspected raw SEND wrapper does not expose measured transfer residuals. Therefore ASPI’s nominal success cannot settle the existing gateway’s actual-byte-reporting question. Bridge’s transport must report actual bytes or explicitly declare that this cannot be established. Unknown actual completion is not an exact transfer.

No robust automatic write retry/resume/rollback algorithm was established in the examined upload branches. The recovery specification consequently records uncertainty and requires reconciliation rather than blindly replaying a header or PCM block.

### Common post-object function

H01/H02 record exactly the same 13-byte message after sample PCM and after program/keygroup creation:

```text
F0 47 00 34 48 01 00 00 00 00 00 00 F7
```

Decoded as the extended miscellaneous envelope: item/function index 1, selector/bank 0, offset 0, byte count 0, no payload. STATIC A04 `0x10006480` constructs zero-payload function calls and its callback `0x10006570` requires REPLY16/status0. H03 already audited this; the bytes/callback were reused, not re-experimented.

Calling it “commit”, “allocation”, “link samples”, “sort programs”, or “resident verification” is unsupported. D02 mentions the named BTSORT function after renumbering, but does not bind the observed numeric index 1 to that name in the retained material. This command is specified neutrally as **post-object function 1**. Its exact firmware effect and necessity are U03.

H02 records subsequent list/header requests and eventual normal-mode restoration in the synthetic lab. They establish MESA client progression when the fixture supplies acceptable responses. They do not prove that the just-created program was selected, linked to PROBE or playable.

## 6. Verification and Bridge consequence

Existing metadata readback commands support proving that named objects and decoded program/keygroup data are visible, once a real target responds. They cannot alone prove complete PCM residency. Exact physical PCM readback, verified transfer completion and sample linkage are separate acceptance criteria.

Bridge’s current B01 transport exchanges complete SysEx only; B02 serializes hardware work on one queue. B03 already makes a disk-oriented program body with GROUPS and zone names, and B04 already creates sample bytes/PCM. These are useful preparation inputs, but do not add bulk mode, residual reporting or sampler recovery to the backend. The implementation contract in [03-bridge-specification.md](03-bridge-specification.md) extends that transaction boundary conceptually without modifying source.

| Requested question | Status at end of this pass |
|---|---|
| SCSI commands/sequences | Client-side framing answered; physical phase/disconnect behavior and exact retained interleaving partial |
| Program/keygroup serialization | Envelopes and key upload fields answered; full firmware-valid defaults/normalization partial |
| PCM protocol/format | Mono probe bytes and static client chunking answered; physical reception, large blocks and variant conversions partial |
| Discovery/memory | Existing discovery and documentary capacity model reused; actual firmware capacity/allocation partial |
| ACK/error recovery | Client checks answered; ambiguous-write recovery unresolved |
| Complete upload → verified residency | Proposed composed sequence documented; no physical end-to-end success established |

The remaining work is enumerated with specific evidence requirements in [04-unresolved-questions.md](04-unresolved-questions.md). No requirement is silently converted from UNKNOWN to CONFIRMED to make the uploader appear complete.
