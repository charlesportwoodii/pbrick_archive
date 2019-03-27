# PBrick

A firmware package for Nordic nRF52 chipset made for powering legos, models, and other gadgets with motor, lighting, and other controls over Bluetooth low energy.

## Documentation

Complete documentation for board support, adding new boards, compiling, and more is provided in the [Wiki](https://github.com/charlesportwoodii/pbrick/wiki).

## Binaries

Pre-compiled versioned binaries ready for flashing are available on the [releases](https://github.com/charlesportwoodii/pbrick/releases) page. Note that you also need [S140 Soft Device](https://www.nordicsemi.com/Software-and-Tools/Software/S140) from Nordic Semiconductor.

## Building

Take a look at the [Getting Started](https://github.com/charlesportwoodii/pbrick/wiki/Getting-Started) page for more information on the dependencies needed.

With your dependencies installed you can compile the project for supported boards by running `make`

```
make BOARD=<board>
```

Run `make` without a board specified to see a list of supported boards.