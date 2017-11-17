byte bufferArray[16];
int gear;
int shift;
int z;
int selchar;
int seg[8] = {2,3,4,5,6,7,8,9};
int com[4] = {10,11,12,13};
int cha[11][8] = {
  {0,0,1,0,1,0,1,0}, // n
  {0,1,1,0,0,0,0,0}, // 1
  {1,1,0,1,1,0,1,0}, // 2
  {1,1,1,1,0,0,1,0}, // 3
  {0,1,1,0,0,1,1,0}, // 4
  {1,0,1,1,0,1,1,0}, // 5
  {1,0,1,1,1,1,1,0}, // 6
  {0,0,0,0,0,0,1,0}, // -
  {0,0,0,0,0,0,1,0}, // -
  {1,0,1,1,0,1,1,0}, // s (shift!)
  {1,0,0,0,1,1,0,0}  // r
};

void setup() {
  Serial.begin(115200);
   while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  // pinMode pins 2-13 to OUTPUT
  for(int thisPin = 2; thisPin < 14; thisPin++) {
    pinMode(thisPin, OUTPUT);
  }
  // digitalWrite pins 2-9 set HIGH
  for(int thisPin = 2; thisPin < 10; thisPin++){
    digitalWrite(thisPin, HIGH);
  }
  // digitalWrite pins 10-13 set LOW
  for(int i = 0; i < 4; i++){
    digitalWrite(com[i], LOW);
  }
}

void loop(){
  if(Serial.available() > 0){
    Serial.readBytes(bufferArray, 4);
    setGear(bufferArray[0]);
//    setGear(1);
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
    delay(0.5);
  }
}

/* disply selected gear
 */
void setGear(int gear){
  delay(10);
  digitalWrite(com[0], LOW);
  delay(10);
  digitalWrite(com[3], HIGH);
  delay(10);
  setSegments(gear);
//  digitalWrite(com[3], LOW);
}

/* set shifter warning 'light'
 */
void setRevLight(int shift){
  if(shift > 0){
    delay(10);
    digitalWrite(com[3], LOW);
    delay(10);
    digitalWrite(com[0], HIGH);
    delay(10);
    setSegments(9);
//    digitalWrite(com[0], LOW);
  }
}
