BOARD?=

.PHONY: pca10059

default:
ifeq ($(BOARD), pca10059)
	$(MAKE) pca10059
else
	$(MAKE) pca10059
endif

clean:
ifeq ($(BOARD), pca10059)
	cd pca10059/s140/armgcc && $(MAKE) clean
else
	cd pca10059/s140/armgcc && $(MAKE) clean
endif

pca10059:
	$(MAKE) -C pca10059/s140/armgcc