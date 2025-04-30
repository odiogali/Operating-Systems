/*
 * Reverse.c - written by Odi Ogali
 * A command line program that takes some sequence of characters in a string,
 * separates them by the lines, stores them in a linked list, and reverses
 * the lines using the new line escape character.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

struct Node {
  char* line;
  struct Node* next;
};

int main(int argc, char* argv[]){
  if (argc > 3) { // when there are more than 3 args, we should fail
    fprintf(stderr, "usage: reverse <input> <output>\n");
    exit(1);
  }

  if (argc == 1){

    char* buffer = NULL;
    size_t buf_size = 3;

    struct Node* head = NULL;
    struct Node* curr = NULL;
    struct Node* prev = NULL;

    while (getline(&buffer, &buf_size, stdin) != -1){
      curr = malloc(sizeof(struct Node));
      char* temp = malloc(strlen(buffer) + 1);
      if (temp == NULL || curr == NULL){
        fprintf(stderr, "malloc failed\n");
        exit(1);
      }

      strcpy(temp, buffer);
      curr->line = temp;
      curr->next = prev;

      head = curr;
      prev = curr;
    }

    struct Node* itr_curr = head;
    while (itr_curr != NULL){
      fprintf(stdout, "%s", itr_curr->line);
      itr_curr = itr_curr->next;
    }

    free(buffer);

  } else if (argc == 2){
    
    FILE* file = fopen(argv[1], "r");
    if (file == NULL){
      fprintf(stderr, "error: cannot open file '%s'\n", argv[1]);
      exit(1);
    }

    char* buffer = NULL; // Initialize memory to hold pointer
    size_t bufsize = 3;

    // All three of these structures are null by default
    struct Node* curr = NULL; 
    struct Node* prev = NULL; 
    struct Node* head = NULL;

    while(getline(&buffer, &bufsize, file) != -1){ // So long as we are not at end of file...
      curr = malloc(sizeof(struct Node)); // allocate space on stack? for new node
      char* temp = malloc(strlen(buffer) + 1); // allocate space on stack? for string that was read
      if (temp == NULL || curr == NULL){
        fprintf(stderr, "malloc failed\n");
        exit(1);
      }

      strcpy(temp, buffer); // Copy string that was read into allocated space
      curr->line = temp; // assign pointer to line variable for node
      curr->next = prev; // Make current node head of the linked list so far
      
      head = curr; // Formally assign head pointer to be recently added node
      prev = curr; // When progressing, set the previous node pointer to current node pointer
    }

    struct Node* itr_curr = head;
    while (itr_curr != NULL){
      fprintf(stdout, "%s", itr_curr->line);
      itr_curr = itr_curr->next;
    }

    free(buffer);
    fclose(file);

  } else { // argc == 3
    
    if (strcmp(argv[1], argv[2]) == 0){
      fprintf(stderr, "Input and output file must differ\n");
      exit(1);
    }

    FILE* in_file = fopen(argv[1], "r");
    if (in_file == NULL){
      fprintf(stderr, "error: cannot open file '%s'\n", argv[1]);
      exit(1);
    }

    char* buffer = NULL; 
    size_t bufsize = 3;

    struct Node* curr = NULL; 
    struct Node* prev = NULL; 
    struct Node* head = NULL;

    while(getline(&buffer, &bufsize, in_file) != -1){ // So long as we are not at end of file...
      curr = malloc(sizeof(struct Node)); // allocate space on stack? for new node
      char* temp = malloc(strlen(buffer) + 1); // allocate space on stack? for string that was read
      if (temp == NULL || curr == NULL){
        fprintf(stderr, "malloc failed\n");
        exit(1);
      }

      strcpy(temp, buffer); // Copy string that was read into allocated space
      curr->line = temp; // assign pointer to line variable for node
      curr->next = prev; // Make current node head of the linked list so far
      
      head = curr; // Formally assign head pointer to be recently added node
      prev = curr; // When progressing, set the previous node pointer to current node pointer
    }

    FILE* out_file = fopen(argv[2], "w+");

    struct Node* itr_curr = head;
    while (itr_curr != NULL){
      fprintf(out_file, "%s", itr_curr->line);
      itr_curr = itr_curr->next;
    }

    free(buffer);
    fclose(in_file);
    fclose(out_file);

  }   

  return 0;
}
