# MESA II → Akai S2000 reverse-engineering research

Offline research supporting a future SEND PROGRAM TO S2000 implementation. Start with the [capture reconciliation](outputs/05-capture-reconciliation.md), then the [protocol report](outputs/01-protocol-report.md), [upload sequence](outputs/02-upload-sequence.md), [implementation contract](outputs/03-bridge-specification.md), and [remaining questions](outputs/04-unresolved-questions.md).

## What this repository contains

- Technical reports, function addresses, disassembly excerpts and documentary field maps.
- Eight recovered original MESA client capture archives, complete trace logs and binary payloads; 899 recovered files including six separately identified guest scratch files.
- Complete 192-byte sample/program/keygroup examples, captured PCM, golden packet vectors and exact command-order transcripts.
- Source/provenance registers, integrity checks and the Bridge serializer byte-difference analysis.
- Both preserved research ASPI shim source versions and their existing probe/fixture tests.
- Historical offline extraction, parsing and analysis scripts.

## Evidence boundary

The captures are original MESA outgoing traffic against a **synthetic ASPI target**. Incoming replies and completion statuses are synthetic. They establish client byte sequences, not physical S2000 acceptance, allocation, linked-program success or reliable hardware recovery. The captured new keygroup has blank sample zones.

MESA's captured sample-creation path sends SDATA then raw PCM without ASPACK. Program creation uses identifier128 then keygroups addressed to255 in the last-created-program context. Neither identifier proves a resident ordinal. Post-object function1 is preserved without speculative semantics.

The material is sufficient to begin offline codecs/uploader/golden-vector tests. No new Bridge uploader was implemented in this chat: that task was stopped before code changes. Hardware-facing use remains unvalidated.

## Verify the package

From the repository root:

```sh
python3 tools/verify_bundle.py
```

This checks every exported file against SHA256SUMS.json and separately checks that raw capture files retain their original recovery hashes. It does not execute MESA, communicate with a sampler, or run hardware tests.

## Historical scripts and lab sources

`tools/` analysis scripts retain the original investigation structure and must be configured for local paths before use. `${LOCAL_HOME}` is an export placeholder, not an automatically expanded Python path. In particular, recover_captures.py previously copied a user-owned QCOW2 disk and extract_captures.py wrote into outputs/. Do not rerun recovery merely to inspect already-recovered data.

`lab/aspi-shim-original` and `lab/aspi-shim-readback` are distinct historical versions. Build scripts require an existing Windows cross-compiler and path configuration; they do not install a toolchain. `reply_test.c` is a historical fixture regression, not a complete Bridge uploader golden suite. No lab executable is included or automatically installed.

## Export/provenance policy

Text exports replace the original user's host home path with `${LOCAL_HOME}`. Binary captures and WAV/header data are unchanged. `export-provenance.json` retains pre-export file hashes; `SHA256SUMS.json` records the exported files. Existing source-register hashes still refer to the original research sources, which can include files not distributed here.

Excluded: MESA/Windows installation images, MSI/cabinets, proprietary DLLs/executables, VM disk, extracted vendor payload trees, compiled lab binaries, Bridge source/build products and full third-party manuals/source distributions. Their relevant identities and references remain in the research register. No new license or permission to redistribute excluded software is asserted.

## Upload to GitHub

Unzip this folder and upload its contents as a repository, or commit them from a local clone. This package does not contain a .git directory and has not been published. The generated SHA256SUMS.json covers repository contents before any edits; regenerate it deliberately if you change documentation.
