#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <Servo.h> 

uint16_t sensorValues[5]= {36, 37, 38, 39, 40}; //pin mega yang digunakan oleh sensor TCRT5000

Servo myservo; //Set servo dengan library

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, NEGATIVE);  // Set alamat dan sambungan LCD ke I2C dari library

#define ENC_IN_LEFT_A 18
#define ENC_IN_RIGHT_A 19
#define ENC_IN_LEFT_B 14
#define ENC_IN_RIGHT_B 15 //pin encoder

volatile long left_wheel_pulse_count = 0;
volatile long right_wheel_pulse_count = 0;

int motor1_kananA = 5;
int motor1_in1 = 2;
int motor1_in2 = 3;
int motor1_kiriB = 6;
int motor1_in3 = 4;
int motor1_in4 = 7; //pin motor gerak

int motor1_kananB = 10;
int motor1_in3B = 8;
int motor1_in4B = 9; //pin motor forklift

int button;
int menu = 1; //

float spd_base=75;
int pwml, pwmr;

int sensor[5];
float left_motor_speed, right_motor_speed, error;
int Rcount_side, Lcount_side, count_mid, take= 1, give= 0, R= 0, M= 0, L= 0;

void setup() {
  lcd.begin(16, 2);
  Serial.begin(9600);

  for ( int x = 0; x < 5; x++ ) {
  pinMode(sensorValues[x], INPUT);
  }

  pinMode(ENC_IN_LEFT_A , INPUT_PULLUP);
  pinMode(ENC_IN_RIGHT_A , INPUT_PULLUP);

  pinMode(ENC_IN_LEFT_B, INPUT_PULLUP);
  pinMode(ENC_IN_RIGHT_B, INPUT_PULLUP);

  pinMode( motor1_in1 , OUTPUT);
	pinMode( motor1_in2 , OUTPUT);
  pinMode( motor1_kananA, OUTPUT);
  pinMode( motor1_in3 , OUTPUT);
	pinMode( motor1_in4 , OUTPUT);
  pinMode( motor1_kiriB, OUTPUT);

  pinMode( motor1_in3B , OUTPUT);
	pinMode( motor1_in4B , OUTPUT);
  pinMode( motor1_kananB, OUTPUT);

  attachInterrupt(digitalPinToInterrupt(ENC_IN_LEFT_A), left_wheel_pulse, RISING);
  attachInterrupt(digitalPinToInterrupt(ENC_IN_RIGHT_A), right_wheel_pulse, RISING); //untuk menghitung pulse encoder tanpa delay
  
  myservo.attach(11); //pin servo

  updateMenu();
}

void loop() {
  gerak_stop(); //mencegah forklift aktif diluar pilihannya
  
  button= analogRead(0); //membaca button yang ditekan

  if(menu != 1){
    stop(); //untuk mencegah motor bergerak kecuali pada pilihan pertama/start
  }

  if (button<350){
    menu--;
    updateMenu();  //jika left button ditekan, menelusuri pilihan menu atas
    delay(400);
  }
  else if (button>350&&button<500){
    menu++;
    updateMenu(); //jika right button ditekan, menelusuri pilihan menu bawah
    delay(400);
  }
  else if (button>500&&button<800){
    executeAction(); //jika select button ditekan, akan melaksanakan sebuah aksi yang sesuai dengan nomor menu
    delay(400);
  }
}

void updateMenu() { //memunculkan pilihan yang tersedia
  switch (menu) {
    case 0:
      menu = 1;
      break;
    case 1:
      lcd.clear();
      lcd.print(">Start");
      lcd.setCursor(0, 1);
      lcd.print(" Pulley^     ");
      printVolts();
      break;
    case 2:
      lcd.clear();
      lcd.print(" Start");
      lcd.setCursor(0, 1);
      lcd.print(">Pulley^     ");
      printVolts();
      break;
    case 3:
      lcd.clear();
      lcd.print(">Pulleyv");
      lcd.setCursor(0, 1);
      lcd.print(" Servo<     ");
      printVolts();
      break;
    case 4:
      lcd.clear();
      lcd.print(" Pulleyv");
      lcd.setCursor(0, 1);
      lcd.print(">Servo<     ");
      printVolts();
      break;
    case 5:
      lcd.clear();
      lcd.print(">Servo>");
      lcd.setCursor(0, 1);
      lcd.print(" IR      ");
      printVolts();
      break;

    case 6:
      lcd.clear();
      lcd.print(" Servo>");
      lcd.setCursor(0, 1);
      lcd.print(">IR      ");
      printVolts();
      break;
    
    case 7:
      menu= 6;
      break;
  }
}

void executeAction() { //berisi aksi yang dapat dilakukan robot
  switch (menu) {
    case 1:
      action1();
      break;
    case 2:
      action2();
      break;
    case 3:
      action3();
      break;
    case 4:
      action4();
      break;
    case 5:
      action5();
      break;
    case 6:
      action6();
      break;
  }
}

void action1() { //fungsi untuk mengaktifkan fungsi utama robot forklift untuk mengambil dan meletakkan barang
  lcd.clear();
  baca(); //untuk membaca hasil sensor TCRT5000
  ambil(); //fungsi untuk melaksanakan gerakan menuju area pengambilan barang

  if((give== 1) && (M== 1)){ //fungsi untuk berputar 180 derajat setelah barang diambil
    right();
    stop();
    delay(300);
    right();
    stop();
    delay(300);
    M = 0;
  }

  kasih(); //fungsi untuk melaksanakan gerakan menuju area peletakkan barang

  motor(0); //motor aktif
  lcd.setCursor(3, 1);
  lcd.print(left_wheel_pulse_count); //menampilkan pulse encoder kiri
  lcd.setCursor(12, 1);
  lcd.print(right_wheel_pulse_count); //menampilkan pulse encoder kanan
}

void action2() { //fungsi untuk memperlihatkan gerakan naik forklift
  lcd.clear();
  lcd.print(">Pulley up");
  lcd.setCursor(0, 1);
  printVolts();
  gerak_naik();
  delay(450);
  gerak_stop();
}

void action3() { //fungsi untuk memperlihatkan gerakan turun forklift
  lcd.clear();
  lcd.print(">Pulley dwn");
  lcd.setCursor(1, 1);
  printVolts();
  gerak_turun();
  delay(425);
  gerak_stop();
}

void action4() { //fungsi untuk memperlihatkan gerakan ke dalam servo untuk memiringkan forklift ke arah robot
  lcd.clear();
  lcd.print(">Servo <");
  lcd.setCursor(1, 1);
  printVolts();
  servog();
} 

void action5() { //fungsi untuk memperlihatkan gerakan ke luar servo kembali meluruskan forklift
  lcd.clear();
  lcd.print(">Servo >");
  lcd.setCursor(1, 1);
  printVolts();
  servor();
} 

void action6() { //fungsi untuk tes hasil sensor TCRT 5000
  servoe();
  lcd.clear();
  while(button>500&&button<800){
    int hasil2;
    lcd.setCursor(0, 0);
    for ( int x = 0; x < 5; x++ ) {
      hasil2= digitalRead(sensorValues[x]); //hitam 1
      lcd.print(hasil2);
    }
    lcd.setCursor(1, 1);
    printVolts();
    servoe();
  }
}

void baca(){ //fungsi untuk membaca hasil sensor TCRT 5000
  int hasil2;
  lcd.setCursor(0, 0);
  for ( int x = 0; x < 5; x++ ) {
    hasil2= digitalRead(sensorValues[x]); //hitam 1, putih 0
    sensor[x]= hasil2;
    lcd.print(hasil2);
    Serial.print(hasil2," ");
    lcd.print("  ");
  }
}

void hasilbutton(){ //fungsi membaca button yang ditekan
  lcd.setCursor(0, 1);
  lcd.print  (button);
}

void ambil(){
  if((sensor[0]==1||sensor[1]==1||sensor[2]==1)&& (take==1)){ //setiap kali sensor bagian kiri mendeteksi garis hitam, L akan bertambah besar
    L= L + 1;
    if((L >= 35)&&(sensor[2]==1||sensor[3]==1||sensor[4]==1)&&(take=1)){ //setelah mencapai nilai threshold, akan berbelok kanan
      right();
      L = 0;
      R = 0;
      M = 1;
      take= 0;
      give= 1;
      lcd.setCursor(10, 1);
      lcd.print("yay");
      left_wheel_pulse_count= 0;
      right_wheel_pulse_count= 0;
      lift_R(); //serta melakukan fungsi gerakan memasuki area pengambilan barang serta pengambilan barang
    }
  }
}

void kasih(){ //fungsi gerakan kembali ke area penurunan barang dan meletakan barang
  if((give== 1)&&(sensor[4]==1||sensor[3]==1)){ //setiap kali sensor bagian kanan mendeteksi garis hitam, R akan bertambah besar
    R++;
    if(R >= 24){ //setelah mencapai nilai threshold, akan tetap lurus hingga pulse encoder kiri mendekati nilai 1000, setelah itu akan menurunkan barang dan berhenti
      left_wheel_pulse_count= 0;
      right_wheel_pulse_count= 0;
      while(left_wheel_pulse_count < 1000){
        motor(0);
      }
      gerak_turun();
      delay(425);
      gerak_stop();
      left_wheel_pulse_count= 0;
      right_wheel_pulse_count= 0;
      while(left_wheel_pulse_count < 1000){
        stop();
      }
    }
  }
}

void lift_R(){ //fungsi dengan rangkaian gerakan untuk memasuki area pengambilan barang, jika start dari sisi kiri arena
  while(left_wheel_pulse_count < 600){ //robot lurus
    motor(0);
  }
  left();//belok kiri menghadap area pengambilan
  left_wheel_pulse_count= 0;
  right_wheel_pulse_count= 0;
  while(left_wheel_pulse_count < 1000){
    motor(0); //lurus
  }
  stop();//stop
  left_wheel_pulse_count= 0;
  right_wheel_pulse_count= 0;
  gerak_naik(); //forklift bergerak ke atas mengambil barang
  delay(450);
  gerak_stop(); //forklift stop
  delay(500);
}

void lift_L(){ //fungsi dengan rangkaian gerakan untuk memasuki area pengambilan barang, jika start dari sisi kanan arena
  while(left_wheel_pulse_count < 700){
    motor(0);
  }
  right();
  left_wheel_pulse_count= 0;
  right_wheel_pulse_count= 0;
  while(left_wheel_pulse_count < 1000){
    motor(0);
  }
  stop();
  left_wheel_pulse_count= 0;
  right_wheel_pulse_count= 0;
  gerak_naik();
  delay(450);
  gerak_stop();
  delay(500);
}

void left_wheel_pulse() { //fungsi increment dan decrement pulse encoder kiri
  int b= digitalRead(ENC_IN_LEFT_B); //membaca arah gerak rode
  if(b > 0){ //roda ke depan
    left_wheel_pulse_count++;
  } else{ //roda ke belakang
    left_wheel_pulse_count--;
  }
}

void right_wheel_pulse() {  //fungsi increment dan decrement pulse encoder kanan
  int b= digitalRead(ENC_IN_RIGHT_B);
  if(b > 0){//roda ke depan
    right_wheel_pulse_count--;
  } else{//roda ke belakang
    right_wheel_pulse_count++;
  }
}

float motor(float PID){ //aktifasi gerak motor
  left_motor_speed = spd_base - PID; 
  right_motor_speed = spd_base + PID;
    
  constrain(left_motor_speed,-85,150);
  constrain(right_motor_speed,-85,150);

  analogWrite(motor1_kananA, right_motor_speed);//22:16 kanan lbh cpt 5(best); 22:21 kiri lbh cpt 4(best); 23:42 kiri/kanan lbh cpt 5(best); 1:55 kiri lbh cpt 4()
  analogWrite(motor1_kiriB, left_motor_speed);
  digitalWrite( motor1_in1, LOW);
  digitalWrite( motor1_in2, HIGH);
  digitalWrite( motor1_in3, LOW);
  digitalWrite( motor1_in4, HIGH);//lurus
}

void stop(){//membuat motor berhenti bergerak
  pinMode( motor1_in1 , LOW);
	pinMode( motor1_in2 , LOW);
  pinMode( motor1_in3 , LOW);
	pinMode( motor1_in4 , LOW);
}

void printVolts(){ //fungsi menampilkan isi voltase baterai yang ada
  int sensorValue = analogRead(A3); //membaca hasil
  int voltage = sensorValue * (5.00 / 1023.00);//convert hasil ke voltase.
  voltage= voltage*2.378; //dikalikan dengan resistor yang digunakan
  voltage= voltage/11.97 * 100; //mendapat persentase
  lcd.print(voltage); //print voltage ke LCD
  lcd.print("%");
}

void gerak_naik(){ //fungsi mengaktifkan gerak naik forklift
  analogWrite (motor1_kananB, 120);
  digitalWrite(motor1_in3B, LOW);
  digitalWrite(motor1_in4B, HIGH);
}

void gerak_turun(){//fungsi mengaktifkan gerak turun forklift
  analogWrite (motor1_kananB, 120);
  digitalWrite(motor1_in3B, HIGH);
  digitalWrite(motor1_in4B, LOW);
}

void gerak_stop(){//fungsi mematikan gerak forklift
  pinMode(motor1_in3B, LOW);
  pinMode(motor1_in4B, LOW);
}

void left(){ //fungsi gerak belok kiri
    lcd.setCursor(1, 1);
    left_wheel_pulse_count = 0;
    right_wheel_pulse_count = 0;
    while(left_wheel_pulse_count < 400){
      motor(0);
    }
    stop();
    left_wheel_pulse_count = 0;
    right_wheel_pulse_count = 0;
    while(right_wheel_pulse_count < 610){
      kiri();
    }
}

void kiri(){ //fungsi untuk motor kanan bergerak lurus, motor kiri reverse
  analogWrite(motor1_kananA, 80);
  analogWrite(motor1_kiriB, 80);
  digitalWrite( motor1_in1, LOW);
  digitalWrite( motor1_in2, HIGH);
  digitalWrite( motor1_in3, HIGH);
  digitalWrite( motor1_in4, LOW);
}

void right(){ //fungsi gerak belok kanan
    lcd.setCursor(1, 1);
    lcd.print("Belok Kanan");
    left_wheel_pulse_count = 0;
    right_wheel_pulse_count = 0;
    while(left_wheel_pulse_count < 400){
      motor(0);
    }
    stop();
    left_wheel_pulse_count = 0;
    right_wheel_pulse_count = 0;
    while(left_wheel_pulse_count < 610){
      kanan();
    }
}

void kanan(){//fungsi untuk motor kiri bergerak lurus, motor kanan reverse
  analogWrite(motor1_kananA, 80);
  analogWrite(motor1_kiriB, 80);
  digitalWrite( motor1_in1, HIGH);
  digitalWrite( motor1_in2, LOW);
  digitalWrite( motor1_in3, LOW);
  digitalWrite( motor1_in4, HIGH);
}

void side(){//fungsi line following area samping (line menuju area mengambil dan menaruh barang)
  
  float Kp=5,Ki=0.025,Kd=0.01; 
  float P, I, D, PID_value;
  float previous_error, previous_I;

  if(((sensor[2]==0)||(sensor[2]==1))&&((sensor[3]==1)||(sensor[3]==0))&&(sensor[4]==1) && (R == 1)){
    Rcount_side++;
  }
  else if((sensor[0]==0)&&(sensor[1]==0)&&(sensor[2]==0)&&(sensor[3]==1)&&(sensor[4]==0)){
    error=-3;
    lcd.setCursor(1, 1);
    lcd.print(L);
  }
  else if((sensor[0]==0)&&(sensor[1]==0)&&(sensor[2]==1)&&(sensor[3]==1)&&(sensor[4]==0)){
    error=-2;
    lcd.setCursor(1, 1);
    lcd.print(L);
  }
  else if((sensor[0]==0)&&(sensor[1]==0)&&(sensor[2]==1)&&(sensor[3]==0)&&(sensor[4]==0)){
    error=0;
    lcd.setCursor(1, 1);
    lcd.print(L);
  }
  else if((sensor[0]==0)&&(sensor[1]==1)&&(sensor[2]==1)&&(sensor[3]==0)&&(sensor[4]==0)){
    error=2;
    lcd.setCursor(1, 1);
    lcd.print(L);
  }
  else if((sensor[0]==0)&&(sensor[1]==1)&&(sensor[2]==0)&&(sensor[3]==0)&&(sensor[4]==0)){
    error=3;//awal 2; semua kelebihan 1
    lcd.setCursor(1, 1);
    lcd.print(L);
  }
  else if((sensor[0]==1)&&((sensor[1]==1)||(sensor[1]==0))&&((sensor[2]==0)||(sensor[2]==1)) && (L==1)){
    Lcount_side++;
  }
  else if((sensor[0]==1)&&((sensor[1]==0)||(sensor[1]==1))&&((sensor[2]==1)||(sensor[2]==0))&&((sensor[3]==1)||(sensor[3]==0))&&(sensor[4]==1) && (M==1)){
    count_mid++;
  }
  else{
    error = error;
  }

  P = error;
  I = I + previous_I;
  D = error-previous_error;
    
  PID_value = (Kp*P) + (Ki*I) + (Kd*D);
    
  previous_I= I;
  previous_error= error;

  motor(PID_value);
}

void servor(){//fungsi untuk meluruskan forklift
  myservo.attach(11);
  myservo.write(90);
  delay(1000);
  myservo.detach(); //untuk menonaktifkan servo
}

void servog(){//fungsi untuk memiringkan forklift ke arah robot
  myservo.attach(11);
  myservo.write(0);
  delay(1000);
  myservo.detach(); //untuk menonaktifkan servo
}

void servoe(){//fungsi menonaktifkan servo
  myservo.detach();
}