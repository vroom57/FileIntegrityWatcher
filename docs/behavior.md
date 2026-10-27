# How File Integrity Watcher behaves

What users see and can rely on. Keep this in sync with the code.

**Status:** nothing user-facing yet. This file fills in as plan steps V1–V3
land.

## Planned

- Only reads your files. The only files it writes are its own checksum
  files in each watched folder.
- Watched files must be stored on the PC. It never downloads OneDrive
  cloud-only (online-only) files: it skips them and warns you to set the
  folder to **Always keep on this device**. A restore check isn't reported
  as OK while any files are still cloud-only.
- Reports each file as edited, silently changed (likely corruption),
  changed, missing or added. See "Change rules" in
  [ideas.md](ideas.md).
- Runs as you, without administrator rights.
