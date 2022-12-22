#include <Keypad.h>            // labrary for keypad
#include <LiquidCrystal.h>    // labrary for 16x2 lcd 
#include <Servo.h>           // labrary for servo motor . motor using as look 
//#include <dht.h>

//dht DHT;

#define DHT11_PIN 2

int n=30;
Servo myservo;               // define object for  servo
const byte ROWS = 4;           //four rows of keypad
const byte COLS = 3;         //three columns keypad
char keys[ROWS][COLS] = 
{
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};
byte rowPins[ROWS] = {9, 8, 7, 6};         //connect to the row pinouts of the keypad
byte colPins[COLS] = {5, 4,3};             //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );  //keypad function arrange row and colum of keypad

// 16x2 LCD 
#define rs 13              // declearing pins for lcd 16x2
#define en A1 
#define d4 2  
#define d5 A3  
#define d6 A4
#define d7 A5

int degree;
double realDegree;
String lcdBuffer;                                                    
                                                  // initialize the library with the numbers of the interface pins
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

String password = "1234";          // here set your own password
String mypassword;              // string varable to store given value on keypad
int buzzer = 2;                     // pin for buzzer

const int ledPin = 1;   //the number of the LED pin
const int ldrPin = A0;  //the number of the LDR pin              // pin for smok or gas sensor
// Your threshold value



#define trigPin 12       // pinout for triger pin of ultrasonic
#define echoPin 11         // pinout for echo pin of ultrasonic

float duration, distance;
int counter = 0;          // initizliting varables
int attempts = 0; 
int max_attempts = 2; 

void setup(){
  Serial.begin(9600);  // show result on serial monitor
        // set up the LCD's number of columns and rows: 
  lcd.begin(16, 2);     // start lcd on
  myservo.attach(10);   // attach servo motor to pin 10 
  
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);   //here declear some varable as out and some as a input 
   pinMode(buzzer, OUTPUT);
   pinMode(ledPin, OUTPUT);  //initialize the LED pin as an output
  pinMode(ldrPin, INPUT);   //initialize the LDR pin as an input
  myservo.write(0);
  
  Serial.println("enter password");
    lcd.print("Enter Password:");      // write this text on lcd and serial monitor 
}
  
void loop()
{
  
 keypadfunction();   // calling  keypad function
 ldr();              // calling Photo resistor function
 ultra();            // calling ultrasonic function 
  
}

void keypadfunction()         // keypad function
{
 char key = keypad.getKey();   // this will get value when someone press the button and put data into key varable
  
  if (key){                     //    here if any button is press check it
    Serial.println(key);  
    counter = counter + 1;      // here is counting the press 
    lcd.setCursor(counter, 1);
    lcd.print("*");              // here we print * instead of showning number for security perpose
  }
  if (key == '1')
  {                                 //here key varable compare with one by if button 1 is pressed 
                                
    mypassword = mypassword + 1;   // 1 will be save in string variable mypassword 
  }
  
    if (key == '2')
  {
                                      // samilarly if 2 is press 2 will be save in varable 
    mypassword = mypassword + 2;  
  }
  
  if (key == '3')
  {
 
    mypassword = mypassword + 3; 
  }
  
   if (key == '4')
  {
  
    mypassword = mypassword + 4;  
  }
  
  if (key == '5')
  {
  
    mypassword = mypassword + 5;
  }
  
   if (key == '6')
  {
   
    mypassword = mypassword + 6; 
  }
  
   if (key == '7')
  {

    mypassword = mypassword + 7; 
  }

   if (key == '8')
  {

    mypassword = mypassword + 8; 
  }
  
  if (key == '9')
  {

    mypassword = mypassword + 9;
  }
             
                 if (key == '0')
  {

    mypassword = mypassword + 0; 
  }
  
  
        if (key == '*')              // after pressing passwor you must be pres * button to enter password 
  {
    Serial.println(mypassword); 
    
if ( password == mypassword )     // here checking password as the password is correct or wrong 
{
lcd.clear();                      // if password is corerect it print message of lcd 
lcd.println("Welcome To");
lcd.setCursor(0,1);
lcd.println("SWEET HOME ");
temp();
myservo.write(90);                  //HERE IS SERVO WILL MOVE AND THE DOOR WILL BE OPEN
delay(5000);                        //AFTER 5 SECOND THE DOOR IT SELF WILL BE CLOSED
myservo.write(0);
mypassword = ""; 
counter = 0;                        //HERE COUNTER WILL BE RESSET
lcd.clear();
lcd.setCursor(0,0);         
lcd.println("Enter password");          //AGAIN MESSAGE WILL BE SHOWS TO ENTER PASSWORD 
} 
else
{
Serial.println("wrong");       
myservo.write(0);                // IF SOMEONE  ENTER WRONG PASSWORD MORE THAN 2 TIME THE  BUZZER WILL GIVE ALERTE SOUND 
attempts = attempts + 1; 
if (attempts >= max_attempts )
{
  
  lcd.clear();
  lcd.setCursor(0,0); 
  lcd.print("Locked Out");       //THE DOOR WILL BE LOCKED
  while(!(n==0))
  {
    n=n-1;
   lcd.setCursor(1,1); 
  lcd.print(n);
  }
delay(5000); 

attempts = 0; 

}
mypassword = ""; 
counter = 0; 
lcd.clear(); 
lcd.setCursor(0,0); 
lcd.print("Wrong Password");
delay(1000);

lcd.setCursor(0,1); 
lcd.print("max attempts 2");
delay(1000);

lcd.clear(); 
lcd.println("Enter password");
lcd.setCursor(0,1); 
}
    
  }  
  
  
}
void ultra()                    // ULTRASONIC SENSOR  FUNTION 
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);              // HERE THE TRIGER SEND THE SIGNAL  (TRANSMITT)
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);     //RECEIVE THE SIGNAL 
  distance = (duration / 2) * 0.0343;     //HERE IF CONVERSION INTO CENTIMETER
  
    if (distance > 10 && distance <=40 )  // IF SOMEONE DETECT WITH IN RANGE OF 10 TO 4O CENTIMETER 
  {
     digitalWrite(buzzer,HIGH);             // THE BUZZER WILL  GIVE ALERT SOUND
     delay(200); 
  }
  else
  {
     digitalWrite(buzzer,LOW);                  // OTHER WISE  NO SOUND
  }

}
void ldr() {

  int ldrStatus = analogRead(ldrPin);   //read the status of the LDR value

  //check if the LDR status is <= 300
  //if it is, the LED is HIGH

   if (ldrStatus <=300) {

    digitalWrite(ledPin, HIGH);               //turn LED on
    Serial.println("LDR is DARK, LED is ON");
    
   }
  else {

    digitalWrite(ledPin, LOW);          //turn LED off
    Serial.println("---------------");
  }
}
/*void Dht(){
  int chk = DHT.read11(DHT11_PIN);
  Serial.print("Temperature = ");
  Serial.println(DHT.temperature);
  Serial.print("Humidity = ");
  Serial.println(DHT.humidity);
  delay(1000);
}
*/
void temp()
{
  lcd.print("                ");
  degree = analogRead(A2);
  realDegree = (double)degree/1024;
  realDegree *= 5;
  realDegree -= 0.5;
  realDegree *= 100;
  lcd.setCursor(0,1);
  realDegree = (9.0/5)*(realDegree) + 32;
  String output = String(realDegree) + String((char)178) + "F";
  lcd.print(output);
}
