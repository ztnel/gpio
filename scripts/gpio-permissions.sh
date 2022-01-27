#!/bin/bash

set -e

# add gpio group if not already added
if ! grep -q gpio /etc/group; then
    sudo groupadd -g 199 gpio
    sudo adduser ubuntu gpio
    echo "Added gpio group @ GID 199 and user ubuntu"
else
    echo "gpio group exists and is set; skipping.."
fi

# set permissions for gpio to access gpiomem space
echo "Setting gpio cli permissions for current session"
sudo chown ubuntu.gpio /dev/gpiomem
sudo chmod g+rw /dev/gpiomem