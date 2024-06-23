#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#define DEBUG

typedef int bool;
struct
{
    // TODO add -h option
    bool displayAllFile;        //-a
    bool detailMode;            //-l
    bool reverseMode;           //-r
    bool timeSequence;          //-t
    bool displayInode;          //-i
    bool anotherDisplayAllFile; //-A
    bool addIcon;               //-F
    bool recursiveMode;         //-R
} displayType;
char dirPath[256];

void lsFunc();
void showFileInfo(char filePath[]);

int main(int argc, char *argv[])
{
    memset(&displayType, 0, sizeof(displayType));
    for (int i = 1; i < argc; i++)
    {
        if (argv[i][0] == '-')
        {
            switch (argv[i][1])
            {
            case 'h':
                puts("usage: ./myLs [option] directoryPath");
                return 0;
            case 'a':
                displayType.displayAllFile = 1;
                break;
            case 'l':
                displayType.detailMode = 1;
                break;
            case 'r':
                displayType.reverseMode = 1;
                break;
            case 't':
                displayType.timeSequence = 1;
                break;
            case 'i':
                displayType.displayInode = 1;
                break;
            case 'A':
                displayType.anotherDisplayAllFile = 1;
                break;
            case 'F':
                displayType.addIcon = 1;
                break;
            case 'R':
                displayType.recursiveMode = 1;
                break;
            default:
                printf("ls: invalid option %s ", argv[i]);
                exit(1);
                break;
            }
        }
        else
            strcpy(dirPath, argv[i]);
    }
    if (dirPath[0] == '\0')
    {
        //如果没有输入路径，就是当前目录。
        dirPath[0] = '.';
    }

    lsFunc();

    return 0;
}

void lsFunc()
{
    DIR *dirent;
    struct dirent *ptr;

    dirent = opendir(dirPath);
    //处理文件夹不存在的情况
    if (dirent == NULL)
    {
        printf("this directory %s doesn't exist, please check path you input\n", dirPath);
        exit(1);
    }

    //文件夹存在，执行ls
    while ((ptr = readdir(dirent)) != NULL)
    {
        showFileInfo(ptr->d_name);
    }
    closedir(dirent);
}
void showFileInfo(char filePath[])
{
    if (displayType.detailMode)
    {
        //获取文件详细数据结构 struct stat info
        struct stat info;
        if (stat(filePath, &info) == -1)
        {
            fprintf(stderr, "cannot read info of file %s", filePath);
            exit(-1);
        }
        //读取权限
        char permissions[11];
        strcpy(permissions, "----------");

        if (S_ISDIR(info.st_mode))
        {
            permissions[0] = 'd';
        }
        else if (S_ISBLK(info.st_mode))
        {
            permissions[0] = 'c';
        }
        else if (S_ISCHR(info.st_mode))
        {
            permissions[0] = 'b';
        }
        //创建用户权限
        if (info.st_mode & S_IRUSR)
        {
            permissions[1] = 'r';
        }
        if (info.st_mode & S_IWUSR)
        {
            permissions[2] = 'w';
        }
        if (info.st_mode & S_IXUSR)
        {
            permissions[3] = 'x';
        }

        //用户组权限
        if (info.st_mode & S_IRGRP)
        {
            permissions[4] = 'r';
        }
        if (info.st_mode & S_IWGRP)
        {
            permissions[5] = 'w';
        }
        if (info.st_mode & S_IXGRP)
        {
            permissions[6] = 'x';
        }

        //其他用户权限
        if (info.st_mode & S_IROTH)
        {
            permissions[7] = 'r';
        }
        if (info.st_mode & S_IWOTH)
        {
            permissions[8] = 'w';
        }
        if (info.st_mode & S_IXOTH)
        {
            permissions[9] = 'x';
        }

        //获取用户名
        struct passwd *pwPtr = (struct passwd *)malloc(sizeof(struct passwd));
        struct group *groupPtr = (struct group *)malloc(sizeof(struct group));
        if ((pwPtr = getpwuid(info.st_uid)) == NULL)
        {
            fprintf(stderr, "cannot read userName of %s", filePath);
        };
        if ((groupPtr = getgrgid(info.st_gid)) == NULL)
        {
            fprintf(stderr, "cannot read groupName of %s", filePath);
        };

        //读取用户信息
        int64_t fileSize;
        char *time = ctime(&info.st_atime);
        time[strlen(time) - 1] = '\0';
        if (displayType.displayAllFile)
        {
            if (displayType.displayInode)
            {
                printf("%-10lld ", (uint64_t)info.st_ino);
            }
            // TODO add arguments
            printf("%s %4d %-8s %-8s %8lld %-12s %s\n", permissions, info.st_nlink, pwPtr->pw_name, groupPtr->gr_name, info.st_size, time, filePath);
        }
        // 处理-A
        else if (displayType.anotherDisplayAllFile)
        {
            if (filePath[0] == '.' && (filePath[1] == '\0' || filePath[1] == '.'))
                return;
            if (displayType.displayInode)
            {
                printf("%-10lld ", (uint64_t)info.st_ino);
            }
            printf("%s %4d %-8s %-8s %8lld %-12s %s\n", permissions, info.st_nlink, pwPtr->pw_name, groupPtr->gr_name, info.st_size, time, filePath);
        }
        //没有 -a ,也没有-A,直接输出
        else
        {
            if (filePath[0] == '.')
                return;
            if (displayType.displayInode)
            {
                printf("%-10lld ", (uint64_t)info.st_ino);
            }
            printf("%s %4d %-8s %-8s %8lld %-12s %s\n", permissions, info.st_nlink, pwPtr->pw_name, groupPtr->gr_name, info.st_size, time, filePath);
        }
        // free(pwPtr);
        // free(groupPtr);
    }
    else
    {
        if (displayType.displayAllFile)
        {
            printf("%s \n", filePath);
        }
        // 处理-A
        else if (displayType.anotherDisplayAllFile)
        {
            if (filePath[0] == '.' && (filePath[1] == '\0' || filePath[1] == '.'))
                return;
            printf("%s \n", filePath);
        }
        //没有 -a ,也没有-A,直接输出
        else
        {
            if (filePath[0] == '.')
                return;
            printf("%s \n", filePath);
        }
    }
}
