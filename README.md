# prerequisites
mingw-w64 (i686-8.1.0-posix-dwarf-rt_v6-rev0) **on PATH**

# FiveInRow Server

## build
```
cd FiveInRowServer
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release -G "CodeBlocks - MinGW Makefiles" ..
cmake --build . --target FiveInRowServer -- -j 8
```

## test
```
cd build
cmake --build . --target TestRun -- -j 8
cd bin 
./TestRun.exe 
```

to generate XML/JSON report:

```
cd bin 
./TestRun.exe --gtest_output [xml|json]
```


## run
```
cd build/bin
./server.exe
```
Default port 8888 can be changed:
```
./server.exe <YOUR_PORT>
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

## run

```
cd build/bin
./client.exe
```
Default server uri 127.0.0.1:8888 can be changed:
```
./client.exe <ip_address>:<port>
```

# Limitations
- windows only
- single threaded
