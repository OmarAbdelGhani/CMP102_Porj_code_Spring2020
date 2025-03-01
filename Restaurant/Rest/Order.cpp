#include "Order.h"
#include<iostream>
Order::Order(int id, ORD_TYPE r_Type)
{
	ID = (id > 0 && id < 1000) ? id : 0;	//1<ID<999
	type = r_Type;
	isUrgent = false;
	promTime = INT_MAX;
	priority = -1;
	status = WAIT;
	ServTime = -1;
	FinishTime = -1;
}

Order::~Order()
{
}

void Order::SetID(int id)
{
	ID = id;
}

int Order::GetID()
{
	return ID;
}


void Order::Set_ORD_Type(ORD_TYPE Type)
{
	type = Type;
}

ORD_TYPE Order::GetType() const
{
	return type;
}


void Order::SetDistance(int d)
{
	Distance = d > 0 ? d : 0;
}

int Order::GetDistance() const
{
	return Distance;
}


void Order::setStatus(ORD_STATUS s)
{
	status = s;
}

ORD_STATUS Order::getStatus() const
{
	return status;
}

void Order::Set_Money(int money)
{
	totalMoney = money;
}

int Order::Get_money()
{
	return totalMoney;
}

void Order::Set_ArrTime(int arrtime)
{
	ArrTime = arrtime;
}

int Order::Get_Arrtime()
{
	return ArrTime;
}

void Order::Set_serveTime(int servetime)
{
	ServTime = servetime;
}

int Order::Get_servetime()
{
	return ServTime;
}

void Order::Set_finishTime(int finishtime)
{
	FinishTime = finishtime;
}

int Order::Get_finishtime()
{
	return FinishTime;
}

void Order::calc_priority()
{
	//int p;
	//p = (24 - ArrTime) + totalMoney + Order_Size;

	priority = 2 * totalMoney - Order_Size; // AMER

}

void Order::Set_size(int s)
{
	Order_Size = s;
}

int Order::get_size()
{
	return Order_Size;
}

void Order::cancel_order(bool s)
{
	canceled = s;
}

bool Order::is_canceled()
{
	return canceled;
}

void Order::promotion(double extramoney)
{
	if (type == TYPE_NRM)
	{
		type = TYPE_VIP;
		totalMoney += extramoney;
		calc_priority();
	}
}
bool Order::getUrgency() {
	return isUrgent;
}
void Order::setUrgency(bool urgency) {
	isUrgent = urgency;
}

int Order::GetPriority() {
	
	return priority;
}
void Order::setPriority(int priority) {
	this->priority = priority;
}
int Order::getPromTime() {
	return promTime;
}
void Order::setPromTime(int prom) {
	promTime = prom;
}