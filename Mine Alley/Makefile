all: compile link

compile:
	g++ -g -c src/main.cpp src/Cinematic_Manager.cpp src/Exposition_Screen.cpp src/Platform_Map.cpp src/Animation_Manager.cpp src/Character.cpp src/Collision_Engine.cpp src/God_Class.cpp src/Generic_Map.cpp src/Play_Screen.cpp src/Drawable_Content.cpp src/Renderer.cpp src/Keyboard_IO.cpp

link:
	g++ main.o Cinematic_Manager.o Exposition_Screen.o  Animation_Manager.o Platform_Map.o God_Class.o Character.o Generic_Map.o Collision_Engine.o Play_Screen.o Drawable_Content.o Renderer.o Keyboard_IO.o -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system 
	rm *.o