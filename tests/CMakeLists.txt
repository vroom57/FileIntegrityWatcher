include(FetchContent)

# doctest is test-only and doesn't ship.
set(DOCTEST_NO_INSTALL ON)
FetchContent_Declare(doctest
    URL https://github.com/doctest/doctest/archive/refs/tags/v2.5.3.tar.gz
    URL_HASH SHA256=174ebc4e769928959614789c5b4e9c3d0a0f81a62bb608756b127bfebfb21331
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
FetchContent_MakeAvailable(doctest)

add_executable(core_tests
    core/change_test.cpp
    core/checksum_file_test.cpp
)
target_link_libraries(core_tests PRIVATE
    fiw::core
    doctest::doctest_with_main
    fiw_options
)

add_test(NAME core_tests COMMAND core_tests)
