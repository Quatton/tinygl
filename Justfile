configure:
  cmake --preset default

build: configure
  cmake --build build --parallel 10 --config Debug

run: build
  ./build/tinygl

clean:
  rm -rf build