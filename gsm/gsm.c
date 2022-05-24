#include<stdio.h>
#include<string.h>

#include<termios.h>
#include<errno.h>
#include<unistd.h>
#include<fcntl.h>

int len,fd;
#define SIZE 1024
unsigned char buf[SIZE]={0x00};


/*
   struct msg_event{
   unsigned char no[14];
   unsigned char msg_id[2];
   };
   */


void appendcrlf(unsigned char *buf){
	len=strlen(buf);
	buf[len++] = 0xd;
	buf[len]=0xa;
}
/*
   unsigned char *get_msg_id(void *buf1, int len)
   {
   int i=2;
   unsigned char read_sms[25] = {0x00};
   unsigned char *buf = (unsigned char *)buf1;
   struct msg_event msg_eve;
//+CMTI: "ME",10

//d a 2b 43 4d 54 49 3a 20 22 4d 45 22 2c 31 30 d a
//+CMGR,    16/ 0X...................
if(buf[i++] == 0x2b)
{
if(buf[i++] == 0x43)
if(buf[i++] == 0x4d)
if(buf[i++] == 0x54)
if(buf[i++] == 0x49)
{
memcpy(&msg_eve, buf, len);
printf("Received msg id is: %s\n",msg_eve.msg_id);
strcat(read_sms,"at+cmgr=");
strcat(read_sms,msg_eve.msg_id);
appendcrlf(read_sms);
printf("final: %s \n", read_sms);
write(fd, read_sms, strlen(read_sms));
return (&msg_eve.msg_id);
}
}
return NULL;
}

void send_sms(unsigned char *buf,unsigned char ph[]){
	unsigned char message[25]={0x00};
	strcat(buf,"at+cmgs=");
	strcat(buf,"\"");
	strcat(buf,ph);
	strcat(buf,"\"");
	appendcrlf(buf);
	write(fd,buf,strlen(buf));
	printf("enter message here\n");
	scanf("%s",message);
	int l1=strlen(message);
	message[l1++] = 0x1a;
	write(fd,message,sizeof(message));


}
*/
  void call(unsigned char *buf, unsigned char *ph){
   strcat(buf,"atd");
//printf("enter the number:");
//scanf("%s",ph);
strcat(buf,ph);
strcat(buf,";");
appendcrlf(buf);
printf("call:%s\n",buf);
write(fd,buf,strlen(buf));

}


int serial_port_init(unsigned char *dev){
	if(dev==NULL)
		return -1;
	int serial_port=open(dev,O_RDWR);
	struct termios tty;
	if(tcgetattr(serial_port, &tty) != 0) {
		printf("Error %i from tcgetattr: %s\n", errno, strerror(errno));
		return 1;
	}


	tty.c_cflag &= ~PARENB; // Clear parity bit, disabling parity (most common)
	tty.c_cflag &= ~CSTOPB; // Clear stop field, only one stop bit used in communication (most common)
	tty.c_cflag &= ~CSIZE; // Clear all bits that set the data size 
	tty.c_cflag |= CS8; // 8 bits per byte (most common)
	tty.c_cflag &= ~CRTSCTS; // Disable RTS/CTS hardware flow control (most common)
	tty.c_cflag |= CREAD | CLOCAL; // Turn on READ & ignore ctrl lines (CLOCAL = 1)

	tty.c_lflag &= ~ICANON;
	tty.c_lflag &= ~ECHO; // Disable echo
	tty.c_lflag &= ~ECHOE; // Disable erasure
	tty.c_lflag &= ~ECHONL; // Disable new-line echo
	tty.c_lflag &= ~ISIG; // Disable interpretation of INTR, QUIT and SUSP
	tty.c_iflag &= ~(IXON | IXOFF | IXANY); // Turn off s/w flow ctrl
	tty.c_iflag &= ~(IGNBRK|BRKINT|PARMRK|ISTRIP|INLCR|IGNCR|ICRNL); // Disable any special handling of received bytes

	tty.c_oflag &= ~OPOST; // Prevent special interpretation of output bytes (e.g. newline chars)
	tty.c_oflag &= ~ONLCR; // Prevent conversion of newline to carriage return/line feed
	// tty.c_oflag &= ~OXTABS; // Prevent conversion of tabs to spaces (NOT PRESENT ON LINUX)
	// tty.c_oflag &= ~ONOEOT; // Prevent removal of C-d chars (0x004) in output (NOT PRESENT ON LINUX)

	tty.c_cc[VTIME] = 10;    // Wait for up to 1s (10 deciseconds), returning as soon as any data is received.
	tty.c_cc[VMIN] = 0;

	// Set in/out baud rate to be 9600
	cfsetispeed(&tty, B9600);
	cfsetospeed(&tty, B9600);

	// Save tty settings, also checking for error
	if (tcsetattr(serial_port, TCSANOW, &tty) != 0) {
		printf("Error %i from tcsetattr: %s\n", errno, strerror(errno));
		return 1;
	}
}
void main(void)
{
	fd = serial_port_init("/dev/ttyUSB0");
	while(1)
	{

		//	len = strlen(buf);
		//	printf("len: %d\n",len);
		//	printf("%s: \n",buf);
		unsigned char ph[25];
		printf("enter the number:\n");
		scanf("%s",ph);
//		send_sms(buf,ph);
		//	printf("enter ph num\n");
		//	printf("enter ph num\n");
		//	scanf("%s",ph);
			call(buf, ph);
		read(fd,buf,SIZE);
		printf("%s\n",buf);
		memset(buf, 0x00, SIZE);
		sleep(1);
	}
}

