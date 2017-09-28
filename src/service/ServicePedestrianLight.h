/*
 * ServicePedestrianLight.h
 *
 *  Created on: May 21, 2017
 *      Author: feud7506
 *
 * Manages the pedestrian light. Wait for traffic light events.
 *
 */

#ifndef SERVICE_SERVICEPEDESTRIANLIGHT_H_
#define SERVICE_SERVICEPEDESTRIANLIGHT_H_

#include "ServiceAbstract.h"
#include "../dao/DeviceLed.h"
#include "../util/SmartDelay.h"
#include "Event.h"

#define PIN_PEDESTRIAN_RED 11
#define PIN_PEDESTRIAN_GREEN 10

#define DELAY_PEDESTRIAN 100

class ServicePedestrianLight : public ServiceAbstract {
public:
	ServicePedestrianLight();
	virtual ~ServicePedestrianLight();
	void update(Event *event);

	void execCurrentState();

private:
	DeviceLed* ledRed;
	DeviceLed* ledGreen;

	SmartDelay stateDelay;

	// pointer to the current state
	void (ServicePedestrianLight::*currentState)();

	// differents states
	void stateGreen();
	void stateRed();
	void stateBlinkOn();
	void stateBlinkOff();
	void stateWait();
};

#endif
