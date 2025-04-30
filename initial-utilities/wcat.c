#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
  int counter = 1;

  while (counter < argc){

    FILE* fp = fopen(argv[counter], "r");
    if (fp == NULL){
      fprintf(stderr, "unable to open file %s", argv[1]);
      exit(1);
    }

    char buffer[32];
    while (fgets(buffer, 32, fp) != NULL){
      printf("%s", buffer);
    }

    counter++;
  }
  return 0;
}
