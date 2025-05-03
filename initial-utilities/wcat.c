/*
 * wcat.c - written by Odi Ogali
 * A command line program that prints the contents of a file.
 */

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
  if (argc == 1){
    exit(0);
  }

  int counter = 1;

  while (counter < argc){

    FILE* fp = fopen(argv[counter], "r");
    if (fp == NULL){
      fprintf(stderr, "wcat: cannot open file\n");
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
