

void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  pinMode(A0, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int ldrStatus = analogRead(A0);
  Serial.println("status");
  Serial.println(ldrStatus);
  delay(1000);
}
