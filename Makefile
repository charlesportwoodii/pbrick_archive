GIT_VERSION = $(shell git describe --dirty --always --tags)

BOARD?=
BOARD_LIST:=$(sort $(subst /,,$(subst boards/,,$(dir $(wildcard boards/*/)))))

default: check-env
ifneq ($(filter $(BOARD),$(BOARD_LIST)),)
	$(MAKE) $(BOARD)
else
	$(error Run `make` with a board specified: ($(BOARD_LIST)))
endif

all: check-env $(BOARD_LIST)

$(BOARD_LIST):
	$(MAKE) -C boards/$@/s140

flash:
ifneq ($(filter $(BOARD),$(BOARD_LIST)),)
	$(MAKE) bootload -C boards/$(BOARD)/s140
else
	$(error Run `make` with a board specified: ($(BOARD_LIST)))
endif

clean: check-env
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

