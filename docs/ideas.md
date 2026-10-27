# File Integrity Watcher: ideas and decisions

Working notes, design decisions and open items. This file is the source of
truth for design; update it when decisions change. Steps are in
[plan.md](plan.md).

## What it is

A tray app (Windows first; Linux and macOS later) that keeps a checksum list of the files in the folders
you choose and tells you when files change, go missing or get corrupted.
Something like Tripwire, but small and for your own files: documents,
photos and other files that shouldn't change often.

Uses:

- **Checking a restore.** You keep everything in OneDrive (or another
  backup), rebuild your PC and restore. The checksum list came back with
  the files, so the app can confirm every file is there and intact.
- **Catching losses over time.** Files deleted by accident, lost in a sync
  conflict, or damaged.
- **Catching silent corruption** ("bit rot"): contents that change without
  anyone editing them.
- Edits aren't wrong, but you get a heads-up, so a change you didn't make
  stands out.

It only reads your files and reports. It doesn't repair or restore them.

## Decisions

- **2026-10-27: name.** "File Integrity Watcher" (repo
  `FileIntegrityWatcher`, exe `fiwatcher.exe`, code namespace `fiw`).
  "Watcher" suggests many files watched over time. "File integrity" is also
  a corporate security term (file integrity monitoring); the README's
  tagline and limitations make clear this is for accidents, not attackers.
- **2026-10-27: watched locations.** Any number of folders, local and
  OneDrive.
- **2026-10-27: checksum list stored in each watched folder**, so it syncs
  and is restored with the files. (An "export a copy" option may come
  later, for restores where the list itself didn't come back.)
- **2026-10-27: MD5 to start**, written as a standard `.md5` file so
  MD5Summer, `md5sum -c` and similar tools can check the files too. Still
  open item 1; see "Hash format".
- **2026-10-27: tray app to start** (runs as you, alerts from the tray).
  Still open item 2.
- **2026-10-27: Windows first, Linux and macOS later.** Same layout as
  ByteLeash: portable logic in `core/`, OS code in `platforms/windows/`,
  `platforms/linux/`, `platforms/macos/`. Only Windows is in development.
  C++ / CMake, same setup as WinNetByApp and ByteLeash.
- **2026-10-27: watched files must be stored locally.** Cloud-only
  (online-only) files can't be checked without downloading them, so the
  app never opens them. When a watched folder has cloud-only files, it
  skips them and shows a clear warning: keep watched folders on this device
  (OneDrive: **Always keep on this device**). The README says the same. See
  open item 6 for details.
- **No third-party runtime dependencies so far.** On Windows, MD5 and
  SHA-256 are in Windows' own CNG (`bcrypt.dll`). Linux and macOS have
  their own hashing APIs, or a small portable MD5 could live in `core/`;
  decide when those editions start.

## Change rules

Implemented in `core/change.h`. Comparing a file's baseline with a scan:

| Contents | Last-modified date | Result |
|----------|--------------------|--------|
| same | any | Unchanged |
| different | different | **Edited** (you or an app changed it) |
| different | same | **Silently changed**: likely corruption; the main alarm |
| different | unknown | Changed (the companion file was missing, so no dates) |
| — | — | **Missing** (in the list, not on disk) / **Added** (on disk, not in the list) |

Size isn't used: a changed file with the same date is suspicious whatever
its size. A file renamed or moved shows as one missing and one added; a
later version could match them by hash.

## Hash format

Standard checksum files hold only a hash and a path per line:
`d41d8cd98f00b204e9800998ecf8427e *photos\beach.jpg`. Parse and format are
in `core/checksum_file.h` (binary `*` and text-mode lines both read;
`;` and `#` comment lines skipped).

**Known limitation: MD5 is broken.** Anyone can create two different files
with the same MD5 (collisions). For catching accidental changes (corruption,
bad restores, sync losses) it's still reliable: random damage won't happen
to keep the same MD5. But it can't prove nobody deliberately swapped a
file. This is stated in the README and SECURITY.md.

## Open items

1. **Hash format: MD5 vs. others.** To discuss. Options:
   - MD5 (`.md5`): widest tool support (MD5Summer, `md5sum`, many backup
     and download tools); broken against tampering.
   - SHA-1 (`.sha1`): also broken (collisions shown in 2017); little gained
     over MD5.
   - SHA-256 (`.sha256`, `sha256sum`): not broken, built into Windows, slower
     than MD5; supported by fewer GUI checkers (check MD5Summer).
   - BLAKE3 (`.b3`, `b3sum`): not broken and the fastest, but needs a
     third-party library and few tools read it.
   - Several at once (a setting, or one file per format).
2. **Tray app or Windows service.** To discuss. Tray app: runs as you, no
   admin, alerts directly, but only while you're signed in. Service: runs
   before sign-in and for all users, needs admin to install and a tray part
   anyway for alerts, and runs as another account (OneDrive folders are
   per-user).
3. **Companion file for dates.** Standard `.md5` files have no room for
   last-modified dates, which the change rules need. Proposal: a second file
   next to it with dates, sizes and accepted changes; other tools ignore it,
   and without it the app still works from the `.md5` alone (changes show as
   "Changed"). Format and name to decide (JSON?).
4. **File names and placement.** What to call the checksum file (e.g.
   `FileIntegrityWatcher.md5`), whether to hide it, and whether it must be
   excluded from its own scan (yes). Does OneDrive sync hidden files?
5. **Path details in `.md5` files.** `\` vs `/` separators (MD5Summer vs
   `md5sum`), UTF-8 file names in MD5Summer, and GNU's escaping of names
   with `\` or newlines. Test with both tools in V1.
6. **OneDrive cloud-only files: details.** Decided: skip and warn (see
   Decisions). Still to work out: detecting placeholders on Windows (file
   attributes `RECALL_ON_DATA_ACCESS` / `OFFLINE`, checked without opening
   the file); how the warning looks (once per folder, with a count, not one
   alert per file); and the restore check, since OneDrive restores most
   files as cloud-only: it should refuse to call a restore "OK" while files
   are still cloud-only, and tell you to set **Always keep on this device**
   and wait for the download. Other sync clients (Dropbox, iCloud, Google
   Drive) use the same Windows placeholder mechanism; check in V1.
7. **Scan scheduling.** How much to scan per day, and how to stay out of
   the way (low I/O priority, pause on battery or when busy).
