DEPENDS = board.o key.o layer.o tests/test_button.o button.o tests/test_reporter.o

%.o: %.c %.h
	g++ -c -I . $<

runtests: $(DEPENDS) tests/tests.cpp tests/minunit.h
	g++ -g $(DEPENDS) -I . tests/tests.cpp -o runtests

tests/test_reporter.o: tests/test_reporter.h tests/test_reporter.cpp reporter.h
	g++ -c -I . tests/test_reporter.cpp -o tests/test_reporter.o

tests/test_button.o: tests/test_button.h tests/test_button.cpp button.h
	g++ -c -I . tests/test_button.cpp -o tests/test_button.o

.PHONY: test
test: runtests
	./runtests

clean:
	rm -f runtests *.o tests/*.o
