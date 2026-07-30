SUBDIRS := note

.PHONY: all clean test $(SUBDIRS)

BINARY := $(shell find ./ -name 'bin_*')

all : $(SUBDIRS)

$(SUBDIRS) :
	$(MAKE) -C $@

test :
	for test_case in $(BINARY); do \
		$$test_case ;                \
		valgrind $$test_case ;       \
	done

clean :
	for dir in $(SUBDIRS); do \
		$(MAKE) -C $$dir clean; \
	done
