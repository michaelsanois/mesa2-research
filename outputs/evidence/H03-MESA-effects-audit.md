# Original MESA effects read path

Read-only disassembly of original MESASAMPLER.dll extracted from the supplied installer. Binary SHA256: `4ff7d6457038c2f9035bb734ab046f8488ebb30a992b74a3c48a0a5fde4785b0`.

The function at 0x10009690 allocates 0x1c00 bytes and fills the buffer with 0xff, then issues operation 0x2d, index0/selector0/offset0/length0x20 at 0x100096b9–0x100096d8. This matches the actual guest sequence46 packet.

The callback at 0x10009770 checks returned function byte equals 0x2e at 0x1000979c. A different reply is routed to error 0x3eb at 0x10009914. Therefore a generic unsupported-operation ACK is not established as a graceful way to skip effects; this path explicitly rejects a non-0x2e result.

On a header reply the callback requests selector1/length0x200, then selector2/length0x80. It increments the effect index through49 at 0x10009869–0x10009889, for50 effect entries. These are inferred request stages from static code, not observed hardware traffic.

This establishes that adding one 32-byte reply alone will not complete refresh. A coherent effects model is needed, including assignments and50 effect entries. Internal field semantics remain unverified. No zero-filled FX fixtures or patched MESA executable were installed. No physical hardware accessed.

## Bounded synthetic compatibility experiment
Implemented exact full-length selector0/1/2 requests only, 50 entries maximum. Name locations follow original MESA name conversion calls (header offset3; entry offsets0 and96). Assignment fixture0xff and unknown fields0 are invented lab values, not source-proven hardware defaults. Explicitly supersedes the earlier decision not to try a blank fixture: this experiment tests client acceptance only.

Native AddressSanitizer/UndefinedBehaviorSanitizer tests passed for 32/512/128 byte replies, all50 entries, invalid index50 and wrong lengths, alongside existing header checks. Windows build succeeded. Guest DLL installation FC/B no differences. Original captures preserved as C:\cap_fx0. New refresh initiated.
DLL SHA2567bfaf61d142ec0a22ae9090a9bcbac9d59a96124a4462122835684d22fc141ff. ISO SHA25667312a41ccbb4d70e0a105aa3abd6e50f092f7b8ae0b540a1dab960884e66477.

## Follow-up refresh/list experiment

REFRESH3 added exact bank-1/index-0x49 miscellaneous read handling. Installed via CD copy and FC /B confirmed identical. MESA startup proceeded to a six-byte request (seq37, tick38184112), then remained UI-disabled; ended the lab process through Windows Close Program. This is not a complete refresh. Trace archived as C:\cap_fx2; prior experiment in C:\cap_fx1.

Added bounded legacy RPLIST/PLIST and RSLIST/SLIST handling according to the retranscribed Akai document https://lakai.sourceforge.net/docs/s1000_sysex.html (lines73–92): two-byte 7-bit count, followed by one12-byte Akai-encoded SYNTH LAB name. Objects are synthetic. Unknown/malformed requests remain rejected by reply builder. Native ASAN/UBSAN regression tests pass and Windows DLL cross-build succeeds. Installed MESA_LIST_LAB via CD with FC /B no differences. Actual MESA acceptance remains under test.

SHA256 mesa-lab-fix/WNASPI32.dll: `62684cffe893af582679550189666aee77adc2bc08a3d91925f42be20a12c0df`

SHA256 /private/tmp/MESA_LIST_LAB.iso: `1af8fe65a72dee640441b898d6535f9b5a90c9217b3ef635e6ac2957c1b69e50`

## Actual list-build result and missing-object handling

MESA displayed SYNTH LAB in its program selector, but keygroups remained0 and a timeout appeared. Captured final request (seq38/tick38644669) was nine bytes: F0 47 00 0A 48 01 00 F7 00. The extra final zero is outside SysEx; sample index1 is beyond the single synthetic index0. Program request seq22 was F0 47 00 06 48 00 00 F7. No claim that program/keygroup fixture decoding is complete.

BOUNDS_LAB handles only the observed zero-after-EOX RSDATA padding, and emits the documented Akai REPLY/error1 for out-of-range legacy object reads. It does not invent a second sample. ASAN/UBSAN tests prove padded index0 reply, index1 error, bad pad rejection; cross-build passes. Installed with FC /B no differences. Capture from list experiment archived C:\cap_list.

SHA256 mesa-lab-fix/WNASPI32.dll: `3c14107a8f170aa44c84872ae1de2d8f0d9244f04898d750cb7e5d8eb490a36a`

SHA256 /private/tmp/MESA_BOUNDS_LAB.iso: `cbe09ab704b253b214b457d5a2cb8db157c0186d25b002aa8efb811ee897b833`

BOUNDS_LAB actual MESA observation: program selector SYNTH LAB and keygroup count1 now visible, unlike prior count0. This is a genuine UI observation with synthetic fixtures; full refresh still not established.

## First actual MESA sample import capture
File > Import D:\PROBE.WAV (mono PCM16,44100Hz,256frames) issued seq354/tick39693889: CDB 0C0000018800,392-byte DATA OUT. DEBUG shows F0 47 00 0B 48 01 00 followed by nibbled192-byte sample header. Length field decodes256frames. Import timed out because no SDATA write reply existed. Packet preserved as guest C:\upload.bin; authoritative trace/capture remain C:\MESA_CAPTURE. This is actual original MESA generated traffic against a synthetic adapter, not physical-device evidence.

Added bounded index1 SDATA handling for this256-frame type3 probe: validate nibbles/length, store complete header, then synthetic ACK; subsequent RSDATA returns stored bytes. No PCM acknowledgement or success is invented. Native ASAN/UBSAN tests cover store/readback, malformed nibbles, truncated write, unsupported size. Windows cross-build passes. New DLL not yet installed.
mesa-lab-fix/WNASPI32.dll SHA256 a1be6b4c1c13540f4c497c3d6b527a0031f4983ce8c483b19c2367f8d755c14c
/private/tmp/MESA_UPLOAD2.iso SHA256 f55ed9d356d8b886ced49b52230a4b895c765d96ab436ba363fc73aef40307a5

## Verified original MESA PCM DATA OUT — 7 October 2026

MESA_UPLOAD2 installed into the guest; FC /B confirmed DLL copy identical. Prior capture archived as C:\cap_import1. Original MESA importing PROBE.WAV generated:

- seq63/tick44310669: 392-byte sample-header DATA OUT, CDB `0C0000018800`.
- seq66/tick44310686: 512-byte raw PCM DATA OUT, CDB `0C0000020080`.
- seq69/tick44310714: 13-byte SysEx `F04700344801000000000000F7`, CDB `0C0000000D00`; adapter has no reply and import times out here.

Guest binary-copy verification: `copy /b /y c:\mesa_capture\*66.bin c:\sentpcm.bin`, then `fc /b c:\wavpcm.bin c:\sentpcm.bin` reports no differences. DIR confirms both files512 bytes. WAVPCM.BIN was extracted from the44-byte-header monoPCM16LE44100Hz256-frame probe WAV via DEBUG. Thus this probe's transmitted PCM is byte-identical to the source PCM, with no nibble conversion or byte swapping.

Important evidence-handling correction: ordinary DOS COPY copied binary captures in text mode: the PCM copy became385bytes, and the13-byte request copy became14bytes. These were copy artifacts, NOT MESA transfer defects. Recopying with /B restores exact512/13byte lengths. Original captures were not altered.

Synthetic adapter replies are not physical S2000 evidence. Complete sample import, readback, program upload, mode sequence and final acknowledgement remain unverified. The last34 request must be traced before adding a response; no speculative success ACK added.

## Post-PCM client callback audit
Original MESASAMPLER.dll10006480 constructs zero-payload miscellaneous34/bank0 requests.10006570 callback parses reply, requires operation16 and status0, then processes function-specific result. This establishes expected client ACK shape, not function1 physical semantics. Added exact captured13-byte function1 synthetic ACK only after a bounded512-byte PCM payload has been stored following valid256-frame sample header. Header replacement invalidates PCM. No generalized hardware implementation.
Tests: absent/short PCM cannot acknowledge, all512 bytes preserved, wrong function and truncated request rejected, header replacement invalidates prior payload. Native ASAN/UBSAN passes; Windows build passes; installed in guest with FC /B no differences. Previous upload capture archived C:\cap_import2. Live synthetic acceptance test pending.
mesa-lab-fix/WNASPI32.dll SHA256 7e38b19f32285618c8cb59a79a992111ed29e1e1b15c724bbca9b30f92e756bf
/private/tmp/MESA_POSTPCM.iso SHA256 4bd6c902b82c27ffdeb0eeca50b08ae20bc1b3fc1289c502ef9844ba9afbaad1

## Bounded program-write lab support
Added exact captured PDATA07 identifier00/01,192-byte nibble payload handler. Validates entire envelope, EOX, every nibble and program type1 before storing. Only this bounded slot receives synthetic REPLY16/status0; matching RPDATA returns stored bytes. No list/allocation semantics or keygroup creation are invented. Lakai encodes00/01 as128; meaning of this MESA creation target remains unresolved.
Native ASAN/UBSAN regression tests pass: truncated payload, invalid nibble/type/identifier/EOX rejected; all192 bytes round-trip exactly. Windows DLL cross-build and ISO generation succeed. Guest installation pending.
mesa-lab-fix/WNASPI32.dll SHA256 f1bec37fb697bf2924d98677c7e65778fbf9a8ce558588723dde2f286d89468c
/private/tmp/MESA_PROGRAM_LAB.iso SHA256 e3687ff7aeb1548d11e87777ad5a3a21474e20795247d7db7667c4c985d2ae9d
Guest installation: closed old MESA normally, archived previous capture as C:\cap_postpcm, copied DLL from MESA_PROGRAM_LAB.iso /B and FC /B reported no differences. Relaunched original MESA; next transaction pending observation.

## FINAL_LAB result

Original MESA progressed beyond exact function1 into list and header reads and finished with seq116/tick49082228 MODE090000000000. Seq81/tick49081234 is32byte PLIST reply; first32bytes inspected confirm two names, SYNTH LAB and PROGPROBE. Scratch wildcard copy also matched seq112, so only original seq81/first32bytes establish the list evidence. Seq84/tick49081324 receives392bytes; seq114/tick49081864 receives393bytes; later seq103 request inspected is program0. Consequently full selected-new-program UI readback and sample assignment remain unverified. Menu/selector interactions currently do not respond although DOS console remains usable; no claim of complete original-client workflow. Captures preserved, no reset/kill or production changes. Consolidated findings in MESA-UPLOAD-FINDINGS.md.
