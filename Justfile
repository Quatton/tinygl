configure:
  cmake --preset=default

build:
  cmake -B build -G Ninja -DCMAKE_BUILD_TYPE=Debug -DCMAKE_TOOLCHAIN_FILE=${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake .

run:
  ./build/tinygl

clean:
  rm -rf build