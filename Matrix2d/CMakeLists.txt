cmake_minimum_required(VERSION 3.16)
project(zad2Matrix_dlaStudentow)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
if (NOT CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    set(CMAKE_CXX_FLAGS "--std=c++17 -Wall -Wextra -pedantic")
    set(COMPILER_DEBUG_FLAGS "-D_DEBUG")
    set(COMPILER_RELEASE_FLAGS "-O3 -DNDEBUG")
    set(LINKER_FLAGS "--std=c++17")
endif()

set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)  # for cppcheck To generate compile_commands.json

set(ENABLE_JSON_COMPILATION_OUTPUT_GCC OFF CACHE BOOL "Enable JSON output from GCC compiler")

if (CMAKE_COMPILER_IS_GNUCC AND ENABLE_JSON_COMPILATION_OUTPUT_GCC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fdiagnostics-format=json")
endif()


set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)


file(GLOB SOURCES *.cpp *.cc *.c)
file(GLOB HEADERS *.h *.hpp)
set(SOURCES_WITHOUT_MAIN ${SOURCES})
list(REMOVE_ITEM SOURCES_WITHOUT_MAIN ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)
message("Katalog do zbudowanego projektu: ${PROJECT_BINARY_DIR}")
message(" + Znaleziono nagłówki: ${HEADERS}")
message(" + Znaleziono źródła: ${SOURCES}")
message(" + Znaleziono źródła bez main.cpp: ${SOURCES_WITHOUT_MAIN}")


############ dodanie binarki z mainem i danymi studenta
add_executable(${PROJECT_NAME} ${HEADERS} ${SOURCES})


############ KOMENDA: make run
add_custom_target(run
    COMMAND ${PROJECT_NAME}
    DEPENDS ${PROJECT_NAME}
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)


############ KOMENDA: make valgrind_${PROJECT_NAME}
find_program(VALGRIND NAMES valgrind)
if (VALGRIND)
    message("\t* valgrind found: ${VALGRIND}")
    add_custom_target(valgrind_${PROJECT_NAME} DEPENDS ${PROJECT_NAME}
        COMMAND ${VALGRIND} --leak-check=full ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME})
endif()


############ KOMENDA: make docs
find_program(DOXYGEN NAMES doxygen)
if (DOXYGEN)
    message("\t* doxygen found: ${DOXYGEN}")
    add_custom_target(docs
            COMMAND ${DOXYGEN} ${CMAKE_CURRENT_SOURCE_DIR} && make -C ${CMAKE_CURRENT_SOURCE_DIR}/latex && cp latex/refman.pdf ${CMAKE_CURRENT_BINARY_DIR}/trescWygenerowana.pdf
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
endif()


############ KOMENDA: make zip
get_filename_component(directoryBasename ${CMAKE_CURRENT_SOURCE_DIR} NAME)
add_custom_target(zip
        COMMAND zip -r ${CMAKE_BINARY_DIR}/${directoryBasename}.zip ./
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})


############ KOMENDA: make format
#idealnym standardem dla C++ jest https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines, niestety nie jest on jeszcze wspierany przez narzędzie clang-format, dlatego używam innego popularnego stylu.
add_custom_target(format
        COMMAND clang-format -i -style=Google ${SOURCES})


############ dodanie podprojektu z testami:
add_subdirectory(tests)
