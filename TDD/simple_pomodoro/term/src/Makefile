.PHONY: all clean include

TOPDIR=$(CURDIR)/..

TARGET=main
EXOBJS=input.o
INOBJS=main.o
OBJS=$(EXOBJS) $(INOBJS)
INCLUDE=$(TOPDIR)/Makefile.include

all: $(TARGET) include

$(TARGET): $(OBJS)
	gcc -o $@ $?

%.o : %.c
	gcc -c $<

%.o : %.c %.h
	gcc -c $<

include:
	echo "SRC_INCDIR=$(CURDIR)" 1>>$(INCLUDE)
	echo "SRC_OBJDIR=$(CURDIR)" 1>>$(INCLUDE)
	echo "SRC_OBJS=$(addprefix $(CURDIR)/, $(EXOBJS))" 1>>$(INCLUDE)

clean:
	rm -rf $(OBJS) $(TARGET) $(INCLUDE)
