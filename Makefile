all:
	gcc -c src/main.c -o target/obj/main.o
	gcc -c src/stalk.c -o target/obj/stalk.o
	gcc -o target/bin/stalk target/obj/main.o target/obj/stalk.o
