#!/usr/bin/env bash
# build the gba development environment
# Usage : ./build.sh

# Use parallelization by default.
# Comment this out if compilation errors for simpler debug
# Defaults to max procs if unset
export MAKEFLAGS="${MAKEFLAGS:--j $(grep -c ^processor /proc/cpuinfo)}"

export BUILDER="${BUILDER:-podman}"
export BASE_IMG=${BASE_IMG:-docker.io/debian:12.5-slim}
export DEVKITPRO_IMG="${DEVKITPRO_IMG:-docker.io/devkitpro/devkitarm:latest}"
export BUTANO="${BUTANO:-17.8.0}"
export MGBA="${MGBA:-0.10.3}"
export SLATE="${SLATE:-0.10.3}"
export PILLOW="${PILLOW:-2.2.2}"
export NIM="${NIM:-https://nim-lang.org/download/nim-2.0.8-linux_x64.tar.xz}"
export NATU="${NATU:-https://git.sr.ht/~exelotl/natu@0.2.1}"

echo "building with $BUILDER"

# Pull our base images
"$BUILDER" pull $BASE_IMG
"$BUILDER" pull $DEVKITPRO_IMG

"$BUILDER" build \
    -t gbadev-base \
    --build-arg MAKEFLAGS="$MAKEFLAGS" \
    --build-arg BASE_IMG="$BASE_IMG" \
    --build-arg DEVKITPRO_IMG="$DEVKITPRO_IMG" \
    --build-arg BUTANO="$BUTANO" \
    --build-arg MGBA="$MGBA" \
    --build-arg SLATE="$SLATE" \
    --build-arg PILLOW="$PILLOW" \
    --build-arg NIM="$NIM" \
    --build-arg NATU="$NATU" \
    --file containers/Containerfile.base \
    .
