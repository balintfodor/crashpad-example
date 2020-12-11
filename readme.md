#Crashpad-example

A simple crashpad example using conan to pull it as a dependency and sentry.io to push the minidumps to.

https://chromium.googlesource.com/crashpad/crashpad/+/master/README.md
https://conan.io/
https://sentry.io/

Create a sentry.io mindump project and replace the `url` variable in `hello.cpp` to your project's submit `url`.

#Build

```
mkdir build; cd build
conan remote add bincrafters https://api.bintray.com/conan/bincrafters/public-conan
conan install ..
cmake -DCMAKE_TOOLCHAIN_FILE=conan_paths.cmake -DCMAKE_INSTALL_PREFIX=$PWD ..
cmake --build .
cmake --install .

./bin/hellocrashpad
```
