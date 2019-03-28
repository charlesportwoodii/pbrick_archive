# PBrick

A firmware package for Nordic nRF52 chipset made for powering legos, models, and other gadgets with motor, lighting, and other controls over Bluetooth low energy.

## Documentation

Complete documentation for board support, adding new boards, compiling, and more is provided in the [Wiki](https://github.com/charlesportwoodii/pbrick/wiki).

## Installing

1. Burn the [Adafruit nRF52 Bootloader](https://github.com/adafruit/Adafruit_nRF52_Bootloader/releases) using `nrfjprog`. Grab a hex/zip for your supported board.

    ```
    nrfjprog --program bootloader_binary.hex --chiperase -f nrf52 --reset
    ```

    > This step is only necessary for boards not already flashed with the Adafruit nRF52 bootloader. Boards such as the `sparkfun-nrf52-pro-mini` can skip this step as they already have a variant of the nRF52 bootloader flashed.
    > You'll need a Segger J-LINK in order to flash the bootloader with the Adafruit bootloader for the first time. Once the Adafruit bootloader is flashed, you can use `adafruit-nrfutil` to update the bootloader. Adafruit sells a [J-Link EDU Mini](https://www.adafruit.com/product/3571) for $19.99 USD if you need a cheap J-Link
    > PBrick utilizes the Adafruit nRF52 bootloader to take advantage of OTA-DFU. The Adafruit bootloader greatly simplifies the need to write a custom bootloader, and also comes pre-loaded with the S140 soft-device.

2. Flash the PBrick hex to your board using either nRF Connect, `adafruit-nrfutil`.

    If you're making changes, run `make <board>` to build your custom solution.

    > You can download pre-compiled binaries from the [releases](https://github.com/charlesportwoodii/pbrick/releases) page if you're just looking to use PBrick.

## Building

Take a look at the [Getting Started](https://github.com/charlesportwoodii/pbrick/wiki/Getting-Started) page for more information on the dependencies needed.

With your dependencies installed you can compile the project for supported boards by running `make`

```
make <board>
```

> Run `make` without a board specified to see a list of supported boards.
> You can also run `make all` to build all boards.