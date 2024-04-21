project(tests)

# 'lib' is the folder with Google Test sources
add_subdirectory(lib)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})


file(GLOB TEST_SOURCES *.cpp *.cc *.c)
message(" + Znaleziono pliki testów: ${TEST_SOURCES}")
message(" + katalog nagłówków: ${INCLUDE_DIRECTORY}")

add_executable(${PROJECT_NAME} ${TEST_SOURCES} ${SOURCES_WITHOUT_MAIN})
target_link_libraries(${PROJECT_NAME} gtest gtest_main)


############ KOMENDA: make run_tests
add_custom_target(run_${PROJECT_NAME}
    COMMAND ${PROJECT_NAME}
    DEPENDS ${PROJECT_NAME}
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)

############ KOMENDA: make valgrind_tests
find_program(VALGRIND NAMES valgrind)
if (VALGRIND)
    add_custom_target(valgrind_${PROJECT_NAME} DEPENDS ${PROJECT_NAME}
        COMMAND valgrind --leak-check=full ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME}
        WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
endif()

############ KOMENDA: make cppcheck_tests
find_program(CPPCHECK NAMES cppcheck)
if (CPPCHECK)
    add_custom_target(cppcheck_${PROJECT_NAME} DEPENDS ${PROJECT_NAME}
        COMMAND cppcheck --project=${CMAKE_BINARY_DIR}/compile_commands.json --force --enable=warning,performance,unusedFunction,style,information --template=gcc --inline-suppr --library=gnu.cfg --library=std.cfg --library=cppcheck-lib.cfg --library=motif.cfg --library=qt.cfg --library=windows.cfg --library=gnu.cfg --library=posix.cfg --library=avr.cfg --suppress=missingIncludeSystem -i   ${TEST_SOURCES} -i ${CMAKE_CURRENT_SOURCE_DIR}
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
endif()
