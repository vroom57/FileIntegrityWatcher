add_library(fiw_core STATIC
    src/change.cpp
    src/checksum_file.cpp
)
add_library(fiw::core ALIAS fiw_core)

target_include_directories(fiw_core PUBLIC include)
target_link_libraries(fiw_core PRIVATE fiw_options)
