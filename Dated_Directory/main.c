/*
  File: Dated_Directory.c
  Author: Mariam Naser
  Date: June 11, 2023
  Description: Creates directories with date.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/stat.h>

void createDirectory(const char *title) {
    if (mkdir(title, 0777) < 0) {
        printf("Error creating directory: %s\n", title);
    } else {
        printf("Directory created: %s\n", title);
    }
}

int main(void) {
    time_t t = time(NULL);
    struct tm *current_time = localtime(&t);

    char title[30];
    snprintf(title, sizeof(title), "Recieved %02d.%02d.%04d",
             current_time->tm_mon + 1,  // Month is zero-based, so adding 1
             current_time->tm_mday,
             current_time->tm_year + 1900);  // Year is the number of years since 1900

    createDirectory(title);

    return 0;
}
