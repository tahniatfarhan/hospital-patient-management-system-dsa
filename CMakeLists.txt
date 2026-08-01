cmake_minimum_required(VERSION 3.15)
project(HospitalPatientManagementDSA VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

# Strict Compiler Warnings Flag Configuration
if(MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Main Application Executable
add_executable(hospital_dsa src/main.cpp)

# Automated Test Suite Executable
add_executable(test_dsa tests/test_dsa.cpp)

enable_testing()
add_test(NAME dsa_unit_tests COMMAND test_dsa)
