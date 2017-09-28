/*
 * ServicePedestrianCall.h
 *
 *  Created on: May 21, 2017
 *      Author: root
 *
 * Manages the pedestrian call. Wait for pedestrian call and send event to ServiceTrafficLight.
 */

#ifndef SERVICE_SERVICEPEDESTRIANCALL_H_
#define SERVICE_SERVICEPEDESTRIANCALL_H_

#include "ServiceAbstract.h"
#include "../dao/DeviceButton.h"
#include "../util/SmartDelay.h"
#include "Event.h"

#define PIN_BUTTON 12

class ServicePedestrianCall : public ServiceAbstract {
public:
	ServicePedestrianCall();
	virtual ~ServicePedestrianCall();
	void update(Event *event);

	void execCurrentState();

private:
	DeviceButton* deviceButton;

	SmartDelay stateDelay;

	// pointer to the current state
	void (ServicePedestrianCall::*currentState)();

	// differents states
	void stateWaitCall();
};

#endif
