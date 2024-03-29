#include <Wire.h>
#include <Adafruit_PWMServoDriver.h> //scl = A5 / sda = A4

Adafruit_PWMServoDriver pwm=Adafruit_PWMServoDriver();

float duty = 0; // 0~100 [%]
float motor_speed, motor_speed_past, motor_speed_filter; //1000~2000us 

float lowpassfilter(float filter, float data, float lowpass_constant)
{
  filter = data * (1 - lowpass_constant) + filter * lowpass_constant;
  return filter;   
}

void BLDC()
{ 
  do
  {
    
    motor_speed = constrain(map(duty, 0, 100, 1613, 3226), 1613, 3226); //1000~2000ms 로 제한을 걸고 duty를 mapping 하여 변환함
    motor_speed_filter = lowpassfilter(motor_speed_past, motor_speed, 0.9);
    Serial.println(motor_speed_filter);
    pwm.setPWM(15,0,motor_speed_filter);
    motor_speed_past = motor_speed_filter;
    delay(200);
    }while(abs(motor_speed - motor_speed_filter) > 3);
    //delay(1000);
    //pwm.setPWM(0,0,1613);
}


void setup() 
{
  Serial.begin(9600);
  pwm.begin();
  pinMode(2, INPUT);
  pinMode(3, OUTPUT);
  pinMode(A2, OUTPUT);
  pwm.setPWMFreq(390); //->400hz로 측정됨 = 2.5ms 즉 1당 0.620us
}

void loop() 
{

  if(Serial.available())
  {
//    if(digitalRead(2) == HIGH)
//    {
//      digitalWrite(3, HIGH);
//    }
//    else
//    {
//      digitalWrite(3, LOW);
//    }
//      
//    
    duty = Serial.parseInt();
    //pwm.setPWM(3,0,duty);
    //analogWrite(A2, duty);
    BLDC();
  }

}
