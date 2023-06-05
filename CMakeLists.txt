cmake_minimum_required(VERSION 3.25)
project(KairosConsole)

set(CMAKE_CXX_STANDARD 20)

include_directories(include)

set(CMAKE_CXX_FLAGS "-lcurl")

add_executable(KairosConsole
        include/Dto/Security/ActivateDto.h
        include/Dto/Security/BaseSecurityDto.h
        include/Dto/Security/ChangePasswordDto.h
        include/Dto/Security/LoginDto.h
        include/Response/BaseResponse.h
        include/Network/ApiHandler.h
        src/Dto/Security/ActivateDto.cpp
        src/Dto/Security/BaseSecurityDto.cpp
        src/Dto/Security/ChangePasswordDto.cpp
        src/Dto/Security/LoginDto.cpp
        src/Network/ApiHandler.cpp
        include/Network/HTTPConstants.h
        include/Network/Helper/json.hpp
        src/Response/BaseResponse.cpp
        main.cpp
        include/Dto/BaseDto.h src/Dto/BaseDto.cpp src/Network/Helper/UriBuilder.cpp include/Network/Helper/UriBuilder.h)