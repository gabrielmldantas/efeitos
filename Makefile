all:
	g++ -std=c++11 -lopencv_highgui -lopencv_imgproc -lopencv_core effects.cpp main.cpp -o efeitos
clean:
	rm efeitos
