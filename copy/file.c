#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdio.h>
#include<unistd.h>
#include<error.h>
int main()
{
int fd1,fd2;
char buf;
fd1=open("file",O_RDONLY);
fd2=open("second_file", O_WRONLY | O_CREAT,00700);
if(fd1 != -1)
{
while(read(fd1,&buf,1))
{
write(fd2,&buf,1);
}
printf("copying successful\n");
}
else
printf("file not opened\n");
perror(" ");
close(fd1);
close(fd2);
}
