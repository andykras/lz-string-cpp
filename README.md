# lz-string-cpp
LZ-based compression algorithm implemented in C++

See original repo https://github.com/pieroxy/lz-string 

# basic usage
```cpp
std::string json = R"([{"n":"ps1.active","q":1,"t":1474356144455,"v":21}])";
std::string compressed = lzstring::compressToBase64(json);
```
http://cpp.sh/6a6h7
