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

Run the example driver cli:
```bash
./bin/ex-pwm -d 8000000 -p 10000000
```