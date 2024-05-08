#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>
#include <math.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Uso: %s <archivo>\n", argv[0]);
        return 1;
    }

    char *archivo = argv[1];
    struct stat info;

    if (stat(archivo, &info) == -1) {
        perror("stat");
        return 1;
    }

    printf("  Fichero: %s\n", archivo);
    printf("  Tamaño: %ld        ", info.st_size);
    printf("Bloques: %ld        Bloque E/S: %ld     fichero ", info.st_blocks, info.st_blksize);

    if (S_ISREG(info.st_mode))
        printf("regular\n");
    else if (S_ISDIR(info.st_mode))
        printf("directorio\n");
    else if (S_ISCHR(info.st_mode))
        printf("dispositivo de caracteres\n");
    else if (S_ISBLK(info.st_mode))
        printf("dispositivo de bloques\n");
    else if (S_ISFIFO(info.st_mode))
        printf("dIFO/pipe\n");
    else if (S_ISLNK(info.st_mode))
        printf("dnlace simbólico\n");
    else if (S_ISSOCK(info.st_mode))
        printf("socket\n");
    else
        printf("tipo desconocido\n");

    printf("Dispositivo: %ld            ", info.st_dev);
    printf("Nodo-i: %ld     ", info.st_ino);
    printf("Enlaces: %ld\n", info.st_nlink);
    printf("Acceso: %o                  ", info.st_mode & 0777);
    printf("Uid: %d      ", info.st_uid);
    printf("Gid: %d\n", info.st_gid);

    char access_time[20];
    char modification_time[20];
    char change_time[20];
    char creation_time[20];

    strftime(access_time, sizeof(access_time), "%Y-%m-%d %H:%M:%S", localtime(&info.st_atime));
    strftime(modification_time, sizeof(modification_time), "%Y-%m-%d %H:%M:%S", localtime(&info.st_mtime));
    strftime(change_time, sizeof(change_time), "%Y-%m-%d %H:%M:%S", localtime(&info.st_ctime));
    strftime(creation_time, sizeof(creation_time), "%Y-%m-%d %H:%M:%S", localtime(&info.st_ctime));

    printf("Acceso: %s\n", access_time);
    printf("Modificación: %s\n", modification_time);
    printf("Cambio: %s\n", change_time);
    printf("Creación: %s\n", creation_time);


    return 0;
}