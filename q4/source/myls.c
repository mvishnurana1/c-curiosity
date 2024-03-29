#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>
#include <sys/sysmacros.h>

#define BUF_SIZE 256

/**
 * The function returns the time credentials 
 * of the file/dir.
 */
char* printTime(time_t time, char *buff){
    struct tm *timeinfo; 
    timeinfo = localtime(&time);

    char * st = buff;
    // the function strftime formats the broken-down time tm 
    // according to the format specs. 
    //              %b -> abbreviated month name
    //              %d -> day of the month ranging from 1 - 31
    strftime(buff, 8, "%b %d\t", timeinfo); 
    buff = buff +7;
    //              %R -> 24 hour notation %H:%M
    strftime(buff, 90, "%R", timeinfo); 

    return st; 
}

/**
 * The function returns the group name  
 */
char* getGroupName(char *buff, gid_t gid){
    struct group *grp; 
    // the function getgrgid returns a pointer to a structure containing
    // the group database that matches the group ID gid
    grp = getgrgid(gid);

    strcpy(buff, grp->gr_name); 
    return buff; 
}

/**
 * The function returns the username  
 */
char* getUserName(char *buff, uid_t uid){
    struct passwd * pwd;
    //getpwuid function searches for a matching uid in the user Database. 
    pwd = getpwuid(uid); 

    strcpy(buff, pwd->pw_name); 

    return buff; 
}

/**
 * The function is essentially a switch case
 * which returns the file type.  
*/
char* getFileType(int mask){
    // bitwise AND for considering the bits involved in the file type 
    int type = mask & S_IFMT;

    switch(type){
        case S_IFSOCK : return "socket"; 
        case S_IFLNK  : return "symbolic link";
        case S_IFREG  : return "regular file";
        case S_IFBLK  : return "block device";
        case S_IFDIR  : return "directory";
        case S_IFCHR  : return "char device";
        case S_IFIFO  : return "FIFO";      
    }
}

struct permMask{
    // permissions 
    char permission;
    // mask 
    short mask;
    // targeted index for mapping  
    int targetIndex;
};

char* getFilePermissions(char * ret, int mask){
    //No permissions
    const int NONE = 00;

    //mapping of output character, file permission mask and output index
    //for each file permission
    const struct permMask masks[] = {
        {'r', 04, 0}, {'w', 02, 1}, {'x', 01, 2}
    };
    const int numMasks = 3;

    strcpy(ret, "---");

    //For each mask, check if its target bit is set, and assign the output character if it is
    for (int i=0; i < numMasks; i++){
        //target bit check
        if ( (mask & masks[i].mask) == masks[i].mask ){
            //assign output character
            ret[masks[i].targetIndex] = masks[i].permission;
        }
    }

    return ret;
}

/**
 * 
 * @param buffer - String of at least size 10. Will be filled with file
 * permission info. End of string will be set to null.
 */
char * getAccessPermissions(char * buffer, int mask){
    //get permission bits from mode mask
    int permissions = mask & 0777;

    //mask out all user permissions (last three bits of permissions mask)
    int all_permissions = (permissions & 07);
    //mask out owner permissions (first three bits of mask)
    int owner_permissions = (permissions & 0700) >> 06;
    //mask out group permissions (middle three bits of mask)
    int group_permissions = (permissions & 070) >> 03;

    //convert bits to string representation at correct buffer indexes.
    getFilePermissions(buffer,  owner_permissions);
    getFilePermissions(buffer + 3,  group_permissions);
    getFilePermissions(buffer + 6,  all_permissions);

    return buffer;
}

int main(int argc, char* *argv){
    struct stat buf; 
    char buff[100];

    int i, res; 
    for(i = 1; i<argc; i++){
        res = stat(argv[i], &buf); 
        printf("%d\n", res);
        
        if(res != -1){
            printf("username            : %s \n", getUserName(buff, buf.st_uid));
            printf("groupname           : %s \n", getGroupName(buff, buf.st_gid));
            printf("size                : %ld\n", buf.st_size);
            printf("type                : %s\n", getFileType(buf.st_mode)); 
            printf("permissions         : %s\n", getAccessPermissions(buff, buf.st_mode)); 
            printf("INode Info          : %ld\n", buf.st_ino);
            printf("Number of Links     : %ld\n", buf.st_nlink);
            printf("Device major version: %d\n", major(buf.st_rdev)); 
            printf("Device minor version: %d\n", minor(buf.st_rdev)); 
            printf("accessed time       : %s\n", printTime(buf.st_atime, buff)); 
            printf("modified time       : %s\n", printTime(buf.st_mtime, buff)); 
            printf("created time        : %s\n", printTime(buf.st_ctime, buff)); 
        }
        else{
            printf("no such file\n");
        }
    }
    return 0; 
}