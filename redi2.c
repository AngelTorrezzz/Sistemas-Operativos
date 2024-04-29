#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main(){
    int fd = open("arch.txt", O_WRONLY | O_CREAT | O_TRUNC, 0600);
    int h = 256;
    write(fd, &h, sizeof(h));
    close(fd);

    return 0;
}