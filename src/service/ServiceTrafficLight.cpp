/*
 ² * ServiceTrafficLight.cpp
 *
 *  Created on: May 21, 2017
 *      Author: root
 */

#include "ServiceTrafficLight.h"

ServiceTrafficLight::ServiceTrafficLight() {
	ledRed = new DeviceLed(PIN_LIGHT_RED);
	ledOrange = new DeviceLed(PIN_LIGHT_ORANGE);
	ledGreen = new DeviceLed(PIN_LIGHT_GREEN);

	currentState = &ServiceTrafficLight::stateGreen;

	stateDelay.reset();
}

ServiceTrafficLight::~ServiceTrafficLight() {
}

void ServiceTrafficLight::execCurrentState() {
	(this->*currentState)();
}

void ServiceTrafficLight::update(Event *event) {

	if (currentState == &ServiceTrafficLight::stateGreen) {
		stateDelay.reset();
	}
}

void ServiceTrafficLight::stateGreen() {
	if (stateDelay.now()) {
		stateDelay.addNextDelay(DELAY_ORANGE);

		ledGreen->turnOff();
		ledOrange->turnOn();
		ledRed->turnOff();

		currentState = &ServiceTrafficLight::stateOrange;
	}
}

void ServiceTrafficLight::stateOrange() {
	if (stateDelay.now()) {
		stateDelay.addNextDelay(DELAY_RED);

		ledGreen->turnOff();
		ledOrange->turnOff();
		ledRed->turnOn();

		Event event(EventTypePedestrianGreen);
		notify(&event);

		currentState = &ServiceTrafficLight::stateRed;
	}
}

void ServiceTrafficLight::stateRed() {
	if (stateDelay.now()) {
		stateDelay.addNextDelay(DELAY_BLINK_RED);

		Event event(EventTypePedestrianBlinkGreen);
		notify(&event);

		currentState = &ServiceTrafficLight::stateBlinkRed;
	}
}

void ServiceTrafficLight::stateBlinkRed() {
	if (stateDelay.now()) {
		stateDelay.addNextDelay(DELAY_GREEN);

		ledGreen->turnOn();
		ledOrange->turnOff();
		ledRed->turnOff();

		Event event(EventTypePedestrianRed);
		notify(&event);

		currentState = &ServiceTrafficLight::stateGreen;
	}
}
