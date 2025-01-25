install:
  conan install . --build=missing --settings build_type=Debug

build:
  conan build . --settings build_type=Debug

run:
  ./build/Debug/tinygl

clean:
  rm -rf build