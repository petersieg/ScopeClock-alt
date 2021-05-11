// Adapted from: https://www.rosettacode.org/wiki/Number_reversal_game#C
// 03/2019 peter.sieg2@gmx.de
// ported to dutchtronix term output in 2021/05/11

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

void shuffle_list(int *list, int len)
{
    //We'll just be swapping 100 times. Could be more/less. Doesn't matter much.
    int n=100;
    int a=0;
    int b=0;
    int buf = 0;
    //Random enough for common day use..
    //srand(time(NULL)); //done in main
    while(n--)
    {
        //Get random locations and swap
        a = rand()%len;
        b = rand()%len;
        buf = list[a];
        list[a] = list[b];
        list[b] = buf;
    }
    // "shuffled to ordered state" fix:
    if (check_array(list, len)) shuffle_list (list, len);
}
 
void do_flip(int *list, int length, int num)
{
    //Flip a part on an array
    int swap;
    int i=0;
    for(i;i<--num;i++)
    {
        swap=list[i];
        list[i]=list[num];
        list[num]=swap;
    }
}
 
int check_array(int *arr, int len)
{
    while(--len)
    {
        if(arr[len]!=(arr[len-1]+1))
            return 0;
    }
    return 1;
}


int main()
{
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
 
    for (;;) { 
    // Write to serial port
    // cls
    unsigned char cls[] = { '\xff', '\xf6', '\x0' };
    write(serial_port, cls,sizeof(cls));
    write(serial_port, "Reversal Game. Type a number to flip thefirst n numbers. \n\n\n", 60);
    sleep(3);
    write(serial_port, cls,sizeof(cls));
    write(serial_port, "Win by sorting the  numbers in ascendingorder.\n\n",48);
    sleep(3);
    write(serial_port, cls,sizeof(cls));
    int list[9] = {1,2,3,4,5,6,7,8,9};
    shuffle_list(list,9);
 
    int tries=0;
    unsigned int i;
    int input;
    unsigned char msg[80];
    
    while(!check_array(list, 9))
    {
        sprintf(msg,"%d %d %d %d %d %d %d %d %d \n\n",list[0],list[1],list[2],list[3],list[4],list[5],list[6],list[7],list[8]);
        write(serial_port, msg,20);
        write(serial_port,"Input number: \n\n",16);
        while(1)
        {
            //Just keep asking for proper input
            scanf("%d", &input);
            if(input>1&&input<10)
                break;
 
            write(serial_port,"\nInput 2-9\n",12);
        }
        tries++;
        do_flip(list, 9, input);
    }
    sprintf(msg,"%d %d %d %d %d %d %d %d %d \n\n",list[0],list[1],list[2],list[3],list[4],list[5],list[6],list[7],list[8]);
    write(serial_port, msg,20);
    sprintf(msg,"Hurray! You solved  it in %02d moves! \n\n", tries);
    write(serial_port, msg,36);
    write(serial_port, "\n\n",2);
    sleep(10);
    }
    close(serial_port);
    return 0; // success
}


