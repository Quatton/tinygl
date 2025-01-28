configure:
  cmake --preset default

build:
  cmake --build build --parallel 10 --config Debug

run:
  ./build/tinygl

clean:
  rm -rf build