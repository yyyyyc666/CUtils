#include<string.h>
#include<stdio.h>
#include"FileUtil.h"
#include <unistd.h>

int getCurrentDirectory( char * buf, int count){
    int i;
    int rslt = readlink("/proc/self/exe", buf, count - 1);
    if (rslt < 0 || (rslt >= count - 1))
    {
        return 0;
    }
    buf[rslt] = '\0';
    for (i = rslt; i >= 0; i--)
    {
        if (buf[i] == '/')
        {
            buf[i + 1] = '\0';
            break;
        }
    }
    return 1;
}