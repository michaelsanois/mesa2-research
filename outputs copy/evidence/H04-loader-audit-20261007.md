# MESA loader investigation — 7 October 2026

Verified in the running Windows 98 VM:
- Installed ASPIProbe loads and calls the synthetic DLL successfully.
- TRACE.TXT contains four ASPIPROBE.EXE events (load, support info, device type, inquiry).
- MESA discovery fails and emits SCSIPlug's No Devices message.
- Installed Dlls folder contains SCSIPlug.dll; no WNASPI32.dll was visible among its final entries.
- A direct launch of C:\Program Files\AKAI\Mesa\Mesa.exe also fails discovery.

This does not yet establish the loaded ASPI path. Absence of MESA entries is evidence that the instrumented module was not called in the observed run, not proof of a particular alternative DLL location.

Prepared ASPIProbe /modules read-only Toolhelp process/module audit. It writes C:\MESA_CAPTURE\MODULES.TXT and performs no ASPI calls in that mode. Disc: aspi-shim/MESA_LOADER_AUDIT.iso. Awaiting media attachment because host drive-menu clicks did not open reliably through computer control.

Local SCSIPlug disassembly: GetASPI32SupportInfo imported ordinal 1; SendASPI32Command ordinal 2. Caller checks AH==1, stores AL as adapter count. Synthetic 0x0101 satisfies both. Send callers clean stack, matching the shim's cdecl. Discovery executes host-adapter inquiry before target scan. These checks alone do not prove sampler handshake support.

No physical hardware, PiSCSI installation or Bridge project modified.
