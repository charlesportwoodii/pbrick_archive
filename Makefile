BOARD?=
SUPPORTED_BOARDS:=pca10059 mdk-usb-dongle sparkfun-pro-mini

default: check-env
ifneq ($(filter $(BOARD),$(SUPPORTED_BOARDS)),)
	$(MAKE) $(BOARD)
else
	$(error Specified a board to build)
endif

clean: check-env
ifneq ($(filter $(BOARD),$(SUPPORTED_BOARDS)),)
	cd boards/$(BOARD)/s140/armgcc && $(MAKE) $(BOARD)
else
	cd boards/pca10059/s140/armgcc && $(MAKE) clean
	cd boards/mdk-usb-dongle/s140/armgcc && $(MAKE) clean
	cd boards/sparkfun-pro-mini/s140/armgcc && $(MAKE) clean
endif

.PHONY: check-env
check-env:
ifndef NORDIC_SDK_PATH
	$(error NORDIC_SDK_PATH is not defined.)
endif

.PHONY: flash
flash: check-env
ifneq ($(filter $(BOARD),$(SUPPORTED_BOARDS)),)
	$(MAKE) -C boards/$(BOARD)/s140/armgcc flash
else
	$(error Specified a board to flash)
endif

.PHONY: flash-softdevice
flash-softdevice: check-env
ifneq ($(filter $(BOARD),$(SUPPORTED_BOARDS)),)
	$(MAKE) -C boards/$(BOARD)/s140/armgcc flash-softdevice
else
	$(error Specified a board to flash the soft device to)
endif

.PHONY: erase
erase: check-env
ifneq ($(filter $(BOARD),$(SUPPORTED_BOARDS)),)
	$(MAKE) -C boards/$(BOARD)/s140/armgcc erase
else
	$(error Specified a board to flash)
endif

.PHONY: pca10059
pca10059: check-env
	$(MAKE) -C boards/pca10059/s140/armgcc

.PHONY: mdk-usb-dongle
mdk-usb-dongle: check-env
	$(MAKE) -C boards/mdk-usb-dongle/s140/armgcc

.PHONE: sparkfun-pro-mini
sparkfun-pro-mini: check-env
	$(MAKE) -C boards/sparkfun-pro-mini/s140/armgcc
