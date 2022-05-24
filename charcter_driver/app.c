#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<string.h>
#include<fcntl.h>

int main(){
int fd1,fd2,len;
char buff[50]="hello world cpg";
char kerndata[50];
len = strlen(buff);
fd1=open("/dev/mychardev-0" ,O_RDWR);
//fd2=open("/dev/mychardev-1" ,O_RDWR);
if(fd1<0){
	perror(" ");
}
else{
	write(fd1,buff,len);
	read(fd1,kerndata,len);	
	printf("dtat from user :%s\n", kerndata);
}
close(fd1);
//close(fd2);
return 0;
}

