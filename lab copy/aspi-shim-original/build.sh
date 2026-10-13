#!/bin/sh
set -eu
ROOT=$(CDPATH= cd -- "$(dirname -- "$0")" && pwd)
CC=${LOCAL_HOME}/Documents/Codex/mesa-re/tools/llvm-mingw-20260922-ucrt-macos-universal/bin/i686-w64-mingw32-clang
"$CC" -shared -nostdlib -fno-stack-protector -fno-builtin \
  -Wl,--entry,_DllMain@12 -Wl,--no-insert-timestamp \
  -Wl,--major-os-version,4 -Wl,--minor-os-version,0 \
  -Wl,--major-subsystem-version,4 -Wl,--minor-subsystem-version,0 \
  -Wl,--enable-stdcall-fixup -Wl,--kill-at \
  -Wl,"$ROOT/winaspi32.def" -lkernel32 \
  -o "$ROOT/WNASPI32.dll" "$ROOT/fake_aspi.c"
shasum -a 256 "$ROOT/WNASPI32.dll" | awk '{print $1 "  WNASPI32.dll"}' > "$ROOT/SHA256.txt"
