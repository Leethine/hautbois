###__REPLACE_TEXT_TAG__###

ifndef INSTALLATION_PATH
INSTALLATION_PATH := /usr/local
endif

.PHONY: all test clean install uninstall

all :
	$(MAKE) -C src

test :
	$(MAKE) -C test

clean :
	$(MAKE) -C src clean
	$(MAKE) -C test clean

install : all
	mkdir -p $(INSTALLATION_PATH)/lib
	mkdir -p $(INSTALLATION_PATH)/bin
	cp src/libHb.a $(INSTALLATION_PATH)/lib
	cp src/engine/hb-preprocessor.bin $(INSTALLATION_PATH)/bin/hb-preprocessor

uninstall :
	rm -f $(INSTALLATION_PATH)/lib/libHb.a
	rm -f $(INSTALLATION_PATH)/bin/hb-preprocessor