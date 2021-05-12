/* simple text mode mastermind game for lccwin-32
   compiled also without any changes under cc65 6502 cross compiler
   www.cc65.org
   (c) 2002-2006 Peter Sieg, Rabishauerstr.9, D-37603 Holzminden,
   peter.sieg1@gmx.de
   program under GNU GPL
   greeting to my family: Heike, Robin and Janis
*/

// ported to dutchtronix term output in 2021/05/12

// C library headers
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Linux headers
#include <fcntl.h> // Contains file controls like O_RDWR
#include <errno.h> // Error integer and strerror() function
#include <termios.h> // Contains POSIX terminal control definitions
#include <unistd.h> // write(), read(), close()
#define WORD int


/*-------------------------------------------------------------------
// Main programm
//-----------------------------------------------------------------*/

void main()
{
   unsigned ret;
   WORD a;
   WORD statusm,apid;
   char ad;
   int bv;
   char ch[20],my[20];
   WORD done;
   WORD i,j,count,offcnt;
   WORD z1,z2,z3,z4; /* 4 digits for my 4-digit char array */
   WORD echo_xy[4];

  // Use current time as 
  // seed for random generator
  srand(time(0));

  // Open the serial port. Change device path as needed (currently set to an standard FTDI USB-UART cable type device)
  int serial_port = open("/dev/ttyUSB0", O_RDWR);

  // Create new termios struc, we call it 'tty' for convention
  struct termios tty;

  // Read in existing settings, and handle any error
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

  // Set in/out baud rate to be 115200
  cfsetispeed(&tty, B115200);
  cfsetospeed(&tty, B115200);

  // Save tty settings, also checking for error
  if (tcsetattr(serial_port, TCSANOW, &tty) != 0) {
      printf("Error %i from tcsetattr: %s\n", errno, strerror(errno));
      return 1;
  }

   unsigned char msg[80];
   for (;;) { 
   // cls
   unsigned char cls[] = { '\xff', '\xf6', '\x0' };

   count = 1; offcnt = 0; done = 0;
   /* create random 4-digit string in char array my */
   /* strcpy(my,"1234"); */

   z1 = (rand() % 9) + 1; /* 1..9 */
   do { z2 = (rand() % 9) + 1; } while (z2==z1);
   do { z3 = (rand() % 9) + 1; } while ((z3==z1) || (z3==z2));
   do { z4 = (rand() % 9) + 1; } while ((z4==z1) || (z4==z2) || (z4==z3));
   my[0] = z1+48; /* int 1..9 + ascii(48)='0' => '1'..'9' */
   my[1] = z2+48;
   my[2] = z3+48;
   my[3] = z4+48;
   my[4] = 0;     /* terminate string */

   write(serial_port, cls,sizeof(cls));
   sprintf(msg,"Guess my 4-digit    number...(%s);    0000 to abort.\n\n","****");
   write(serial_port,msg,56);
   sleep(3);
   /* insert my to see code */
   do {
     sprintf(msg,"# %02d: ",count+offcnt*10);
     write(serial_port,msg,6);
     scanf("%s",&ch);
     ch[4] = 0;
     write(serial_port,ch,4);
     write(serial_port,"-",1);
     if (strcmp("0000",ch)==0) done = 2; /* give up */
     if (strcmp(my,ch)==0) done = 1; /* success; code broken */
     /* check how near guess it and print hint */
     /* for right digit at  right position print # */
     /* for right digit but wrong position print + */
     if (done==0) {
       for (i=0;i<4;i++) {
         if (ch[i]==my[i]) write(serial_port,"# ",2);
         else for (j=0;j<4;j++) if (ch[i]==my[j]) write(serial_port,"+ ",2);
       }
     }
     write(serial_port,"\n",1);
     count++;
     if (count==11) {
       count = 1;
       offcnt++;
     }
   } while (done==0);
   if (done==1)
     sprintf(msg,"\nYou broke the code!");
   else
     sprintf(msg,"\nYou gave up..      ");
   write(serial_port,msg,20);
   sleep(10);
   }
   exit(0);
}

