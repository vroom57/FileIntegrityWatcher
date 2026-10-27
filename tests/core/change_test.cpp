#include <doctest/doctest.h>

#include "fiw/change.h"

using namespace fiw;

TEST_CASE("same contents is unchanged, even with a new date") {
    CHECK(classifyChange(FileState{"aa", 100}, FileState{"aa", 100}) ==
          Change::Unchanged);
    CHECK(classifyChange(FileState{"aa", 100}, FileState{"aa", 200}) ==
          Change::Unchanged);
}

TEST_CASE("new contents with a new date is an edit") {
    CHECK(classifyChange(FileState{"aa", 100}, FileState{"bb", 200}) ==
          Change::Edited);
}

TEST_CASE("new contents with the same date is a silent change") {
    CHECK(classifyChange(FileState{"aa", 100}, FileState{"bb", 100}) ==
          Change::SilentlyChanged);
}

TEST_CASE("new contents without dates can't be told apart") {
    CHECK(classifyChange(FileState{"aa", std::nullopt}, FileState{"bb", 100}) ==
          Change::Changed);
    CHECK(classifyChange(FileState{"aa", 100}, FileState{"bb", std::nullopt}) ==
          Change::Changed);
}

TEST_CASE("missing and added files") {
    CHECK(classifyChange(FileState{"aa", 100}, std::nullopt) == Change::Missing);
    CHECK(classifyChange(std::nullopt, FileState{"aa", 100}) == Change::Added);
    CHECK_FALSE(classifyChange(std::nullopt, std::nullopt));
}
