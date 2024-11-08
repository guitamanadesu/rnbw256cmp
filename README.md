# rnbw256cmp

## Description

`rnbw256cmp` is a command-line utility used to compare two sha256 checksums using colors to make the differences more visible.

## Story

I get paranoid when I download files from the internet, when I'm reviewing the checksums I always have to compare them manually, I'm also a color code person, so I thought it would be nice to create a tool that would help me compare the checksums visually.

## Requirements

- A C compiler (e.g., `gcc`)
- `make` installed on your system

## Installation

### Step 1: Clone the repository

Clone the repository to your local machine:

```sh
git clone https://github.com/mcaymm/rnbw256cmp.git
cd rnbw256cmp
```

### Step 2: Compile the binary

Compile the binary using the Makefile:

```sh
make
```

### Step 3: Install the binary

Install the binary to your system, it will be installed in `/usr/local/bin` by default, but you can change the installation path by setting the `PREFIX` variable:

```sh
sudo make install
```

install the binary in a custom path:

```sh
sudo make install PREFIX=/path/to/directory
```

## Usage

```sh
[ echo / cat / sha256sum / etc ] <checksum> | rnbw256cmp -c <checksum> [--no-color]
```

### Options

- `-c <checksum>`: The checksum to compare with the input checksum.
- `--no-color`: Disable the colored output.
- `-h`, `--help`: Show the help message.

## Examples

```sh
echo "1234567890abcdef1234567890abcdef1234567890abcdef1234567890abcdef" | rnbw256cmp -c 1234567890abcdef1234567890abcdef1234567890abcdef1234567890abcdef
```

```sh
cat checksum.txt | rnbw256cmp -c 1234567890abcdef1234567890abcdef1234567890abcdef1234567890abcdef --no-color
```

