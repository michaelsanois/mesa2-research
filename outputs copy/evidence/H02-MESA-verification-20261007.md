# MESA isolated lab verification — 7 October 2026

## Result
MESA now passes synthetic device discovery and emits Akai requests through the research ASPI adapter. Full synthetic sampler handshake remains incomplete. No physical sampler, Pi, gateway or Bridge was accessed or modified.

## Corrections and evidence
- The original research installer falsely reported success after a read-only DLL copy failed. Installation was performed directly, clearing the DLL attribute, copying, and checking FC /B: no differences encountered.
- Host adapter scan bound corrected to eight.
- Absent IDs now return SS_NO_DEVICE (0x82) with host status zero and cleared input buffers, rather than successful SRB plus selection-timeout host status. SCSIPlug maps nonzero host status to error4, disrupting discovery.
- Completion events are signalled for success, absence and error.
- MESA SCSIPlug requests SCSI peripheral type3 (processor): constructor at 0x100038d1 pushes3, discovery at 0x10001b10 compares inquiry type. Synthetic target2 formerly reported type0 (disk); corrected both INQUIRY and GDEV to type3.
- Updated ASPIProbe /tests passed inside Windows98: absent-ID status, cleared buffer, target2 inquiry/type, oversized request rejection, and completion events for success/absence/error.

## Actual MESA-origin capture
Guest TRACE.TXT records MESA.EXE target2 SCSI 0C DATA OUT, 8 bytes, followed by repeated 0D DATA IN, 3 bytes. Sequence22 output file DATA0000022.BIN has size8. Its DOS short alias DATA0~14.BIN was inspected with DEBUG (read-only dump), yielding:
```
F0 47 00 0A 48 00 00 F7
```
The unknown DATA IN shim currently returns synthetic zeros. No Akai response is queued, so MESA reports "something has timed out". This is progress beyond discovery, not a completed handshake or real-hardware validation. Original requests can now be captured; reply emulation requires source-grounded investigation before further changes.

## Isolation limits
No physical SCSI or USB passthrough was used. Shared directory is empty. UTM currently displays Shared Network (ne2k_isa), so network isolation is not yet configured as originally requested; no network/Pi access was performed during this verification.

## Changed research files
fake_aspi.c, aspi_probe.c; rebuilt WNASPI32.dll and ASPIProbe.exe; MESA_PROCESSOR_FIX.iso installed in guest. Bridge and production gateway unchanged.

## Artifact hashes
- WNASPI32.dll: SHA256 `0519c5d4c6635ef2ed64c0e131a8851c317e7b793fce9be3d637c821ad2cc847`
- ASPIProbe.exe: SHA256 `92f93ee40bacf9b25b254ee929d0951470c5ab0dbed4130a30c1d5870f6496a2`
- MESA_PROCESSOR_FIX.iso: SHA256 `70767f7a60f353fe6908782dd2d258011a008c636098b9dd217be712890b88c5`

## Program-header fixture follow-up
Implemented a strictly synthetic index-zero legacy RPDATA (06) / PDATA (07) reply in fake_aspi.c, alongside the existing sample-header fixture. Both contain 192 nibble-encoded bytes in a 392-byte legacy envelope. Program fixture explicitly identifies one keygroup; it is not a real resident program. Corrected fixture Akai name encoding to SYNTH LAB. Added a program-reply regression check in aspi_probe.c.

DLL and probe compiled successfully. Mounted MESA_PROGRAM_REPLY.iso in the running Win98 guest. Closed MESA, cleared destination read-only attributes, copied both binaries, and FC /B confirmed DLL byte identity. ASPIProbe /tests displayed PASS in the guest (includes added program-header check although dialog wording is unchanged). Restarted MESA. UI still displays No Selection; complete synthetic sampler discovery has NOT been proven. Trace now exceeds Notepad capacity and was opened read-only in WordPad; latest observed entries reached sequence 245. These entries do not alone prove acceptance of the program fixture. Remaining investigation: inspect the current session's full SEND/RECEIVE sequence and next unhandled request, rather than treating UI startup as successful discovery.

No Bridge, production gateway, Pi, SSH or physical sampler access.

## Startup ACK and status follow-up
MESA startup SEND sequence28 contains exactly F0 47 00 34 48 0B 00 01 00 00 01 00 05 00 F7. Added an exact-packet-only synthetic command ACK (F0 47 00 16 48 00 F7). Guest FC /B confirmed installed DLL identity; regression PASS observed. Subsequent MESA sequence30 receive payload was inspected using DEBUG and contains precisely that seven-byte ACK. MESA then emitted sequence31: F0 47 00 00 48 F7, the documented RSTAT request. Thus the startup ACK has been consumed and the handshake advances; full sampler availability still unproven.

Added exact channel0 RSTAT synthetic STAT response with the documented 21-byte layout (version, blocks/free blocks, words/free words, exclusive channel). Invented lab capacities: version2.0,1024blocks/1022free,1048576words/1048560free. Source layout: https://lakai.sourceforge.net/docs/s1000_sysex.html lines60–71. This is not captured physical sampler data.
Built DLL/probe and MESA_STATUS_REPLY.iso. Guest DLL copy was verified FC /B no differences. Updated probe run directly from D: displayed PASS in Win98. MESA restarted for next handshake check.
- WNASPI32.dll SHA256: 0c53f1da6e427708dcf8c82e50274bab1fd6e7016426b455f010a1dbc7d0f8f2
- ASPIProbe.exe SHA256: a2301d479a3fe99bfbc2ebb0ca8790ba4dacc945ba9121b6a0a4c01cf4bdeff0
- MESA_STATUS_REPLY.iso SHA256: 2844025a26e1bd291707d9e2f8e9773b37fedd083ee9573d7b95db6adee0e915

## Keygroup follow-up
After STAT fixture installation, MESA's next SEND sequence34 (tick33473229) is F0 47 00 08 48 00 00 00 F7: legacy RKDATA program0/keygroup0. This advances beyond RSTAT. Added an exact index-zero synthetic KDATA reply (393bytes:8byteenvelope+192nibbleencodedheader+F7); ID2,range24–127,filter99,amp sustain99,zone1 SYNTH LAB velocity0–127,otherzonesblank. Layout sourced from Akai documentation reproduced by Lakai, keygroup common and24bytezone structures. Reply buffer increased from392 to393bytes.
Added focused keygroup reply regression. Built MESA_KEYGROUP_REPLY.iso. Guest DLL installation FC /B showed no differences; updated probe from D: displayed PASS. MESA restarted with this fixture; next request/discovery pending inspection. No hardware or Bridge changes.
- WNASPI32.dll SHA256: 0707018513d6a9f4b2d5021157d21174cfad9273eeba322b7288e28bd6a4e43a
- ASPIProbe.exe SHA256: 8959d04a0e2f7760e055ae2134871afcceea09425435294bcdf7c0202b5884c5
- MESA_KEYGROUP_REPLY.iso SHA256: c219c35aab9b301f2c9dac5a599145b619507f5fdc7f71584595a0dce114c9d1

## Direct MESA UI verification and refresh failure
7 October continuation: MESA visibly displays Keygroups=1 after the KDATA fixture. SEND sequence37 (tick34144474) has requested/payload length2; the first two bytes of DATA0000037.BIN inspected with DEBUG are C0 00, ordinary channel0 MIDI program change0 transported through SCSI0C. Bytes displayed after those two bytes are DEBUG memory beyond the file, not captured payload. This is not an unhandled Akai SysEx request. No response fixture was added for it.

Opened MESA Sampler Memory via its existing UI. It displays total programs0 and synthetic free memory99%. Sequence40 is RSTAT F0 47 00 00 48 F7. The UI later updates its displayed capacity. Thus synthetic discovery/status processing advances, but program enumeration is NOT complete.

Used the visible Sampler > Refresh from Sampler command. MESA showed Receiving Sampler data, issued further SEND records through sequence69 (tick34976496), then displayed an invalid page fault in MFC42.DLL at0167:5f4039e4. EAX00c90f9e, EBX0079136c, ECX0066f4b4, EDX00000000, ESP0066f474, EBP0066f544, ESI0066f4b4, EDI00000000. Instruction bytes83 78 f4 00 0f 8c 99 81 05 00 89 06 83 c0 f4 50. No root cause is established yet. Final sequence69 payload begins C0 00; its actual length must be read from its trace record before interpreting any further DEBUG bytes. Individual LOG files are no longer generated by current logging source; TRACE.TXT is authoritative. Attempts to open individual LOG0000037.TXT were rejected without creating a file.

Captured trace remains in guest C:\MESA_CAPTURE\TRACE.TXT, filtered SEND records C:\send.txt. No upload or PCM capture was completed, and no real-device protocol success is claimed. Bridge/Pi/production gateway remain unchanged. Next investigation must correlate full refresh records and disassemble the MFC fault/caller; do not keep retrying refresh or fabricate additional responses to make the list look populated.

## Refresh packet correlation and staged fix
Current failing session's sequence45 (tick34973959), SCSI0C DATA OUT requested13/payload13, is exactly `F0 47 00 33 48 14 00 01 00 00 01 00 F7`. The adapter had no response for this S3RMDATA request. Sequence43 file belongs to older tick29362432, a 3-byte STATUS response; prior interpretation as a current refresh SEND was incorrect. Sequence69 is exactly a two-byte MIDI program change, not a longer packet.

Prepared changes in this chat workspace `mesa-lab-fix/fake_aspi.c`, leaving original lab source unchanged: exact captured bank1/index20 request receives a 15-byte synthetic S3MDATA response containing explicitly invented zero; program PLAYLO/PLAYHI corrected from invalid zero to24/127, priority normal, stereo level99, individual outputOFF. The index20 meaning is not established; this fixture is a lab hypothesis, not verified hardware semantics. Envelope source: https://lakai.sourceforge.net/docs/s2800_sysex.html, miscellaneous bytes sections.

Native test exercises actual extracted queue_header_reply implementation: exact request, echoed header/function/data/EOX, unknown index and truncated request rejection, decoded program range and keygroup length. PASS. Windows DLL builds. SHA256 `14ac8411018398b8d3237957f3fdd40a7f2149f989ce08b98e0de74f547c10f6`. ISO SHA256 `4a1c8fe3639a958c61a45764ef0ddab3d62b316e3e45da82adf7406136820e94`.

Closed crashed MESA. Backed up264 capture files to guest C:\pre_fix and renamed original capture directory C:\cap_old to prevent stale-file confusion. Installed new DLL from MESA_REFRESH_FIX.iso; FC/B no differences. Relaunched MESA for UI verification. No Bridge/Pi/gateway changes.

## Actual MESA retest result
Fresh process started at tick36664xxx. Startup reaches Keygroups1. Sampler > Refresh from Sampler now emits sequence43 at tick36734834, thirteen-byte miscellaneous read; then sequence46 at36734859. The latter is exactly `F0 47 00 2D 48 00 00 00 00 00 20 00 F7` (inspected13bytes only). This is an FX/Reverb header read: index0, selector0, offset0, length32. It has no reply fixture and MESA displays "something has timed out". Thus the new miscellaneous reply advances the request chain to an additional unsupported operation. It does not yet prove the original MFC crash eliminated or a usable memory list.

Do not blindly provide a zero-filled FX header: the available extension manual specifies the envelope but does not provide this header's internal structure. Further safe work needs a source-grounded FX fixture or a confirmed way to disable optional effect retrieval in the MESA lab. No upload/PCM trace captured. Guest is left at DOS DEBUG of the new13byte request, with MESA running behind it after timeout dismissal.

## Original MESA effects-code audit
Read-only original MESASAMPLER.dll disassembly confirms the observed32byte FX read and a subsequent512byte assignment read plus50x128byte effects reads. Non0x2e replies branch to an error, so an unsupported ACK is not a verified skip mechanism. See mesa-lab-fix/MESA-effects-audit.md for addresses and binary hash. No further guest changes; memory enumeration/upload remain incomplete.

## BOUNDS_LAB refresh and import retest
Installed bounded legacy list/error handling; see mesa-lab-fix/MESA-effects-audit.md for exact current DLL/ISO hashes and tests. MESA shows SYNTH LAB and Keygroups1. Explicit Sampler > Refresh progressed to sequence344/tick39321744 with thirteen-byte SEND records and returned to responsive menus. No timeout or MFC crash observed in this refresh. File > Import opens the actual Import file to Sampler dialog. This establishes synthetic client progress only, not physical protocol correctness or full FX semantics.

Created separate probe media MESA_PCM_PROBE.iso containing PROBE.WAV: mono PCM16 little-endian,44100Hz,256 frames,512 PCM bytes. Mounted through UTM and requested File > Import of D:\PROBE.WAV. Capture result under investigation. Bridge/Pi/gateway unchanged.

## Actual sample-write boundary captured
First import timed out. Trace seq354/tick39693889 proves original MESA emits SCSI0C CDB0C0000018800 carrying392-byte SDATA: F0 47 00 0B 48 01 00 +192 nibbledheaderbytes+EOX. Header samplelength256. Capture preserved C:\cap_import1, extractedcopy C:\upload.bin. Added bounded headerstorage/readback/ACK in separate labadapter only; native sanitizer tests and Windowscrossbuild pass. Installed MESA_UPLOAD2.iso DLL with FC/B no differences. Relaunched MESA; PCM stage not yet captured.

## Verified original MESA PCM DATA OUT — 7 October 2026

MESA_UPLOAD2 installed into the guest; FC /B confirmed DLL copy identical. Prior capture archived as C:\cap_import1. Original MESA importing PROBE.WAV generated:

- seq63/tick44310669: 392-byte sample-header DATA OUT, CDB `0C0000018800`.
- seq66/tick44310686: 512-byte raw PCM DATA OUT, CDB `0C0000020080`.
- seq69/tick44310714: 13-byte SysEx `F04700344801000000000000F7`, CDB `0C0000000D00`; adapter has no reply and import times out here.

Guest binary-copy verification: `copy /b /y c:\mesa_capture\*66.bin c:\sentpcm.bin`, then `fc /b c:\wavpcm.bin c:\sentpcm.bin` reports no differences. DIR confirms both files512 bytes. WAVPCM.BIN was extracted from the44-byte-header monoPCM16LE44100Hz256-frame probe WAV via DEBUG. Thus this probe's transmitted PCM is byte-identical to the source PCM, with no nibble conversion or byte swapping.

Important evidence-handling correction: ordinary DOS COPY copied binary captures in text mode: the PCM copy became385bytes, and the13-byte request copy became14bytes. These were copy artifacts, NOT MESA transfer defects. Recopying with /B restores exact512/13byte lengths. Original captures were not altered.

Synthetic adapter replies are not physical S2000 evidence. Complete sample import, readback, program upload, mode sequence and final acknowledgement remain unverified. The last34 request must be traced before adding a response; no speculative success ACK added.

## POSTPCM continuation observation

Original MESA run with POSTPCM lab build generated a seven-byte synthetic response receive at sequence71/tick45574454, CDB0E0000000700, requested/payload7 and successful ASPI statuses. Trace subsequently reaches sequence117 (normal-mode09zero), after keygroup request113, status114, receive115 and two-byte MIDI116. This establishes progression beyond the former sequence69 post-PCM no-reply boundary. It does not establish physical acceptance, resident sample readback, complete import, or program upload.

Current guest UI shows SYNTH LAB and Keygroups1; attempts to open program menu did not produce a usable menu. Menus appeared grey/inactive in most observations. Do not classify the import complete from this UI. An attempted wildcard binary copy *71.bin also matched sequence100; that scratch ACK.BIN is not authoritative evidence. Original capture files are unchanged. Use exact-length filename patterns for future extraction.

No physical S2000, Pi, SSH, gateway or Bridge source accessed or changed.

## Program creation capture — follow-up

Guest focus restored; original Program menu opened successfully. Grey menus previously observed cannot be treated as proof of a hung import. Post-PCM acknowledgement prefix inspected with DEBUG: F0 47 00 16 48 00 F7, consistent with sequence71 seven-byte receive. Scratch ACK.BIN contains concatenated wildcard matches, so only the prefix is corroborative; original sequence71 remains authoritative.

Program > New Program: second attempt visibly entered `progprobe` before submission. MESA reports "Can't create program - it must have a unique name". Actual trace proves DATA OUT sequence129/tick46627081, CDB0C0000018800, requested/payload392, followed by repeated STATUS0D requested3/payload3 through sequence137, with no RECEIVE. Earlier attempt emitted sequence119/tick46555639 with same CDB/size.

Sequence129 copied /B to C:\prog.bin; COPY listed exactly DATA00000129.BIN. DEBUG prefix: F0 47 00 07 48 00 01 followed by nibble-encoded data. Thus original MESA generates program-data operation07, separate from sample-header0B and rawPCM bulk DATA OUT. The two program identifier bytes00/01 are recorded without assuming ordinary resident index semantics; creation/flag encoding requires further audit. Full192-byte decoded program fields, final EOX and keygroup follow-up have not yet been extracted/verified.

Lab adapter queue_header_reply has no operation07 write handler, so it cannot supply the expected reply for this request. Repeated STATUS with no RECEIVE establishes the immediate experimental boundary. The UI's unique-name error does not by itself prove a name collision. Do not claim program creation succeeded. Next bounded lab work needs validated program storage/readback and exact reply handling, with tests, before proceeding to keygroup capture. No generic ACK or physical implementation added in this follow-up.

## Program ACK accepted; original keygroup write captured

Bounded program handler installed with FC /B no differences; previous capture archived C:\cap_postpcm. ASAN/UBSAN tests and Windows cross-build pass (see mesa-lab-fix/MESA-effects-audit.md). Original MESA New Program `progprobe` visibly entered and submitted. New capture:
- seq58/tick47391439:392-byte PDATA DATA OUT, CDB0C0000018800.
- seq63/tick47391587:393-byte DATA OUT, CDB0C0000018900. Exact captured prefix inspected with DEBUG: F0 47 00 09 48 7F 01 00.

Operation09 is KDATA. Lakai's put_keygroup uses identical envelope: two7-bit program identifier bytes plus one keygroup byte, then nibbled header. 7F/01 decodes255; Lakai explicitly documents prognum255 as previously created program. Keygroup byte00 observed. This is actual MESA client traffic against synthetic ASPI; hardware acceptance remains unproven.

Sequence63 copied /B to C:\kg.bin; COPY listed exactly DATA00000063.BIN. Decoded initial header byte2 consistent with keygroup type. No keygroup ACK support exists yet; do not call complete program upload successful. Need next bounded KDATA storage/ACK plus coherent new-program list/readback to capture any finalization stages. Full captured binary remains authoritative in C:\MESA_CAPTURE. Guest left in DEBUG of KG.BIN. Bridge/Pi/gateway unchanged.

## Keygroup ACK and common post-object function captured

Installed KG_LAB with FC/B no differences; prior PROGRAM_LAB capture preserved C:\cap_program. New Program visibly named progprobe. Original MESA issued seq58/tick48716159 PDATA392, seq63/tick48716214 KDATA393, then seq68/tick48716269 thirteen-byte CDB0C0000000D00. The latter copied /B (exactly DATA00000068.BIN) to C:\final.bin; DEBUG first13bytes are F04700344801000000000000F7. Thus the identical bank0 function1 is emitted after both sample PCM import and program/keygroup creation. Its hardware semantics remain unproven. Missing synthetic ACK caused timeout here.

FINAL_LAB now accepts this exact function only after either complete bounded sample header+PCM or complete bounded program+keygroup state. No generic acknowledgement. Sanitizer tests pass, Windows build passes. DLL SHA2564cad034ee724d406500980999cf27aeac25fe4138ac27234d12cdf6b34a1784f; ISO56960687edf844bf2fd3680a0171badcf6e1b8c216ba434d96ec5015258997b1. Installed /B, FC/B no differences. KG_LAB capture preserved C:\cap_kg. Original MESA retest in progress.

## FINAL_LAB result

Original MESA progressed beyond exact function1 into list and header reads and finished with seq116/tick49082228 MODE090000000000. Seq81/tick49081234 is32byte PLIST reply; first32bytes inspected confirm two names, SYNTH LAB and PROGPROBE. Scratch wildcard copy also matched seq112, so only original seq81/first32bytes establish the list evidence. Seq84/tick49081324 receives392bytes; seq114/tick49081864 receives393bytes; later seq103 request inspected is program0. Consequently full selected-new-program UI readback and sample assignment remain unverified. Menu/selector interactions currently do not respond although DOS console remains usable; no claim of complete original-client workflow. Captures preserved, no reset/kill or production changes. Consolidated findings in MESA-UPLOAD-FINDINGS.md.

## READBACK_LAB guest validation
Installed bounded 0x27 program-header range replies using the same legacy program model, after captures proved reads at offsets16 and15. Local sanitizer regression tests and Windows cross-build passed. DLL SHA256 0ed179e18c703380de29066fc44769b13bf84cd980c06dd6a30d691aa6985cb4; ISO SHA256 26885301045b9fbbdf347377251d989c139c7eaac8b02ea335580933bd4426ce. Guest FC /B reports no differences. Previous captures preserved as C:\cap_range and C:\cap_final.

Original MESA New Program created PROGPROBE; explorer shows program2, one keygroup. File Import D:\PROBE.WAV subsequently populated PROBE in the sample list in the SAME running process. Trace reaches seq223/tick52152398, after range requests208/211 and15-byte request214, then status217, sample-header request220, and two-byte MIDI223. No timeout dialog observed in this run. This establishes synthetic list population and client progression, not physical acceptance.

Uploaded-program selection and zone assignment are not yet verified. Native CUA coordinate clicks fail with windowNotFoundAtPosition; keyboard menu operations work but explorer Tab navigation has not selected PROGPROBE. Current MESA process remains running with both uploaded objects; captures remain C:\MESA_CAPTURE. No production Bridge/Pi/gateway changes or hardware access.
