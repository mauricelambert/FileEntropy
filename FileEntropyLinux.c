// This file generates a file entropy array
// (initially used to get entropy  on a complet hard disk).

/*
    Copyright (C) 2023  Maurice Lambert
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.
    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

// Linux:
// gcc -O5 FileEntropyLinux.c -o LinuxFileEntropy -lm
// gcc -O5 FileEntropyLinux.c -shared -o libFileEntropy.so -lm

#include <math.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <sys/stat.h>

// This function generates shannon entropy from occurences
extern double entropy_from_occurences(
    unsigned long long int occurrences[256],
    unsigned long long int chunk_size,
    int diff
) {
    double entropy = 0.0;
    for (unsigned int character = 0; character < 256; character += 1) {
        if (occurrences[character]) {
            double p = (double)occurrences[character] / (double)chunk_size;
            entropy -= p * log2(p);
        }
    }
    return entropy;
}

// This function generates entropy and entropy array from FILE object
extern double entropy_from_file(
    FILE *file,
    double entropies[101],
    unsigned char *buffer,
    unsigned int bufferSize,
    off_t file_size
) {
    size_t readSize;
    int diff = 0;

    for (unsigned int entropy; entropy < 101; entropies[entropy++] = 0.0);

    unsigned long long int chunk_size =
        (unsigned long long int)round(file_size / 100);
    unsigned long long int counter = 0;
    unsigned int chunk_number = 0;

    unsigned long long int occurrences[256] = { [ 0 ... 255 ] = 0 };
    unsigned long long int full_file_occurrences[256] = { [ 0 ... 255 ] = 0 };

    do {
        readSize = fread(buffer, sizeof(char), bufferSize, file);
        for (unsigned int index = 0; index < readSize; index += 1) {
            occurrences[buffer[index]] += 1;
            full_file_occurrences[buffer[index]] += 1;
            counter += 1;

            if (counter >= chunk_size) {
                double entropy = entropy_from_occurences(
                    occurrences, counter, diff
                );
                entropies[chunk_number] = entropy;
                for (
                    unsigned int character = 0;
                    character < 256;
                    occurrences[character++] = 0
                );
                chunk_number += 1;
                counter = 0;
            }
        }
    } while (readSize);

    double entropy = entropy_from_occurences(occurrences, counter, diff);
    entropies[chunk_number] = entropy;
    return entropy_from_occurences(full_file_occurrences, file_size, 1);
}

// This function generates entropy and entropy array from string filename
extern double entropy_from_filename(
    const unsigned char *filepath,
    double entropies[101],
    unsigned char *buffer,
    unsigned int bufferSize
) {
    struct stat st;
    FILE *source = fopen(filepath, "rb");

    if (source == NULL) {
        // fputs("Error opening the source file.", stderr);
        return 0.0;
    }

    stat(filepath, &st);

    double entropy = entropy_from_file(
        source, entropies, buffer, bufferSize, st.st_size
    );

    fclose(source);
    return entropy;
}

// This function starts the program execution (parses ARGV and print entropies)
/*int main(int argc, const char** argv) {
    if (argc < 2 || argc > 3) {
        fputs(
            "USAGES: ./FileEntropy [bufferSize, default: 131072] sourcePath",
            stderr
        );
        return 1;
    }

    if (argc == 3) {
        for (unsigned int index = 0; argv[1][index] != 0; index += 1) {
            if (!isdigit(argv[1][index])) {
                fputs("bufferSize is invalid, must be digits.", stderr);
                return 2;
            }
        }
    }

    const unsigned char *sourcepath = argv[1];
    unsigned char defaultBuffer[131072];
    unsigned int bufferSize = 131072;

    unsigned char *buffer = defaultBuffer;
    double entropies[1001] = { [ 0 ... 1000 ] = 0.0 };

    if (argc == 3) {
        bufferSize = atoi(argv[1]);
        buffer = malloc(sizeof(char) * bufferSize);
        sourcepath = argv[2];
    }

    double entropy = entropy_from_filename(
        sourcepath, entropies, buffer, bufferSize
    );

    if (argc == 3) {
        free(buffer);
    }

    if (entropy == 0.0) {
        return 3;
    }

    printf("{\n\t\"full_entropy\": %f,\n\t\"entropies\": [", entropy);
    for (unsigned int index; index < 101; index += 1) {
        printf("%f, ", entropies[index]);
    }
    puts("\b\b]\n}");
    return 0;
}*/
