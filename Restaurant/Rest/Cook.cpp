#include <cmath>
#include "Cook.h"

Cook::Cook()
{
	isAvailable = true;
	preparing = nullptr;
}


Cook::~Cook()
{
}


int Cook::GetID() const
{
	return ID;
}


ORD_TYPE Cook::GetType() const
{
	return type;
}


void Cook::setID(int id)
{
	ID = id;
}

void Cook::setType(ORD_TYPE t)
{
	type = t;
}


void Cook::SetSpeed(int x, int y) {

	speed = rand() % y + x;

}
void Cook::SetBreak(int x, int y) {

	Break = rand() % y + x;

}

void Cook::setStatus(bool status) {
	isAvailable = status;
}
bool Cook::getStatus() {
	return isAvailable;
}
int Cook::getCd() {
	return cooldownEnd;
}
void Cook::setCd(int cd) {
	cooldownEnd = cd;
}
void Cook::checkCd(int timestep) {
	if (cooldownEnd = timestep) {
		isAvailable = true;
	}
}
void Cook::serveOrder(Order* _order, int& timeStep) {
	isAvailable = false; // becuase the cook cant receive an order if he is serving another
	preparing = _order; // order is currently being served
	_order->setStatus(SRV);
	_order->Set_serveTime(timeStep);
	// we now calculate the time taken to serve the order:
	float timeTaken = round((_order->get_size()) / speed); // the size of the order divided by the speed of the cook
														   // then rounded to the nearest time step
	cooldownEnd = timeTaken;
	_order->Set_finishTime(_order->Get_servetime() + timeTaken);


}