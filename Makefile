CFLAGS :=

SRC := $(wildcard src/*.c)

all:
	gcc $(CFLAGS) $(SRC) -Iinclude/ -shared -fPIC -lwallaby -o libbotball.so

install:
	ln -sf $$PWD/libbotball.so /usr/lib/
	ln -sf $$PWD/include/*.h /usr/include/
