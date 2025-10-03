# Grawk

Think `grep` + `awk` (as commonly used in pipes). Directly from the `grawk.c` help output:

```txt

grawk 1.5.0
Usage: grawk [OPTION] PATTERN OUTPUT_PATTERN file1 [file2]...
Options:
  --help                       show help and examples
  -i, --ignore-case            ignore case distinctions
  -W, --with-filename          Print filename for each match
  -w, --no-filename            Never print filename for each match
  -n, --line-number            Prefix each line of output with line number.
  -F fs, --field-separator=fs  Use fs as the field separator
  -h, --help                   Print a brief help summary
  -v, --version                Print version information and exit normally
  PATTERN                      a basic regular expression
  OUTPUT_PATTERN               awk-style print statement; defines output fields

Examples:
  Retrieve joe123's home directory from /etc/passwd:
        grawk -F : "joe123" '$6' /etc/passwd

  Find fields 2 3 and 4 on lines that begin with @ from stdin:
        cat file.txt | grawk "^@" '$2,$3,$4'

  Use as a simple grep:
        grawk "string to find" '$0' /file.txt
```

## Libgrawk (Micro C Library Based On Grawk)

The `grawk` program evolved over a decade of being hacked to do something else
it didn't do before.

The `libgrawk` library is meant to take that code, clean it up a bit and make it
re-usable and thread-safe, and implement it into a filtering library that can
make the functionality accessible in embedded code, as well as re-produce the
functionality of the original executable. `ngrawk` is based on the new code, 
`grawk` is the self-contained (not concurrent, hacky) implementation that
inspired it.

### License: MIT

Or whatever license works for you. It's just a useful log saw and matching tool.

