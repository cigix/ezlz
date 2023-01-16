# EZLZ: a simple implementation of a Lempel-Ziv compression scheme

## Usage

```sh
$ ezlz [input [output]] # compression
$ unzelz [[input] output] # decompression
```

If both input and output files are omitted, `stdin` and `stdout` are used. For
compression, you can specify only an input file; for decompression, only an
output file.

## Building

Running `make` at the root will build `ezlib`, `ezlz`, and `unezlz`, and copy
them at the root.

## Escape value

Lempel-Ziv requires the use of an escape byte. By default, `ezlib` will use
`0xAA`. To change this value, run `make` with the `ESCAPE` variable set to any C
litteral, e.g.

```sh
$ make ESCAPE="'@'"
```

Note that `unezlz` will not properly decompress streams compressed with a
different escape value.
