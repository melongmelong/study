.PHONY: all clean

TARGET=server

#expose obj for external use(ex. testcase)
SRCS=server.c client.c
OBJS=$(patsubst %.c,%.o,$(SRCS))

#only internal obj not to be seen to external(ex. testcase)
_SRCS=server_main.c
_OBJS=$(patsubst %.c,%.o,$(_SRCS))

#for reference by test Makefile
$(shell echo SRC_INCDIR=$(CURDIR) 1>$(CURDIR)/../test/Makefile.include)
$(shell echo SRC_OBJS=$(addprefix $(CURDIR)/,$(OBJS)) 1>>$(CURDIR)/../test/Makefile.include)

all: $(TARGET)

clean:
	rm -rf $(OBJS) $(_OBJS) $(TARGET) $(CURDIR)/../test/Makefile.include

$(TARGET): $(OBJS) $(_OBJS)
	gcc -o $@ $(OBJS) $(_OBJS)

%.o: %.h
%.o: %.c
	gcc -c $<
