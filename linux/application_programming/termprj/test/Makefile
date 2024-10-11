.PHONY: all clean

CUNIT_INCDIR=$(CURDIR)/lib/CUnit/include
CUNIT_LIBDIR=$(CURDIR)/lib/CUnit/lib
CUNIT_LIB=-lcunit

-include Makefile.include #made by Makefile in src

TARGET=main

SRCS=main.c
OBJS=$(patsubst %.c,%.o,$(SRCS))

all: $(TARGET)
	LD_LIBRARY_PATH=$(CUNIT_LIBDIR) $(CURDIR)/$(TARGET)

clean:
	rm -rf $(CURDIR)/$(OBJS) $(CURDIR)/$(TARGET)

$(TARGET): $(OBJS)
	gcc -o $@ $(OBJS) $(SRC_OBJS) -L$(CUNIT_LIBDIR) $(CUNIT_LIB)

%.o: %.h
%.o: %.c
	gcc -c $< -I$(CUNIT_INCDIR) -I$(SRC_INCDIR)
