#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]){
  if (argc != 2){
    fprintf(stdout, "usage: wzip <filename>\n");
    exit(1);
  }

  FILE* fp = fopen(argv[1], "r");
  if (fp == NULL){
    fprintf(stdout, "Unable to open file...\n");
    exit(1);
  }
  size_t intSize = sizeof(int);

  char* buf = NULL;
  size_t buf_size = 32;

  while(getline(&buf, &buf_size, fp) != -1){ // Go line by line...

    int i = 0;
    int currLetterCount = 0;
    char lastChar = '\0';

    while (i < strlen(buf)){ // Go character by character...
      if (lastChar != buf[i]){
        if (lastChar != '\0'){
          size_t numsWritten = fwrite(&currLetterCount, sizeof(int), (size_t) 1, stdout);
          size_t charsWritten = fwrite(&lastChar, sizeof(char), (size_t) 1, stdout);
          // printf("%d%c ", currLetterCount, lastChar);
        }

        lastChar = buf[i];
        currLetterCount = 1;
      } else {
        currLetterCount++;
      }
      i++;
    }

  }

  fclose(fp);
  return 0;
}
