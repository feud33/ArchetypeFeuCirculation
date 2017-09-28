/*
 * ServiceTrafficLight.h
 *
 *  Created on: May 21, 2017
 *      Author: root
 *
 * Manages Traffic light. Send events to ServicePedestrianLight. Wait for time events or pedestrian events.
 */

#ifndef SERVICE_SERVICETRAFFICLIGHT_H_
#define SERVICE_SERVICETRAFFICLIGHT_H_

#include "ServiceAbstract.h"
#include "../dao/DeviceLed.h"
#include "../util/SmartDelay.h"
#include "Event.h"

#define PIN_LIGHT_RED 4
#define PIN_LIGHT_ORANGE 3
#define PIN_LIGHT_GREEN 2

#define DELAY_GREEN 5000
#define DELAY_ORANGE 1000
#define DELAY_RED 3000
#define DELAY_BLINK_RED 1000

class ServiceTrafficLight : public ServiceAbstract {
public:
	ServiceTrafficLight();
	virtual ~ServiceTrafficLight();
	void update(Event *event);

	void execCurrentState();

private:
	DeviceLed* ledRed;
	DeviceLed* ledOrange;
	DeviceLed* ledGreen;

	SmartDelay stateDelay;

	// pointer to the current state
	void (ServiceTrafficLight::*currentState)();

	// differents states
	void stateGreen();
	void stateOrange();
	void stateRed();
	void stateBlinkRed();
};

#endif /* PROCESSTRAFFICLIGHT_H_ */
