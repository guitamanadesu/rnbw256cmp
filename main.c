#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "ANSI_COLORS.h"

#define EXPECTED_LENGTH 64
#define COMPARE_FLAG "-c"
#define NO_COLOR_FLAG "--no-color"

char buffer[EXPECTED_LENGTH + 1];
char buffer_2[EXPECTED_LENGTH + 1];
int hasCompareFlag = 0;
int hasNoColorFlag = 0;

void printHelpMessage() {
    printf("Usage: [ echo / cat / sha256sum / etc ] <checksum> | rnbw256cmp -c <checksum> [--no-color]");
    printf("\n");
    printf("Flags:\n");
    printf("  -c <checksum>  Compare the checksum to the provided value\n");
    printf("  --no-color     Disable colored output\n");
    printf("  -h, --help     Prints this help message\n");
    printf("\n");
}

void readChecksum(char *buffer) {
    int c, i = 0;
    while ((c = getchar()) != EOF && i < EXPECTED_LENGTH) {
        buffer[i++] = c;
    }
    buffer[i] = '\0';
}

void parseArguments(int argc, char **argv) {
    for (int i = 1; i < argc; i++) {

        if(strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
            printHelpMessage();
            exit(EXIT_SUCCESS);
        }

        if (strcmp(argv[i], COMPARE_FLAG) == 0) {
            hasCompareFlag = i;
        } else if (strcmp(argv[i], NO_COLOR_FLAG) == 0) {
            hasNoColorFlag = i;
        }
    }

    if (hasCompareFlag == 0) {
        fprintf(stderr, "Flag -c is missing, include it with the checksum value\n");
        exit(EXIT_FAILURE);
    } else if (strlen(argv[hasCompareFlag + 1]) != EXPECTED_LENGTH) {
        fprintf(stderr, "Compare to checksum value is not the correct length\n");
        exit(EXIT_FAILURE);
    } else {
        strncpy(buffer_2, argv[hasCompareFlag + 1], EXPECTED_LENGTH);
        buffer_2[EXPECTED_LENGTH] = '\0';
    }
}

void printRainbowTextWSeparator(const char *text, int separator) {
    for (int i = 0; i < strlen(text); i++) {
        if (i % separator == 0) {
            printf(" ");
        }

        switch (i % 6) {
            case 0: printf(BRED "%c" reset, text[i]); break;
            case 1: printf(BGRN "%c" reset, text[i]); break;
            case 2: printf(BYEL "%c" reset, text[i]); break;
            case 3: printf(BBLU "%c" reset, text[i]); break;
            case 4: printf(BMAG "%c" reset, text[i]); break;
            case 5: printf(BCYN "%c" reset, text[i]); break;
            default: printf("%c", text[i]); break;
        }
    }
}

int main(int argc, char **argv) {

    if (isatty(fileno(stdin))) {
        printHelpMessage();
        exit(EXIT_FAILURE);
    }

    readChecksum(buffer);
    parseArguments(argc, argv);

    printf("Checksum[%lu]: ", strlen(buffer));
    printRainbowTextWSeparator(buffer, 8);
    printf("\n");

    printf("Checksum[%lu]: ", strlen(buffer_2));
    printRainbowTextWSeparator(buffer_2, 8);
    printf("\n");

    if (strcmp(buffer, buffer_2) == 0) {
        printf(BGRN "Checksums match\n" reset);
    } else {
        printf(BRED "Checksums do not match\n" reset);
    }

    return 0;
}