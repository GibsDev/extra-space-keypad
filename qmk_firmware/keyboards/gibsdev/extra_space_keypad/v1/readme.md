# extra_space_keypad

![extra_space_keypad](imgur.com image replace me!)

This small and simple keypad is meant to be placed below the spacebar of almost any keyboard to add extra an set of keys to bind to (sorry wrist rest users). Reminiscent of the [A4Tech G800 X7](http://x7.a4tech.com/product.aspx?id=87), your thumb can now access 4 more buttons without needing to stretch.

* Keyboard Maintainer: [GibsDev](https://github.com/GibsDev)
* Hardware Supported: RP2040
* Hardware Availability: Coming soon

Make example for this keyboard (after setting up your build environment):

    `make extra_space_keypad:default`
    
    or
    
    `qmk compile -kb gibsdev/extra_space_keypad/v1 -km default`

Flashing example for this keyboard:

    `make extra_space_keypad:default:flash`
    
    or
    
    `qmk flash -kb gibsdev/extra_space_keypad/v1 -km default`

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Double tap the reset button
* **Physical reset button**: Hold the boot button while you quickly press the reset button
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
