#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include<stdio.h>
#include <unistd.h>
#include<string.h>

int main(){
int fd;
char buff[1024];
fd=open("file.c",O_RDONLY);
if(fd<0)
printf("no such file/directory\n");
else
{
int fd1= read(fd,buff,100);
printf("%s%d",buff,fd1);
}
}
