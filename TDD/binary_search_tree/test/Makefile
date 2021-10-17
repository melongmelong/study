OBJS=../src/bst.o
TEST_OBJS=main.o
TEST=main

all: $(TEST)

$(TEST): $(TEST_OBJS) $(OBJS)
	gcc -o $@ $(TEST_OBJS) $(OBJS) /home/knw/Desktop/Study/git/study/TDD/Cunit/install/lib/libcunit.a
	./$(TEST); RET=`./$(TEST) | grep -c 'FAILED'`; if [ $$RET -ne 0 ]; then exit 1; fi

%.o: %.c
	gcc -I/home/knw/Desktop/Study/git/study/TDD/Cunit/install/include -o $@ -c $<

clean:
	rm -rf $(TEST) $(TEST_OBJS)

.PHONY: all clean
