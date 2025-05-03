/*
 * wgrep.c - written by Odi Ogali
 * A command line program that searches for a sequence of characters within stdin, 1, or many files.
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]){
  // argv[1] is the search term, argv[2]+ are the files to search 
  if (argc == 1){
    fprintf(stderr, "wgrep: searchterm [file ...]\n");
    exit(1);
  }
  
  if (argc == 2){ // search for term in stdin
    char* buf = NULL;
    size_t buf_size = 32;

    while (getline(&buf, &buf_size, stdin) != -1){ // For each line in stdin...
      bool match = false;
      int i = 0;
      
      while (i < strlen(buf)){ // Go through each character...

        if (buf[i] == argv[1][0]){
          i++;
          int j = 1;

          while (buf[i] == argv[1][j]){
            if (j == strlen(argv[1]) - 1){
              match = true;
              break;
            }

            i++;
            j++;
          }

          if (match){
            printf("%s", buf);
            match = false;
          }
        }
        i++;
      }
    }

    return 0;
  }

  // When there are more than one file specified to search from...
  int j = 2;
  while (argv[j] != NULL){ // For each file in the arg...
    char* buf = NULL;
    size_t buf_size = 32;

    FILE* fd = fopen(argv[j], "r");
    if (fd == NULL){
      fprintf(stderr, "wgrep: cannot open file\n");
      exit(1);
    }

    while(getline(&buf, &buf_size, fd) != -1){ // For each line in the file...
      int i = 0;
      bool match = false;
      
      while(i < strlen(buf)){ // go through the chars in line

        if (buf[i] == argv[1][0]){ // if there is a match with the first search char somewhere
          i++; // increment line char pointer 
          int k = 1; // k will be the search term char pointer
          
          while (buf[i] == argv[1][k]){ // while there is a match between STP and LCP...
            if (k == strlen(argv[1]) - 1){
              match = true; // If we got to the end of search term, then there is 100% match
              break;
            }
            k++;
            i++;
          }

          if (match == true){
            if (argc == 3){ // If there is only one file specified, then you can print the line
              printf("%s", buf);
            } else { // Else, since there are other files, we specify which this line is from
              printf("%s: %s", argv[j], buf);
            }
            match = false;
            break;
          }
        }
        i++;

      }
    }

    j++;
  }

  return 0;
}
