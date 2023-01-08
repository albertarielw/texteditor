texteditor: texteditor.o
	g++ texteditor.o -o texteditor

texteditor.o: texteditor.cpp
	g++ -c texteditor.cpp

clean:
	rm *.o texteditor