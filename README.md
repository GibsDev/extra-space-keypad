# Extra Space Keypad

The Extra Space Keypad (ESK) is a small, simple 4 button mechanical RGB backlit keypad. It utilizes a Waveshare RP2040 Zero microcontroller and a custom made PCB with hot swappable 1350 sockets. The thin profile (<15mm) allows it to sit comfortably underneath the spacebar of most keyboards without interference. This gives your thumb easy access to 4 more keys that you can configure to your liking.

It comes pre assembled with 4 Kailh Choc v1 brown switches. The Choc v1 style switches have a unique keycap interface that is very 3D printer friendly. So while it may lack compatibility with cherry style keycaps, anyone can easily design and print their own!

## Where to get one

TODO etsy

## Firmware options

### Write your own firmware (Arduino IDE)

It is very easy to start programming your own firmware for the ESK using Arduino studio. Please read arduino.md for more information on how to do so.

### Use QMK firmware

The ESK is also compatible with QMK firmware. QMK is no longer accepting pull requests for "custom" keyboards anymore, but hopefully if there is enough interest in this keypad, and I continue to make and sell them, we will be able to get the ESK natively into the QMK repo. For now you will need to follow the instructions in qmk.md to flash QMK on to the ESK.

#### Configuration using Via

One awesome benefit of using QMK firmware is that it allows the keypad to be configured using the Via web app. This browser based tool allows you to directly connect to the ESK and configure the bindings and lighting whenever you want. Via requires a valid pull request in QMK in order to get native support for your device. Hopefully coming soon. For now you can follow the instructions in qmk.md to manually add the Via configuration for the ESK.
