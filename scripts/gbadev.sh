#!/usr/bin/env bash
# build the game folder
# using the image created with ./build.sh
# Usage : ./gbadev.sh

# Use parallelization by default.
# Comment this out if compilation errors for simpler debug
# Defaults to max procs if unset
export MAKEFLAGS="${MAKEFLAGS:--j $(grep -c ^processor /proc/cpuinfo)}"

export BUILDER="${BUILDER:-podman}"
SQUASH="--squash"
if [ "$BUILDER" = "docker" ]; then
  BASE="gbadev-base"
  SQUASH=""  # https://github.com/docker/buildx/issues/1287
fi
BASE="${BASE:-localhost/gbadev-base}"

IN="${IN:-`pwd`/in}"
OUT="${OUT:-`pwd`/out}"

mkdir -p "$OUT"

"$BUILDER" build \
    -t gbadev-build \
    $SQUASH \
    --no-cache \
    --build-arg MAKEFLAGS="$MAKEFLAGS" \
    --build-arg BASE="$BASE" \
    --file containers/Containerfile.build \
    -v "${IN}:/in" \
    -v "${OUT}:/out" \
    . \
    || { echo 'BUILD FAILED!' ; exit 1 ; } \
    &&   echo 'BUILD COMPLETE!'

# FIXME: folder name always seems to be used for rom, rename to expected.
cp ${OUT}/$(basename ${OUT}).gba ${OUT}/${ROMTITLE:-out.gba} 2>/dev/null || exit 0
