# bobbycar-boardcomputer-firmware

![Build Status](https://github.com/bobbycar-graz/bobbycar-boardcomputer-firmware/actions/workflows/main.yml/badge.svg)
[![Codacy Badge](https://api.codacy.com/project/badge/Grade/04c264db40c44276833f43b9c083dc14)](https://app.codacy.com/gh/bobbycar-graz/bobbycar-boardcomputer-firmware?utm_source=github.com&utm_medium=referral&utm_content=bobbycar-graz/bobbycar-boardcomputer-firmware&utm_campaign=Badge_Grade_Dashboard)

## How to clone ? (READ THIS OR YOU WILL FAIL)

```
git clone --recursive git@github.com:bobbycar-graz/bobbycar-boardcomputer-firmware.git
cd bobbycar-boardcomputer-firmware/
./esp-idf/install.sh
./switchconf.sh feedc0de
```

## How to compile
Also do the initialization if you use an IDE, otherwise build will fail.

```
# before you try to build anything, always do this first:
. export.sh

# if needed, switch to the right configuration for your hardware (run with --list to list available configurations)
./switchconf.sh feedc0de

# flash bootloader, partition table and app (only do once)
idf.py -p /dev/ttyUSB0 -b 921600 flash monitor

# flash only app (do this for development as it is much faster)
idf.py -p /dev/ttyUSB0 -b 921600 app-flash monitor
```

if you are inside monitor, hit Ctrl+T then Ctrl+X to exit.

Hit Ctrl+T then Ctrl+A to reflash the app and return to monitor (very handy during development)

## How to wire all connections?

![Wiring diagram](/img/wiring.png)

### -DFEATURE_DPAD
![dpad switches with 5 wires](/img/dpadsw.png)

### -DFEATURE_DPAD_3WIRESW
![3 wire switches](/img/3wiresw.png)

### -DFEATURE_ROTARY
![rotary encoder](/img/rotary.png)
