#!/usr/bin/env bash
# run examples provided by dev libraries
# Usage : ./run-examples.sh

export BUILDER="${BUILDER:-podman}"

"$BUILDER" rm -f gbadev-examples >/dev/null 2>&1
"$BUILDER" run \
    -it \
    --name gbadev-examples -h gbadev-examples \
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
    gbadev-examples \
    bash -c "find /opt -type f -name '*.gba' -exec echo {} \; -exec mgba {} \;"
