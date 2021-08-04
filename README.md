# lz-string-cpp
LZ-based compression algorithm implemented in C++

See original repo https://github.com/pieroxy/lz-string 

# basic usage
```cpp
std::string json = R"([{"foo":42},{"pi":3.14}])";

// NobwRAZg9lYFwBYBMBfANOADgS3gZgDoBGBFAXSA
std::string compressed = lzstring::compressToBase64(json);

// [{"foo":42},{"pi":3.14}]
std::string decompressed = lzstring::decompressFromBase64(compressed);
```
http://cpp.sh/2f5vf
