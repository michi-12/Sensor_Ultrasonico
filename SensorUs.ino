#include <Servo.h> // incluir la biblioteca para controlar el servo
 
Servo myservo; // declarar un objeto de tipo Servo
 
int trigPin = 6;  // pin para el trigger del sensor
int echoPin = 7; // pin para el echo del sensor
int angle = 0; // ángulo actual del servo
int buzzer = 11;

long duration;
int safetyDistance;
int distance;
int distancetemp;
 
void setup() {
  Serial.begin(9600); // inicializar el puerto serie
  myservo.attach(4); // conectar el servo al pin 9
  pinMode(trigPin, OUTPUT); // configurar el pin trigger como salida
  pinMode(echoPin, INPUT); // configurar el pin echo como entrada
  pinMode(buzzer, OUTPUT);
}
 
void loop() {
  for (angle = 0; angle <= 180; angle += 5) {
    myservo.write(angle); //movemos el servo
    delay(100); //para que el servo no este moviendose
    int distance = getMedianDistance(); // distancia medida por el sensor
    if (distance <= 20) {
      digitalWrite(buzzer, HIGH);
    }else if (distance > 20 & distance < 45){
      digitalWrite(buzzer, HIGH);
    }else{
      digitalWrite(buzzer, LOW);
    }
    Serial.print(angle);
    Serial.print(", ");
    Serial.println(distance);
    delay(50);
  }
  for (angle = 180; angle >= 0; angle -= 5) {
    myservo.write(angle); //movemos el servo
    delay(100); //para que el servo no este moviendose
    int distance = getMedianDistance(); // distancia medida por el sensor
    if (distance <= 20) {
      digitalWrite(buzzer, HIGH);
    }else if (distance > 20 & distance < 45){
      digitalWrite(buzzer, HIGH);
    }else{
      digitalWrite(buzzer, LOW);
    }

    Serial.print(angle);
    Serial.print(", ");
    Serial.println(distance);
    delay(50);
  }
}
 
int cmp_desc(const void *c1, const void *c2){  
  return *((int *)c2) - *((int *)c1);
}
 
int getMedianDistance() {
  int distances[3];
  for (int i = 0; i < 3; i++) { //3 mediciones
    long duration, distance;
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    distance = (duration / 2) / 29.1;
    distances[i] = distance;
  }
 
  //ordenamos
  qsort(distances, 3, sizeof(int), cmp_desc);
   
  //tomamos la mediana (el central)
  return distances[1];
}