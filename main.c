#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <dirent.h>
#include <errno.h>
#include <string.h>

#define BUFSIZE 128

void usage(int *argc, char **argv) {
	fprintf(stderr, "\"Argument list too long\" Incinerator\n");
	fprintf(stderr, "\n*** Run binary outside the target directory ***\n");
	fprintf(stderr, "\nUsage: %s <dir>\n", argv[0]);
	exit(1);
}

int main(int argc, char **argv) {

    DIR *dirp;
	int dir_fd = 0, count = 0;
    struct dirent *dp;
	char dir[BUFSIZE];
	
	if((argv[1] == NULL) || (argc > 2) || ((strcmp((argv[1]), ".")) == 0))
		usage(&argc, argv);

	dirp = opendir(argv[1]);
	chdir(argv[1]);

	while((dp = readdir(dirp)) != NULL) {
		fprintf(stderr, "%s\n", dp->d_name);
		unlink(dp->d_name);
	}

	closedir(dirp);

	return 0;
}

