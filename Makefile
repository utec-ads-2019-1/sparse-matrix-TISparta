run: FORCE
	g++ main.cpp tester/tester.cpp mocker/mocker.cpp -o test -O2

FORCE: ;

clean:
	rm test
