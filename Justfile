build:
  cmake --preset default -B build -S .

run:
  ./build/tinygl

clean:
  rm -rf build