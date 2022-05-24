#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<string.h>
#include<fcntl.h>

int main(){
int fd,len;
char buff[50]="message";
char kerndata[50];
len = strlen(buff);
fd=open("/dev/device_name" ,O_RDWR);
if(fd<0){
	perror(" ");
}
else{
	write(fd,buff,len);
	read(fd,kerndata,len);
	printf("%s\n%s",buff,kerndata);
   	}
close(fd);
return 0;
}

