#ifndef __RESTAURANT_H_
#define __RESTAURANT_H_

#include "..\Defs.h"
#include "..\CMUgraphicsLib\CMUgraphics.h"
#include "..\GUI\GUI.h"
#include "..\Generic_DS\Queue.h"
#include "..\Generic_DS\LinkedList.h"
#include "..\Generic_DS\priorityQueue.h"
#include "..\Events\Event.h"
#include "..\Events\ArrivalEvent.h"
#include "..\Cancellation_event.h"
#include "..\PromotionEvent.h"
#include <fstream>
#include <time.h>



#include "Order.h"

// it is the maestro of the project
class Restaurant
{
private:
	GUI* pGUI;
	Queue<Event*> EventsQueue;	//Queue of all events that will be loaded from file


	/// ==> 
	//	DEMO-related members. Should be removed in phases 1&2
	Queue<Order*> DEMO_Queue;	//Important: This is just for demo
	/// ==>



	//
	// TODO: Add More Data Members As Needed
	//
	Queue<Order*> VEGANOrder;  //  vegan queues
	Queue<Order*>normalorder;
	priorityQueue<Order*>VIPorder; // priority queue of vip
	LinkedList<Cook*>VIPcook;
	LinkedList<Cook*>NORMALcook;
	LinkedList<Cook*>VEGANcook;
	LinkedList<Order*>Inservicelist;
	LinkedList<Order*>Finishedlist;
	LinkedList<Cook*>CooksInService;
	int TS;  //timestep

	//int SV;     //speed of vip cook
	//int SN;    //speed of normal cook 
	//int SG;   //speed of vegan cook
	// the above lines are of no use in phase 2

	int SN_max;   //Max speed of normal
	int SN_min;    //Min speed of normal
	int SG_max;    //MAx speed of vegan
	int SG_min;     //Min speed of vegan
	int SV_max;      // Max speed of VIP
	int SV_min;      //Min speed of VIP


	int V;   // no. of vip cooks
	int N;  // no. of normal cooks
	int G;  // no. of vegan cooks
	int BO;  // the number of orders a cook must prepare before taking a break

	//int BN;  //BREAK DURATION FOR NORMAL
	//int BG;   //BREAK DURATION FOR VEGAN
	//int BV;   //BREAK DURATION FOR VIP
	// the above lines are of no use in phase 2

	int BN_min;     //Min break time of normal
	int BN_max;       //Max break of normal
	int BG_min;        //Min break of vegan
	int BG_max;         //Max break of vegan
	int BV_min;          //Min break of vip
	int BV_max;			//Max break of vip

	float InjProb;        //Injury probability of cook
	int RstPrd;          //Rest period of the injured cook

	int AutoP;    //TIME TO PROMOT NORMAL ORDER TP VIP
	int VIP_WT;   //time to turn VIP to urgent
	int M;        // NO of Events in file

	float NoNormal;    //No of Nomral Orders
	float NoVegan;	//No of Vegan Orders
	float NoVIP;		//No of VIP	  Orders
	float NoInj;      //No of injured cooks
	//Float to diplay percentage of AutoPromoted Orders


	float WaitingTime;  //Total Waiting time
	float ServiceTime;  //Total serving time

	int NoUrgent;  //Total urgent orders
	int NoAutoPromoted; //Total number of auto promoted orders

	int CurServNormal,CurServVIP,CurServVegan; 

	ofstream Ofile;
	string Service;  //String to store Cooks and serviced orders each time step
	string name;  //name of input file

public:

	Restaurant();
	~Restaurant();

	void ExecuteEvents(int TimeStep);	//executes all events at current timestep
	void RunSimulation();




	void FillDrawingList();

	//
	// TODO: Add More Member Functions As Needed
	void AddEvents(Event* ev); // add event to queue
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	void AddToVeganQueue(Order* po); // add frozen to queue
	void AddNormalToQueue(Order* po); // add normal order to list
	void AddToVIPArray(Order* ord);  //add to vip array   //Omar AbdelGhani removed the priorty as it is by default in the order
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	ORD_TYPE Getordertype(char ordtype);   // convert the char to the order type
	void CancelNormal(int id);  // lsa mat3amlsh
/// ===================    DEMO-related functions. Should be removed in phases 1&2   ================= 

	void Just_A_Demo();	//just to show a demo and should be removed in phase1 1 & 2
	void AddtoDemoQueue(Order* po);	//adds an order to the demo queue

/// ================================================================================================== 

	//By Omar AbdelGhani
	void LoadFile();         //Loads Input data from a File
	void InitializeNormal();
	void InitializeVIP();
	void InitializeVegan();
	//to initialize cooks of each type with data entered in the file

	Order* CancelById(int);      //For order Cancellation
	int WaitNormal();         //Counts number of waiting Orders
	int WaitVegan();			//Counts number of waiting vegan orders
	int WaitVIP();				//Counts number of waiting vip orders
	void OutputOrder(Order*);   //Prints order data to the outputfile



	// By Amer

	void setNoNormal(int);
	int getNoNormal();

	void setNoVegan(int);
	int getNoVegan();

	void setNoVIP(int);
	int getNoVIP();

	void getAvailableCooksNo(int& VIP, int& vegan, int& normal); // by Amer and Abdelghani
	Cook* getFirstAvailableCook(ORD_TYPE);
	Cook* getFirstCookBreak();
	Cook* getFirstCookInj();
	void adjustCookCooldown();
	void checkVIPtoUrgent();
	void adjustBreak();
	//ahmed sami
	void checkNormaltoVIP();

	//hamzawy
	void cooksHealthEmergencyProblems();
	Cook* getFirstveganCookinBreak();
	Cook* getFirstveganCookInj();
};

#endif