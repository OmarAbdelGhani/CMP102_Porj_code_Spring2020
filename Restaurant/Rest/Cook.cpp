#include <cmath>
#include<iostream>
#include "Cook.h"
using namespace std;
Cook::Cook()
{
	isAvailable = true;
	preparing = nullptr;
	cooldownEnd = -1;
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

	speed = rand() % (x - y) + x;

}
void Cook::SetBreak(int x, int y) {

	Break = rand() % (x - y) + x;

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
	if (cd <= 0) { // fault tolerant
		cooldownEnd = -1;
	}
	else {
		cooldownEnd = cd;
	}


}
void Cook::checkCd(int timestep) {
	if (cooldownEnd = timestep) {
		isAvailable = true;
		cooldownEnd = -1; // as a flag
	}
}
void Cook::serveOrder(Order* _order, int& timeStep) {
	isAvailable = false; // becuase the cook cant receive an order if he is serving another
	preparing = _order; // order is currently being served
	_order->setStatus(SRV);
	_order->Set_serveTime(timeStep);
	// we now calculate the time taken to serve the order:
	float timeTaken = ceil((_order->get_size()) / speed); // the size of the order divided by the speed of the cook
														   // then rounded to the nearest time step
	cooldownEnd = timeTaken + timeStep;
	_order->Set_finishTime(_order->Get_servetime() + timeTaken);
}
bool Cook::checkOrder(int timestep, Order*& finishedOrder) {
	if (preparing == nullptr) {
		return false;
	}
	else if (preparing->Get_finishtime() == timestep) {
		preparing->setStatus(DONE);
		finishedOrder = preparing;
		cout << "Order with ID " << preparing->GetID() << " finished" << endl;
		preparing = nullptr;
		return true;
	}
}