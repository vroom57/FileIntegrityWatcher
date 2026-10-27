#pragma once

#include <optional>
#include <string>
#include <string_view>

namespace fiw {

// Lines of a standard checksum file (.md5), as written by md5sum and read by
// MD5Summer and similar tools:
//   d41d8cd98f00b204e9800998ecf8427e *photos\2024\beach.jpg
// " *" marks binary mode, "  " (two spaces) text mode; both read the same.
// Strings are UTF-8.

struct ChecksumEntry {
    std::string hash;  // Lowercase hex.
    std::string path;  // Relative to the folder holding the checksum file.
};

// Parses one line. Returns nothing for blank lines, comments (starting with
// ';' or '#') and lines that aren't a hex hash followed by a path. A trailing
// '\r' is ignored. Hash length isn't checked, so other hash types parse too.
std::optional<ChecksumEntry> parseChecksumLine(std::string_view line);

// Formats an entry in binary mode ("<hash> *<path>"), without a line ending.
std::string formatChecksumLine(const ChecksumEntry& entry);

}  // namespace fiw
