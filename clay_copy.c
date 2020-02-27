/*
*  Clayton Johnson
*  cpjohnson@mavs.coloradomesa.edu
*
*  Copy a File
*/

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


const int MAX_FILENAME_LENGTH = 20;
const int MAX_RW = 1024;

void cj_copy(int fd1, int fd2) {
  void *buf[MAX_RW + 1]; 
  int size_read;
  while( (size_read = read(fd1, buf, MAX_RW)) > 0 ) {
    buf[MAX_RW] = '\000';
    write(fd2, buf, size_read);
  }
}

int main(int argc, char **argv) {

  if (argc > 2) {
    char file1[MAX_FILENAME_LENGTH];
    char file2[MAX_FILENAME_LENGTH];

    strncpy(file1, argv[1], MAX_FILENAME_LENGTH - 1);
    file1[MAX_FILENAME_LENGTH - 1] = '\000';
    strncpy(file2, argv[2], MAX_FILENAME_LENGTH - 1);
    file2[MAX_FILENAME_LENGTH - 1] = '\000';

    int fd1 = open(file1, O_RDONLY);
    int fd2 = open(file2, O_WRONLY | O_CREAT, 0666); 

    if ( fd1 != -1 && fd2 != -1) {
      // Copy file1 to file2
      cj_copy(fd1, fd2);
    } else {
      // We can't copy...
      if (fd1 == -1) printf("File could not be opened: %s\n", file1);
      if (fd2 == -1) printf("File could not be created/opened: %s\n", file2);
    }

  
  }

  return 0;
}
