configure:
  cmake --preset=default -DCMAKE_EXPORT_COMPILE_COMMANDS=1 .

build:
  cmake -B build -G Ninja -DCMAKE_BUILD_TYPE=Debug -DCMAKE_TOOLCHAIN_FILE=${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake .

run:
  ./build/tinygl

clean:
  rm -rf build