#!/usr/bin/env bash
# Run slate pixel editor.
# Images may be saved to /in/graphics which is mounted via a "volume" to the external source code by ``cmd.sh``
echo "Running slate..."
GBADEV_CONTAINER_NAME=gbadev-base-slate GBADEV_CONTAINER_IMAGE=gbadev-base $(dirname "$0")/cmd.sh bash -c 'cd /in; slate'
