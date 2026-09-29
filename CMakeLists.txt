cmake_minimum_required(VERSION 3.20)
project(data_structures_2027 LANGUAGES C)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

include(CTest)

function(add_ds_test_executable target)
    add_executable(${target} ${ARGN})
    target_include_directories(${target} PRIVATE "${PROJECT_SOURCE_DIR}/tests")
    target_compile_features(${target} PRIVATE c_std_17)
    target_compile_options(${target} PRIVATE
            $<$<C_COMPILER_ID:AppleClang,Clang,GNU>:-Wall;-Wextra;-Wpedantic>
    )
endfunction()

function(add_ds_test_case target case_name)
    add_test(NAME "${target}.${case_name}"
            COMMAND "$<TARGET_FILE:${target}>" "${case_name}")
endfunction()

if(BUILD_TESTING)
    file(GLOB CHAPTER_DIRS CONFIGURE_DEPENDS LIST_DIRECTORIES true
            "${CMAKE_CURRENT_SOURCE_DIR}/chapters/*")
    foreach(CHAPTER_DIR IN LISTS CHAPTER_DIRS)
        if(EXISTS "${CHAPTER_DIR}/CMakeLists.txt")
            add_subdirectory("${CHAPTER_DIR}")
        endif()
    endforeach()
endif()
