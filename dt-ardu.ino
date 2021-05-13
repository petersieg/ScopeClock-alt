/*  PS2Keyboard library example
  
  PS2Keyboard now requries both pins specified for begin()
  keyboard.begin(data_pin, irq_pin);
  
  Valid irq pins:
     Arduino Uno:  2, 3
     Arduino Due:  All pins, except 13 (LED)
     Arduino Mega: 2, 3, 18, 19, 20, 21
     Teensy 3.0:   All pins, except 13 (LED)
     Teensy 2.0:   5, 6, 7, 8
     Teensy 1.0:   0, 1, 2, 3, 4, 6, 7, 16
     Teensy++ 2.0: 0, 1, 2, 3, 18, 19, 36, 37
     Teensy++ 1.0: 0, 1, 2, 3, 18, 19, 36, 37
     Sanguino:     2, 10, 11
  
  for more information you can read the original wiki in arduino.cc
  at http://www.arduino.cc/playground/Main/PS2Keyboard
  or http://www.pjrc.com/teensy/td_libs_PS2Keyboard.html
  
  Like the Original library and example this is under LGPL license.
  
  Modified by Cuninganreset@gmail.com on 2010-03-22
  Modified by Paul Stoffregen <paul@pjrc.com> June 2010
*/
   
#include <avr/pgmspace.h>
#include <PS2Keyboard.h>

const int DataPin = 4;
const int IRQpin =  3;
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
const char msg_3[]  PROGMEM ="Ein Plan der sich   nicht aendern laesstist ein schlechter Plan.                                                     \r\r";
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
const char msg_18[] PROGMEM ="Auge um Auge bedeutet nur dass die Welt erblindet.                                                                   \r\r";
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

PS2Keyboard keyboard;

void setup() {
  delay(1000);
  keyboard.begin(DataPin, IRQpin);
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
    delay(10000);
  }
}

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
        while (!keyboard.available()); // wait for ps2 kbd key
        c = keyboard.read();
        input = (c - '0'); // '0'..'9' -> 0..9
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

void mastermind() {
  Serial.println("2: Mastermind");
}

void menue() {
  cls();
  Serial.println("Menue:");
  Serial.println("0: Philo");
  Serial.println("1: Reverse");
  Serial.println("2: Mastermind");
}

void loop() {
  if (keyboard.available()) {
    // read the next key
    app = keyboard.read();
    if (app == '0') philo();
    if (app == '1') reverse();
    if (app == '2') mastermind();
  }
}
