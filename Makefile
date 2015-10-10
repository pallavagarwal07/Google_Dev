hello : hello.cpp
	g++ -o $@ $< -lGL -lGLU -lglut
