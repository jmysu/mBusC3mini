/*
 * C3mBusmini LED Blink 
 */
 
void setup() {
  delay(10);
  // put your setup code here, to run once:
  Serial.begin(115200);
  //delay(100);
  Serial.print("\n---C3mBusMini V2605 Blink---");
  delay(500);

  pinMode(0, OUTPUT); //AD0
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite( 0, LOW);
  delay(1000); // this speeds up the simulation

  digitalWrite( 0, HIGH);
  delay(1000); // this speeds up the simulation
}