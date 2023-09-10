#!/usr/bin/env python3
# -*- coding: utf-8 -*-

###################
#    This file generates a file entropy report with python
#    Copyright (C) 2023  FileEntropy

#    This program is free software: you can redistribute it and/or modify
#    it under the terms of the GNU General Public License as published by
#    the Free Software Foundation, either version 3 of the License, or
#    (at your option) any later version.

#    This program is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#    GNU General Public License for more details.

#    You should have received a copy of the GNU General Public License
#    along with this program.  If not, see <https://www.gnu.org/licenses/>.
###################

"""
This file generates a file entropy report with python
"""

__version__ = "0.0.1"
__author__ = "Maurice Lambert"
__author_email__ = "mauricelambert434@gmail.com"
__maintainer__ = "Maurice Lambert"
__maintainer_email__ = "mauricelambert434@gmail.com"
__description__ = """
This file generates a file entropy report with python
"""
__url__ = "https://github.com/mauricelambert/FileEntropy"

__all__ = ["main"]

__license__ = "GPL-3.0 License"
__copyright__ = """
FileEntropy  Copyright (C) 2023  Maurice Lambert
This program comes with ABSOLUTELY NO WARRANTY.
This is free software, and you are welcome to redistribute it
under certain conditions.
"""
copyright = __copyright__
license = __license__

print(copyright)

from sys import stderr, exit, argv, executable
from os.path import join, exists, dirname
from subprocess import check_output
from ctypes import c_char, c_double
from os.path import getsize
from os import getcwd, name

if name == "nt":
    from ctypes import windll
    filename = "libFileEntropy.dll"
    LoadLibrary = windll.LoadLibrary
else:
    from ctypes import cdll
    filename = "libFileEntropy.so"
    LoadLibrary = cdll.LoadLibrary

filenames = (join(dirname(__file__), filename), join(getcwd(), filename))
bufferSize = 131072

for filename in filenames:
    if exists(filename):
        break
else:
    print(f"Library {filename!r} is missing", file=stderr)
    exit(1)

libfileentropy = LoadLibrary(filename)


def main() -> int:
    """
    This function starts the script from the command line.
    """

    if len(argv) != 2:
        print(
            f"USAGES: {executable} {argv[0]} sourceFilePath",
            file=stderr,
        )
        return 2

    _, sourcefilepath = argv

    filesize = getsize(sourcefilepath)
    chunk_size = round(filesize / 100)

    buffer = (c_char * bufferSize)(b"\0")
    entropies = (c_double * 101)(0)

    libfileentropy.entropy_from_filename.restype = c_double
    entropy = libfileentropy.entropy_from_filename(
        sourcefilepath.encode(),
        entropies,
        buffer,
        bufferSize,
    )

    if not entropy:
        print("Error opening file.", file=stderr)
        return 3

    print(f"Entropies (chunk size: {chunk_size}):")
    for i, entropy in enumerate(entropies):
        if i > 100:
            print(f"  {i * chunk_size:0>10x}-{filesize:0>10x} {entropy:.20f}")
        else:
            print(
                f"  {i * chunk_size:0>10x}-{(i + 1) * chunk_size:0>10x}"
                f" {entropy:.20f}"
            )

    print(f"Full file entropy:      {entropy:.20f}")

    return 0


if __name__ == "__main__":
    exit(main())
