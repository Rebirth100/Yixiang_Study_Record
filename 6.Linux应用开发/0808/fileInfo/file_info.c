#include "file_info.h"
// TODO:文件信息fileInfo
char *fileInfo(const char *fileName, char *info)
{
    if (fileName == NULL || info == NULL)
    {
#ifdef DEBUG
        fprintf(stderr, "callFunction:fileInfo 参数错误 fileName:%p info:%p\n", fileName, info);
#endif
        return NULL;
    }

    if (strlen(fileName) == 0)
    {
#ifdef DEBUG
        fprintf(stderr, "callFunction:fileInfo 参数错误 strlen(fileName):%ld\n", strlen(fileName));
#endif
        return NULL;
    }

    struct stat sb;
    if (lstat(fileName, &sb))
    {
#ifdef DEBUG
        perror("call lstat错误");
#endif
        return NULL;
    }
    // TODO:TYPE
    char type = '\0';
    switch (sb.st_mode & 0770000)
    {
    case 0100000:
        type = '-';
        break;
    case 040000:
        type = 'd';
        break;
    case 010000:
        type = 'p';
        break;
    case 0120000:
        type = 'l';
        break;
    case 060000:
        type = 'b';
        break;
    case 020000:
        type = 'c';
        break;
    case 0140000:
        type = 's';
        break;
    default:
        type = '?';
        break;
    }

    // TODO:TYPE:MODE
    mode_t mode = sb.st_mode & 0777;
#ifdef DEBUG
    printf("%-20s\tmode:%#o\n", fileName, mode);
#endif
    // 3542
    // 542 =>101 100 010
    char modeBits[10] = {'\0'};
    for (int i = 0; i < 9; i++)
    {
        modeBits[8 - i] = ((mode >> i) & 01) ? '1' : '0';
    }
#ifdef DEBUG
    printf("%-20s\tmode:%s\n", fileName, modeBits);
#endif
    // 101 100 010
    // r-x r-- -w-
    char modAnds[4] = {"rwx"};
    for (int i = 0; i < 9; i++)
    {
        modeBits[i] = (modeBits[i] == '1') ? modAnds[i % 3] : '-';
    }
#ifdef DEBUG
    printf("%-20s\tmode:%s\n", fileName, modeBits);
#endif
    // 3
    mode_t setMode = (sb.st_mode >> 9) & 07;
#ifdef DEBUG
    printf("%-20s\tsetMode:%d\n", fileName, setMode);
#endif
    if (setMode & 01)
    {
        modeBits[8] = ((modeBits[8] == 'x') ? 't' : 'T');
    }
    if ((setMode >> 1) & 01)
    {
        modeBits[5] = ((modeBits[5] == 'x') ? 's' : 'S');
    }
    if ((setMode >> 2) & 01)
    {
        modeBits[2] = ((modeBits[2] == 'x') ? 's' : 'S');
    }
#ifdef DEBUG
    printf("%-20s\tmode:%s\n", fileName, modeBits);
#endif

    // TODO:HARD_LINKS
    nlink_t hardLinks = sb.st_nlink;

    // TODO:owner
    char owner[64] = "\0";
    struct passwd *pwd = getpwuid(sb.st_uid);
    struct group *grp = getgrgid(sb.st_gid);
    sprintf(owner, "%s %s", pwd->pw_name, grp->gr_name);

    // TODO:TOTAL_SIZE
    off_t totalSize = sb.st_size;

    // TODO:atime
    char timeText[32] = "\0";
    struct tm *fileTime = localtime(&(sb.st_atime));
    // 8月  7 15:31
    sprintf(timeText, "%d月 %d %d:%d",
            fileTime->tm_mon + 1,
            fileTime->tm_mday,
            fileTime->tm_hour,
            fileTime->tm_min);

    sprintf(info, "%c%s %ld %s %ld %s",
            type, modeBits, hardLinks,
            owner, totalSize, timeText);
    return info;
}

// TODO:目录下的子文件信息
void dirFileInfo(const char *path, char *info)
{
    if (path == NULL || info == NULL)
    {
#ifdef DEBUG
        fprintf(stderr, "调用%s 参数错误path:%p info:%p\n", __FUNCTION__, path, info);
#endif
        return;
    }
    if (strlen(path) == 0)
    {
#ifdef DEBUG
        fprintf(stderr, "调用%s path中无内容\n", __FUNCTION__);
#endif
        return;
    }

    if (isDirect(path) != 1)
    {
#ifdef DEBUG
        fprintf(stderr, "path:%s不是目录\n", path);
#endif
        return;
    }

    char fileAttrib[256] = "\0";
    DIR *Dir = opendir(path);
    if (Dir)
    {
        struct dirent *dir = readdir(Dir);
        while (dir)
        {
            chdir(path);
            fileInfo(dir->d_name, fileAttrib);
            fprintf(stderr, "%s %s\n", fileAttrib, dir->d_name);

            dir = readdir(Dir);
        }
    }
}

// TODO:是否是目录
int isDirect(const char *path)
{
    if (path == NULL)
    {
#ifdef DEBUG
        fprintf(stderr, "调用%s 参数错误path:%p\n", __FUNCTION__, path);
#endif
    }
    if (strlen("path") == 0)
    {
#ifdef DEBUG
        fprintf(stderr, "调用%s path中无内容\n", __FUNCTION__);
#endif
    }
    struct stat sb;
    if (lstat(path, &sb))
    {
        perror("lstat错误");
        return -1;
    }

    if (S_ISDIR(sb.st_mode))
    {
        return 1;
    }
    return 0;
}