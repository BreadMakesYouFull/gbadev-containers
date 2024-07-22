#!/usr/bin/env bash
# run the generated build gba file with mgba
# Usage : ./run.sh

$(dirname "$0")/cmd.sh mgba "/$(basename ${OUT})/${ROMTITLE:-out.gba}"
