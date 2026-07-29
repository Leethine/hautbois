SUBDIRS := note symbol

.PHONY: all clean $(SUBDIRS)

TARGET := libHb.a
OBJS := $(shell find ./ -name '*.o')

all : $(TARGET)

$(TARGET) : $(SUBDIRS)
	ar cr $(TARGET) $(OBJS)

$(SUBDIRS) :
	$(MAKE) -C $@

clean :
	for dir in $(SUBDIRS); do \
		$(MAKE) -C $$dir clean; \
	done
