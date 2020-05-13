#pragma once
#include"Order.h"
#include "..\Defs.h"
#include <stdlib.h> 

#pragma once
class Cook
{
	int ID;
	ORD_TYPE type;	//for each order type there is a corresponding type (VIP, Normal, Vegan)
	int speed;		//dishes it can prepare in one clock tick (in one timestep)
	int Break;		//Break time for each cook
	bool isAvailable; // is set to false whenever a cook isnt availble to receive a new order , ie: (injured, on a break, etc...) -Amer
					  // it is set to true by defualt
	Order* preparing; // the order that is being currently prepared by this cook -Amer
	int cooldownEnd; // the timestep at which the cook is available again after being unavailable
				  // Amer
public:
	Cook();
	virtual ~Cook();
	int GetID() const;
	ORD_TYPE GetType() const;
	void setID(int);
	void setType(ORD_TYPE);
	void SetSpeed(int, int);
	void SetBreak(int, int);
	///////////////////////////////////////

	//By Amer

	void serveOrder(Order*, int& timestep); //Makes the Cook Prepare the order
	bool getStatus(); // we check if the cook is available or not
	void setStatus(bool);
	
	void setCd(int); // sets the cooldown of the cook, cd = cooldown
					 // cool down means the down time of the cook, the time at which he cant take orders
	int getCd();

	void checkCd(int); //checks if the cooldown of the cooks has ended or not, 
	bool checkOrder(int, Order*&); // checks whether the order is finished or not.
	void decreasespeedtohalf();//hamzawyi i will use it in cook health
};
