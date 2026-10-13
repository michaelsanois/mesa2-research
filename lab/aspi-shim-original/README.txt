MESA II ISOLATED SYNTHETIC ASPI ADAPTER

This is a research-only WNASPI32.DLL for the isolated Windows 98 MESA VM.
It advertises one SYNTHETIC AKAI S2000 at host adapter 0, SCSI ID 2, LUN 0.
It does not access physical SCSI, USB, MIDI, networking, the Raspberry Pi,
or the real S2000. Data-in replies other than INQUIRY/REQUEST SENSE are
synthetic zeroes. Every log entry is marked synthetic=true.

INSTALL ONLY IN THE MESA APPLICATION DIRECTORY INSIDE THE VM.
Do not copy this DLL into Windows\System or onto the host Mac.
If a WNASPI32.DLL already exists in the application directory, do not replace
it; stop and inspect first.

The ASPI command trace and captured data are written in the VM to:
  C:\MESA_CAPTURE\TRACE.TXT
  C:\MESA_CAPTURE\DATA######.BIN

TRACE.TXT records the ASPI command, target, CDB, transfer direction, requested
length, response status, and whether a capture file was written. DATA files
contain MESA outbound buffers or synthetic responses. All responses remain
synthetic; this shim does not implement or prove the full Akai protocol.

These captures record MESA's requests, but all adapter responses are fake.
They are not evidence of a real S2000 transfer.

Build SHA-256 is supplied in SHA256.txt.
