#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <dirent.h>
#include <errno.h>
#include <string.h>

#define BUFSIZE 128

void usage(int *argc, char **argv) {
	fprintf(stderr, "\"Argument list too long\" Incinerator\n");
	fprintf(stderr, "\n*** Run binary outside the target directory ***\n");
	fprintf(stderr, "\nUsage: %s [-v] dir\n", argv[0]);
	exit(1);
}

int main(int argc, char **argv) {

    DIR *dirp;
	int dir_fd = 0, count = 0;
    struct dirent *dp;
	char dir[BUFSIZE];
	char *target;
	int option = 0;

	char c = '\0';

	if((c = getopt(argc, argv, "v")) == -1)
		target = argv[1];

	else {
		target = argv[2];
		option = 1;
	}

	// input sanitation
	if((argc < 2) || 
		(argc > 3) ||
		(strcmp(target, ".") == 0) ||
		(strcmp(target, "..") == 0) ||
		(strcmp(target, "../") == 0))
		usage(&argc, argv);


	if(option) {
		dirp = opendir(target);
		chdir(target);

		while((dp = readdir(dirp)) != NULL) {
			fprintf(stderr, "%s\n", dp->d_name);
			unlink(dp->d_name);
		}

		closedir(dirp);
	}
	else {
		dirp = opendir(target);
		chdir(target);

		while((dp = readdir(dirp)) != NULL) {
			unlink(dp->d_name);
		}

		closedir(dirp);

	}

	return 0;
}

