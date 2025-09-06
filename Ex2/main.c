#include <stdio.h>
#include <sys/stat.h>
#include <time.h>

int main(int argc, char *argv[]) {
    struct stat Stat;
    if (argc != 2) {
        printf("Usage: filestat <path_to_file>\n");
        return 0;
    }
    printf("%s test\n", argv[1]);
    if (lstat(argv[1], &Stat) == -1) {
	perror("lstat");
        return 1;
    };

    if (S_ISLNK(Stat.st_mode)) {
        printf("%s Is a symbolic link\n", argv[1]);
    } else if (S_ISDIR(Stat.st_mode)) {
        printf("%s Is a Directory\n", argv[1]);
    } else if (S_ISREG(Stat.st_mode)) {
        printf("%s Is a regular file\n", argv[1]);
    };

    printf("Size: %lld\n", (long long)Stat.st_size);
    printf("Last modified: %s", ctime(&Stat.st_mtime));
}
