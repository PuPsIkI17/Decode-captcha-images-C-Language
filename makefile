build:main.c bmp_header.h
	gcc tema.c bmp_header.h -o project -Wall
run:project
	./project
clean:
	rm -rf project	
