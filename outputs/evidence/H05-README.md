# MESA II reverse-engineering lab

This folder is reserved for the isolated MESA II / Windows 98 SE research VM. The VM is not created yet. The physical S2000 and PiSCSI must remain disconnected and inaccessible.

## Current artifacts

- Windows 98 SE Retail Full ISO: `${LOCAL_HOME}/Downloads/Windows 98 SE (101 - Retail Full).iso`
  - 652,738,560 bytes; SHA-256 `5e3e7b7c6a3cf466da60361ba8d5e1640e50822c0fc7c5b8dab94c86cd6feac7`.
  - ISO 9660, volume `WIN98 SE`; no El Torito boot catalog, so it is not bootable on its own.
- UTM 4.7.5 official release disk image: [`downloads/UTM-4.7.5.dmg`](downloads/UTM-4.7.5.dmg)
  - 251,872,449 bytes; SHA-256 `23c32cf1148186040bd9c0030b726d94e913b4eb0ab058275c5c08573cc401eb`.
- UTM is now installed at `/Applications/UTM.app` (user-confirmed).
- Startup floppy supplied by user: `downloads/Windows 98 Second Edition Boot.img`.
  - 1,474,560 bytes (1.44 MB, 2880 sectors), FAT12 boot sector; SHA-256 `c43199628b9b65428ff5645a70d2139a6e6275c854ae6ca7c7cee6308b5013d5`.
  - Working copy: [`vm/win98se-startup.img`](vm/win98se-startup.img). The original download remains unchanged.
- MESA II PC v1.5 ISO: `${LOCAL_HOME}/Downloads/MESA.ISO` (5,474,304 bytes).
  - Installer: `MESA2PC/MESA2V15/MESA_INS/SETUP.EXE`.
  - MSI: `MESA2PC/MESA2V15/MESA_INS/DPSSETUP.MSI`.
  - Runtime dependency shipped alongside installer: `MESA2PC/MESA2V15/MFC42.DLL`.
  - The MESA ReadMe says Windows 98 SE/Me are supported, Windows NT/2000 are unsupported, and the installer destination should not be changed.
  - Static inspection previously found `SCSIPlug.dll` and `MesaSampler.dll` in the MSI payload. Their exact installed path should be confirmed after installation; do not patch either binary.
- Directories are prepared: `downloads/`, `vm/`, `mesa/`, `aspi-shim/`, `captures/`, `protocol/`, `notes/`.

## Boot-media finding

The Windows ISO contains `TOOLS/MTSUTIL/FAT32EBD/FAT32EBD.EXE`, `FAT32EBD.TXT`, and `IMAGE.DSK`. So the complete startup disk can be generated from the supplied Windows media using Microsoft's utility, but the utility expects a running DOS/Windows environment and a writable 1.44 MB `A:` drive. This does not solve the first-boot problem by itself; use a legitimate complete Windows 98 SE Startup Disk image, or provide a DOS bootstrap image and generate the Microsoft disk inside that isolated guest.

`IMAGE.DSK` is only 36,864 bytes and is a boot-sector/disk template, not a complete 1.44 MB startup disk image. A first-pass copy was removed from `vm/` after checking its size. Do not attach that template as a boot floppy.

The user supplied a complete 1.44 MB startup image. The file is staged at the path above. Do not attach the 36 KB `IMAGE.DSK` template.

## UTM VM settings

Create a new VM only after the complete startup floppy image is available:

1. In UTM choose **Create a New Virtual Machine → Emulate → Windows → Intel i440FX based PC**. This is a 32-bit PC model; ensure it is emulated, not virtualized.
3. Allocate 128 MB RAM and one CPU core. Keep defaults for CPU model and display/input.
4. Create a 2 GB IDE hard disk (QCOW2 is fine).
5. Boot from the supplied Windows 98 startup floppy image. Attach the Windows 98 ISO as an IDE CD/DVD image after creating the VM.
6. Do not mount a shared directory. Remove/disable the network device. Do not add USB devices, USB passthrough, MIDI, SCSI controllers/devices, serial adapters, or host folders.
7. Use the startup floppy's CD-ROM support to access the Windows CD and launch `SETUP` from its `WIN98` directory. Partition/format only the VM's 2 GB virtual disk.
8. After Windows setup completes and boots from the virtual hard disk, eject the Windows ISO and attach `${LOCAL_HOME}/Downloads/MESA.ISO` as the CD image. Run `MESA2PC/MESA2V15/MESA_INS/SETUP.EXE`; accept the default destination.
9. Verify Windows 98 SE boots and MESA installs and launches. Stop there; do not start ASPI capture yet.

UTM's Classic Windows guide specifies **Emulate**, the Intel i440FX PC model, a boot image, virtual disk allocation, and optional installer ISO. Its QEMU drive settings support choosing a bus interface; use IDE for both disk and CD. This configuration intentionally has no route to PiSCSI or the S2000. The VM has not yet been created, so isolation settings must be verified in UTM before first boot.

## ASPI stage boundary

No shim has been implemented. After Windows 98 SE boots and MESA launches, the next task is to snapshot the VM, verify all host bridges are disabled, then design and test a guest-local fake `WNASPI32.dll`. The fake target must not be implemented or connected to physical hardware. Preserve each VM snapshot and all captures beneath this folder.
