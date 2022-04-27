int s0 = 2;
int s1 = 3;
int s2 = 4;
int s3 = 5;
int enable = 8;
int reader = 9;
int sr0 = 10;
int sr1 = 11;
int sr2 = 12;
int sr3 = 13;

void setup() {
  pinMode(s0, OUTPUT);
  pinMode(s1, OUTPUT);
  pinMode(s2, OUTPUT);
  pinMode(s3, OUTPUT);
  pinMode(enable, OUTPUT);
  pinMode(sr0, OUTPUT);
  pinMode(sr1, OUTPUT);
  pinMode(sr2, OUTPUT);
  pinMode(sr3, OUTPUT);
  pinMode(reader, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  //int[][] ledMatrix = new int[4][4];
  //int ledList[] = {1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1};
  
  for(int i = 0; i < 9; i++){
    sensorRead(i);
    writeLEDnum(i, digitalRead(reader));
    delay(1);  
  }
}

void writeLEDnum(int num, bool active){
    digitalWrite(enable, !active);
    digitalWrite(s0, bitRead(num, 0));
    digitalWrite(s1, bitRead(num, 1));
    digitalWrite(s2, bitRead(num, 2));
    digitalWrite(s3, bitRead(num, 3));
}

void sensorRead(int num){
    digitalWrite(sr0, bitRead(num, 0));
    digitalWrite(sr1, bitRead(num, 1));
    digitalWrite(sr2, bitRead(num, 2));
    digitalWrite(sr3, bitRead(num, 3));
}
