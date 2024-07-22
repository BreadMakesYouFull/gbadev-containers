#!/usr/bin/env bash
# Run slate pixel editor.
# Images may be saved to /in/graphics which is mounted via a "volume" to the external source code by ``cmd.sh``

echo "Running gimp..."
GBADEV_CONTAINER_NAME=gbadev-base-gimp GBADEV_CONTAINER_IMAGE=gbadev-base $(dirname "$0")/cmd.sh bash -c "cd /in ; export BUTANO_GRAPHICS_PATH=/in/graphics; gimp "
