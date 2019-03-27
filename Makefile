BOARD?=

default: check-env
ifeq ($(BOARD),)
	$(error Specified a board to build pca10059, mdk-usb-dongle, sparkfun-pro-mini)
endif
ifeq ($(BOARD), pca10059)
	$(MAKE) pca10059
endif
ifeq ($(BOARD), mdk-usb-dongle)
	$(MAKE) mdk-usb-dongle
endif
ifeq ($(BOARD), sparkfun-pro-mini)
	$(MAKE) sparkfun-pro-mini
endif

clean: check-env
ifeq ($(BOARD), pca10059)
	cd boards/pca10059/s140/armgcc && $(MAKE) clean
endif
ifeq ($(BOARD), mdk-usb-dongle)
	cd boards/mdk-usb-dongle/s140/armgcc && $(MAKE) clean
endif
ifeq ($(BOARD), sparkfun-pro-mini)
	cd boards/sparkfun-pro-mini/s140/armgcc && $(MAKE) clean
endif

ifeq $(BOARD,)
	cd boards/pca10059/s140/armgcc && $(MAKE) clean
	cd boards/mdk-usb-dongle/s140/armgcc && $(MAKE) clean
	cd boards/sparkfun-pro-mini/s140/armgcc && $(MAKE) clean
endif

.PHONY: check-env
check-env:
ifndef NORDIC_SDK_PATH
	$(error NORDIC_SDK_PATH is not defined.)
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