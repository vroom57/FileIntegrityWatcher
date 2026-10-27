# File Integrity Watcher

Know when files in your folders change, go missing or get corrupted — and
check that a restore brought everything back.

You choose the folders to watch: a local folder, your OneDrive folder, or
several. File Integrity Watcher keeps a list of every file in each folder
with its checksum (a fingerprint of its contents), then checks the files
against that list in the background and lets you know when:

- a file was **edited**,
- a file **changed without being edited** (its contents changed but its
  date didn't, a sign of corruption or "bit rot"),
- a file **disappeared**, deleted by accident or lost in a sync,
- a **new file** appeared.

The list is stored in each watched folder, so it travels with your files.
After rebuilding a PC and restoring everything from OneDrive or a backup,
File Integrity Watcher can confirm every file came back intact, and tell
you exactly what didn't.

The list is a standard `.md5` checksum file, so other tools such as
MD5Summer or `md5sum -c` can check your files too.

## Where things stand

- **Now:** the Windows edition, step V1: creating the list and checking a
  folder against it. There's nothing to download or run yet. Linux and
  macOS editions are planned for later.
- **Details:** [docs/plan.md](docs/plan.md) (order of work),
  [docs/ideas.md](docs/ideas.md) (design notes and decisions).

## Good to know

- **It's for catching accidents, not attackers.** MD5 checksums reliably
  catch corruption, bad restores and lost files, but MD5 is broken as a
  security measure: someone who deliberately swaps a file can make the
  fake one match. Don't rely on it to prove nobody tampered with your files.
- **It doesn't repair anything.** It tells you what's wrong so you can
  restore those files from a backup or OneDrive's version history.
- **Watched files must be stored on your PC.** OneDrive can keep files
  "online-only", with just a placeholder on your PC. File Integrity Watcher
  can't check those without downloading them, so it skips them and warns
  you. For the folders you watch, right-click the folder in File Explorer
  and choose **Always keep on this device**. After a restore, do the same
  and let OneDrive finish downloading before you run a restore check.

## Platform status

| Platform | Directory             | Status         |
|----------|-----------------------|----------------|
| Windows  | `platforms/windows/`  | In development |
| Linux    | `platforms/linux/`    | Planned        |
| macOS    | `platforms/macos/`    | Planned        |

## Repository layout

```
FileIntegrityWatcher/
├── core/            Shared, platform-independent logic (checksum files, change rules)
├── platforms/
│   ├── windows/     Windows code: hashing, scanning, the tray app
│   ├── linux/       Linux code and packaging
│   └── macos/       macOS code and packaging
├── tests/           Tests for core and per-platform code
├── scripts/         Build and helper scripts
└── docs/            Plan, design notes and behavior
```

Platform-independent code goes in `core/`. Each directory under
`platforms/` contains only what is specific to that operating system, and
builds on `core/`.

## Building (Windows)

Needs Visual Studio 2022 or later with the C++ workload (it includes CMake
and Ninja).

- From a command prompt: `scripts\build.cmd` (or `scripts\build.cmd release`)
- In Visual Studio: **File → Open → Folder** and pick this folder.

## Contact and support

- **Bugs and feature requests:** open an
  [issue](https://github.com/vroom57/FileIntegrityWatcher/issues). Please
  include your operating system version and what you expected to happen.
- **Security problems:** please don't open a public issue. Report them
  privately as described in [SECURITY.md](SECURITY.md).

File Integrity Watcher is a personal project, so replies are best effort.

## License

File Integrity Watcher is licensed under the GNU General Public License
v3.0. See [LICENSE](LICENSE).
