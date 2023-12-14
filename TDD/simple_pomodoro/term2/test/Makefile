.PHONY: all clean

TOPDIR = $(CURDIR)/..

include $(TOPDIR)/Makefile.include

CUNIT_INCDIR = $(CURDIR)/CUnit/include
CUNIT_LIBDIR = $(CURDIR)/CUnit/lib
CUNIT_LIB = -lcunit

TARGET=main
OBJS=main.o

all: $(TARGET)
	LD_LIBRARY_PATH=$(CUNIT_LIBDIR) $(CURDIR)/$(TARGET)

%.o : %.c
	gcc -c $< -I$(CUNIT_INCDIR) -I$(SRC_INCDIR)

%.o : %.c %.h
	gcc -c $< -I$(CUNIT_INCDIR) -I$(SRC_INCDIR)

$(TARGET) : $(OBJS)
	gcc -o $@ $(OBJS) $(SRC_OBJS) -L$(CUNIT_LIBDIR) $(CUNIT_LIB)

clean:
	rm -rf $(OBJS) $(TARGET)
