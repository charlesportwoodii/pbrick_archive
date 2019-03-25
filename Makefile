BOARD?=

default: check-env
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
	cd pca10059/s140/armgcc && $(MAKE) clean
endif
ifeq ($(BOARD), mdk-usb-dongle)
	cd mdk-usb-dongle/s140/armgcc && $(MAKE) clean
endif
ifeq ($(BOARD), sparkfun-pro-mini)
	cd sparkfun-pro-mini/s140/armgcc && $(MAKE) clean
endif
#cd pca10059/s140/armgcc && $(MAKE) clean
#cd mdk-usb-dongle/s140/armgcc && $(MAKE) clean
#cd sparkfun-pro-mini/s140/armgcc && $(MAKE) clean

.PHONY: check-env
check-env:
ifndef NORDIC_SDK_PATH
	$(error NORDIC_SDK_PATH is not defined.)
endif

.PHONY: pca10059
pca10059: check-env
	$(MAKE) -C pca10059/s140/armgcc

.PHONY: mdk-usb-dongle
mdk-usb-dongle: check-env
	$(MAKE) -C mdk-usb-dongle/s140/armgcc

.PHONE: sparkfun-pro-mini
sparkfun-pro-mini: check-env
	$(MAKE) -C sparkfun-pro-mini/s140/armgcc