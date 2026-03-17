#!/usr/bin/env bash
set -euo pipefail

ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
BUILD_DIR="${ROOT_DIR}/build"

# Configure (only needs to happen once, but safe to rerun)
cmake -S "${ROOT_DIR}" -B "${BUILD_DIR}" -DCMAKE_BUILD_TYPE=Debug

# Build
cmake --build "${BUILD_DIR}" -j

# Run (CMake places it under build/<subdir>/<target> for Makefiles/Ninja)
if [[ -x "${BUILD_DIR}/love/Love" ]]; then
  "${BUILD_DIR}/love/Love"
elif [[ -x "${BUILD_DIR}/game/Love" ]]; then
  "${BUILD_DIR}/game/Love"
else
  echo "Could not find the built executable. Tried:"
  echo "  ${BUILD_DIR}/love/Love"
  echo "  ${BUILD_DIR}/game/Love"
  echo
  echo "Tip: check your target name and build output folder."
  exit 1
fi

