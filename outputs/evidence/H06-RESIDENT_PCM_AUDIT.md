# Resident PCM — pre-implementation audit, 3 October 2026

## Verified baseline

The user reports deployed gateway stability and identifies piscsi.service start-rate limiting as the previous failure: StartLimitBurst 5 / interval 10 seconds changed to 60 / 30 seconds. Local gateway-live-verification.jsonl independently contains 52 passing records: health, 50 TUR, status. No new deployment or hardware operation was performed during this audit. Existing gateway lifecycle remains unchanged.

## Existing Bridge integration

Project: ${LOCAL_HOME}/Documents/Codex/2026-09-07/h/outputs/Akai-S2000-Bridge

- src/S2000/S2000SampleReader.h: resident list request 04/reply05, number-based header request 2B/reply2C. Header reply is 397 wire bytes containing 192 bytes decoded from low/high nibbles. Verifies address, index, name, selector, offset and count. Already stores raw header, start/end/loopAt and raw length/loop-length fields.
- Header request: F0 47 cc 2B 48 index-low7 index-high7 00 00 00 40 01 F7. Header is metadata, never PCM.
- src/S2000EditorSelection.h: shared program/keygroup/zone/sample selection; zone names matched to a unique current resident-list number. Identity and audio availability separate. Existing header-only branch explicitly reports waveform not transferred. Attach audio to the existing reference; do not manufacture another selection model.
- src/Library/AkaiDiskMetadata.h: known disk metadata offsets: root2, name3..14, sample-rate-valid15, playback19, tuning20/21, sample length26, start30/end34, eight loop structures at38+12*n, sample rate138. Disk-specific validation must not be misrepresented as proof of resident bulk encoding.
- src/Library/AkaiSampleDecoder.h: disk sample decoder uses mono signed16 little-endian; cancellation supported. This is evidence for disk data, not independent proof of raw SCSI encoding.
- src/S2000LocalSample.h and S2000LocalAudition: existing waveform/source ownership and editor bounds. Reuse a decoded immutable audio source while retaining resident origin and hardware header.
- AkaiTransport, registry and AkaiHardwareRequestQueue: transport-neutral asynchronous boundary and single hardware worker. New bulk capability belongs at this boundary, not a Pi HTTP dependency inside selection/protocol code.
- No complete resident PCM path exists in these components.

## Reference protocol evidence

Bundled source: ${LOCAL_HOME}/Documents/Codex/2026-09-06/you-are-building-a-native-macos/work/protocol-verification/lakai-0.1.orig/lakai.c

lakai_setmode (173 onward), lakai_get_sample (887 onward), sendrecv_scsimidi2 (1588 onward), getbulkdata (1699 onward) implement:

1. Mode CDB 09 00 01 01 00 00 (SCSI bulk).
2. Send Akai RSPACK function0C through SCSI SEND0C. SysEx has 14-bit resident sample number, four low-first 7-bit offset bytes, four low-first 7-bit count bytes, interval01 00, F7.
3. Poll SCSI STATUS CDB 0D 00 00 00 00 80; returned length is three bytes, most significant first.
4. Receive bulk using 0E 00 00 length-high length-low 80, repeated in reference chunks of at most65534 bytes.
5. Restore normal interface mode via 09 00 00 00 00 00.

This supports a separate bulk-mode path alongside SysEx metadata (option C). It does not support feeding PCM through the current akai_exchange parser, which forces MIDI mode, uses control00, bounds replies65534 and returns hexadecimal/decimal JSON.

Unresolved evidence conflicts must be settled before enabling retrieval:
- lakai_get_sample labels RSPACK count as samples, while lakbak passes header word-count multiplied by2 (bytes). Offset/count units cannot safely be guessed.
- getbulkdata returns requested bytes and explicitly marks actual transfer reporting TODO. Do not inherit that defect.
- SCSI raw signedness/byte order require authoritative evidence or a known sample capture; existing disk decoder alone is insufficient.
- Stereo should not be assumed interleaved. Legacy Akai documentation describes separately named mono members; verify S2000 behavior and preserve independent references.
- The bulk reference shows SCSI status/receive rather than MIDI packet checksums, but this is not enough to assert all handshake behavior without adapter verification.

Documentation checked: https://lakai.sourceforge.net/docs/s1000_sysex.html and https://lakai.sourceforge.net/docs/s2000_sysex.html (transcriptions include explicit caveats).

## Proposed binary API and integration

Provisional POST /akai-sample/read with MIDI address, resident sample number and expected header/name identity. Gateway revalidates identity and header under the SAME transaction ownership, reads full sample into a bounded temporary binary file, restores interface/PiSCSI, then returns application/octet-stream only if all stages succeed. Failures, including restoration failure, remain structured JSON. No PCM arrays/base64, no hardware writes/retries.

Metadata remains available through the existing validated header reader. Response must identify sample/frame count, byte format and header identity so Bridge cannot attach stale audio. Keep full SCSI transfer ownership; never release lock between bulk blocks. Separate bounded bulk deadline is necessary: current3-second operation budget is for small SysEx and must remain unchanged for existing routes. Cancellation between blocks must still run restoration. HTTP download progress must not pretend to measure SCSI progress; gateway progress needs explicit support if staging before response.

Bridge queues retrieval on existing worker, validates full length/format before publication, decodes off audio/message threads, then attaches immutable PCM to the existing resident reference. Cache key must include device session, resident identity and generation; invalidate on reconnect/list replacement/known PCM changes. An explicit refresh is necessary for undetectable front-panel PCM changes. Do not route metadata-only edits to PCM upload.

## Blocking adapter detail

The user supplied deployed scsiexec 0.1.0 help: -F/--binary-output writes DATA IN, -f is DATA OUT, -n forces length, -b caps inferred input, -t bounds command timeout. No deployed source was found. Its --cdb-meta extension may be a custom build; upstream command flags cannot be assumed. Binary output capability is confirmed by that help. Source/revision is still requested to verify actual transferred-byte reporting and whether binary files include padding on short transfers. No SSH attempts were made.

No bulk implementation, decoder assumptions, deployment or new live tests are claimed. Resume with adapter inspection, resolve wire-unit/encoding evidence, then implement and test the complete path. Real waveform retrieval remains unverified until real S2000 audio is displayed.

## Independent implementation completed

S2000SampleReader::Header now exposes header sampleFrames, optional rate/root, raw tuning bytes and all eight loop records (including fractional lengths and dwell). Metadata is refreshed both on full header receive and parameter updates. No resident PCM format is inferred; absent rate-valid flag keeps rate unknown. Added metadata tests in tests/S2000SampleReaderTests.cpp. These additions do not change gateway commands or enable bulk transfer.
