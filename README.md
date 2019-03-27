# PBrick

A firmware package for Nordic nRF52 chipset made for powering legos, models, and other gadgets with motor, lighting, and other controls over Bluetooth low energy.

## Documentation

Complete documentation for board support, adding new boards, compiling, and more is provided in the [Wiki](https://github.com/charlesportwoodii/pbrick/wiki).

## Binaries

Pre-compiled versioned binaries ready for flashing are available on the [releases](https://github.com/charlesportwoodii/pbrick/releases) page. Note that you also need [S140 Soft Device](https://www.nordicsemi.com/Software-and-Tools/Software/S140) from Nordic Semiconductor.

## Building

### Dependencies

1. [GNU Toolchain for ARM Cortex-M 8-2018-q4-major](https://developer.arm.com/tools-and-software/open-source-software/gnu-toolchain/gnu-rm/downloads)

Extract and install to `PATH`.

2. [Nordic SDK 15.3.0](https://www.nordicsemi.com/Software-and-Tools/Software/nRF5-SDK)

Extract the Nordic SDK and set `NORDIC_SDK_PATH` environment variable to the extracted directory.

> Note that you may need to adjust `components/toolchain/gcc/Makefile.posix` with the path to `gcc-arm-none-eabi-7-2018-q2-update/bin/`.


3. [nRF Connect](https://www.nordicsemi.com/Software-and-Tools/Development-Tools/nRF-Connect-for-desktop)

Used for flashing.

4. [nRF Command Line Tools](https://www.nordicsemi.com/Software-and-Tools/Development-Tools/nRF5-Command-Line-Tools)

Used for manual flashing. Extract tools and their dependencies and add to your `PATH`.

### Compiling

With your dependencies installed you can compile the project for supported boards by running `make`

```
make BOARD=<board>
```

Run `make` without a board specified to see a list of supported boards.