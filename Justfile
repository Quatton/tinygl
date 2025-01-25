configure:
  cmake --preset default

build: configure
  cmake --build build --parallel 10

run: build
  ./build/tinygl

clean:
  rm -rf build