/*
irsensors.ino
Owen Ziegler
2025 02 26

Description:
Driver code for the IR sensor array
*/
//declare pin addresses
const int PINS[8] = {
  12, 
  13, 
  14, 
  NULL, 
  NULL, 
  NULL,
  NULL
};
//declare sequences
#define LEFT 0b10000000
#define CENTER 0b01000000
#define RIGHT 0b00100000
#define LOST 0b00000000


void setup() {
  Serial.begin(115200);
  //activate all pins
  for(int i = 0; i < 8; i++) {
    if (PINS[i]) pinMode(PINS[i], INPUT);
  }
}

void loop() {
  //load pin values into a byte
  uint8_t pinState = 0;
  for(int i = 0; i < 8; i++) {
    if (PINS[i]) pinState |= ((digitalRead(PINS[i]) ^ 1) << i);
    else pinState |= (0 << i);
  }
  //check pin values
  for (int i = 7; i >= 0; i--) {
  Serial.print((pinState >> i) & 1); // Extract each bit
  }
  Serial.println(); // New line
  delay(100);
}