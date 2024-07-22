#!/usr/bin/env
# Split an audio file into 5 second wav files for use in butano.
ffmpeg -i $1 -f segment -segment_time 5 -ar 22050 -ac 1  music%04d.wav
