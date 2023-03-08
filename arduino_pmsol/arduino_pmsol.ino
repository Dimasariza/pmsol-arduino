#include <Bounce2.h>

  // Define arduino pin
#define analog_1 A0
#define analog_2 A1
#define analog_3 A2
#define analog_4 A3

#define digital_1 2
#define digital_2 3
#define digital_3 4
#define digital_4 5
#define digital_5 6
#define digital_6 7
#define digital_7 8

#define safety_1 22
#define safety_2 24
#define safety_3 26
#define safety_4 28
#define safety_5 30
#define safety_6 32
#define safety_7 34

#define alarm_sound 9

  // Instance Bounce Object  
Bounce deB_digital_1 = Bounce(); 
Bounce deB_digital_2 = Bounce();
Bounce deB_digital_3 = Bounce();
Bounce deB_digital_4 = Bounce();
Bounce deB_digital_5 = Bounce();
Bounce deB_digital_6 = Bounce();
Bounce deB_digital_7 = Bounce();

Bounce deB_safety_1 = Bounce();
Bounce deB_safety_2 = Bounce();
Bounce deB_safety_3 = Bounce();
Bounce deB_safety_4 = Bounce();
Bounce deB_safety_5 = Bounce();
Bounce deB_safety_6 = Bounce();
Bounce deB_safety_7 = Bounce();

int analogNum1;
int analogNum2;
int analogNum3;
int analogNum4;

int stepAnalog1 = 0;
int stepAnalog2 = 0;
int stepAnalog3 = 0;
int stepAnalog4 = 0;

bool readAnalog = true;

int digitalNum1;
int digitalNum2;
int digitalNum3;
int digitalNum4;
int digitalNum5;
int digitalNum6;
int digitalNum7;

int safetyNum1;
int safetyNum2;
int safetyNum3;
int safetyNum4;
int safetyNum5;
int safetyNum6;
int safetyNum7;

bool activate_alarm = false;
  
void setup()
{
  Serial.begin(9600);

  pinMode(alarm_sound, OUTPUT);

  pinMode(analog_1, INPUT);
  pinMode(analog_2, INPUT);
  pinMode(analog_3, INPUT);
  pinMode(analog_4, INPUT);
  
  pinMode(digital_1, INPUT_PULLUP);
  pinMode(digital_2, INPUT_PULLUP);
  pinMode(digital_3, INPUT_PULLUP);
  pinMode(digital_4, INPUT_PULLUP);
  pinMode(digital_5, INPUT_PULLUP);
  pinMode(digital_6, INPUT_PULLUP);
  pinMode(digital_7, INPUT_PULLUP);
  
  pinMode(safety_1, INPUT_PULLUP);
  pinMode(safety_2, INPUT_PULLUP);
  pinMode(safety_3, INPUT_PULLUP);
  pinMode(safety_4, INPUT_PULLUP);
  pinMode(safety_5, INPUT_PULLUP);
  pinMode(safety_6, INPUT_PULLUP);
  pinMode(safety_7, INPUT_PULLUP);
  
  deB_digital_1.attach(digital_1);
  deB_digital_1.interval(5);
  deB_digital_2.attach(digital_2);
  deB_digital_2.interval(5);
  deB_digital_3.attach(digital_3);
  deB_digital_3.interval(5);
  deB_digital_4.attach(digital_4);
  deB_digital_4.interval(5);
  deB_digital_5.attach(digital_5);
  deB_digital_5.interval(5);
  deB_digital_6.attach(digital_6);
  deB_digital_6.interval(5);
  deB_digital_7.attach(digital_7);
  deB_digital_7.interval(5);

  deB_safety_1.attach(safety_1);
  deB_safety_1.interval(5);
  deB_safety_2.attach(safety_2);
  deB_safety_2.interval(5);
  deB_safety_3.attach(safety_3);
  deB_safety_3.interval(5);
  deB_safety_4.attach(safety_4);
  deB_safety_4.interval(5);
  deB_safety_5.attach(safety_5);
  deB_safety_5.interval(5);
  deB_safety_6.attach(safety_6);
  deB_safety_6.interval(5);
  deB_safety_7.attach(safety_7);
  deB_safety_7.interval(5);
}

void loop()
{
  String RPi_Data =  Serial.readString();
  Serial.print("RPi Data : ");
  Serial.println(RPi_Data);
  if(RPi_Data == "activateAlarm") activate_alarm = true;
  else if(RPi_Data == "deactivateAlarm") activate_alarm = false;

  if(activate_alarm) digitalWrite(alarm_sound, HIGH);
  else if(!activate_alarm) digitalWrite(alarm_sound, LOW);
  Serial.print("alarm condition");
  Serial.println(activate_alarm);
  
  delay(10);

  update_debouncer();

  if(readAnalog) 
  {
    analogNum1 = getDebouncedAnalog(analog_1, analogNum1);
    analogNum2 = getDebouncedAnalog(analog_2, analogNum2);
    analogNum3 = getDebouncedAnalog(analog_3, analogNum3);
    analogNum4 = getDebouncedAnalog(analog_4, analogNum4); 
  }
  analogSteps();
  
  digitalNum1 = deB_digital_1.read();
  digitalNum2 = deB_digital_2.read();
  digitalNum3 = deB_digital_3.read();
  digitalNum4 = deB_digital_4.read();
  digitalNum5 = deB_digital_5.read();
  digitalNum6 = deB_digital_6.read();
  digitalNum7 = deB_digital_7.read();
  
  safetyNum1 = deB_safety_1.read();
  safetyNum2 = deB_safety_2.read();
  safetyNum3 = deB_safety_3.read();
  safetyNum4 = deB_safety_4.read();
  safetyNum5 = deB_safety_5.read();
  safetyNum6 = deB_safety_6.read();
  safetyNum7 = deB_safety_7.read();

  print_to_port();
}  

int getDebouncedAnalog(const byte pin, int prevValue)
{
  int newReading = analogRead(pin);
  if(newReading == 0) prevValue = 0;
  if(newReading == 1023) prevValue = 1023;
  
  if(newReading - 5 > prevValue 
  || newReading + 5 < prevValue
  || newReading == 0
  || newReading == 1023
  )
  prevValue = newReading;
  return prevValue;
}

void analogSteps()
{
  if(
    analogNum1 > stepAnalog1
    && analogNum1 > 0
    )
  stepAnalog1 += 2;
  else if (
    analogNum1 < stepAnalog1
    && analogNum1 < 1023
    ) 
  stepAnalog1 -= 2;

  if(
    analogNum2 > stepAnalog2
    && analogNum2 > 0
    )
  stepAnalog2 += 2;
  else if(
    analogNum2 < stepAnalog2
    && analogNum2 < 1023
    ) 
  stepAnalog2 -= 2;

  if(
    analogNum3 > stepAnalog3
    && analogNum3 > 0
    )
  stepAnalog3 += 2;
  else if(
    analogNum3 < stepAnalog3
    && analogNum3 < 1023
    )
  stepAnalog3 -= 2;

  if(
    analogNum4 > stepAnalog4
    && analogNum4 > 0
    )
  stepAnalog4 += 2;
  else if(
    analogNum4 < stepAnalog4
    && analogNum4 < 1023
    )
  stepAnalog4 -= 2;
}

void update_debouncer() 
{  
  deB_digital_1.update();
  deB_digital_2.update();
  deB_digital_3.update();
  deB_digital_4.update();
  deB_digital_5.update();
  deB_digital_6.update();
  deB_digital_7.update();

  deB_safety_1.update();
  deB_safety_2.update();
  deB_safety_3.update();
  deB_safety_4.update();
  deB_safety_5.update();
  deB_safety_6.update();
  deB_safety_7.update();
}

void  print_to_port() 
{
  Serial.print("digital");
  Serial.print(",");
  Serial.print(digitalNum1);
  Serial.print(",");
  Serial.print(digitalNum2);
  Serial.print(",");
  Serial.print(digitalNum3);
  Serial.print(",");
  Serial.print(digitalNum4);
  Serial.print(",");
  Serial.print(digitalNum5);
  Serial.print(",");
  Serial.print(digitalNum6);
  Serial.print(",");
  Serial.print(digitalNum7);
  Serial.println("");

  Serial.print("analog");
  Serial.print(",");
  Serial.print(stepAnalog1);
  Serial.print(",");
  Serial.print(stepAnalog2);
  Serial.print(",");
  Serial.print(stepAnalog3);
  Serial.print(",");
  Serial.print(stepAnalog4);
  Serial.println("");
  
  Serial.print("safety");
  Serial.print(",");
  Serial.print(safetyNum1);
  Serial.print(",");
  Serial.print(safetyNum2);
  Serial.print(",");
  Serial.print(safetyNum3);
  Serial.print(",");
  Serial.print(safetyNum4);
  Serial.print(",");
  Serial.print(safetyNum5);
  Serial.print(",");
  Serial.print(safetyNum6);
  Serial.print(",");
  Serial.print(safetyNum7);
  Serial.println("");
}

void alertion_digital() 
{
  if(safetyNum1 == 0
  || safetyNum2 == 0
  || safetyNum3 == 0
  || safetyNum4 == 0
  || safetyNum5 == 0
  || safetyNum6 == 0
  || safetyNum7 == 0
  ) return;
  
  if(
  stepAnalog1 > 483
  && stepAnalog2 > 255
  && stepAnalog3 > 255 )
  {
    readAnalog = false;
    analogNum1 = 483;
    analogNum2 = 255;
    analogNum3 = 255;
    digitalWrite(alarm_sound, HIGH);
    return;
  } 
  readAnalog = true;
  
  if(stepAnalog1 >= 411 || stepAnalog1 <= 87)
  {
    digitalWrite(alarm_sound, HIGH);
    return;
  } 

  if(stepAnalog2 >= 810 || stepAnalog2 <= 750)
  {
    digitalWrite(alarm_sound, HIGH);
    return;
  }

  if(stepAnalog3 >= 256 || stepAnalog3 <= 153)
  {
    digitalWrite(alarm_sound, HIGH);
    return;
  }
  
  if(stepAnalog4 >= 818 || stepAnalog4 <= 358)
  {
    digitalWrite(alarm_sound, HIGH);
    return;
  }

  digitalWrite(alarm_sound, LOW);
}
