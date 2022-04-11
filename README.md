# BINDE

A small, simple C utility to perform a full "binary deletion" of files. It will overwrite all bytes in the file and then try to delete it, so that it cannot be recovered.
This is useful for deleting sensitive data, such as PII, keys and more.

## Usage

Usage is simple, download the repo and build with `make` which will produce the binary `./binde`. `sudo make install` will then move the binary into `/usr/bin`.

Once installed or compiled, you can either supply a list of files as arguments like:
```bash
binde file1.txt file2.txt file3.txt
```

or through STD-IN, such as:
```bash
cat file-list.txt | binde
```
