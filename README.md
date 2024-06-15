# opcua_server
OPC-UA server implementation with Open62541

### Conan install

* Release
```bash
conan install . -b build --build=missing -s build_type=Release 
```

* Debug
```bash
conan install . -b build --build=missing -s build_type=Debug 
```

### CMake configure

* Release 

```bash
cmake -B build -G Ninja -DCMAKE_TOOLCHAIN_FILE="build/Release/generators/conan_toolchain.cmake" -DCMAKE_BUILD_TYPE=Release 
```

* Debug

```bash
cmake -B build -G Ninja -DCMAKE_TOOLCHAIN_FILE="build/Debug/generators/conan_toolchain.cmake" -DCMAKE_BUILD_TYPE=Debug 
```
### Build 

```bash
cmake --build build 
```

### Run
```bash
./opcua_server --host <hostname> --port <port>
```