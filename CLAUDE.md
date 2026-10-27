# File Integrity Watcher (FileIntegrityWatcher)

Tray app (Windows in development; Linux and macOS planned) that keeps a
checksum list (standard `.md5` file) of the
files in the folders you choose (local and OneDrive) and alerts when files
are edited, silently change (likely corruption), go missing or are added.
Main use: confirm a PC rebuild + OneDrive restore brought back every file
intact, and catch accidental deletions over time. Not a security tool (MD5
is broken against tampering). See docs/ideas.md for design and decisions.

## Status (2026-10-27)
- Base repo only. `core/` has checksum line parse/format
  (`checksum_file.h`) and the change rules (`change.h`), unit-tested.
  `platforms/windows/` builds `fiwatcher.exe`, a placeholder that prints a
  version line. `platforms/linux/` and `platforms/macos/` are README-only.
- No hashing or scanning yet.

## Where to pick up
**Next: plan V1**: console `fiwatcher baseline <folder>` / `fiwatcher check
<folder>` (hash files, write the folder's `.md5` + companion file, report
changes; skip OneDrive cloud-only files). Then V2 (tray app), V3 (restore
check report). Steps in docs/plan.md. **Open items to discuss** (docs/ideas.md):
1 hash format (MD5 vs others), 2 tray app vs service, plus the companion
file and checksum file names.

## Layout
- `core/`: portable logic, no OS calls. Headers in `core/include/fiw/`.
- `platforms/windows/`: Windows code (hashing, scanning, tray app), builds
  `fiwatcher.exe`. `platforms/linux/`, `platforms/macos/`: future editions.
- `tests/core/`: doctest unit tests, one file per core module.
- `scripts/build.cmd [debug|release]`: finds VS, configures, builds, tests.
  Or open the folder in Visual Studio (uses CMakePresets.json). Output in
  `build/<preset>/`.
- `docs/plan.md` (steps V1–V3), `docs/ideas.md` (design source of truth),
  `docs/behavior.md` (user-facing behavior), `SECURITY.md`, `README.md`.

## Tooling
C++20, CMake, MSVC (Visual Studio Community 2026), static CRT (`/MT`),
`/W4 /WX`, doctest 2.5.3 (fetched at configure time with a pinned hash).
MD5 via Windows' own CNG (`bcrypt.dll`), so no third-party runtime
dependencies. App behavior for users is documented in docs/behavior.md;
keep it in sync.

## Licensing
GPLv3 (LICENSE). If a shipped third-party dependency is ever added (e.g. a
BLAKE3 library), ship a combined LICENSE.txt with one labeled section per
component. doctest is test-only and doesn't ship.

## Working agreements
- Don't commit without asking. Pushing to GitHub (origin/main) is fine when
  asked to commit and push.
- Commits use the GitHub noreply address
  (190971508+vroom57@users.noreply.github.com, set globally); never the
  personal address.
- docs/ideas.md is the source of truth for design; update it when decisions
  change. Record new discussion topics there as Open items.
- Never trigger downloads of OneDrive cloud-only files (skip them and warn
  that watched files must be kept on the device), and never modify watched
  files; the app only reads them and writes its own checksum files.
