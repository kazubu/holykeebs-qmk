#!/bin/sh

make crkbd/rev1:via -e USER_NAME=holykeebs -e POINTING_DEVICE=trackpoint -e POINTING_DEVICE_POSITION=right -e OLED=yes -e CONSOLE=no -j8
make ai03/altair_x:via -e USER_NAME=holykeebs -e POINTING_DEVICE=trackpoint -e POINTING_DEVICE_POSITION=right -e OLED=no -e CONSOLE=no -j8
