# Requires
1. uv   
1. MSVC or g++   
1. cmake   
1. vcpkg   

# 의존성 설치
* REQUIRED ADD ENVIREMENT VCPKG_ROOT
```
vcpkg install utfcpp
vcpkg install rapidjson
```
   
# 빌드
```
uv build --wheel --python <사용하고자하는 Python Version>   
uv build --wheel --python 3.13   
```