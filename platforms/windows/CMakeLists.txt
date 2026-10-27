add_executable(fiwatcher
    main.cpp
)
target_compile_definitions(fiwatcher PRIVATE UNICODE _UNICODE)
target_link_libraries(fiwatcher PRIVATE
    fiw::core
    fiw_options
)
