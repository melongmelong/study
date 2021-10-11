PROG_OBJS=main.o op.o
PROG=main
TEST_OBJS=test/main.o op.o
TEST=test/main

all: $(PROG)

$(PROG) : $(TEST) $(PROG_OBJS)
	gcc -o $@ $(PROG_OBJS)

$(TEST) : $(TEST_OBJS)
	gcc -o $@ $(TEST_OBJS) /home/knw/Desktop/Study/git/study/TDD/Cunit/install/lib/libcunit.a
	$(TEST)

%.o:%.c
	gcc -I/home/knw/Desktop/Study/git/study/TDD/Cunit/install/include -o $@ -c $<

clean:
	rm -rf $(PROG_OBJS) $(PROG) $(TEST_OBJS) $(TEST)
