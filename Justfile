install:
  conan install . --output-folder=build --build=missing

build:
  conan build .