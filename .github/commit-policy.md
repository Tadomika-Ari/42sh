---
description: "Use this policy when generating git commit messages in this repository."
applyTo: "**"
---

# Commit Message Policy

Generate commit messages with this format:

[PREFIX] Short description (max 72 chars)

Optional body with more details.

## Prefixes
- [+] New feature or file added
- [-] File or feature removed
- [~] Modification or update
- [!] Bug fix
- [*] Refactor or cleanup
- [?] Tests
- [#] Configuration or build

## Examples
[+] Add user authentication module
[-] Remove deprecated payment API
[~] Update README with new install steps
[!] Fix crash on null pointer in parser
[*] Refactor database connection pool