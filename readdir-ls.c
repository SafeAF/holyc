//readdir
// we are building ls

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <errno.h>

int main(int argc, char *argv[]){
	if(argc < 2){
	    fprintf(stderr, "Usage: %s <directory_path>\n", argv[0]);
        return EXIT_FAILURE;
	}

	DIR *dirp = opendir(argv[1]);
	if(dirp == NULL){
		perror("opendir");
		return EXIT_FAILURE;
	}

	struct dirent *entry;

	while((entry = readdir(dirp)) != NULL){
		printf("Name %s\n", entry->d_name);
		printf("Inode: %lu\n", (unsigned long) entry->d_ino);
		printf("Record length %u\n", entry->d_reclen);
		printf("Type: %u\n\n", entry->d_type);
	}

	if(closedir(dirp) == -1){
		perror("closedir");
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}