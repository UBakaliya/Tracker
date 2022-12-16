run:
	rm -f program.exe
	g++ -g -Wall -std=c++11 app.cpp -o program.exe
	./program.exe