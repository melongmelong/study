.PHONY: all clean

SERVER_TARGET=server
CLIENT_TARGET=client

#expose obj for external use(ex. testcase)
SRCS=server.c client.c
OBJS=$(patsubst %.c,%.o,$(SRCS))

#only internal obj not to be seen to external(ex. testcase)
_SERVER_SRCS=server_main.c
_SERVER_OBJS=$(patsubst %.c,%.o,$(_SERVER_SRCS))

_CLIENT_SRCS=client_main.c
_CLIENT_OBJS=$(patsubst %.c,%.o,$(_CLIENT_SRCS))


#for reference by test Makefile
$(shell echo SRC_INCDIR=$(CURDIR) 1>$(CURDIR)/../test/Makefile.include)
$(shell echo SRC_OBJS=$(addprefix $(CURDIR)/,$(OBJS)) 1>>$(CURDIR)/../test/Makefile.include)

all: $(SERVER_TARGET) $(CLIENT_TARGET)

clean:
	rm -rf $(OBJS) $(_OBJS) $(SERVER_TARGET) $(CLIENT_TARGET) $(_SERVER_OBJS) $(_CLIENT_OBJS) $(CURDIR)/../test/Makefile.include

$(SERVER_TARGET): $(OBJS) $(_SERVER_OBJS)
	gcc -o $@ $(OBJS) $(_SERVER_OBJS)

$(CLIENT_TARGET): $(OBJS) $(_CLIENT_OBJS)
	gcc -o $@ $(OBJS) $(_CLIENT_OBJS)


%.o: %.h
%.o: %.c
	gcc -c $<
