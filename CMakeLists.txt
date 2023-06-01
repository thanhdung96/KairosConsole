cmake_minimum_required(VERSION 3.25)
project(KairosConsole)

set(CMAKE_CXX_STANDARD 20)

include_directories(include)
include_directories(include/Dto)
include_directories(include/Dto/Security)
include_directories(include/Response)

add_executable(KairosConsole
        include/Dto/Security/ActivateDto.h
        include/Dto/Security/BaseSecurityDto.h
        include/Dto/Security/ChangePasswordDto.h
        include/Dto/Security/LoginDto.h
        include/Response/BaseResponse.h
        src/Dto/Security/ActivateDto.cpp
        src/Dto/Security/BaseSecurityDto.cpp
        src/Dto/Security/ChangePasswordDto.cpp
        src/Dto/Security/LoginDto.cpp
        src/Response/BaseResponse.cpp
        main.cpp)
