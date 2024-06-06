#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

int main() {
    int fd;
    struct stat sb;
    char *mapped;

    // Abre el archivo
    fd = open("archivo.txt", O_RDONLY);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    // Obtiene el tamaño del archivo
    if (fstat(fd, &sb) == -1) {
        perror("fstat");
        exit(EXIT_FAILURE);
    }

    // Mapea el archivo a memoria
    mapped = mmap(NULL, sb.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
    if (mapped == MAP_FAILED) {
        perror("mmap");
        exit(EXIT_FAILURE);
    }

    // Ahora puedes acceder al contenido del archivo a través de 'mapped'
    printf("Contenido del archivo:\n%s\n", mapped);

    // Deshace el mapeo
    if (munmap(mapped, sb.st_size) == -1) {
        perror("munmap");
        exit(EXIT_FAILURE);
    }

    // Cierra el archivo
    if (close(fd) == -1) {
        perror("close");
        exit(EXIT_FAILURE);
    }

    return 0;
}
