SRC := $(wildcard *.c)

all:
	gcc $(SRC) -shared -fPIC -lwallaby -o libbotball.so

install:
	ln -sf $$PWD/libbotball.so /usr/lib/
	ln -sf $$PWD/include/*.h /usr/include/
