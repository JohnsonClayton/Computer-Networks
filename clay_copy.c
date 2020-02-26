/*
*  Clayton Johnson
*  cpjohnson@mavs.coloradomesa.edu
*
*  Copy a File
*/

const int MAX_FILENAME_LENGTH = 20;

int main(int argc, char **argv) {

  if (argc > 2) {
    char file1[MAX_FILENAME_LENGTH] = '\000';
    char file2[MAX_FILENAME_LENGTH] = '\000';

    strncpy(file1, argv[1], MAX_FILENAME_LENGTH - 1);
    file1[MAX_FILENAME_LENGTH - 1] = '\000';
    strncpy(file2, argv[2], MAX_FILENAME_LENGTH - 1);
    file2[MAX_FILENAME_LENGTH - 1] = '\000';

    int fd1 = open(file1, O_RDONLY);
    int fd2 = open(file2, O_WRONLY | O_CREAT); 

    if ( fd1 != -1 && fd2 != -1) {
      // Copy file1 to file2
    } else {
      // We can't copy...
      if (fd1 == -1) printf("File could not be opened: %s\n", file1);
      if (fd2 == -1) printf("File could not be created/opened: %s\n", file2);
    }

  
  }

  return 0;
}
