all:
    gcc libcreate.c create_velocities.c -shared -fPIC -lwallaby -o libcreate.so

install:
    ln -sf $$PWD/libcreate.so /usr/lib/
    ln -sf $$PWD/include/*.h /usr/include/
