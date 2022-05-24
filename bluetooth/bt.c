#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<fcntl.h>
#include<errno.h>

int main(){
	int fd ,len;
	 char buff[512];
	fd=open("/dev/ttyUSB0",O_RDWR);
	if(fd<0){
		printf("file not opened\n");
		perror(" ");
	}
	else
	{
	//	len=strlen(buff);
	while(read(fd,buff,sizeof(buff)))

		printf("%s",buff);
	}
	return 0;
}


