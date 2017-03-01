if [[ `uname` == 'Linux' ]]; then
    cp ./gcc.js /harrogate/apps/compiler/compiler-environments/c/gcc.js
    make
    make install
else
    echo "Setup script only supported on Linux!"
fi
