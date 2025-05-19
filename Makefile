compile:
	gcc src/*.c test/*.c -g -Isrc -lffi -lm libraylib.so -Wl,-rpath=.
