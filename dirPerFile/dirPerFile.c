#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>

int createdirectory(char *directory){

}
int moveFilesToDirectories(char *directory, char *destinationDirectory) {
    DIR *dir;
    struct dirent *entry;
    struct stat filestat;
    char filename[256];

    // Open the directory
    dir = opendir(directory);
    if (!dir) {
        printf("Error opening directory: %s\n", directory);
        return 0;
    }
    // Read each entry in the directory
    while ((entry = readdir(dir)) != NULL) {
        // Ignore current directory and parent directory entries
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        snprintf(filename, sizeof(filename), "%s/%s", directory, entry->d_name);

        // Get file information
        if (stat(filename, &filestat) < 0) {
            printf("Error stating file: %s\n", filename);
            continue;
        }

        // Check if it's a regular file
        if (S_ISREG(filestat.st_mode)) {
            // Create a directory with the same name as the file (without extension)
            char filenameWithoutExtension[256];
            snprintf(filenameWithoutExtension, sizeof(filenameWithoutExtension), "%.*s", (int)(strrchr(entry->d_name, '.') - entry->d_name), entry->d_name);

            // Create the directory in the destination directory
            char destDirectoryPath[256];
            snprintf(destDirectoryPath, sizeof(destDirectoryPath), "%s/%s", destinationDirectory, filenameWithoutExtension);
            if (mkdir(destDirectoryPath, 0777) < 0) {
                printf("Error creating directory: %s\n", destDirectoryPath);
                return 0;
            }

            // Move the file to the new directory
            char newpath[256];
            snprintf(newpath, sizeof(newpath), "%s/%s/%s", destinationDirectory, filenameWithoutExtension, entry->d_name);
            if (rename(filename, newpath) < 0) {
                printf("Error moving file: %s\n", filename);
                continue;
            }
        }
    }
    closedir(dir);
    return 1;
}

int main(int argc, char *argv[]) {
    if (argc > 3){
      printf("Usage: %s <source_directory> <destination_directory>\n", argv[0]);
      return 1;
    }
    else if (argc == 3){
      char *directory = argv[1];
      char *destinationDirectory = argv[2];
      if (moveFilesToDirectories(directory, destinationDirectory)){
        printf("Files organized successfully!\n");
      }
      return 0;
    }
    else if (argc == 2){
      char *directory = argv[1];
      destinationDirectory = createdirectory(directory);
      if (moveFilesToDirectories(directory, destinationDirectory)){
        printf("Files organized successfully!\n");
      }
      return 0;
    }
    else{
      printf("hi\n");
    }
}
