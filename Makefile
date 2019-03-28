BOARD?=
SUPPORTED_BOARDS:=pca10059 mdk-usb-dongle sparkfun-pro-mini

comma:=, 
empty:=
space:= $(empty) $(empty)

default: check-env
ifneq ($(filter $(BOARD),$(SUPPORTED_BOARDS)),)
	$(MAKE) $(BOARD)
else
	$(error Run `make` with a board specified: ($(subst $(space),$(comma),$(SUPPORTED_BOARDS))))
endif

all: check-env $(SUPPORTED_BOARDS)

$(SUPPORTED_BOARDS):
	$(MAKE) -C boards/$@/s140/armgcc

clean: check-env
ifneq ($(filter $(BOARD),$(SUPPORTED_BOARDS)),)
	@cd boards/$(BOARD)/s140/armgcc && $(MAKE) $(BOARD)
	@rm pbrick/$(BOARD).hex
else
	@cd boards/pca10059/s140/armgcc && $(MAKE) clean
	@cd boards/mdk-usb-dongle/s140/armgcc && $(MAKE) clean
	@cd boards/sparkfun-pro-mini/s140/armgcc && $(MAKE) clean
	rm *.hex
endif

.PHONY: check-env
check-env:
ifndef NORDIC_SDK_PATH
	$(error NORDIC_SDK_PATH is not defined.)
endif

