all:
	gcc main.cpp -o binde

install:
	sudo cp ./binde /usr/bin/binde
