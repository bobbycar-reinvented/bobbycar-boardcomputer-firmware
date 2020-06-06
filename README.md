# bobbycar-boardcomputer-firmware

## How to clone and compile?

```
git clone --recursive git@github.com:bobbycar-graz/bobbycar-boardcomputer-firmware.git
cd bobbycar-boardcomputer-firmware/
platformio run --environment bobbycar_usb --target upload
```

## How to wire all connections?

![Wiring diagram](/img/wiring.png)

### -DFEATURE_DPAD
![dpad switches with 5 wires](/img/dpadsw.png)

### -DFEATURE_DPAD_3WIRESW
![3 wire switches](/img/3wiresw.png)

### -DFEATURE_ROTARY
![rotary encoder](/img/rotary.png)
