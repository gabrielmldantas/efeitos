all:
	g++ -lopencv_highgui -lopencv_core main.cpp -o efeitos
clean:
	rm efeitos
