#include <stdio.h>
#include <time.h>

int main(void)
{
    time_t now = time(NULL);
    char* string = ctime(&now);
    struct tm* time = localtime(&now);
    int day = time->tm_mday + 1;
    int month = time->tm_mon + 1;
    int year = time->tm_year + 1900;
}