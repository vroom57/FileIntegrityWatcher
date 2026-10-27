#include "fiw/change.h"

namespace fiw {

std::optional<Change> classifyChange(const std::optional<FileState>& baseline,
                                     const std::optional<FileState>& scanned) {
    if (!baseline && !scanned) {
        return std::nullopt;
    }
    if (!scanned) {
        return Change::Missing;
    }
    if (!baseline) {
        return Change::Added;
    }
    if (baseline->hash == scanned->hash) {
        return Change::Unchanged;
    }
    // Without both dates (e.g. the baseline came from a plain .md5 file),
    // an edit and corruption look the same.
    if (!baseline->modified || !scanned->modified) {
        return Change::Changed;
    }
    return *baseline->modified == *scanned->modified ? Change::SilentlyChanged
                                                     : Change::Edited;
}

}  // namespace fiw
