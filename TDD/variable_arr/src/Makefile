OBJS=main.o arr.o
PROG=main

all: $(PROG)

$(PROG) : $(OBJS)
	gcc -o $@ $(OBJS)

clean:
	rm -rf $(OBJS) $(PROG)

.PHONY: all clean
