# [DP](https://ahfakt.github.io/DP/)

```shell
# Target system processor
SYSTEM_PROCESSOR=x64

# Debug, Release, RelWithDebInfo, MinSizeRel
BUILD_TYPE=Release

git clone https://github.com/ahfakt/DP.git

# Generate
mkdir build && cd DP
cmake \
    -B../build/${SYSTEM_PROCESSOR}/${BUILD_TYPE}/DP \
    -DCMAKE_BUILD_TYPE:STRING=${BUILD_TYPE} \
    -DCMAKE_CXX_STANDARD:STRING=20 \
    -G "Unix Makefiles"

# Build
# DPDoc
# Test targets are avaiable only when BUILD_TYPE=Debug
# Documentation is avaiable only when BUILD_TYPE=Release
cmake \
    --build ../build/${SYSTEM_PROCESSOR}/${BUILD_TYPE}/DP \
    --config ${BUILD_TYPE} \
    --target all
```
