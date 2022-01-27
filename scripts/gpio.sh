#!/bin/bash

set -e

CLK=17
RCLK=18

gpio readall
gpio -g mode "$CLK" in
gpio -g mode "$RCLK" out
clk_pulse=0

while :
do
	if [ "$(gpio -g read $CLK)" == 1 ]; then
		clk_pulse=$(("$clk_pulse"+1))
        fi
        if [ "$clk_pulse" == 7 ]; then
                echo "Reached max"
		clk_pulse=0
                gpio -g write "$RCLK" 1
	else
		gpio -g write "$RCLK" 0
	fi
done
