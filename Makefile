default:
	g++ main.cpp -lraylib -lopengl32 -lgdi32 -lwinmm -Llib -Iinclude -o main

clean:
	rm -f main
