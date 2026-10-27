# File Integrity Watcher Plan

The order of work and when each step counts as done. Design decisions live
in [ideas.md](ideas.md), user-facing behavior in [behavior.md](behavior.md).
Update this file as steps finish or the direction changes.

## Goal

A tray app that keeps a checksum list of the files in each folder
you choose (local folders and OneDrive), checks them in the background, and
alerts when files are edited, silently change, go missing or are added.
Its main job is to confirm that a PC rebuild and restore brought back every
file intact, and to catch files lost or damaged over time.

Steps V1–V3 are for the **Windows** edition (`platforms/windows/`). Linux
and macOS editions come after, building on the same `core/`.

## V0: Base repo (done 2026-10-27)

- CMake / MSVC build, doctest unit tests, `core/` and `platforms/` layout
  (Windows in development; Linux and macOS placeholders), docs.
- `core/`: checksum file line parse / format, change rules.

## V1: Baseline and check (console)

Settle open items 1 (hash format) and 3 (companion file) first.

- `fiwatcher baseline <folder>`: hash every file in the folder and its
  subfolders, write the folder's checksum file and companion file.
- `fiwatcher check <folder>`: scan again and print what was edited,
  silently changed, missing or added.
- Hash with Windows' own CNG (`bcrypt.dll`); read files without changing
  their last-access time where possible.
- Skip OneDrive cloud-only files (placeholders) without downloading them;
  list them as skipped, with a clear warning that watched files must be
  kept on this device (**Always keep on this device**).

**Done when:** on a test folder, the checksum file verifies in MD5Summer
and `md5sum -c`, and `check` correctly reports a test edit, a silent
change (contents changed, date put back), a deletion and a new file; and
a OneDrive folder with online-only files gets the warning without any
download.

## V2: Tray app

Settle open item 2 (tray app or service) first.

- Tray icon that starts at sign-in, with a list of watched folders.
- Background scans at low disk and CPU priority, spread over time (some
  files each day), paused on battery or when you're busy.
- Windows notifications for changes; a window listing them, where you can
  accept an edit (update the baseline) or mark a file as a problem.

**Done when:** it runs on your own PCs for a couple of weeks, watching a
local folder and OneDrive, with alerts you find useful rather than noisy.

## V3: Restore check

- A "check this restore" action: compare a restored folder against its
  checksum file and show a clear report (everything OK, or the exact list
  of missing and damaged files).
- Works for a folder restored on a new PC, with the checksum file that came
  back with it, or with an exported copy.
- Never reports a restore as OK while files are still cloud-only; tells you
  to set **Always keep on this device** and wait for OneDrive to finish.

**Done when:** it confirms a real OneDrive restore on a rebuilt or second
PC.
