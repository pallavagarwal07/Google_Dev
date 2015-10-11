gl_2 : gl_2.cpp
	g++ -o $@ $< -lGL -lGLU -lglut
gl_test : gl_test.cpp
	g++ -o $@ $< -lGL -lGLU -lglut
multiple_window : multiple_window.cpp
	g++ -o $@ $< -lGL -lGLU -lglut
