# FiveInRow Server
## prerequisites
mingw-w64 (i686-8.1.0-posix-dwarf-rt_v6-rev0) on PATH

## build
```
cd FiveInRow
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release -G "CodeBlocks - MinGW Makefiles" ..
cmake --build . --target FiveInRowServer -- -j 8
cmake --build . --target TestRun -- -j 8
```

# FiveInRow Client
## build
```
cd FiveInRowClient
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release -G "CodeBlocks - MinGW Makefiles" ..
cmake --build . --target FiveInRowClient -- -j 8
```

# Limitations
- windows only
- missing implementation of win conditions (failing unit tests)
- missing many unit tests
- single threaded
