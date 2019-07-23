BOARD ?=
BOARD_LIST := $(sort $(subst /,,$(subst boards/,,$(dir $(wildcard boards/*/)))))

rwildcard = $(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2) $(filter $(subst *,%,$2),$d))

default: check-env
ifneq ($(filter $(BOARD),$(BOARD_LIST)),)
	$(MAKE) -C boards/$(BOARD)/s140
else
	$(error Run `make` with a board specified: ($(BOARD_LIST)))
endif

all: check-env $(BOARD_LIST)

$(BOARD_LIST):
	$(MAKE) -C boards/$@/s140

flash: default
	$(MAKE) flash -C boards/$(BOARD)/s140

clean_build: clean
	$(MAKE) -C boards/$(BOARD)/s140 dfu_package

clean_flash: clean_build
	$(MAKE) -C boards/$(BOARD)/s140 erase flash

usb_flash: check_port default
	$(MAKE) -C boards/$(BOARD)/s140 usb_flash

check_port:
ifndef PORT
	$(error PORT must be defined to perform usb serial flashing)
endif

clean: check-env
ifneq ($(filter $(BOARD),$(BOARD_LIST)),)
	@cd boards/$(BOARD)/s140 && $(MAKE) clean
	@rm -rf $(BOARD).hex
	@rm -f $(BOARD).zip
	@rm -f debug_$(BOARD).zip
else
	@for board in $(BOARD_LIST); do \
		cd boards/$$board/s140 && $(MAKE) clean; \
		cd ../../..; \
	done
	@rm -f *.hex
	@rm -f *.zip
endif

.PHONY: check-env
check-env:
ifndef NORDIC_SDK_PATH
	$(error NORDIC_SDK_PATH is not defined.)
endif