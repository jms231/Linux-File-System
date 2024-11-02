#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
int checkMtime(time_t mtime, char *mmin) {
    int minutes = atoi(mmin);
    time_t currentTime = time(NULL);
/*returns result of comparision operations to find so that the conditional statement knows whether or not to print file path
multiplies mins by 60 to convert to seconds as he currenttime-mtime result is in seconds.*/
	//multiplies minutes by- to convert back to a positive value for comparison operation
	if (mmin[0] == '-'){
		return ((currentTime - mtime) < (minutes*-60));
    	}
	else if (mmin[0] == '+') {
        	return (mtime - currentTime) < (minutes*60);
    	}
    	else {
        	return (currentTime - mtime) == (minutes*60);
    	}
}



//find function to find the file with given conditions. 
void find(char *where, char *name, char *mmin, char *inum) {
       	DIR *dp = opendir(where);
    	struct dirent *dirp;
	struct stat fileInfo;
   	if (dp != NULL) {
       		 while ((dirp = readdir(dp)) != NULL) {
           	 char *filename = dirp->d_name;
           	 char *filepath=malloc(sizeof(char)*2000);
           	 sprintf(filepath, "%s/%s", where, filename);

            		if (strcmp(filename, ".") != 0 && strcmp(filename, "..") != 0) {
                
                		if (lstat(filepath, &fileInfo) == 0) {
					//if name is the same it prints the file path.
     				        if (((name != NULL && strcmp(filename, name) == 0)))
						printf("%s\n", filepath);
					//gets the result of the comparison operation from checkMtime
					else if((mmin != NULL && checkMtime(fileInfo.st_mtime, mmin)))
                       				printf("%s\n", filepath);
					//returns file path after converting inum from user into unsigned long and comparing.
					else if ((inum != NULL && fileInfo.st_ino == strtoul(inum, NULL, 10))) {
                        			printf("%s\n", filepath);
                    		}
				//checks if file is a directory and procedes to recursively call the find function if it is.
                    		if (S_ISDIR(fileInfo.st_mode)) {
                        		find(filepath, name, mmin, inum);  // Recursively search subdirectories
                   	 	}
               			}
            		}
        	}
        closedir(dp);
	}
}


int main(int argc, char **argv) {
    char *where = NULL, *name = NULL, *mmin = NULL, *inum = NULL;

    if (argc < 4) {
        printf("Incorrect format. Ex: Command dirname -name (filename)\n");
        exit(1);
    }

    where = argv[1];

    if (strcmp(argv[2], "-name") == 0 || strcmp(argv[2], "-n") == 0) {
        name = argv[3];
    } else if (strcmp(argv[2], "-mmin") == 0 || strcmp(argv[2], "-m") == 0) {
        mmin = argv[3];
    } else if (strcmp(argv[2], "-inum") == 0 || strcmp(argv[2], "-i") == 0) {
        inum = argv[3];
    } else {
        printf("Incorrect format. Ex: Command dirname -name (filename)\n");
        exit(1);
    }

    // Call the find function based on the specified criteria
    find(where, name, mmin, inum);

    exit(0);
}

