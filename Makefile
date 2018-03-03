DEPENDS = board.o key.o layer.o

%.o: %.c %.h
	g++ -c -I . $<

runtests: $(DEPENDS) tests/tests.cc tests/minunit.h
	g++ -g $(DEPENDS) -I . tests/tests.cc -o runtests

clean:
	rm -f runtests *.o
