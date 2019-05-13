include_directories(include)


file(GLOB CLIENT_SRCS
        "src/*.cpp"
        )

file(GLOB CLIENT_HDRS
        "include/*.h"
        )


add_executable(client main.cpp ${CLIENT_SRCS} ${CLIENT_HDRS})
target_link_libraries(client pthread)
