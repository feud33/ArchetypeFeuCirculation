#include "ServicePedestrianLight.h"

#include "Event.h"

ServicePedestrianLight::ServicePedestrianLight() {
	ledRed = new DeviceLed(PIN_PEDESTRIAN_RED);
	ledGreen = new DeviceLed(PIN_PEDESTRIAN_GREEN);

	currentState = &ServicePedestrianLight::stateBlinkOn;

	stateDelay.reset();
}

ServicePedestrianLight::~ServicePedestrianLight() {
}

void ServicePedestrianLight::execCurrentState() {
	(this->*currentState)();
}

void ServicePedestrianLight::update(Event *event) {
	if( event->getEventType() == EventTypePedestrianGreen) {
		currentState = &ServicePedestrianLight::stateGreen;
	} else if( event->getEventType() == EventTypePedestrianRed) {
		currentState = &ServicePedestrianLight::stateRed;
	} else if( event->getEventType() == EventTypePedestrianBlinkGreen) {
		currentState = &ServicePedestrianLight::stateBlinkOff;
	} else {
		currentState = &ServicePedestrianLight::stateWait;
	}
}

void ServicePedestrianLight::stateBlinkOn() {
	if( stateDelay.now()) {
		stateDelay.addNextDelay(DELAY_PEDESTRIAN);

		ledGreen->turnOn();
		ledRed->turnOff();

		currentState = &ServicePedestrianLight::stateBlinkOff;
	}
}

void ServicePedestrianLight::stateBlinkOff() {
	if( stateDelay.now()) {
		stateDelay.addNextDelay(DELAY_PEDESTRIAN);

		ledGreen->turnOff();
		ledRed->turnOff();

		currentState = &ServicePedestrianLight::stateBlinkOn;
	}
}

void ServicePedestrianLight::stateGreen() {
	ledGreen->turnOn();
	ledRed->turnOff();

	currentState = &ServicePedestrianLight::stateWait;
}

void ServicePedestrianLight::stateRed() {
	ledGreen->turnOff();
	ledRed->turnOn();

	currentState = &ServicePedestrianLight::stateWait;
}

void ServicePedestrianLight::stateWait() {
}
