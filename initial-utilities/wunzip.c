#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
  if (argc != 2){
    fprintf(stdout, "usage: unwzip <filename>\n");
    exit(1);
  }
  FILE* fp = fopen(argv[1], "r");

  int int_buf = 0;
  char char_buf = '\0';

  while(fread(&int_buf, sizeof(int), (size_t) 1, fp) != 0){
    fprintf(stdout, "%d", int_buf);
    fread(&char_buf, sizeof(char), (size_t) 1, fp);
    fprintf(stdout, "%c", char_buf);
  }
  
  return 0;
}
