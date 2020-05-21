#include <cmath>
#include<iostream>
#include "Cook.h"
using namespace std;
Cook::Cook()
{
	isAvailable = true;
	isOnAbreak = false;
	isInj=false;
	preparing = nullptr;
	cooldownEnd = -1;
	ordersServedPreBreak = 0;
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
	srand(this->ID);
	speed = rand() % (y - x + 1) + x;

}
void Cook::SetBreak(int x, int y) {
	srand(this->ID);
	Break = rand() % (y - x + 1) + x;

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
	if (cooldownEnd == timestep) {
	//	cout << "cook with id " << ID << " of type " << type << " has returned from break/rest" << endl;
		isAvailable = true;
		isOnAbreak = false;
		cooldownEnd = -1; // as a flag

	}
}

bool Cook::isBreak() {
	return isOnAbreak;
}

bool Cook::isHurt() {
	return isInj;
}

void Cook::setHurt(bool damage) {
	isInj = damage;
}

void Cook::serveOrder(Order* _order, int& timeStep) {
	isAvailable = false; // becuase the cook cant receive an order if he is serving another
	if (preparing) {
		return;
	}
	cout << "cook with id " << ID << " of type " << type << "is now serving order " << _order->GetID() << endl;
	preparing = _order; // order is currently being served
	ordersServedPreBreak++;
	_order->setStatus(SRV);
	_order->Set_serveTime(timeStep);
	// we now calculate the time taken to serve the order:
	float timeTaken = ceil(float(_order->get_size() / speed)); // the size of the order divided by the speed of the cook
														   // then rounded to the nearest time step
	cooldownEnd = timeTaken + timeStep;
	_order->Set_finishTime(_order->Get_servetime() + timeTaken);
}
bool Cook::checkOrder(int timestep, Order*& finishedOrder) {
	if (preparing == nullptr) {
		finishedOrder = nullptr;
		return false;
	}
	else if (preparing->Get_finishtime() == timestep) {
		preparing->setStatus(DONE);
		finishedOrder = preparing;
		cout << "Order with ID " << preparing->GetID() << " finished" <<"by cook id "<<ID<<" of type "<<type<< endl;
		preparing = nullptr;
		return true;
	}
	return false;
}

int Cook::getOrdersServed() {
	return ordersServedPreBreak;
}
void Cook::setOrdersServed(int orders) {
	ordersServedPreBreak = orders;
}
void Cook::goOnAbreak(int timeStep) {
	cooldownEnd = timeStep + Break;
	isAvailable = false;
	isOnAbreak = true;
	cout << "Cook with id " << ID << " of type " << type << " Went on a break, and will comeback at timestep " << cooldownEnd << endl;
}

void Cook::decreasespeedtohalf() {
	speed = speed / 2;
}
void Cook::returnspeedtonormal() {
	speed = speed * 2;
}
Order* Cook::getpreparing() {
	return preparing;

}