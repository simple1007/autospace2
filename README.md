# Requires
uv   
MSVC or g++   
cmake   
vcpkg   

# 의존성 설치
vcpkg install utfcpp   
vcpkg install rapidjson   
REQUIRED ADD ENVIREMENT VCPKG_ROOT   

# 빌드
```uv build --wheel --python <사용하고자하는 Python Version>   
example> 
uv build --wheel --python 3.13   
```