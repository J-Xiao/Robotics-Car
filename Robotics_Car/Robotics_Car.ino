#include <SoftwareSerial.h>
#include <Servo.h>

#define echoPin_1 8 // Echo Pin of the sensor in the front
#define trigPin_1 7 // Trigger Pin of the sensor in the front
#define echoPin_2 2 // Echo Pin of the sensor on the right
#define trigPin_2 4 // Trigger Pin of the sensor on the right

Servo myservo_1; //Left wheel, not used in the simulation, represented by the red LED
Servo myservo_2; //Right wheel, not used in the simulation, represented by the green LED

int maximumRange_front = 15;// Maximum range in the front needed
int maximumRange_right = 5;// Maximum range on the right needed
long duration, distance_front, distance_right; 

long get_distance_front(){ //Function used to measure the distance in the front
 long duration;
 long distance_front;
 
 digitalWrite(trigPin_1, LOW); 
 delayMicroseconds(2); 

 digitalWrite(trigPin_1, HIGH); //Emitting soundwave
 delayMicroseconds(10); 
 
 digitalWrite(trigPin_1, LOW);
 duration = pulseIn(echoPin_1, HIGH); //Receiving soundwave
 
 //Calculate the distance (in cm) based on the speed of sound.
 distance_front = duration/58.2;

 return distance_front;
}

long get_distance_right(){ //Function used to measure the distance on the right
 long duration;
 long distance_right;
 
 digitalWrite(trigPin_2, LOW); 
 delayMicroseconds(2); 

 digitalWrite(trigPin_2, HIGH);
 delayMicroseconds(10); 
 
 digitalWrite(trigPin_2, LOW);
 duration = pulseIn(echoPin_2, HIGH);
 
 //Calculate the distance (in cm) based on the speed of sound.
 distance_right = duration/58.2;

 return distance_right;
}

void setup() {
 Serial.begin (9600);
 pinMode(trigPin_1, OUTPUT);
 pinMode(echoPin_1, INPUT);
 pinMode(trigPin_2, OUTPUT);
 pinMode(echoPin_2, INPUT);
 pinMode(9, OUTPUT); //Not used in the simulation
 pinMode(10, OUTPUT); //Not used in the simulation
 pinMode(12, OUTPUT); //Red LED, representing the left wheel
 pinMode(13, OUTPUT); //Green LED, representing the right wheel
 
 myservo_1.attach(9); //Not used in the simulation
 myservo_2.attach(10); //Not used in the simulation
}

void loop() {
 distance_front = get_distance_front();
 distance_right = get_distance_right();
 
 if(distance_front >= maximumRange_front){ 
    digitalWrite(12, HIGH); 
    digitalWrite(13, HIGH); //Both LEDs (wheels) are working
    /*myservo_1.write(0);
    myservo_2.write(180);*/ //Corresponded servo code
 }else if(distance_front < maximumRange_front && distance_right >= maximumRange_right){ 
    digitalWrite(12, HIGH);
    digitalWrite(13, LOW); //Right wheel stops, turing right
    //myservo_1.write(0);
 }else if(distance_front < maximumRange_front && distance_right < maximumRange_right){
    digitalWrite(12, LOW);
    digitalWrite(13, HIGH); //Left wheel stops, turing left
    //myservo_2.write(180); 
 }
 delay(5); //Delay 5 ms before the next loop
}
