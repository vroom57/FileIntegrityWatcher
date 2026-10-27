#pragma once

#include <cstdint>
#include <optional>
#include <string>

namespace fiw {

// How a file differs between the baseline and a scan. See "Change rules" in
// docs/ideas.md.

// What's known about one file at one point in time.
struct FileState {
    std::string hash;                     // Lowercase hex.
    std::optional<std::int64_t> modified; // Last-modified time, if known.
};

enum class Change {
    Unchanged,       // Same contents (the date may have changed).
    Edited,          // Contents and last-modified time both changed.
    SilentlyChanged, // Contents changed, last-modified time didn't: likely
                     // corruption.
    Changed,         // Contents changed; no dates to tell which kind.
    Missing,         // In the baseline, not on disk.
    Added,           // On disk, not in the baseline.
};

// Compares a file's baseline state with its scanned state. Returns nothing
// when the file is in neither.
std::optional<Change> classifyChange(const std::optional<FileState>& baseline,
                                     const std::optional<FileState>& scanned);

}  // namespace fiw
