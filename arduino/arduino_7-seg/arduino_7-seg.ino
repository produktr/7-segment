byte bufferArray[16];
int gear;
int shift;
int velocity;
int z;
int selchar;
volatile int buttonState = 0;
int interrupt_pins[1] = {2};
int segment_pins[7] = {3,4,5,6,7,8,9};
int analog_pins[6] = {A0, A1, A2, A3, A4, A5};
int com_pins[4] = {10,11,12,13};
int cha[12][7] = {
  {1,1,1,1,1,0,1}, // 0
  {1,1,0,0,0,0,0}, // 1
  {1,0,1,1,0,1,1}, // 2
  {1,1,1,0,0,1,1}, // 3
  {1,1,0,0,1,1,0}, // 4
  {0,1,1,0,1,1,1}, // 5
  {0,1,1,1,1,1,1}, // 6
  {1,1,0,0,0,0,1}, // 7
  {1,1,1,1,1,1,1}, // 8
  {1,1,1,0,1,1,1}, // 9
  {0,1,0,1,0,1,0}, // n
  {0,0,0,1,1,0,1}  // r
};

void setup() {
  Serial.begin(115200);
   while(!Serial){
    ; // wait for serial port to connect
  }

  // interrupt pins are INPUT
  pinMode(interrupt_pins[0], INPUT);
  // attach interrupt on CHANGE
  attachInterrupt(interrupt_pins[0], switchChange, CHANGE);
  // first time read button state
  buttonState = digitalRead(interrupt_pins[0]);

  // segment pins are OUTPUT
  for(int x = 0; x < sizeof(segment_pins) - 1; x++){
    pinMode(segment_pins[x], OUTPUT);
  }
  // segment pins to HIGH
  writePins(segment_pins, true);

  // analog pins are OUTPUT
  for(int x = 0; x < sizeof(analog_pins) - 1; x++){
    pinMode(analog_pins[x], OUTPUT);
  }
  // analog pins to HIGH
  writePins(analog_pins, true);

  // com pins are OUTPUT
  for(int x = 0; x < sizeof(com_pins) - 1; x++){
    pinMode(com_pins[x], LOW);
  }
  // com pins to LOW
  writePins(com_pins, false);
}

void loop(){
  if(Serial.available() > 0){
    Serial.readBytes(bufferArray, 4);
    if(buttonState == HIGH){
      setRevLight(1);
//      setSpeed(bufferArray[4]);
    }else{
      setRevLight(0);
//      setGear(bufferArray[0]);
    }
    setRevLight(bufferArray[2]);
  }
}

/* interrupt call, set opposite value
 */
void switchChange(){
  buttonState = !buttonState;
}

/* set pins in array pins high or not
 */
void writePins(int pins[], bool high){
  for(int x = 0; x < sizeof(pins) - 1; x++){
    if(high){
        digitalWrite(pins[x], HIGH);
    }else{
        digitalWrite(pins[x], LOW);
    }
  }
}

/* set which segments should light up
 */
void setSegments(int selchar){
  z = 0;
  while(z < 7){
    if(cha[selchar][z] > 0){
      // turn on segment
      digitalWrite(segment_pins[z], LOW);
    }else{
      // turn off segment
      digitalWrite(segment_pins[z], HIGH);
    }
    z++;
  }
}

/* display speed of vehicle
 */
void setSpeed(int speed){
  // code to set speed
}

/* display selected gear
 */
void setGear(int gear){
  if(gear == 0){
    gear = 10;
  }
  if(gear == 10){
    gear++;
  }
  writePins(com_pins, false);
  digitalWrite(com_pins[3], HIGH);
  setSegments(gear);
  delay(1);
}

/* rev warning light
 */
void setRevLight(int shift){
  if(shift > 0){
    digitalWrite(analog_pins[1], LOW);
  }else{
    digitalWrite(analog_pins[1], HIGH);
  }
}
