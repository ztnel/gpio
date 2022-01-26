# Linux Sysfs PWM Driver

ModifiedL 2022-01

Linux compatible PWM driver for raspberrypi. Low performance compared to DMA due to file level IO operations. 

## Setup
1. Run an apt update and full upgrade to address 2019 PWM driver fix at upper frequencies
```bash
sudo apt update -y
sudo apt full-upgrade -y
```
2. Get PWM clock frequency to get default frequency
```bash
vcgencmd measure_clock pwm
```
3. Add pwm `dtoverlay` configuration to the last line in the `/boot/config.txt` to enable 2 channel pwm
```bash
dtoverlay=pwm-2chan
```

## Driver Configuration
The linux driver is configured to show the pwm as a single chip in sysfs @ `/sys/class/pwm/pwmchip0`. To work with either pwm channel we need to export the channel first.

## Resources
https://www.iot-programmer.com/index.php/books/22-raspberry-pi-and-the-iot-in-c/chapters-raspberry-pi-and-the-iot-in-c/57-raspberry-pi-and-the-iot-in-c-sysfs-the-linux-way-to-gpio