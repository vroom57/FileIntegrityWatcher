#include "fiw/checksum_file.h"

namespace fiw {

namespace {

bool isHexDigit(char c) {
    return (c >= '0' && c <= '9') || (c >= 'a' && c <= 'f') ||
           (c >= 'A' && c <= 'F');
}

char toLower(char c) {
    return (c >= 'A' && c <= 'Z') ? static_cast<char>(c - 'A' + 'a') : c;
}

}  // namespace

std::optional<ChecksumEntry> parseChecksumLine(std::string_view line) {
    if (!line.empty() && line.back() == '\r') {
        line.remove_suffix(1);
    }
    if (line.empty() || line.front() == ';' || line.front() == '#') {
        return std::nullopt;
    }

    std::size_t hash_end = 0;
    while (hash_end < line.size() && isHexDigit(line[hash_end])) {
        ++hash_end;
    }
    // Hash, a space, a mode character (' ' or '*'), then at least one
    // character of path.
    if (hash_end == 0 || hash_end + 2 >= line.size() || line[hash_end] != ' ' ||
        (line[hash_end + 1] != ' ' && line[hash_end + 1] != '*')) {
        return std::nullopt;
    }

    ChecksumEntry entry;
    for (char c : line.substr(0, hash_end)) {
        entry.hash += toLower(c);
    }
    entry.path = line.substr(hash_end + 2);
    return entry;
}

std::string formatChecksumLine(const ChecksumEntry& entry) {
    return entry.hash + " *" + entry.path;
}

}  // namespace fiw
