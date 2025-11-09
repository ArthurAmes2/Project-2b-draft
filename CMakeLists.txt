cmake_minimum_required(VERSION 3.8)
project(Project_2b_draft)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(externals/SFML)

add_executable(Project_2b_draft
        main.cpp
        DataLoader.cpp
        DataLoader.h
        Graph.cpp
        Graph.h
        BPlusTree.cpp
        BPlusTree.h
)
#using SFML version 2.5.1 referenced from COP3530C
target_link_libraries(Project_2b_draft PRIVATE sfml-graphics sfml-window sfml-system)

if(WIN32 AND BUILD_SHARED_LIBS)
    add_custom_command(TARGET Project_2b_draft POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:sfml-graphics> $<TARGET_FILE_DIR:Project_2b_draft>
            COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:sfml-window> $<TARGET_FILE_DIR:Project_2b_draft>
            COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:sfml-system> $<TARGET_FILE_DIR:Project_2b_draft>
    )
endif()