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
    -G "Unix Makefiles"

# Build
# DPDoc
# Test targets are available only when BUILD_TYPE=Debug
# Documentation is available only when BUILD_TYPE=Release
cmake \
    --build ../build/${SYSTEM_PROCESSOR}/${BUILD_TYPE}/DP \
    --config ${BUILD_TYPE} \
    --target all
```
