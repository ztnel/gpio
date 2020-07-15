#!/bin/bash

set -e

# check for permissions
gpio readall

gpio -g mode 18 output
gpio -g write 18 1
sleep 2
gpio -g write 18 0
sleep 2
gpio -g write 18 1
sleep 2
gpio -g write 18 0
sleep 2
gpio -g write 18 1
sleep 2
gpio -g write 18 0
sleep 2
gpio -g write 18 1
sleep 2
gpio -g write 18 0
sleep 2
gpio -g write 18 1