#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
//recursively reads subdirectories and files
void read_sub(char *sub_dir) {
    DIR *sub_dp = opendir(sub_dir);
    struct dirent *sub_dirp;
	//ensures that directory exists.
    if (sub_dp != NULL) {
	    //while loop to iterate through entire directory.
        while ((sub_dirp = readdir(sub_dp)) != NULL) {
            char *temp = sub_dirp->d_name;
            char temp1[] = ".";
            char temp2[] = "..";
		//if statement to ensure the directory is not the current dir or parent dir
            if (strcmp(temp, temp1) != 0 && strcmp(temp, temp2) != 0) {
		    //print path of current dir
                printf("%s/%s\n", sub_dir, sub_dirp->d_name);
			
                char temp3[] = "/";
                char *temp_sub = temp3;
                temp_sub = strcat(temp_sub, temp);
                char *temp_full_path = malloc(sizeof(char)*2000);
                strcpy(temp_full_path, sub_dir);
                strcat(temp_full_path, temp_sub);
                read_sub(temp_full_path);

            }
        }
        closedir(sub_dp);
    } 
    
}

int main(int argc, char **argv) {
    char *dir;

    if (argc < 2) {
        dir = ".";
    } else {
        dir = argv[1];
    }

    read_sub(dir);

    exit(0);
}

