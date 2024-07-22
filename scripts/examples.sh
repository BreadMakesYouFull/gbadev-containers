#!/usr/bin/env bash
# compile and run all examples in the gbadev environment
# Usage : ./examples.sh

# Use parallelization by default.
# Comment this out if compilation errors for simpler debug
# Defaults to max procs if unset
export MAKEFLAGS="${MAKEFLAGS:--j $(grep -c ^processor /proc/cpuinfo)}"

export BUILDER="${BUILDER:-podman}"
if [ "$BUILDER" = "docker" ]; then
  BASE="gbadev-base"
fi
BASE="${BASE:-localhost/gbadev-base}"

# Compile examples
"$BUILDER" build \
    -t gbadev-examples \
    --build-arg MAKEFLAGS="$MAKEFLAGS" \
    --build-arg BASE="$BASE" \
    --file containers/Containerfile.examples \
    .

