/*driver app for dutchtronix scopeclock term app
  (C) 2021 peter.sieg2@gmx.de  CC-BY-NC-SA 4.0
  

*/
   
#include <avr/pgmspace.h>
#include <IRremote.h>   // Das Programm greift an dieser Stelle auf eine „Library“ zurück. Das erleichtert einem viel Arbeit. Denn das Infrarotlicht wird mit einem Code verschlüsselt gesendet. Um diesen Code selber auszulesen und in passende Werte umzuwandeln, wären sehr viele Zeilen Code erforderlich.

int RECV_PIN = 11;  //  Der Kontakt der am Infrarotsensor die Daten ausgibt, wird mit Pin 11 des Arduinoboards verbunden.

IRrecv irrecv(RECV_PIN);   // An dieser Stelle wird ein Objekt definiert, dass den Infrarotsensor an Pin 11 ausliest.

decode_results results;  // Dieser Befehl sorgt dafür, dass die Daten, die per Infrarot eingelesen werden unter „results“ abgespeichert werden.

char app = 0;
char buffer[128];
#define MAX 50 // max number of msgs
 /*                                                                                                                              1         1         1
                                       1         2         3         4         5         6         7         8         9         0         1         2
                              123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890
 */
const char msg_0[]  PROGMEM ="Der der ich bin     gruesst traurig den der ich sein moechte                                                         \r\r";
const char msg_1[]  PROGMEM ="Der Idealismus      waechst mit der     Entfernung vom      Problem.                                                 \r\r";
const char msg_2[]  PROGMEM ="Fernsehen unterhaeltdie Leute indem es  verhindert dass sie sich unterhalten.                                        \r\r";
const char msg_3[]  PROGMEM ="Ein Plan der sich   nicht aendern laesstist ein schlechter  Plan.                                                    \r\r";
const char msg_4[]  PROGMEM ="Fehler die wir      einsehen koennen    nicht mehr ins Auge gehen.                                                   \r\r";
const char msg_5[]  PROGMEM ="Der Vorteil der     Klugheit besteht    darin dass man sich dumm stellen kann.  Das Gegenteil ist   schwieriger.     \r\r";
const char msg_6[]  PROGMEM ="Eine Familie ist einsteuerlich beguenstigter Kleinbetrieb   zur Herstellung     von Steuerzahlern.                   \r\r";
const char msg_7[]  PROGMEM ="Traeume nicht dein  Leben lebe deinen   Traum.                                                                       \r\r";
const char msg_8[]  PROGMEM ="Wer keinen Mut zum  Traeumen hat hat    keine Kraft zum     Kaempfen.                                                \r\r";
const char msg_9[]  PROGMEM ="In Dir muss brennen was Du in anderen   entzuenden moechtest                                                         \r\r";
const char msg_10[] PROGMEM ="Ein Freund ist ein  Mensch vor dem man  laut denken kann.                                                            \r\r";
const char msg_11[] PROGMEM ="Menschen die nicht  an sich selbst      glauben koennen     anderen keinen Halt geben.                               \r\r";
const char msg_12[] PROGMEM ="Wenn man seine Ruhe nicht in sich findetist es zwecklos sie anderswo zu suchen.                                      \r\r";
const char msg_13[] PROGMEM ="An dem Tag an dem duzu reisen aufhoerst wirst du angekommen sein.                                                    \r\r";
const char msg_14[] PROGMEM ="Die modernste Form  menschlicher Armut  ist das Keine-Zeit- Haben.                                                   \r\r";
const char msg_15[] PROGMEM ="ZEIT ist keine      Schnellstrasse zw.  Wiege und Grab      sondern Platz zum   Parken in der SONNE.                 \r\r";
const char msg_16[] PROGMEM ="Der Zufall ist der  gebraeuchlichste    Deckname von Gottes Plan.                                                    \r\r";
const char msg_17[] PROGMEM ="Es ist moralisch    notwendig das DaseinGottes anzunehmen.                                                           \r\r";
const char msg_18[] PROGMEM ="Auge um Auge        bedeutet nur dass   die Welt erblindet.                                                          \r\r";
const char msg_19[] PROGMEM ="Der Mensch ist      nichts anderes als  wozu er sich macht.                                                          \r\r";
const char msg_20[] PROGMEM ="Die Schoenheit der  Dinge lebt in der   Seele dessen der siebetrachtet.                                              \r\r";
const char msg_21[] PROGMEM ="Du kannst dem Leben nicht mehr Tage     geben aber dem Tag  mehr Leben.                                              \r\r";
const char msg_22[] PROGMEM ="Wege entstehen      dadurch dass man siegeht.                                                                        \r\r";
const char msg_23[] PROGMEM ="Wende Dich stets derSonne zu dann fallendie Schatten hinter Dich.                                                    \r\r";
const char msg_24[] PROGMEM ="Glueck bedeutet     nicht das zu kriegenwas wir wollen      sondern das zu      wollen was wir      kriegen.         \r\r";
const char msg_25[] PROGMEM ="Phantasie ist       wichtiger als Wissendenn Wissen ist     begrenzt.                                                \r\r";
const char msg_26[] PROGMEM ="Gib jedem Tag die   Chance der schoenstedeines Lebens zu    werden.                                                  \r\r";
const char msg_27[] PROGMEM ="Nicht der ist ein   Verlierer der       hinfaellt sondern   der der liegenbleibt                                     \r\r";
const char msg_28[] PROGMEM ="Man kann dir den Wegweisen gehen musst  du ihn selbst.                                                               \r\r";
const char msg_29[] PROGMEM ="Eine schmerzliche   Wahrheit ist besser als eine Luege.                                                              \r\r";
const char msg_30[] PROGMEM ="Selbst eine Reise   von tausend Meilen  beginnt mit dem     ersten Schritt.                                          \r\r";
const char msg_31[] PROGMEM ="Wer einen Fehler    macht und ihn nicht korrigiert begeht   einen zweiten.                                           \r\r";
const char msg_32[] PROGMEM ="Die Menschen        verlieren die meisteZeit damit dass sie Zeit gewinnen wollen                                     \r\r";
const char msg_33[] PROGMEM ="Ein Tag ohne zu     Laecheln ist ein    verlorener Tag.                                                              \r\r";
const char msg_34[] PROGMEM ="Das Glueck ist das  einzige was sich    verdoppelt wenn man es teilt.                                                \r\r";
const char msg_35[] PROGMEM ="Jede Roheit hat     ihren Ursprung in   einer Schwaeche.                                                             \r\r";
const char msg_36[] PROGMEM ="Kinder die man nichtliebt werden        Erwachsene die nichtlieben.                                                  \r\r";
const char msg_37[] PROGMEM ="Ich kann die Welt   nicht veraendern    aber einen einzelnenMenschen -          mich selbst.                         \r\r";
const char msg_38[] PROGMEM ="Der Optimist sieht  in jedem Problem    eine Aufgabe. Der   Pessimist sieht in  jeder Aufgabe ein   Problem.         \r\r";
const char msg_39[] PROGMEM ="Der beste Weg einen schlechten Vorschlagvom Tisch zu wischenbesteht darin einen Besseren zu machen.                  \r\r";
const char msg_40[] PROGMEM ="Nicht die Jahre in  unserem Leben       zaehlen sondern das Leben in unseren    Jahren zaehlt.                       \r\r";
const char msg_41[] PROGMEM ="Die Grenzen des     Moeglichen lassen   sich nur bestimmen  indem man sich uebersie hinaus ins Unmoegliche wagt.     \r\r";
const char msg_42[] PROGMEM ="Tritt nicht in die  Fussstapfen anderer du hinterlaesst     sonst selbst keine  Spuren.                              \r\r";
const char msg_43[] PROGMEM ="Weine nicht weil es vorbei ist sondern  lache weil es so    schoen war.                                              \r\r";
const char msg_44[] PROGMEM ="Mitleid bekommt man geschenkt. Neid mussman sich hart       erarbeiten.                                              \r\r";
const char msg_45[] PROGMEM ="Wenn jemand sagt er habe keine Zeit     bedeutet das nur    dass andere Dinge   wichtiger fuer ihn  sind.            \r\r";
const char msg_46[] PROGMEM ="Wenn Du immer nur   das tust was Du     bereits kannst      bleibst Du immer nurdas was Du heute    bist.            \r\r";
const char msg_47[] PROGMEM ="Erfolg besteht darindass man genau die  Faehigkeiten hat dieim Moment gefragt   sind.                                \r\r";
const char msg_48[] PROGMEM ="Wenn wir nicht immerwieder etwas Neues  probiert haetten    wuerden wir heute   noch in Hoehlen     leben.           \r\r";
const char msg_49[] PROGMEM ="Es gibt viele die   suchen das ganze    Leben nach dem Sinn.Dabei hat es gar    keinen. Man muss ihmeinen geben.     \r\r";
// Initialisiere die Tabelle von Strings
const char* const msgs[] PROGMEM = { 
  msg_0, msg_1, msg_2, msg_3, msg_4, msg_5 , msg_6, msg_7, msg_8, msg_9, 
  msg_10, msg_11, msg_12, msg_13, msg_14, msg_15 , msg_16, msg_17, msg_18, msg_19,
  msg_20, msg_21, msg_22, msg_23, msg_24, msg_25 , msg_26, msg_27, msg_28, msg_29,
  msg_30, msg_31, msg_32, msg_33, msg_34, msg_35 , msg_36, msg_37, msg_38, msg_39,
  msg_40, msg_41, msg_42, msg_43, msg_44, msg_45 , msg_46, msg_47, msg_48, msg_49
};

int irnum() {
  int i;
  i=-1;
  do {
    if (irrecv.decode(&results)) {    //Wenn Daten empfangen wurden,
    if (digitalRead(12) == 0) {       //Debug
      Serial.print("->");
      Serial.println(results.value, DEC); //werden sie als Dezimalzahl (DEC) an den Serial-Monitor ausgegeben.
    }
    switch (results.value) {
 // Elegoo UNO R3 Starterkit
      case 16738455: i=0; break;
      case 16724175: i=1; break;
      case 16718055: i=2; break;
      case 16743045: i=3; break;
      case 16716015: i=4; break;
      case 16726215: i=5; break;
      case 16734885: i=6; break;
      case 16728765: i=7; break;
      case 16730805: i=8; break;
      case 16732845: i=9; break; //*/
 /* Philips TV
      case 65536: i=0; break;
      case 65537: i=1; break;
      case 65538: i=2; break;
      case 65539: i=3; break;
      case 65540: i=4; break;
      case 65541: i=5; break;
      case 65542: i=6; break;
      case 65543: i=7; break;
      case 65544: i=8; break;
      case 65545: i=9; break; */
      default: i=-1;
    }
    delay(250);
    irrecv.resume();  //Der nächste Wert soll vom IR-Empfänger eingelesen werden 
    }
  } while ((i < 0) || (i > 9));
  return i;
}

void setup() {
  delay(1000);
  pinMode (13, OUTPUT);
  pinMode (12, INPUT_PULLUP);
  irrecv.enableIRIn();   //Dieser Befehl initialisiert den Infrarotempfänger.
  Serial.begin(115200);
  // if analog input pin 0 is unconnected, random analog
  // noise will cause the call to randomSeed() to generate
  // different seed numbers each time the sketch runs.
  // randomSeed() will then shuffle the random function.
  randomSeed(analogRead(0));  
  menue();
}

void cls() {
  Serial.print('\xff');
  Serial.print('\xf6');
  Serial.print('\x0');
}

void philo() {
  for (;;) {
    cls();
    unsigned int num = random(MAX);
    strcpy_P(buffer, (char*)pgm_read_word(&(msgs[num]))); // Casts und Dereferenzierung des Speichers
    Serial.println(buffer);
    delay(30000);
  }
}

//===========================================================================================================

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


void reverse() {
  int tries=0;
  unsigned int i;
  int input;
  char c;

  for (;;) { 
    cls();
    Serial.println("Reversal Game. Type a number to flip thefirst n numbers.");
    delay(3000);
    cls();
    Serial.println("Win by sorting the  numbers in ascendingorder.");
    delay(3000);
    cls();
    int list[9] = {1,2,3,4,5,6,7,8,9};
    shuffle_list(list,9);
    
    while(!check_array(list, 9))
    {
        sprintf(buffer,"%d %d %d %d %d %d %d %d %d",list[0],list[1],list[2],list[3],list[4],list[5],list[6],list[7],list[8]);
        Serial.println(buffer);
        Serial.println("Input number:");
        input = irnum();
        if ((input > 1) && (input < 10)) {
          tries++;
          do_flip(list, 9, input);      
        }
        else {
          Serial.println("\nInput 2-9");
        }
        
    }
    sprintf(buffer,"%d %d %d %d %d %d %d %d %d",list[0],list[1],list[2],list[3],list[4],list[5],list[6],list[7],list[8]);
    Serial.println(buffer);
    sprintf(buffer,"Hurray! You solved  it in %02d moves! \n", tries);
    Serial.println(buffer);
    Serial.println();
    delay(10000);
  }
}

//===========================================================================================================

void mastermind() {
   char ch[10],my[10];
   int done;
   int i,j,count,offcnt;
   int z1,z2,z3,z4; /* 4 digits for my 4-digit char array */
   
   for (;;) { 

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

   cls();
   sprintf(buffer,"Guess my 4-digit    number...(%s);    0000 to abort.","****");
   Serial.println(buffer);
   delay(3000);
   /* insert my to see code */
   do {
     sprintf(buffer,"# %02d: ",count+offcnt*10);
     Serial.print(buffer);
     for (i=0; i<4; i++) {
       ch[i] = irnum() + 48; /* int 1..9 + ascii(48)='0' => '1'..'9' */
     }
     ch[4] = 0;
     Serial.print(ch);
     Serial.print("-");
     if (strcmp("0000",ch)==0) done = 2; /* give up */
     if (strcmp(my,ch)==0) done = 1; /* success; code broken */
     /* check how near guess it and print hint */
     /* for right digit at  right position print # */
     /* for right digit but wrong position print + */
     if (done==0) {
       for (i=0;i<4;i++) {
         if (ch[i]==my[i]) Serial.print("#");
         else for (j=0;j<4;j++) if (ch[i]==my[j]) Serial.print("+");
       }
     }
     Serial.println();
     count++;
     if (count==11) {
       count = 1;
       offcnt++;
     }
   } while (done==0);
   if (done==1)
     sprintf(buffer,"\nYou broke the code!");
   else
     sprintf(buffer,"\nYou gave up..      ");
   Serial.print(buffer);
   delay(10000);
   }

}

//===========================================================================================================

// othello code:
// https://pc3.5ch.net/test/read.cgi/tech/984182993/337
// https://dev.to/iigura/reversiothello-game-program-which-you-can-choose-the-first-or-the-second-in-7-lines-code-of-c-3799

int p,t,a,d,c,v,i,m[90],s,r[]={-10,-9,-8,-1,1,8,9,10}; // i
char h[]=" - o x\n";

void k()
{
    if(m[p]==0)
        for(i=0;i<8;i++)
        {
            for(c=0,v=p+r[i];m[v]==3-t;v+=r[i])
                c++;
            if(c && m[v] == t)
            {
                a+=c;
                v=p;
                if(d)
                    do 
                        m[v]=t,v+=r[i];
                    while(m[v]-t);
            }
        }
}

void myscanf() {
  p = irnum();
  i = irnum();
}

void othello()
{
   for (;;) { 
    cls();
    t=1; //human 'o' starts

    for(i=1,m[41]=m[49]=2;i<10;m[i++*9]=3)
        m[40]=m[50]=s=1;
    for(;;a=d=0)
    {
        for(p=9;p<82;++p) {
            k();
            sprintf(buffer,"%.2s",h+m[p]*2);
            Serial.print(buffer);
        }
        if(a)
            for(d=a=s=p=8;a==8;k())
                t-2?myscanf(),p+=i*9:++p;
        else if(s) {
            s=0;
            Serial.print("pass");
        }
        else 
            break;
        t=3-t;
    }
   delay(10000);
   }
}

//===========================================================================================================

#define BOARD_ROWS 6
#define BOARD_COLS 7

void printBoard(char *board){
   int row, col;

   cls();
   //puts("*Connect Four*\n");
   for(row = 0; row < BOARD_ROWS; row++){
      for(col = 0; col < BOARD_COLS; col++){
         sprintf(buffer,"|%c",  board[BOARD_COLS * row + col]);
         Serial.print(buffer);
      }
      Serial.println("|");
      //puts("---------------");
   }
   Serial.println(" 1 2 3 4 5 6 7\n");
}

int takeTurn(char *board, int player, const char *PIECES){
   int row, col = 0;
   sprintf(buffer,"Player %d (%c):\nEnter Column:", player + 1, PIECES[player]);
   Serial.print(buffer);
   while(1){ 
      col = irnum();
      if ((col >= 1) && (col <= 7 )) break;
   }
   col--;

   for(row = BOARD_ROWS - 1; row >= 0; row--){
      if(board[BOARD_COLS * row + col] == ' '){
         board[BOARD_COLS * row + col] = PIECES[player];
         return 1;
      }
   }
   return 0;
}

int checkWin(char *board){
    return (horizontalCheck(board) || verticalCheck(board) || diagonalCheck(board));

}

int checkFour(char *board, int a, int b, int c, int d){
    return (board[a] == board[b] && board[b] == board[c] && board[c] == board[d] && board[a] != ' ');

}

int horizontalCheck(char *board){
    int row, col, idx;
    const int WIDTH = 1;

    for(row = 0; row < BOARD_ROWS; row++){
       for(col = 0; col < BOARD_COLS - 3; col++){
          idx = BOARD_COLS * row + col;
          if(checkFour(board, idx, idx + WIDTH, idx + WIDTH * 2, idx + WIDTH * 3)){
             return 1;
          }
       }
    }
    return 0;
}

int verticalCheck(char *board){
    int row, col, idx;
    const int HEIGHT = 7;

    for(row = 0; row < BOARD_ROWS - 3; row++){
       for(col = 0; col < BOARD_COLS; col++){
          idx = BOARD_COLS * row + col;
          if(checkFour(board, idx, idx + HEIGHT, idx + HEIGHT * 2, idx + HEIGHT * 3)){
              return 1;
          }
       }
    }
    return 0;
}

int diagonalCheck(char *board){
   int row, col, idx, count = 0;
   const int DIAG_RGT = 6, DIAG_LFT = 8;

   for(row = 0; row < BOARD_ROWS - 3; row++){
      for(col = 0; col < BOARD_COLS; col++){
         idx = BOARD_COLS * row + col;
         if(count <= 3 && checkFour(board, idx, idx + DIAG_LFT, idx + DIAG_LFT * 2, idx + DIAG_LFT * 3) || count >= 3 && checkFour(board, idx, idx + DIAG_RGT, idx + DIAG_RGT * 2, idx + DIAG_RGT * 3)){
            return 1;
         }
         count++;
      }
      count = 0;
   }
   return 0;
}

void c4() {
   const char *PIECES = "XO";
   char board[BOARD_ROWS * BOARD_COLS];

   for (;;) {
   memset(board, ' ', BOARD_ROWS * BOARD_COLS);
   int turn, done = 0;
   
   for(turn = 0; turn < BOARD_ROWS * BOARD_COLS && !done; turn++){
      printBoard(board);   
      while(!takeTurn(board, turn % 2, PIECES)){
         printBoard(board);   
         Serial.println("*Column full!*\n");
      }
      done = checkWin(board);
   } 
   printBoard(board);

   if(turn == BOARD_ROWS * BOARD_COLS && !done){
      Serial.println("It's a tie!");
   } else {
      turn--;
      sprintf(buffer,"%d (%c) wins!", turn % 2 + 1, PIECES[turn % 2]);
      Serial.println(buffer);
   }
   delay(10000);
   }
}

//===========================================================================================================

void menue() {
  cls();
  Serial.println("Menue:");
  Serial.println("0: Philo");
  Serial.println("1: Reverse");
  Serial.println("2: Mastermind");
  Serial.println("3: Othello");
  Serial.println("4: Connect 4");
}

void loop() {
    // read the next key
    app = irnum();
    if (app == 0) philo();
    if (app == 1) reverse();
    if (app == 2) mastermind();
    if (app == 3) othello();
    if (app == 4) c4();
}
