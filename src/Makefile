SUBDIRS := note synth

.PHONY: all clean $(SUBDIRS)

TARGET := libHb.a

all : $(SUBDIRS)
	ar cr $(TARGET) $(shell find ./ -name '*.o')

$(SUBDIRS) :
	$(MAKE) -C $@

$(TARGET) : $(SUBDIRS)
	ar cr $(TARGET) $(OBJS)

clean :
	for dir in $(SUBDIRS); do \
		$(MAKE) -C $$dir clean; \
	done
	rm -f *.a
