# install packages
```
    cd /script/installation
    sudo bash packages.sh
```

# build

```
    mkdir build
    cmake -DCMAKE_BUILD_TYPE=Debug -DUSE_SANITIZER=Address -DCMAKE_CXX_FLAGS="-DLOG_LEVEL=LOG_LEVEL_INFO" ${peloton}
    make ycsb
```