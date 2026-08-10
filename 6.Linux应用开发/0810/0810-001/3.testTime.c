#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/sysmacros.h>
#include <time.h>
#include <err.h>
#include <errno.h>
#include <dirent.h>
#include <strings.h>
#include <unistd.h>
#include <signal.h>
#include <syslog.h>
#include <pwd.h>
int main()
{
    int index = 1000;
    uid_t currentUid = getuid();
    struct passwd *pwd = getpwuid(currentUid);
    while (1)
    {
        // syslog(LOG_DAEMON,"Hello!user %d\n",index++);
        time_t curr_time = time(NULL);
        struct tm *currentTime = localtime(&curr_time);

        fprintf(stderr,
                "uid:%d user: %s setMessage:Hello(%d) onTime:%d-%d-%d %d:%d:%d\n",
                currentUid,
                pwd->pw_name,
                index++,
                currentTime->tm_year + 1900,
                currentTime->tm_mon + 1,
                currentTime->tm_mday,
                currentTime->tm_hour,
                currentTime->tm_min,
                currentTime->tm_sec);
        sleep(10);
    }
}