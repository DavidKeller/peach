include_directories(${CMAKE_SOURCE_DIR}/include)

add_library(
    peach
    SHARED

    config_reader.c
    set.c
    stack.c
    list.c
    config_reader_scanner.c
    config_reader_parser.c
    hash.c
    string.c
    log.c
    debug.c
    module.c
)

target_link_libraries(
    peach

    dl
)

install(
    TARGETS 

    peach

    LIBRARY DESTINATION lib
)
