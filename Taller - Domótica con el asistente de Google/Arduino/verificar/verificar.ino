void setup() {
  pinMode(D3, OUTPUT);
}

void loop() {
  digitalWrite(D3, HIGH);
  delay(1000);
  digitalWrite(D3, LOW);
  delay(1000);
}
