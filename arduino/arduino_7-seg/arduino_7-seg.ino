byte bufferArray[16];
int gear;
int shift;
int velocity;
int z;
int selchar;
int segment_pins[8] = {2,3,4,5,6,7,8,9};
int analog_pins[5] = {A1, A2, A3, A4, A5};
int com_pins[4] = {10,11,12,13};
int cha[11][8] = {
  {1,1,1,1,1,1,0,0}, // 0
  {0,1,1,0,0,0,0,0}, // 1
  {1,1,0,1,1,0,1,0}, // 2
  {1,1,1,1,0,0,1,0}, // 3
  {0,1,1,0,0,1,1,0}, // 4
  {1,0,1,1,0,1,1,0}, // 5
  {1,0,1,1,1,1,1,0}, // 6
  {1,1,1,0,0,0,0,0}, // 7
  {1,1,1,1,1,1,1,0}, // 8
  {1,1,1,1,0,1,1,0}, // 9
  {0,0,1,0,1,0,1,0}, // n
  {1,0,0,0,1,1,0,0}  // r
};

void setup() {
  Serial.begin(115200);
   while(!Serial){
    ; // wait for serial port to connect
  }
  // segment pins to OUTPUT
  for(int x = 0; x < sizeof(segment_pins) - 1; x++){
    pinMode(segment_pins[x], OUTPUT);
  }
  // segment pins to HIGH
  writePins(segment_pins, true);
  //for(int x = 0; x < sizeof(segment_pins) - 1; x++){
    //digitalWrite(segment_pins[x], HIGH);
  //}
  // analog pins to OUTPUT
  for(int x = 0; x < sizeof(analog_pins) - 1; x++){
    pinMode(analog_pins[x], OUTPUT);
  }
  // analog pins to HIGH
  writePins(analog_pins, true);
  //for(int x = 0; x < sizeof(analog_pins) - 1; x++){
    //digitalWrite(analog_pins[x], HIGH);
  //}
  // com pins to OUTPUT
  for(int x = 0; x < sizeof(com_pins) - 1; x++){
    pinMode(com_pins[x], LOW);
  }
  // com pins to LOW
  writePins(com_pins, false);
  //for(int x = 0; x < sizeof(com_pins) - 1; x++){
    //digitalWrite(com_pins[x], LOW);
  //}
}

/* set pins in array pins high or not
 */
void writePins(int pins, bool high){
  for(int x = 0; x < sizeof(pins) - 1; x++){
    if(high){
        digitalWrite(pins[x], HIGH);
    }else{
        digitalWrite(pins[x], LOW);
    }
  }
}

void loop(){
  if(Serial.available() > 0){
    Serial.readBytes(bufferArray, 4);
    //if(digitalRead(analog_in[0]) === HIGH){
      setSpeed(bufferArray[4]);
    //}else{
      //setGear(bufferArray[0]);
    //}
    setRevLight(bufferArray[2]);
  }
}

/* set which segments should light up
 */
void setSegments(int selchar){
  z = 0;
  while(z < 7){
    if(cha[selchar][z] > 0){
      // turn on segment
      digitalWrite(seg[z], LOW);
    }else{
      // turn off segment
      digitalWrite(seg[z], HIGH);
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
  digitalWrite(com[3], HIGH);
  setSegments(gear);
  delay(1);
}

/* rev warning light
 */
void setRevLight(int shift){
  if(shift > 0){
    digitalWrite(analog_pins[0], LOW);
  }else{
    digitalWrite(analog_pins[0], HIGH);
  }
}
