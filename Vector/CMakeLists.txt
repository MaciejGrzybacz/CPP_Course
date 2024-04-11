cmake_minimum_required(VERSION 3.16)
project(zad3SimpleVector)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    include(CheckCXXCompilerFlag)
    CHECK_CXX_COMPILER_FLAG("/std:c++latest" _cpp_latest_flag_supported)
    if (_cpp_latest_flag_supported)
        add_compile_options("/std:c++latest")
    endif()
else()
    set(CMAKE_CXX_FLAGS "--std=c++23 -Wall -Wextra -pedantic")
    set(COMPILER_DEBUG_FLAGS "-D_DEBUG")
    set(COMPILER_RELEASE_FLAGS "-O3 -DNDEBUG")
    set(LINKER_FLAGS "--std=c++23")
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
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/README.md")
   add_executable(${PROJECT_NAME} ${HEADERS} ${SOURCES} "${CMAKE_CURRENT_SOURCE_DIR}/README.md")
else()
   add_executable(${PROJECT_NAME} ${HEADERS} ${SOURCES})
endif()


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

############ KOMENDA: make ctags
add_custom_target(ctags
        COMMAND ctags -x --c++-types=f --extras --format=1 ${HEADERS} ${SOURCES_WITHOUT_MAIN})

############ KOMENDA: make cppcheck_${PROJECT_NAME}
find_program(CPPCHECK NAMES cppcheck)
if (CPPCHECK)
    message("\t* cppcheck found: ${CPPCHECK}")
    add_custom_target(cppcheck_${PROJECT_NAME} DEPENDS ${PROJECT_NAME}
        COMMAND cppcheck --project=${CMAKE_BINARY_DIR}/compile_commands.json --force --enable=warning,performance,unusedFunction,style,information --template=gcc --inline-suppr --library=gnu.cfg --library=std.cfg --library=cppcheck-lib.cfg --library=motif.cfg --library=qt.cfg --library=windows.cfg --library=gnu.cfg --library=posix.cfg --library=avr.cfg --suppress=missingIncludeSystem -i ${HEADERS} ${SOURCES_WITHOUT_TESTS} -i ${CMAKE_CURRENT_SOURCE_DIR}
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
endif()

############ dodanie podprojektu z testami:
add_subdirectory(tests)
