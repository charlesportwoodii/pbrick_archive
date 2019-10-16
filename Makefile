BOARD ?=
BOARD_LIST := $(sort $(subst /,,$(subst boards/,,$(dir $(wildcard boards/*/)))))

rwildcard = $(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2) $(filter $(subst *,%,$2),$d))

default: check-env 	## Builds PBrick
ifneq ($(filter $(BOARD),$(BOARD_LIST)),)
	$(MAKE) -C boards/$(BOARD)/s140
else
	$(error Run `make` with a board specified: ($(BOARD_LIST)))
endif

.PHONY: help
help:	## Lists all available commands and a brief description.
	@grep -E '^[a-zA-Z/_-]+:.*?## .*$$' $(MAKEFILE_LIST) | sort | awk 'BEGIN {FS = ":.*?## "}; {printf "\033[36m%-30s\033[0m %s\n", $$1, $$2}'

all: check-env $(BOARD_LIST) ## Builds PBrick for all boards

$(BOARD_LIST): ## Builds PBrick for a specific board
	$(MAKE) -C boards/$@/s140

flash: default ## Builds and flashes PBrick via nrfjprog
	$(MAKE) flash -C boards/$(BOARD)/s140

clean_build: clean default ## Performs a clean build and generates a .zip DFU package
	$(MAKE) -C boards/$(BOARD)/s140 dfu_package

clean_flash: clean_build ## Performs a clean build and flashes a .zip DFU package
	$(MAKE) -C boards/$(BOARD)/s140 erase flash

usb_flash: check_port default ## Flash the specified firmware to PORT
	$(MAKE) -C boards/$(BOARD)/s140 usb_flash

clean: check-env ## Cleans the build environment
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