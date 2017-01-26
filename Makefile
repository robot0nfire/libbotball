all:
	gcc libbotball.c libcreate.c create_velocities.c -shared -fPIC -lwallaby -o libbotball.so

install:
	ln -sf $$PWD/libbotball.so /usr/lib/
	ln -sf $$PWD/include/*.h /usr/include/
