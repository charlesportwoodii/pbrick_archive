GIT_VERSION = $(shell git describe --dirty --always --tags)

BOARD?=
BOARD_LIST:=$(sort $(subst /,,$(subst boards/,,$(dir $(wildcard boards/*/)))))

.PHONY: help
help:	## Lists all available commands and a brief description.
	@grep -E '^[a-zA-Z/_-]+:.*?## .*$$' $(MAKEFILE_LIST) | sort | awk 'BEGIN {FS = ":.*?## "}; {printf "\033[36m%-30s\033[0m %s\n", $$1, $$2}'

default: check-env 	## Builds PBrick
ifneq ($(filter $(BOARD),$(BOARD_LIST)),)
	$(MAKE) $(BOARD)
else
	$(error Run `make` with a board specified: ($(BOARD_LIST)))
endif

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
else
	@for board in $(BOARD_LIST); do \
		cd boards/$$board/s140 && $(MAKE) clean; \
		cd ../../..; \
	done
	@rm -f *.hex
endif

.PHONY: check-env
check-env:
ifndef NORDIC_SDK_PATH
	$(error NORDIC_SDK_PATH is not defined.)
endif

