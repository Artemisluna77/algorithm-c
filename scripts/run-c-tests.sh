#!/bin/sh
set -eu

resolve_tool() {
  tool=$1
  resolved=$(command -v "$tool" 2>/dev/null || true)
  if [ -n "$resolved" ]; then
    printf '%s\n' "$resolved"
    return 0
  fi

  if [ -n "${CMAKE_BIN:-}" ]; then
    sibling="$(dirname "$CMAKE_BIN")/$tool"
    if [ -x "$sibling" ]; then
      printf '%s\n' "$sibling"
      return 0
    fi
  fi

  case "$(uname -m 2>/dev/null || true)" in
    arm64|aarch64) arches="aarch64 arm64" ;;
    x86_64) arches="x86_64" ;;
    *) arches="aarch64 arm64 x86_64" ;;
  esac

  for arch in $arches; do
    candidate="/Applications/CLion.app/Contents/bin/cmake/mac/$arch/bin/$tool"
    if [ -x "$candidate" ]; then
      printf '%s\n' "$candidate"
      return 0
    fi
  done

  printf 'Required CMake tool not found: %s. Install CMake/CTest or add it to PATH.\n' "$tool" >&2
  return 1
}

CMAKE_BIN=$(resolve_tool cmake) || exit 1
CTEST_BIN=$(resolve_tool ctest) || exit 1

"$CMAKE_BIN" -S . -B build
"$CMAKE_BIN" --build build --parallel "${CMAKE_BUILD_JOBS:-4}"
"$CTEST_BIN" --test-dir build --output-on-failure
