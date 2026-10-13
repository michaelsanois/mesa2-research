# Original MESA II upload capture — 7 October 2026

Research scope: original MESA executable in Windows98 with a synthetic ASPI adapter. No physical sampler, Pi, gateway, Bridge source or installed AU was accessed or modified.

## Captured client sequence

| Stage | Actual client payload | SCSI CDB | Evidence |
|---|---|---|---|
| Sample header | SDATA0B,192-byte nibbled header,392 wire bytes | 0C0000018800 | UPLOAD2 seq63 |
| PCM |512 raw bytes, mono PCM16LE, byte-identical to PROBE.WAV PCM |0C0000020080| UPLOAD2 seq66; guest FC/B |
| Post-sample function | F04700344801000000000000F7 |0C0000000D00| UPLOAD2 seq69 |
| Program | PDATA07, identifier00/01,192-byte nibbled header,392 wire bytes |0C0000018800| PROGRAM_LAB seq58 |
| Keygroup | KDATA09, identifier7F/01 (255), KG00,192-byte nibbled header,393 wire bytes |0C0000018900| PROGRAM_LAB seq63 |
| Post-program function | F04700344801000000000000F7 |0C0000000D00| KG_LAB seq68/tick48716269 |

Sample and program creation are separate observed user actions, not one captured combined upload. Lakai documents keygroup program255 as previously-created program. Program128 allocation semantics and function1 hardware semantics require separate confirmation.

## Bounded lab implementation

fake_aspi.c stores validated sample header,512PCMbytes, program192bytes and keygroup192bytes. Unknown writes remain without synthetic acknowledgement. Exact function1 gets REPLY16/status0 only when complete bounded sample or program/keygroup state exists. New program/keygroup data are available for synthetic list/readback at lab slot1. This allocation is a fixture decision, not a hardware claim.

Tests cover malformed/truncated envelopes, invalid nibble/type/index, keygroup-before-program rejection, complete192byte program/keygroup readback, uploaded-name list inclusion, reset/invalidation and exact post-function gating. ASAN/UBSAN suite and Windows cross-build pass. Production Bridge has not been changed.

## FINAL_LAB original-client retest

Installed DLL via COPY/B, FC/B no differences. Original MESA New Program visibly entered progprobe. It progressed beyond the common function into further list/header reads. Trace records seq81/tick49081234 RECEIVE32bytes, seq84/tick49081324 RECEIVE392bytes, seq114/tick49081864 RECEIVE393bytes, then seq115 two-byte MIDI DATAOUT and seq116/tick49082228 normal MODE090000000000. No further unsupported SEND is present in the inspected final trace tail.

Seq81 reply prefix32bytes inspected: F0470003480200 followed by SYNTH LAB and encoded PROGPROBE names, endingF7. Scratch extraction wildcard also concatenated seq112; only first32bytes are corroborative. Original capture is authoritative. Later seq103 request is program0, not proof that the UI selected uploaded program1. UI selection and linked sample assignment are not yet verified.

## Remaining limits

Synthetic replies cannot prove S2000 acceptance, actual allocation, finalization semantics, physical phase behavior, playback or production upload correctness. The client-side sample PCM encoding is established for the small probe only. Full transfer sizes, block boundaries, acknowledgement/receive draining and errors still require hardware-grounded validation before SEND TO S2000 implementation.

## Artifacts

FINAL_LAB DLL SHA256:4cad034ee724d406500980999cf27aeac25fe4138ac27234d12cdf6b34a1784f.
ISO SHA256:56960687edf844bf2fd3680a0171badcf6e1b8c216ba434d96ec5015258997b1.
Source/tests:mesa-lab-fix/fake_aspi.c and reply_test.c.
Guest preserved captures:C:\cap_import2,C:\cap_postpcm,C:\cap_program,C:\cap_kg; newest C:\MESA_CAPTURE.
