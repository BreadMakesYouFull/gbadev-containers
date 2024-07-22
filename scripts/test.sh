#!/usr/bin/env bash
# Run a build and compare with the fixture
make
cmp -s gbadev-containers.gba out/out.gba && echo "Test pass: gbadev-containers.gba == out/out.gba" ||echo "Test fail: gbadev-containers.gba != out/out.gba"
