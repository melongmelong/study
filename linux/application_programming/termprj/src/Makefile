.PHONY: all clean

TARGET=server

SRCS=server.c
OBJS=$(patsubst %.c,%.o,$(SRCS))

#for reference by test Makefile
$(shell echo SRC_INCDIR=$(CURDIR) 1>$(CURDIR)/../test/Makefile.include)
$(shell echo SRC_OBJS=$(addprefix $(CURDIR)/,$(OBJS)) 1>>$(CURDIR)/../test/Makefile.include)

all: $(TARGET)

clean:
	rm -rf $(OBJS) $(TARGET) $(CURDIR)/../test/Makefile.include

$(TARGET): $(OBJS)
	#gcc -o $@ $(OBJS)

%.o: %.h
%.o: %.c
	gcc -c $<
