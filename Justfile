install:
  conan install . --build=missing

build:
  conan build . --settings build_type=Debug

run:
  ./build/Debug/tinygl

clean:
  rm -rf build