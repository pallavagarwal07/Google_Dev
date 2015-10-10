hello : hello.cpp
	g++ -o $@ $< -lGL -lGLU -lglut
multiple_window : multiple_window.cpp
	g++ -o $@ $< -lGL -lGLU -lglut
