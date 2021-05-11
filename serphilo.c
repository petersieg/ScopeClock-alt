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

#define MAX 50 // max number of msgs

int main() {
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

  // Write to serial port
  
  // cls
  unsigned char cls[] = { '\xff', '\xf6', '\x0' };
  write(serial_port, cls,sizeof(cls));
  
 /*                                                                                                  1         1         1
           1         2         3         4         5         6         7         8         9         0         1         2
  123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890
 */
  char *msg[MAX] = { 
"Der der ich bin     gruesst traurig den der ich sein moechte.                                                        \r\r",
"Der Idealismus      waechst mit der     Entfernung vom      Problem.                                                 \r\r",
"Fernsehen unterhaeltdie Leute indem es  verhindert dass sie sich unterhalten.                                        \r\r",
"Ein Plan der sich   nicht aendern laesstist ein schlechter Plan.                                                     \r\r",
"Fehler die wir      einsehen koennen    nicht mehr ins Auge gehen.                                                   \r\r",
"Der Vorteil der     Klugheit besteht    darin dass man sich dumm stellen kann.  Das Gegenteil ist   schwieriger.     \r\r",
"Eine Familie ist einsteuerlich beguenstigter Kleinbetrieb   zur Herstellung     von Steuerzahlern.                   \r\r",
"Traeume nicht dein  Leben lebe deinen   Traum.                                                                       \r\r",
"Wer keinen Mut zum  Traeumen hat hat    keine Kraft zum     Kaempfen.                                                \r\r",
"In Dir muss brennen was Du in anderen   entzuenden moechtest                                                         \r\r",
"Ein Freund ist ein  Mensch vor dem man  laut denken kann.                                                            \r\r",
"Menschen die nicht  an sich selbst      glauben koennen     anderen keinen Halt geben.                               \r\r",
"Wenn man seine Ruhe nicht in sich findetist es zwecklos sie anderswo zu suchen.                                      \r\r",
"An dem Tag an dem duzu reisen aufhoerst wirst du angekommen sein.                                                    \r\r",
"Die modernste Form  menschlicher Armut  ist das Keine-Zeit- Haben.                                                   \r\r",
"ZEIT ist keine      Schnellstrasse zw.  Wiege und Grab      sondern Platz zum   Parken in der SONNE.                 \r\r",
"Der Zufall ist der  gebraeuchlichste    Deckname von Gottes Plan.                                                    \r\r",
"Es ist moralisch    notwendig das DaseinGottes anzunehmen.                                                           \r\r",
"Auge um Auge bedeutet nur dass die Welt erblindet.                                                                   \r\r",
"Der Mensch ist      nichts anderes als  wozu er sich macht.                                                          \r\r",
"Die Schoenheit der  Dinge lebt in der   Seele dessen der siebetrachtet.                                              \r\r",
"Du kannst dem Leben nicht mehr Tage     geben aber dem Tag  mehr Leben.                                              \r\r",
"Wege entstehen      dadurch dass man siegeht.                                                                        \r\r",
"Wende Dich stets derSonne zu dann fallendie Schatten hinter Dich.                                                    \r\r",
"Glueck bedeutet     nicht das zu kriegenwas wir wollen      sondern das zu      wollen was wir      kriegen.         \r\r",
"Phantasie ist       wichtiger als Wissendenn Wissen ist     begrenzt.                                                \r\r",
"Gib jedem Tag die   Chance der schoenstedeines Lebens zu    werden.                                                  \r\r",
"Nicht der ist ein   Verlierer der       hinfaellt sondern   der der liegenbleibt                                     \r\r",
"Man kann dir den Wegweisen gehen musst  du ihn selbst.                                                               \r\r",
"Eine schmerzliche   Wahrheit ist besser als eine Luege.                                                              \r\r",
"Selbst eine Reise   von tausend Meilen  beginnt mit dem     ersten Schritt.                                          \r\r",
"Wer einen Fehler    macht und ihn nicht korrigiert begeht   einen zweiten.                                           \r\r",
"Die Menschen        verlieren die meisteZeit damit dass sie Zeit gewinnen wollen                                     \r\r",
"Ein Tag ohne zu     Laecheln ist ein    verlorener Tag.                                                              \r\r",
"Das Glueck ist das  einzige was sich    verdoppelt wenn man es teilt.                                                \r\r",
"Jede Roheit hat     ihren Ursprung in   einer Schwaeche.                                                             \r\r",
"Kinder die man nichtliebt werden        Erwachsene die nichtlieben.                                                  \r\r",
"Ich kann die Welt   nicht veraendern    aber einen einzelnenMenschen -          mich selbst.                         \r\r",
"Der Optimist sieht  in jedem Problem    eine Aufgabe. Der   Pessimist sieht in  jeder Aufgabe ein   Problem.         \r\r",
"Der beste Weg einen schlechten Vorschlagvom Tisch zu wischenbesteht darin einen Besseren zu machen.                  \r\r",
"Nicht die Jahre in  unserem Leben       zaehlen sondern das Leben in unseren    Jahren zaehlt.                       \r\r",
"Die Grenzen des     Moeglichen lassen   sich nur bestimmen  indem man sich uebersie hinaus ins Unmoegliche wagt.     \r\r",
"Tritt nicht in die  Fussstapfen anderer du hinterlaesst     sonst selbst keine  Spuren.                              \r\r",
"Weine nicht weil es vorbei ist sondern  lache weil es so    schoen war.                                              \r\r",
"Mitleid bekommt man geschenkt. Neid mussman sich hart       erarbeiten.                                              \r\r",
"Wenn jemand sagt er habe keine Zeit     bedeutet das nur    dass andere Dinge   wichtiger fuer ihn  sind.            \r\r",
"Wenn Du immer nur   das tust was Du     bereits kannst      bleibst Du immer nurdas was Du heute    bist.            \r\r",
"Erfolg besteht darindass man genau die  Faehigkeiten hat dieim Moment gefragt   sind.                                \r\r",
"Wenn wir nicht immerwieder etwas Neues  probiert haetten    wuerden wir heute   noch in Hoehlen     leben.           \r\r",
"Es gibt viele die   suchen das ganze    Leben nach dem Sinn.Dabei hat es gar    keinen. Man muss ihmeinen geben.     \r\r"};

  
  unsigned int num = rand() % MAX;
  write(serial_port, msg[num], 119);

  // Allocate memory for read buffer, set size according to your needs
  // char read_buf [256];

  // Normally you wouldn't do this memset() call, but since we will just receive
  // ASCII data for this example, we'll set everything to 0 so we can
  // call printf() easily.
  // memset(&read_buf, '\0', sizeof(read_buf);

  // Read bytes. The behaviour of read() (e.g. does it block?,
  // how long does it block for?) depends on the configuration
  // settings above, specifically VMIN and VTIME
  // int num_bytes = read(serial_port, &read_buf, sizeof(read_buf));

  // n is the number of bytes read. n may be 0 if no bytes were received, and can also be -1 to signal an error.
  // if (num_bytes < 0) {
  //     printf("Error reading: %s", strerror(errno));
  //     return 1;
  // }

  // Here we assume we received ASCII data, but you might be sending raw bytes (in that case, don't try and
  // print it to the screen like this!)
  // printf("Read %i bytes. Received message: %s", num_bytes, read_buf);

  close(serial_port);
  return 0; // success
}

