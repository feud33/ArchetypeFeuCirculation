/**
 * Main programme for Traffic light managment
 * This is an example of objet oriente programm on arduino
 *
 */
#include "TrafficLight.h"

#include "src/process/Scheduler.h"
#include "src/service/ServiceTrafficLight.h"
#include "src/service/ServicePedestrianLight.h"
#include "src/service/ServicePedestrianCall.h"

#define LOGGER "LightMyFire : "

Scheduler scheduler(10000);
SmartDelay schedulerDelay;

void setup() {
	Serial.begin(9600);
	delay(200);
	Serial.print(LOGGER);
	Serial.println("starting");

	ServiceTrafficLight* serviceTrafficLight = new ServiceTrafficLight();
	ServicePedestrianLight* servicePedestrianLight = new ServicePedestrianLight();
	ServicePedestrianCall* servicePedestrianCall = new ServicePedestrianCall();

	servicePedestrianCall->addAListener(serviceTrafficLight);
	serviceTrafficLight->addAListener(servicePedestrianLight);

	scheduler.addService(serviceTrafficLight, "TL");
	scheduler.addService(servicePedestrianLight, "PL");
	scheduler.addService(servicePedestrianCall);

	delay(1000);
}

void loop() {
	scheduler.runAllProcesses();
}
