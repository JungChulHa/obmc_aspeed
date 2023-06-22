//==============================================================================
//	Serial Test Program (COM1 / COM2)
//		made by JCHA, 2012-03-19
//==============================================================================
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/poll.h>
#include <termios.h>					// B115200, CS8 �� ��� define
#include <fcntl.h>						// O_RDWR , O_NOCTTY ���� ��� define

enum comport_number { COM1, COM2, COM3, COM4 };

#define BAUDRATE B115200	//baudrate setting
//#define BAUDRATE B38400	//baudrate setting
//#define BAUDRATE B9600	//baudrate setting

struct termios oldtio, newtio;	// for terminal attribute save & setting
int serial_fd;					// serial port file descriptor

//------------------------------------------------------------------------------
//	Func: serial open function
//------------------------------------------------------------------------------
int serial_open(int which_port)
{
	char *port_str;
	
	switch(which_port)
	{
	case COM1:
		port_str = "/dev/ttySAC0";
		break;
	case COM2:
		port_str = "/dev/ttySAC1";
		break;
	case COM3:
		port_str = "/dev/ttySAC2";
		break;
	case COM4:
		port_str = "/dev/ttySAC3";
		break;
	default:
		printf(" input serial port error\n");
		exit(EXIT_FAILURE);
	}

	serial_fd = open(port_str, O_RDWR | O_NOCTTY | O_NONBLOCK | O_NDELAY );
	if( serial_fd < 0 )
	{
		printf(" serial_port open error: %s\n", port_str);
		exit(-1);
	}

	tcgetattr(serial_fd, &oldtio);	// save current attribute to oldtio

	bzero(&newtio, sizeof(newtio));
	//newtio.c_cflag = BAUDRATE | CRTSCTS | CS8 | CLOCAL | CREAD;
	newtio.c_cflag = BAUDRATE | CS8 | CLOCAL | CREAD;	// flow control none
	newtio.c_iflag = IGNPAR;

	// preprocessing output: ie. output�ϱ� ���� � ó���� �ؼ� ouput�� �Ѵ�.
	newtio.c_oflag |= OPOST;		// post processing enable
	newtio.c_oflag |= ONLCR;		// ���н� ���� newline(NL:'\n')�� dos���� newline��
									// CR-NL('\r'\'n')���� �ڵ� ��ȯ �ɼ�

	// set input mode (non-canonical, no echo,...)
	newtio.c_lflag = 0;
	
	newtio.c_cc[VTIME]    = 0;		// ���� ������ timer�� disable
	newtio.c_cc[VMIN]     = 1;		// �ּ� 5 ���� ���� ������ blocking
	
	tcflush(serial_fd, TCIFLUSH);
	tcsetattr(serial_fd, TCSANOW, &newtio);

	return 0;
}

//------------------------------------------------------------------------------
//	Func: make pattern	dir=> 0:inc		1:dec
//------------------------------------------------------------------------------
void make_pattern(char *buf, int dir)
{	
	int	i;
	unsigned char ch='A';

	if(dir == 1)
		ch = 'Z';

	for (i=0; i<26; i++)
	{
		buf[i] = ch;
		
		if(dir == 0)
			ch++;
		else
			ch--;
	}
}

//------------------------------------------------------------------------------
//	Func: read from COM port function
//------------------------------------------------------------------------------
void read_COM_port(char* rbuf)
{
	struct	pollfd  poll_events;		// üũ�� event ������ ���� struct
	int		poll_state;
	int 		cnt, i;

	poll_events.fd        = serial_fd;
	poll_events.events    = POLLIN | POLLERR;		// receive data exist? error?
	poll_events.revents   = 0;
	
	// data send/receive
	for (i = 0; i < 10; i++)
	{
		poll_state = poll(							// poll()�� ȣ���Ͽ� event �߻� ���� Ȯ��     
	    		(struct pollfd*)&poll_events,		// event register ����
				1,									// üũ�� pollfd ����
	    		100									// time out �ð�
		);
	
		if ( poll_state > 0 )						// �߻��� event �� ����
		{
			if ( poll_events.revents & POLLIN )		// receive data exist?
			{
				bzero(rbuf, 32);					//clear_pattern( rbuf );
				cnt = read( serial_fd, rbuf, 32 );
				printf( " data received - %d %s\n", cnt, rbuf );
				tcflush  ( serial_fd, TCIFLUSH );
				if (cnt >= 26) break;
			}
			if ( poll_events.revents & POLLERR )	// event is error?
			{
				printf( " Communication error happened!, program is terminated!\n" );
				close( serial_fd );
				exit(-1);
			}
		}
	}
}


//------------------------------------------------------------------------------
//	Func: write to COM prt function
//------------------------------------------------------------------------------
void write_COM_port(char* sbuf, int ptn)
{
	int chkin;
	
	make_pattern( sbuf, ptn%2 ); 			//( A to Z / Z to A )
	chkin = write( serial_fd, sbuf, 26 );			// serial�� 26 char�� string�� ���� 
	
	if (chkin < 0) 
		printf(" cannot write to port\n");

	fcntl( serial_fd, F_SETFL, FNDELAY ); 
	usleep( 100000 );
}


//------------------------------------------------------------------------------
//	Func: main function
//------------------------------------------------------------------------------

int main(void)
{
	int		i, nret;
	char 		sbuf[32], rbuf[32];

	printf("\n");
	//loop COM1 ~ COM3
	for(i=COM1; i<=COM3; i++)
	{
		printf("Serial Loopback Test (COM%d) Start ...\n", i+1);
		serial_open(i);					//set serial_fd (global var)

		write_COM_port(sbuf, i);
		read_COM_port(rbuf);

		nret = strncmp(sbuf, rbuf, 26);

		if ( !nret )
			printf("Serial Loopback Test (COM%d) OK!!!\n\n", i+1);
		else
			printf("Serial Loopback Test (COM%d) Failed!!!\n\n", i+1);

		// return to original attribute
		tcsetattr(serial_fd, TCSANOW, &oldtio);
		close( serial_fd );
	}
	return 0;
}

