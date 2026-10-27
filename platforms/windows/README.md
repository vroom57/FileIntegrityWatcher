# File Integrity Watcher for Windows

Windows-specific code, built as `fiwatcher.exe`.

**Status:** In development

- **Baseline and check** (plan V1): hash the files in a folder, write the
  folder's checksum file, and compare a later scan against it. Detects
  OneDrive cloud-only files without opening them (opening one would
  download it), skips them and warns that watched files must be kept on
  this device.
- **Tray app** (plan V2): watches the chosen folders in the background at
  low priority and alerts from the tray.

`fiwatcher.exe` is a placeholder for now: it prints a version line and
exits.
