#include "Extend_Card_lib/configTest1.h"

#include "Extend_Card_lib/Extend_Card_lib.h"
#include "Screen_lib/LibScreen.h"

#include "Arduino.h"
#include "ServoDS3240.h"


#define SERVO_PIN 18 //à remplacer par le pin qu'on voudra PWM
#define SERVO_CHANNEL 0

Screen myScreen;
Extend_Card myCard;
ServoDS3240 monServo(SERVO_PIN, SERVO_CHANNEL);


unsigned long Time_screen;
unsigned long Time;
unsigned long total_time1;

unsigned long Time_config;
unsigned long total_time2;

int iteration1;
int iteration2;

#define FirmwareVersion "0.5"

float timeDelay = 10000;

void setup() {
  Serial.begin(115200);

  myCard = Extend_Card();
  monServo.begin();

  myScreen = Screen(); 
  myScreen.touch_calibrate();
  
  myScreen.imageStart(FirmwareVersion);
  Serial.println("Initialisation finie");

  delay(5000);

  myScreen.Select_Menu_init();

  Time_screen = millis();
  
  Time_config = micros();

  Time = millis();

  total_time1 = 0;
  iteration1 = 0;

  total_time2 = 0;
  iteration2 = 0;
}

void loop() 
{
	if (millis() - Time_screen > 20){
		Time_screen = millis();
		myScreen.run(&myScreen);
		total_time1 = total_time1 + (millis() - Time_screen);
		iteration1 ++;
	}

	if (micros() - Time_config > 400){
		Time_config = micros();
		if (myScreen.activeControle == true){
		Task2();
		}
		total_time2 = total_time2 + (micros() - Time_config);
		iteration2 ++;
	}

	if (millis() - Time >= timeDelay){
	
		Serial.print("Temp de gestion des taches sur "+String(timeDelay/1000.0));
		//Serial.print(" seconde :");
		//Serial.print(total_time1);
		Serial.print("  Ecran :");
		Serial.print((total_time1/timeDelay)*100);
		Serial.print("%");
		Serial.print("  Run config :");
		Serial.print((total_time2/(timeDelay*1000))*100);
		Serial.print("%");

		Serial.println("");

		float temp_moyen1 = total_time1/((float)iteration1);
		float temp_moyen2 = total_time2/((float)iteration2);
		Serial.print("Le temps moyen en miliseconde est de :");
		Serial.print(" Ecran :");
		Serial.print(temp_moyen1);
		Serial.println("");

		Serial.print("Le temps moyen en microseconde est de :");
		Serial.print(" Run config :");
		Serial.print(temp_moyen2);

		Serial.println("");

		iteration1 = 0;
		iteration2 = 0;

		total_time1 = 0;
		total_time2 = 0;

		Time = millis();
	}
}

void Task2(){
  
  if (myScreen.config_selectionne == 0){
    configTest1::run();
    myScreen.linearMeters[0].new_value = (int)(configTest1::value1*100.0/4095.0);
    myScreen.linearMeters[1].new_value = (int)(configTest1::value2*100.0/4095.0);
    myScreen.linearMeters[2].new_value = (int)(configTest1::value3*100.0/4095.0);
    myScreen.linearMeters[3].new_value = (int)(configTest1::value4*100.0/4095.0);
    myScreen.linearMeters[4].new_value = (int)(configTest1::value5*100.0/4095.0);
    myScreen.linearMeters[5].new_value = (int)(configTest1::value6*100.0/4095.0);
  
    if (myScreen.myGauge != nullptr){ 

      myScreen.myGauge->new_value = (int)((configTest1::value6) );

    }

	/// exemple simulé comme j'ai pas l'esp et le moteur avec moi
    /// Simulation pression sinusoïdale entre 0 et 4095
	static int step = 0;
    float pression = (sin(step / 10.0) + 1.0) / 2.0 * 4095.0;
    step++;

	/// qu'on remplacera par :
	/// Version capteur réel (activer ça plus tard)
	float pression = configTest1::value6;

    float angle = map(pression, 0, 4095, 0, 180);
    angle = constrain(angle, 0, 180);

    Serial.print("Pression = ");
    Serial.print(pression);
    Serial.print(" convertie donne Angle = ");
    Serial.println(angle);

    monServo.setAngle(angle);
  }
}