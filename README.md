# FileEntropy

## Description

This repository implements an optimized code to get a file entropy report.

## Requirements

There is no requirements.

Optional:
 - Python3
 - Python3 Standard Library

## Installation

### Compilation

#### Linux

```bash
git clone "https://github.com/mauricelambert/FileEntropy.git"
cd "FileEntropy"
gcc -O5 FileEntropyLinux.c -o LinuxFileEntropy -lm
./LinuxFileEntropy sdDisk.bin
```

#### Windows

```bash
git clone "https://github.com/mauricelambert/FileEntropy.git"
cd "FileEntropy"
gcc -O5 FileEntropyWindows.c -o WindowsFileEntropy.exe
WindowsFileEntropy.exe sdDisk.bin
```

### Download

#### Windows

```bash
git clone "https://github.com/mauricelambert/FileEntropy.git"
cd "FileEntropy"
wget https://mauricelambert.github.io/info/python/security/libFileEntropy.dll
python FileEntropyInterface.py sdDisk.bin
```

```bash
wget https://mauricelambert.github.io/info/python/security/WindowsFileCloner.exe
WindowsFileCloner.exe sdDisk.bin
```

#### Linux

```bash
git clone "https://github.com/mauricelambert/FileEntropy.git"
cd "FileEntropy"
wget https://mauricelambert.github.io/info/python/security/libFileEntropy.so
python3 FileEntropyInterface.py sdDisk.bin
```

```bash
wget https://mauricelambert.github.io/info/python/security/LinuxFileEntropy
./LinuxFileEntropy sdDisk.bin
```

## Usages

### Command line

```bash
./LinuxFileEntropy sdDisk.bin
python3 FileEntropyInterface.py sdDisk.bin
```

## Links

 - [Github](https://github.com/mauricelambert/FileEntropy)
 - [Linux executable](https://mauricelambert.github.io/info/python/security/LinuxFileEntropy)
 - [Linux Shared Object](https://mauricelambert.github.io/info/python/security/libFileEntropy.so)
 - [Windows executable](https://mauricelambert.github.io/info/python/security/WindowsFileEntropy.exe)
 - [Windows DLL](https://mauricelambert.github.io/info/python/security/libFileEntropy.dll)

## License

Licensed under the [GPL, version 3](https://www.gnu.org/licenses/).
