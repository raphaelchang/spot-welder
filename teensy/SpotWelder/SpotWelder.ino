int trigger = 0;
int gate = 1;
boolean welding = false;
int weldTime = 500;
boolean reset = false;

void setup() {
  Serial.begin(115200);
  pinMode(trigger, INPUT);
  *portConfigRegister(trigger) |= PORT_PCR_PE; //pull enable
  *portConfigRegister(trigger) &= ~PORT_PCR_PS; //pull down
  pinMode(gate, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
}

void loop() {
  Serial.println(digitalRead(trigger));
  if (Serial.available() > 0)
  {
    String b = Serial.readString();
    weldTime = b.toInt();
    Serial.println(weldTime);
  }
  if (digitalRead(trigger) == LOW && !reset)
  {
    delay(500);
    reset = true;
  }
  if (digitalRead(trigger) && !welding && reset)
  {
    welding = true;
    reset = false;
  }
  if (welding)
  {
    digitalWrite(gate, HIGH);
  digitalWrite(LED_BUILTIN, LOW);
    delay(weldTime);
    digitalWrite(gate, LOW);
  digitalWrite(LED_BUILTIN, HIGH);
    welding = false;
  }
}

