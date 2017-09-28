#include "ServicePedestrianCall.h"

/**
 * Constructor
 *
 */
ServicePedestrianCall::ServicePedestrianCall() {
	deviceButton = new DeviceButton(PIN_BUTTON);

	currentState = &ServicePedestrianCall::stateWaitCall;

	stateDelay.reset();
}

ServicePedestrianCall::~ServicePedestrianCall() {
}

void ServicePedestrianCall::execCurrentState() {
	(this->*currentState)();
}

void ServicePedestrianCall::update(Event *event) {
}

void ServicePedestrianCall::stateWaitCall() {
	if( deviceButton->isPressed()) {
		Event event(EventTypePedestrianCall);
		notify(&event);
	}
}
