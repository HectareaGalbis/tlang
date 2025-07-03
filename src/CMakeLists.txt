

find_package(pegtl REQUIRED)

add_executable(tlang main.cpp environment.cpp procedure.cpp linenoise.c special_operator.cpp package.cpp objects.cpp)

target_link_libraries(tlang)
