# Lib GPIO Driver Examples

Modified: 2022-02

## Sysfs PWM Driver
Build the example and link to `gpio` static library
```bash
mkdir -p build
cd build
cmake ..
make -j
```

Run the example driver cli
```bash
./bin/example_pwm_driver 500000 100000
```