#!/usr/bin/env bash
set -euo pipefail

ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
BUILD_DIR="${ROOT_DIR}/build"

# Configure (only needs to happen once, but safe to rerun)
cmake -S "${ROOT_DIR}" -B "${BUILD_DIR}" -DCMAKE_BUILD_TYPE=Debug

# Build
cmake --build "${BUILD_DIR}" -j

# Run (CMake places it under build/<subdir>/<target> for Makefiles/Ninja)
if [[ -x "${BUILD_DIR}/love/SukiGame" ]]; then
  "${BUILD_DIR}/love/SukiGame"
elif [[ -x "${BUILD_DIR}/game/SukiGame" ]]; then
  "${BUILD_DIR}/game/SukiGame"
else
  echo "Could not find the built executable. Tried:"
  echo "  ${BUILD_DIR}/love/SukiGame"
  echo "  ${BUILD_DIR}/game/SukiGame"
  echo
  echo "Tip: check your target name and build output folder."
  exit 1
fi

