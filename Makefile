all:
	g++ -std=c++11 -lopencv_highgui -lopencv_imgproc -lopencv_core effects.cpp main.cpp -o efeitos_bsg
	g++ -std=c++11 -lopencv_highgui -lopencv_imgproc -lopencv_core effects.cpp teatro.cpp -o efeitos_teatro
clean:
	rm efeitos
