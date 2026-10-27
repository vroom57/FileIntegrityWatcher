# core

Shared, platform-independent logic used by every edition: reading and
writing checksum file lines, and deciding how a file changed (edited,
silently changed, missing, added).

Code here must not call OS-specific APIs directly. Anything that differs
between platforms (hashing, scanning folders, cloud placeholders, the tray
app) belongs in the matching directory under `platforms/`.
