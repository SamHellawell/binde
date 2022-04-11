#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include <cstdlib>

#ifndef PATH_MAX
#define PATH_MAX 4096
#endif

// Perform "binary deletion" on a file
// this will overwrite the entire file with zero bytes
// and then attempt to remove the file
int doDeletion(char* fileName, bool quiet) {
  if (strcmp(fileName, "") == 0) {
    printf("File name is empty string %s\n", fileName);
    return 1;
  }

  // Attempt to open the file in read/write binary mode
  FILE* fp = fopen(fileName, "rb+");
  if (fp) {
    // Gather file size
    fseek(fp, 0, SEEK_END);
    long fileSize = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    if (!quiet) {
      printf("File: %s", fileName);
      printf("\tSize: %d bytes\n", fileSize);
    }

    // Write zero byte for every byte
    char* data = (char*)malloc(fileSize);
    fwrite(data, 1, fileSize, fp);
    free(data);

    // Close file handler
    fclose(fp);

    // Now remove the file
    int del = remove(fileName);
    if (del) {
      printf("Unable to delete the file: %s\n", fileName);
      return 1;
    }
  } else {
    printf("Unable to open the file: %s\n", fileName);
    return 1;
  }

  return 0;
}

// Entry point, expects arguments or line
// delimeted list of file paths from STD-IN
int main(int argc, char** argv) {
  bool quiet = false;

  // Read from STD-IN
  if (argc == 1) {
    char ch;
    size_t i = 0;
    char fileName[PATH_MAX];

    // Read all bytes using new lines as delimeters for file names
    // once a filename has been accumulated, perform the operation
    while (read(STDIN_FILENO, &ch, 1) > 0) {
      if (ch == '\n') {
        if (i > 0) {
          fileName[i] = '\0';
          i = 0;

          int result = doDeletion(fileName, quiet);
          if (result > 0) {
            return result;
          }
        }
      } else {
        fileName[i] = ch;
        i++;
      }
    }
  } else {
    // Expect list of file names from argv
    for (int i = 1; i < argc; i++) {
      int result = doDeletion(argv[i], quiet);
      if (result > 0) {
        return result;
      }
    }
  }

  return 0;
}
