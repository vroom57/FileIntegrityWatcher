# Security policy

## Reporting a vulnerability

Please report security problems privately, not in a public issue:

1. Go to the repository's **Security** tab.
2. Choose **Report a vulnerability**
   ([direct link](https://github.com/vroom57/FileIntegrityWatcher/security/advisories/new)).
3. Describe the problem, the steps to reproduce it, the File Integrity
   Watcher version and Windows version, and what an attacker could do with
   it.

The report is visible only to you and the maintainer. We can discuss it,
work on a fix privately, and publish an advisory once a fix is available.
File Integrity Watcher is a personal project, so responses are best effort.

## Supported versions

File Integrity Watcher hasn't had a release yet. Until it does, reports
should be against the latest code on `main`. Once releases start, only the
latest release will receive security fixes.

## What counts as a vulnerability

File Integrity Watcher runs as you (no admin rights) and reads the folders
you choose, so the most important problems are ones that make it do more
than read and report, for example:

- Getting code to run through it, for example with a crafted checksum file
  or file name, or a DLL planted where it looks for one.
- Making it modify, delete or upload files it should only read, or write
  outside the checksum files it owns.
- Making it download OneDrive cloud-only files it should skip.

## Known limitations (not vulnerabilities)

- **MD5 is broken against deliberate tampering.** Someone can create two
  different files with the same MD5, so a swapped file can go unnoticed.
  File Integrity Watcher is meant to catch accidental changes (corruption,
  bad restores, lost files), not to prove that nobody tampered with them.
  See "Hash format" in [docs/ideas.md](docs/ideas.md).
- **The checksum file sits next to the files it checks.** Anyone who can
  change your files can also change or delete the list.
