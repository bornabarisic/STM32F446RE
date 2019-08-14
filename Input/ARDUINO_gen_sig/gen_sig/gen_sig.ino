#define OUT 3
int i=0;
bool flag = true;

void setup() {
  Serial.begin(9600);
  pinMode(OUT, OUTPUT);
}

void loop() {
  if (flag){
    for(i=0;i<10;i++){
    digitalWrite(OUT, HIGH);
    delay(500);
    digitalWrite(OUT, LOW);
    delay(500);
    }
  }  
}
