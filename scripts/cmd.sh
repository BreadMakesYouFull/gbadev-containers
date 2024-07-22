#!/usr/bin/env bash
# run a command in the the gba development environment
# Usage : ./cmd.sh mgba [path to rom]
#         ./cmd.sh bash

export BUILDER="${BUILDER:-podman}"

IN="${IN:-`pwd`/in}"
OUT="${OUT:-`pwd`/out}"

# Start container with audio and graphics forwarded to host
"$BUILDER" rm -f ${GBADEV_CONTAINER_NAME:-gbadev} >/dev/null 2>&1
"$BUILDER" run \
    -it \
    --name ${GBADEV_CONTAINER_NAME:-gbadev} \
    -h ${GBADEV_CONTAINER_NAME:-gbadev} \
    -v "${IN}:/in" \
    -v "${OUT}:/out" \
    -v /dev/snd:/dev/snd \
    -v /tmp/.X11-unix:/tmp/.X11-unix \
    --device=/dev/dri:/dev/dri \
    --device=/dev/net/tun \
    --cap-add NET_ADMIN \
    -e DISPLAY="$DISPLAY" \
    -v "/etc/alsa:/etc/alsa" \
    -v "/usr/share/alsa:/usr/share/alsa" \
    -v "${HOME}/.config/pulse:/.config/pulse" \
    -v "/run/user/$UID/pulse/native:/run/user/$UID/pulse/native" \
    --env "PULSE_SERVER=unix:/run/user/$UID/pulse/native" \
    -v "/run/user/$(id -u)/$WAYLAND_DISPLAY:/tmp/wayland-0:ro" \
    ${GBADEV_CONTAINER_IMAGE:-gbadev} "${@}"
