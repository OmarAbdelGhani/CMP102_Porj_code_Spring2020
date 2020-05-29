#include <cstdlib>
#include <time.h>
#include <iostream>
using namespace std;

#include "Restaurant.h"




Restaurant::Restaurant()
{
	pGUI = NULL;


}

void Restaurant::RunSimulation()
{
	pGUI = new GUI;
	PROG_MODE	mode = pGUI->getGUIMode();
	LoadFile();
	Ofile.open("output.txt", ios::out); //initialization of outputfile
	Ofile << "FT\tID\tAT\tWT\tST" << endl;
	//Initialize all count variables by zero, ex NoNormal,NoVegan and so on   By Omar AbdelGhani
	NoNormal = 0; NoVegan = 0;   NoVIP = 0;
	WaitingTime = 0;  ServiceTime = 0;
	NoUrgent = 0;  NoAutoPromoted = 0;
	NoInj = 0;
	NoInj = 0;
	CurServNormal=0;
	CurServVegan=0;
	CurServVIP=0;

	LinkedList<Order*>Inservicelist1;
	InitializeNormal();
	InitializeVIP();
	InitializeVegan();

	TS = 0;
	string ts;
	string Nn, Nv, Ng;
	int x = 1; // a variable to know after 5 time steps
	string v;// to count the number of waiting  vip orders
	string ve;// to count the number of waiting  vegan orders
	string n;// to count the number of waiting  normal orders
	//bool first=true;
		//Add a function for each mode in next phases
		// try changing to one


	while (!EventsQueue.isEmpty() || Inservicelist.getHead() || !normalorder.isEmpty() || !VEGANOrder.isEmpty() || !VIPorder.isEmpty()) {
		std::cout << "*****TIMESTEP " << TS << " BEGIN*****" << endl;
		if (!EventsQueue.isEmpty()) {
			while (EventsQueue.getPtrToFront()->getItem()->getEventTime() == TS) {//while the event time=the current time step

				ArrivalEvent* p = dynamic_cast<ArrivalEvent*>(EventsQueue.getPtrToFront()->getItem());
				PromotionEvent* r = dynamic_cast<PromotionEvent*>(EventsQueue.getPtrToFront()->getItem());
				Cancellation_event* q = dynamic_cast<Cancellation_event*>(EventsQueue.getPtrToFront()->getItem());
				if (p) {    //if it is an arrival event
					p->Execute(this); //generate an order and add it to the appropriate waiting list

				}
				else if (q) {    //if it is a cancellation event
					if (!(normalorder.isEmpty()) && normalorder.Exists(q->getOrderID())) {
						// delete the corresponding normal order if found
						q->Execute(this);
					}
				}
				else if (r) {
					if (!normalorder.isEmpty()) {
						r->Execute(this);
					}
				}
				Event* u = EventsQueue.getPtrToFront()->getItem();

				EventsQueue.dequeue(u);// get the next event
				if (!EventsQueue.getPtrToFront())
					break;

			}
		}


		//		string p=itos(i);
					//pGUI->PrintMessage("click to display the output of next time step");


			//*************** OLD PHASE ONE ORDER HANDLING DELETE WHEN READY ***************  -Amer


		//if (!VIPorder.isEmpty()) {
		//	Order* Q = VIPorder.getPtrToFront()->getItem();
		//	Inservicelist.InsertEnd(Q);
		//	VIPorder.dequeue(Q);                            //each time step pick one order from each type and add it to inservice list
		//								// i used insert end so that in finished list the first order is the first order putted in inservice list

		//}
		//if (!VEGANOrder.isEmpty()) {
		//	Order* t = VEGANOrder.getPtrToFront()->getItem();
		//	Inservicelist.InsertEnd(t);
		//	VEGANOrder.dequeue(t);

		//}
		//if (!normalorder.isEmpty()) {
		//	Order* w = normalorder.getPtrToFront()->getItem();
		//	Inservicelist.InsertEnd(w);
		//	normalorder.dequeue(w);

		//}
		//cout << " GOT THIS FAR BEFORE CRASHING"; // FOR DEBUGGING PURPOSES ONLY REMOVE BEFORE SUBMISSION -Amer


		//if ((i == (5 * x))) { //each 5 time steps pick one order from each type from inservice list to finished list
		//	if (Inservicelist.getHead()) {

		//		Order* e = Inservicelist.getHead()->getItem(); //the first order putted in inservice list which is a vip order
		//		Finishedlist.InsertEnd(e);
		//		Inservicelist.DeleteFirst(); //pick this order from in service list
		//		 //put it in finished list
		//	}if (Inservicelist.getHead()) {
		//		Order* a = Inservicelist.getHead()->getItem();
		//		Finishedlist.InsertEnd(a);
		//		Inservicelist.DeleteFirst();
		//	}if (Inservicelist.getHead()) {

		//		Order* b = Inservicelist.getHead()->getItem();
		//		Finishedlist.InsertEnd(b);
		//		Inservicelist.DeleteFirst();
		//	}


		//	//so that we enter the if second time after 5 time steps when i = 5*x=5*2=10 and so on

		//	this->FillDrawingList();
		//	pGUI->UpdateInterface();
		//	pGUI->ResetDrawingList();
		//	x++;

		//	//so that we enter the if second time after 5 time steps when i = 5*x=5*2=10 and so on
		//}

		//********** BEGIN NEW ORDER HANDLING CODE FOR PHASE 2 **********
		// ezayoko ya shabab
		// ana amer
		//ele hy7sl kalaaty
		//hn4oof el list of orders bta3ty fadya wla l2
		//b3den a5tar el cook el monaseb
		// b3den a3ml el cook ele e5tarto -> serveOrder()
		//tabe3ey y3ny el cook hayotbo5
		// w b3den n7ot el order fel in service list zy ma ben4of fel mata3em el 3adeya
		// w b3den n4eel el order mn el queue of order
		// ay so2al kalemony messenger aw whatsapp y3ny
		// el mfrood lw 5adto copy w paste mn el functions de
		// w 3adelto feha 7aba el mfrood tb2o 5alasto goz2 el order handling
		
		// BUG WORKAROUND!!
		

		cooksHealthEmergencyProblems();//hamzawy
		Node<Cook*>* c = CooksInService.getHead();
		while (c) {
			Cook* p = c->getItem();
			//if (p->isHurt()) {
			if (p->getCd() == TS) {
				if (p->isHurt()) {
					p->setHurt(false);
					p->returnspeedtonormal();
				}//Cook*f=p;
				//p=c->getNext()->getItem();
				c = c->getNext();
				CooksInService.DeleteNode(p);
			}
			else {
				c = c->getNext();
			}
		}


		adjustCookCooldown(); // at the end--->beggining of each timestep this function makes sure that every cook
		// returns to work when his cooldown ends (remember to add breaks and injuries too)
		//(hamzawy changed the place of this because of the logic)	//		Then Omar AbdelGhani Changed it
		//Should be in the beginning of the time step instead of end to be available to use
		// enama meen ele 3amal el function b2a? : Amer

		checkVIPtoUrgent(); //Omar AbdelGhani Changed Place
		//Also should be in the beginning of time step
		// then amer put it back right where it belongs


		Order* finishedOrder = nullptr;
		Node<Cook*>* travVIP = VIPcook.getHead();
		while (travVIP) {
			// make the vip cooks check if thier orders are finished or not
			if (travVIP->getItem()->checkOrder(TS, finishedOrder)) {
				if (finishedOrder) {
					Finishedlist.InsertBeg(finishedOrder);
					Inservicelist.DeleteNode(finishedOrder);
					OutputOrder(finishedOrder);
					//ServiceTime += ((finishedOrder->Get_finishtime()) - (finishedOrder->Get_servetime()));//added by hamzawy
				}
			}
			travVIP = travVIP->getNext();
		}
		Order* finishedOrderNormal = nullptr;
		Node<Cook*>* travNorm = NORMALcook.getHead();
		while (travNorm) {
			// make the normal cooks check if thier orders are finished or not
			if (travNorm->getItem()->checkOrder(TS, finishedOrderNormal)) {
				if (finishedOrderNormal) {
					Finishedlist.InsertBeg(finishedOrderNormal);
					Inservicelist.DeleteNode(finishedOrderNormal);
					OutputOrder(finishedOrderNormal);
					//ServiceTime += ((finishedOrderNormal->Get_finishtime()) - (finishedOrderNormal->Get_servetime()));//added by samy
				}
			}
			travNorm = travNorm->getNext();
		}
		Order* finishedOrdervegan = nullptr;//from here hamzawy
		Node<Cook*>* c1 = VEGANcook.getHead();
		while (c1) {
			// make the vegan cooks check if thier orders are finished or not
			if (c1->getItem()->checkOrder(TS, finishedOrdervegan)) {
				if (finishedOrdervegan) {
					Finishedlist.InsertBeg(finishedOrdervegan);
					Inservicelist.DeleteNode(finishedOrdervegan);
					OutputOrder(finishedOrdervegan);
					//ServiceTime += ((finishedOrdervegan->Get_finishtime()) - (finishedOrdervegan->Get_servetime()));
				}
			}
			c1 = c1->getNext();
		}//to here
		adjustBreak();
		//	checkVIPtoUrgent();
		while (!VIPorder.isEmpty()) {
			Cook* assigned = nullptr; // using nullptr as a flag later on in the code , nullptr here means no cook available
			Order* currentOrder = VIPorder.getPtrToFront()->getItem();
			if (currentOrder->getUrgency()) {
				if (getFirstAvailableCook(TYPE_VIP)) {         //order service criteria, vip orders must be served
					assigned = getFirstAvailableCook(TYPE_VIP);//with any available cook, we choose the cook in this
															   // code snippet.
				}
				else if (getFirstAvailableCook(TYPE_NRM)) {
					assigned = getFirstAvailableCook(TYPE_NRM);

				}
				else if (getFirstAvailableCook(TYPE_VGAN)) {
					assigned = getFirstAvailableCook(TYPE_VGAN);

				}
				else if (getFirstCookBreak()) {
					assigned = getFirstCookBreak();
				}
				else if (getFirstCookInj()) {
					assigned = getFirstCookInj();
				}
			}
			else { // if the order isnt urgent
				if (getFirstAvailableCook(TYPE_VIP)) {         //order service criteria, vip orders must be served
					assigned = getFirstAvailableCook(TYPE_VIP);//with any available cook, we choose the cook in this
															   // code snippet.
				}
				else if (getFirstAvailableCook(TYPE_NRM)) {
					assigned = getFirstAvailableCook(TYPE_NRM);

				}
				else if (getFirstAvailableCook(TYPE_VGAN)) {
					assigned = getFirstAvailableCook(TYPE_VGAN);

				}
			}
			if (assigned && currentOrder->getStatus() == WAIT && !assigned->getpreparing()) { //cook the order if a cook is available
				CooksInService.InsertEnd(assigned);//added by hamzawy because i will use it in cooks health
				assigned->serveOrder(currentOrder, TS);


				Inservicelist.InsertEnd(currentOrder);
				CurServVIP++;
				VIPorder.dequeue(currentOrder);
				//WaitingTime += ((currentOrder->Get_servetime()) - (currentOrder->Get_Arrtime()));//added by hamzawy
			}
			else {
				break;
			}
		}
		// ahmed sami
		while (!normalorder.isEmpty())
		{
			Cook* assigned = nullptr; // using nullptr as a flag later on in the code , nullptr here means no cook available
			if (getFirstAvailableCook(TYPE_NRM)) {  //order service criteria, vip orders must be served
													//with any available cook, we choose the cook in this
													// code snippet.
				assigned = getFirstAvailableCook(TYPE_NRM);
			}
			else {
				assigned = getFirstAvailableCook(TYPE_VIP);
			}

			Order* currentOrder = normalorder.getPtrToFront()->getItem();
			if (assigned && currentOrder->getStatus() == WAIT && !assigned->getpreparing()) { //cook the order if a cook is available
				CooksInService.InsertEnd(assigned);//added by hamzawy
				assigned->serveOrder(currentOrder, TS);

				Inservicelist.InsertEnd(currentOrder);
				CurServNormal++;
				normalorder.dequeue(currentOrder);
				//	WaitingTime += ((currentOrder->Get_servetime()) - (currentOrder->Get_Arrtime()));
				//NoNormal++;
			}
			else {
				break;
			}

		}
		checkNormaltoVIP();
		while (!VEGANOrder.isEmpty()) {//from here hamzawy
			Order* currentOrder = VEGANOrder.getPtrToFront()->getItem();
			Cook* assigned = nullptr; // using nullptr as a flag later on in the code , nullptr here means no cook available

			if (getFirstAvailableCook(TYPE_VGAN)) {
				assigned = getFirstAvailableCook(TYPE_VGAN);

			}


			if (assigned && currentOrder->getStatus() == WAIT && !assigned->getpreparing()) { //cook the order if a cook is available
				CooksInService.InsertEnd(assigned);
				assigned->serveOrder(currentOrder, TS);

				Inservicelist.InsertEnd(currentOrder);
				CurServVegan++;
				VEGANOrder.dequeue(currentOrder);
				//	WaitingTime += ((currentOrder->Get_servetime()) - (currentOrder->Get_Arrtime()));
				//NoVegan++;
			}
			else {
				break;
			}
		}//to here






		//adjustCookCooldown(); // at the end of each timestep this function makes sure that every cook
							  // returns to work when his cooldown ends (remember to add breaks and injuries too)
		//std::cout << "Cook cooldown adjusted" << endl;




		//pGUI->waitForClick();
		std::cout << "*****TIMESTEP " << TS << " END*******" << endl << endl;
		// increment time
		int Anormal, Avegan, Avip;   //Available Normal,Vegan, and VIP

		switch (mode) {
		case MODE_INTR:
			this->FillDrawingList();
			pGUI->UpdateInterface();
			pGUI->ResetDrawingList();
			//An is Available normal
			getAvailableCooksNo(Avip, Avegan, Anormal);
			n = to_string(long double(this->WaitNormal()));
			ve = to_string(long double(this->WaitVegan()));
			v = to_string(long double(this->WaitVIP()));
			ts = to_string((long double(TS)));
			Nn = to_string(long double(Anormal));
			Nv = to_string(long double(Avip));
			Ng = to_string(long double((Avegan)));
			pGUI->PrintMessage("Ts: " + to_string(TS)); //here you should also print i (timestep)
			pGUI->PrintMessage("No. of Available Normal Cooks: " + to_string(Anormal), 670);
			pGUI->PrintMessage("No. of Available Vegan Cooks: " + to_string(Avegan), 690);
			pGUI->PrintMessage("No. of Available VIP Cooks: " + to_string(Avip), 710);
			pGUI->PrintMessage("No of Waiting Normal Orders: " + to_string(WaitNormal())+"     No of Serving Normal Orders till now: "+to_string(CurServNormal), 730);
			pGUI->PrintMessage("No of Waiting Vegan Orders: " + to_string(WaitVegan())+"     No of Serving Vegan Orders till now: "+to_string(CurServVegan), 750);
			pGUI->PrintMessage("No of Waiting VIP Orders: " + to_string(WaitVIP())+"     No of Serving VIP Orders till now: "+to_string(CurServVIP), 770);
			pGUI->waitForClick();
			TS++;
			break;
		case MODE_STEP:
			this->FillDrawingList();
			pGUI->UpdateInterface();
			pGUI->ResetDrawingList();

			getAvailableCooksNo(Avip, Avegan, Anormal);
			//this->FillDrawingList();
			//pGUI->UpdateInterface();
			//pGUI->ResetDrawingList();
			n = to_string(long double(this->WaitNormal()));
			ve = to_string(long double(this->WaitVegan()));
			v = to_string(long double(this->WaitVIP()));
			ts = to_string((long double(TS)));
			Nn = to_string(long double(Anormal));
			Nv = to_string(long double(Avip));
			Ng = to_string(long double((Avegan)));
			pGUI->PrintMessage("Ts: " + to_string(TS)); //here you should also print i (timestep)
			pGUI->PrintMessage("No. of Available Normal Cooks: " + to_string(Anormal), 670);
			pGUI->PrintMessage("No. of Available Vegan Cooks: " + to_string(Avegan), 690);
			pGUI->PrintMessage("No. of Available VIP Cooks: " + to_string(Avip), 710);
			pGUI->PrintMessage("No of Waiting Normal Orders: " + to_string(WaitNormal())+"     No of Serving Normal Orders till now: "+to_string(CurServNormal), 730);
			pGUI->PrintMessage("No of Waiting Vegan Orders: " + to_string(WaitVegan())+"     No of Serving Vegan Orders till now: "+to_string(CurServVegan), 750);
			pGUI->PrintMessage("No of Waiting VIP Orders: " + to_string(WaitVIP())+"     No of Serving VIP Orders till now: "+to_string(CurServVIP), 770);
			Sleep(1000);
			TS++;
			break;
		case MODE_SLNT:
			TS++;
			break;
		case MODE_DEMO:
			Just_A_Demo();

		};
	}
	//this->FillDrawingList();
	//pGUI->UpdateInterface();
	//pGUI->ResetDrawingList();
	if (mode == MODE_INTR)
		pGUI->PrintMessage("Finished,click to continue");
	else if (mode == MODE_STEP) {
		pGUI->PrintMessage("Finished,program will now exit");

		Sleep(1000);
	}
	//AMER: Uncomment when ready
	Ofile << "Orders: " << NoNormal + NoVegan + NoVIP << "[Norm:" << NoNormal << ", Veg:" << NoVegan << ", VIP:" << NoVIP << "]" << endl;
	Ofile << "cooks:" << V + N + G << "[Norm:" << N << ", Veg:" << G << ", VIP:" << V << ",  injured:" << NoInj << "]" << endl;
	if((NoNormal + NoVegan + NoVIP)!=0)
	Ofile << "Avg Wait = " << WaitingTime / (NoNormal + NoVegan + NoVIP) << ",  Avg Serv = " << ServiceTime / (NoNormal + NoVegan + NoVIP) << endl;
	else
		Ofile << "Avg Wait =  0 ,  Avg Serv = 0"<<endl;
	if(NoNormal!=0)
	Ofile << "Urgent orders: " << NoUrgent << ",   Auto-promoted: " << (NoAutoPromoted / (NoNormal + NoVegan + NoVIP)) * 100 << "%" << endl;
	else
		Ofile << "Urgent orders: " << NoUrgent << ",   Auto-promoted: 0%" << endl;
}



//////////////////////////////////  Event handling functions   /////////////////////////////

//Executes ALL events that should take place at current timestep
void Restaurant::ExecuteEvents(int CurrentTimeStep)
{
	Event* pE;
	while (EventsQueue.peekFront(pE))	//as long as there are more events
	{
		if (pE->getEventTime() > CurrentTimeStep)	//no more events at current timestep
			return;

		pE->Execute(this);
		EventsQueue.dequeue(pE);	//remove event from the queue
		delete pE;		//deallocate event object from memory
	}

}


Restaurant::~Restaurant()
{
	if (pGUI)
		delete pGUI;
}

void Restaurant::FillDrawingList()
{
	int v = 0;// to count the number of waiting  vip orders
	int ve = 0;// to count the number of waiting  vegan orders
	int n = 0;// to count the number of waiting  normal orders
	int z;
	int x;
	int y;
	int h;
	int w;

	if (!VIPorder.isEmpty()) {
		x = VIPorder.getPtrToFront()->getItem()->GetID();
		do {// this 4 while loops to add all orders to the drawing list

			pGUI->AddToDrawingList(VIPorder.getPtrToFront()->getItem());
			Order* r = VIPorder.getPtrToFront()->getItem();
			VIPorder.enqueueNoPriority(r);
			VIPorder.dequeue(r);
			v++; //here you should print v
		} while (!(VIPorder.isEmpty()) && !(x == VIPorder.getPtrToFront()->getItem()->GetID()));
	}
	if (!VEGANOrder.isEmpty()) {
		y = VEGANOrder.getPtrToFront()->getItem()->GetID();
		do {
			pGUI->AddToDrawingList(VEGANOrder.getPtrToFront()->getItem());
			Order* r = VEGANOrder.getPtrToFront()->getItem();
			VEGANOrder.enqueue(r);
			VEGANOrder.dequeue(r);
			ve++;//here you should print ve
		} while (!(VEGANOrder.isEmpty()) && !(y == VEGANOrder.getPtrToFront()->getItem()->GetID()));
	}

	if (!normalorder.isEmpty()) {
		z = normalorder.getPtrToFront()->getItem()->GetID();
		do {
			//	pGUI->AddToDrawingList(normalorder.getPtrToFront()->getItem());
			Order* r = normalorder.getPtrToFront()->getItem();
			Order r1 = *r;
			normalorder.enqueue(r);
			normalorder.dequeue(r);
			pGUI->AddToDrawingList(&r1);
			n++;//here you should print n
		} while (!(normalorder.isEmpty()) && !(z == normalorder.getPtrToFront()->getItem()->GetID()));
	}
	//if(Inservicelist.getHead())
	if (Inservicelist.getHead()) {
		h = Inservicelist.getHead()->getItem()->GetID();
		do {
			Inservicelist.getHead()->getItem()->setStatus(SRV);
			pGUI->AddToDrawingList(Inservicelist.getHead()->getItem());
			Order* r = Inservicelist.getHead()->getItem();
			Inservicelist.InsertEnd(r);
			Inservicelist.DeleteFirst();

		} while (!(h == Inservicelist.getHead()->getItem()->GetID()));
	}
	if (Finishedlist.getHead()) {
		w = Finishedlist.getHead()->getItem()->GetID();
		do {
			Finishedlist.getHead()->getItem()->setStatus(DONE);
			pGUI->AddToDrawingList(Finishedlist.getHead()->getItem());
			Order* r = Finishedlist.getHead()->getItem();
			Finishedlist.InsertEnd(r);
			Finishedlist.DeleteFirst();

		} while (!(w == Finishedlist.getHead()->getItem()->GetID()));
	}
	/*
	while (Finishedlist.DeleteNode(Finishedlist.getHead()->getItem())) {
		Finishedlist.getHead()->getItem()->setStatus(DONE);
		pGUI->AddToDrawingList(Finishedlist.getHead()->getItem());
	}
	*/
	//This function should be implemented in phase1
//It should add ALL orders and Cooks to the drawing list
//It should get orders from orders lists/queues/stacks/whatever (same for Cooks)
//To add orders it should call function  void GUI::AddToDrawingList(Order* pOrd);
//To add Cooks it should call function  void GUI::AddToDrawingList(Cook* pCc);
	int first;
	int current;
	Cook* curr;
	first = NORMALcook.getHead()->getItem()->GetID();

	if (NORMALcook.getHead()) {           //to make sure list isnot empty
		do {
			curr = NORMALcook.getHead()->getItem();
			if (curr->getStatus())
				pGUI->AddToDrawingList(curr);
			NORMALcook.InsertEnd(curr);
			NORMALcook.DeleteFirst();
			curr = NORMALcook.getHead()->getItem();
			current = curr->GetID();
		} while (first != current);
	}

	if (VEGANcook.getHead()) {
		first = VEGANcook.getHead()->getItem()->GetID();
		do {
			curr = VEGANcook.getHead()->getItem();
			if (curr->getStatus())
				pGUI->AddToDrawingList(curr);
			VEGANcook.InsertEnd(curr);
			VEGANcook.DeleteFirst();
			curr = VEGANcook.getHead()->getItem();
			current = curr->GetID();
		} while (first != current);
	}

	if (VIPcook.getHead()) {
		first = VIPcook.getHead()->getItem()->GetID();
		do {
			curr = VIPcook.getHead()->getItem();
			if (curr->getStatus())
				pGUI->AddToDrawingList(curr);
			VIPcook.InsertEnd(curr);
			VIPcook.DeleteFirst();
			curr = VIPcook.getHead()->getItem();
			current = curr->GetID();
		} while (first != current);

	}


}




//////////////////////////////////////////////////////////////////////////////////////////////
/// ==> 
///  DEMO-related functions. Should be removed in phases 1&2

//Begin of DEMO-related functions



void Restaurant::AddEvents(Event* ev)
{
	EventsQueue.enqueue(ev);
}

void Restaurant::AddToVeganQueue(Order* po)
{
	VEGANOrder.enqueue(po);
}

void Restaurant::AddNormalToQueue(Order* po)
{
	normalorder.enqueue(po);
}

void Restaurant::AddToVIPArray(Order* ord)
{

	VIPorder.enqueue(ord, ord->GetPriority());
	//setNoVIP(getNoVIP() + 1);
//	VIPorder.reQueue();
}

ORD_TYPE Restaurant::Getordertype(char ordtype)
{
	if (ordtype == 'V')
		return TYPE_VIP;
	else if (ordtype == 'N')
		return TYPE_NRM;
	else if (ordtype == 'G')
		return TYPE_VGAN;

}

void Restaurant::CancelNormal(int id)
{
	// lsa cancel of order 
}

//This is just a demo function for project introductory phase
//It should be removed starting phase 1
void Restaurant::Just_A_Demo()
{

	//
	// THIS IS JUST A DEMO FUNCTION
	// IT SHOULD BE REMOVED IN PHASE 1 AND PHASE 2

	int EventCnt;
	Order* pOrd;
	Event* pEv;
	srand(time(NULL));

	pGUI->PrintMessage("Just a Demo. Enter EVENTS Count(next phases should read I/P filename):");
	EventCnt = atoi(pGUI->GetString().c_str());	//get user input as a string then convert to integer

	pGUI->PrintMessage("Generating Events randomly... In next phases, Events should be loaded from a file...CLICK to continue");
	pGUI->waitForClick();

	//Just for sake of demo, generate some cooks and add them to the drawing list
	//In next phases, Cooks info should be loaded from input file
	int C_count = 12;
	Cook* pC = new Cook[C_count];
	int cID = 1;

	for (int i = 0; i < C_count; i++)
	{
		cID += (rand() % 15 + 1);
		pC[i].setID(cID);
		pC[i].setType((ORD_TYPE)(rand() % TYPE_CNT));
	}


	int EvTime = 0;

	int O_id = 1;

	//Create Random events and fill them into EventsQueue
	//All generated event will be "ArrivalEvents" for the demo
	for (int i = 0; i < EventCnt; i++)
	{
		O_id += (rand() % 4 + 1);
		int OType = rand() % TYPE_CNT;	//Randomize order type		
		EvTime += (rand() % 5 + 1);			//Randomize event time
		pEv = new ArrivalEvent(EvTime, O_id, (ORD_TYPE)OType);
		EventsQueue.enqueue(pEv);

	}

	// --->   In next phases, no random generation is done
	// --->       EventsQueue should be filled from actual events loaded from input file





	//Now We have filled EventsQueue (randomly)
	int CurrentTimeStep = 1;


	//as long as events queue is not empty yet
	while (!EventsQueue.isEmpty())
	{
		//print current timestep
		char timestep[10];
		itoa(CurrentTimeStep, timestep, 10);
		pGUI->PrintMessage(timestep);


		//The next line may add new orders to the DEMO_Queue
		ExecuteEvents(CurrentTimeStep);	//execute all events at current time step


/////////////////////////////////////////////////////////////////////////////////////////
		/// The next code section should be done through function "FillDrawingList()" once you
		/// decide the appropriate list type for Orders and Cooks

		//Let's add ALL randomly generated Cooks to GUI::DrawingList
		for (int i = 0; i < C_count; i++)
			pGUI->AddToDrawingList(&pC[i]);

		//Let's add ALL randomly generated Ordes to GUI::DrawingList
		int size = 0;
		Order** Demo_Orders_Array = DEMO_Queue.toArray(size);

		for (int i = 0; i < size; i++)
		{
			pOrd = Demo_Orders_Array[i];
			pGUI->AddToDrawingList(pOrd);
		}
		/////////////////////////////////////////////////////////////////////////////////////////

		pGUI->UpdateInterface();
		Sleep(1000);
		CurrentTimeStep++;	//advance timestep
		pGUI->ResetDrawingList();
	}

	delete[]pC;


	pGUI->PrintMessage("generation done, click to END program");
	pGUI->waitForClick();


}
////////////////

void Restaurant::AddtoDemoQueue(Order* pOrd)
{
	DEMO_Queue.enqueue(pOrd);
}

/// ==> end of DEMO-related function
//////////////////////////////////////////////////////////////////////////////////////////////



//By OmarAbdelGhani

void Restaurant::LoadFile() {
	string name = pGUI->GetString();
	ifstream IF(name, ios::in);
	//IF.open("djSamy.txt",ios::in);
	if (IF.is_open()) {
		IF >> N; //initialize No. of Normal cooks
		for (int i = 1; i <= N; i++) {
			Cook* c = new Cook;
			c->setType(TYPE_NRM);
			NORMALcook.InsertBeg(c);
			NORMALcook.getHead()->getItem()->setID(i);
		}
		IF >> G; // Same for vegan
		for (int i = 1; i <= G; i++) {
			Cook* c = new Cook;
			c->setType(TYPE_VGAN);
			VEGANcook.InsertBeg(c);
			VEGANcook.getHead()->getItem()->setID(i);
		}
		IF >> V; // and for VIP
		for (int i = 1; i <= V; i++) {
			Cook* c = new Cook;
			c->setType(TYPE_VIP);
			VIPcook.InsertBeg(c);
			VIPcook.getHead()->getItem()->setID(i);
		}

		IF >> SN_min >> SN_max;
		IF >> SG_min >> SG_max;
		IF >> SV_min >> SV_max;
		//Initialization of min and max speed of each type

		IF >> BO; //Initialize No. of orders before break
		IF >> BN_min >> BN_max;
		IF >> BG_min >> BG_max;
		IF >> BV_min >> BV_max;
		//Initialization of min and max BreaktTime of each type

		IF >> InjProb;
		IF >> RstPrd;

		IF >> AutoP; //Initialize NO. of time steps befor auto promotion
		IF >> VIP_WT;


		IF >> M; //Initialize No. of events

		//Looping until i=m to initialize all events
		char Etype; // for the type of event
		int eTime; //time of arrival
		int Id;   //Id of Order
		char Otype; //type of order
		ORD_TYPE T; //type of order in enum format
		int Size; // Size of Order
		double Money; // total money of order
		for (int i = 0; i < M; i++) {
			IF >> Etype;

			if (Etype == 'R') {
				IF >> Otype;
				T = Getordertype(Otype);
				IF >> eTime;
				IF >> Id;
				IF >> Size;
				IF >> Money;
				ArrivalEvent* R = new ArrivalEvent(eTime, Id, Size, Money, T);
				this->AddEvents(R);
			}
			else if (Etype == 'X') {
				IF >> eTime;
				IF >> Id;
				Cancellation_event* X = new Cancellation_event(eTime, Id);
				this->AddEvents(X);
			}
			else if (Etype == 'P') {
				IF >> eTime;
				IF >> Id;
				IF >> Money;
				PromotionEvent* P = new PromotionEvent(eTime, Id, Money);
				this->AddEvents(P);


			}


		}

	}

}

Order* Restaurant::CancelById(int id) {
	Order* O;
	if (normalorder.dequeueWithOrderID(id, O))
		return (O);
	else
		return nullptr;

}
void Restaurant::setNoNormal(int number) {
	if (number < 0) {
		NoNormal = number * -1;
	}
	else {
		NoNormal = number;
	}

}
void Restaurant::setNoVegan(int number) {
	if (number < 0) {
		NoVegan = number * -1;
	}
	else {
		NoVegan = number;
	}

}
void Restaurant::setNoVIP(int number) {
	if (number < 0) {
		NoVIP = number * -1;
	}
	else {
		NoVIP = number;
	}

}
int Restaurant::getNoNormal() {
	return NoNormal;
}
int Restaurant::getNoVegan() {
	return NoVegan;
}
int Restaurant::getNoVIP() {
	return NoVIP;
}

int Restaurant::WaitNormal() {
	if (normalorder.isEmpty())
		return 0;
	int count = 0;
	int first = (normalorder.getPtrToFront()->getItem()->GetID());
	int curr;
	Order* d;
	do {
		normalorder.dequeue(d);
		normalorder.enqueue(d);
		count++;
		curr = (normalorder.getPtrToFront()->getItem()->GetID());
	} while (first != curr);
	return count;
}

int Restaurant::WaitVegan() {
	if (VEGANOrder.isEmpty())
		return 0;
	int count = 0;
	int first = (VEGANOrder.getPtrToFront()->getItem()->GetID());
	int curr;
	Order* d;
	do {
		VEGANOrder.dequeue(d);
		VEGANOrder.enqueue(d);
		count++;
		curr = (VEGANOrder.getPtrToFront()->getItem()->GetID());
	} while (first != curr);
	return count;
}


int Restaurant::WaitVIP() {
	if (VIPorder.isEmpty())
		return 0;
	int count = 0;
	int first = (VIPorder.getPtrToFront()->getItem()->GetID());
	int curr;
	Order* d;
	do {
		VIPorder.dequeue(d);
		VIPorder.enqueueNoPriority(d);
		count++;
		curr = (VIPorder.getPtrToFront()->getItem()->GetID());
	} while (first != curr);
	return count;
}


void  Restaurant::InitializeNormal() {


	//int first = 1;
	Node<Cook*>* curr = NORMALcook.getHead();


	while (curr) {
		Cook* CurrCook = curr->getItem();
		CurrCook->SetBreak(BN_min, BN_max);
		CurrCook->SetSpeed(SN_min, SN_max);
		//NORMALcook.InsertEnd(CurrCook);
		//NORMALcook.DeleteFirst();
		curr = curr->getNext();


	}
}
void Restaurant::InitializeVIP() {

	Node<Cook*>* curr = VIPcook.getHead();
	//Cook* CurrCook = VIPcook.getHead()->getItem();

	while (curr) {
		Cook* CurrCook = curr->getItem();
		CurrCook->SetBreak(BV_min, BV_max);
		CurrCook->SetSpeed(SV_min, SV_max);
		//NORMALcook.InsertEnd(CurrCook);
		//NORMALcook.DeleteFirst();
		curr = curr->getNext();
		//CurrCook=curr->getItem();
	}



}
void Restaurant::InitializeVegan() {

	Node<Cook*>* curr = VEGANcook.getHead();
	//Cook* CurrCook = VEGANcook.getHead()->getItem();

	while (curr) {
		Cook* CurrCook = curr->getItem();
		CurrCook->SetBreak(BG_min, BG_max);
		CurrCook->SetSpeed(SG_min, SG_max);
		//NORMALcook.InsertEnd(CurrCook);
		//NORMALcook.DeleteFirst();
		curr = curr->getNext();
		//CurrCook=curr->getItem();
	}


}
void Restaurant::getAvailableCooksNo(int& VIP, int& vegan, int& normal) { // counts the number of available cooks of each type
	int resultVIP = 0, resultVegan = 0, resultNormal = 0;
	Node<Cook*>* trav = VIPcook.getHead(); // start by counting the available vip cooks
	while (trav) {
		if (trav->getItem()->getStatus() == true) {
			resultVIP++;
		}
		trav = trav->getNext();
	}
	trav = VEGANcook.getHead(); // then the function counts the available vegan cooks
	while (trav) {
		if (trav->getItem()->getStatus() == true) {
			resultVegan++;
		}
		trav = trav->getNext();
	}
	trav = NORMALcook.getHead(); // then finally we count the available normal cooks
	while (trav) {
		if (trav->getItem()->getStatus() == true) {
			resultNormal++;
		}
		trav = trav->getNext();
	}
	// and then we set the values
	VIP = resultVIP;
	vegan = resultVegan;
	normal = resultNormal;

}
Cook* Restaurant::getFirstAvailableCook(ORD_TYPE orderType) {
	if (orderType == TYPE_VIP) {
		Node<Cook*>* readyCook = VIPcook.getHead();
		while (readyCook) {
			if (readyCook->getItem()->getStatus() && !readyCook->getItem()->isBreak() && !readyCook->getItem()->isBreak() && !readyCook->getItem()->getpreparing())
				return readyCook->getItem();
			readyCook = readyCook->getNext();
		}
	}
	else if (orderType == TYPE_VGAN) {
		Node<Cook*>* readyCook = VEGANcook.getHead();
		while (readyCook) {
			if (readyCook->getItem()->getStatus() && !readyCook->getItem()->isBreak() && !readyCook->getItem()->isBreak() && !readyCook->getItem()->getpreparing())
				return readyCook->getItem();
			readyCook = readyCook->getNext();
		}
	}
	else {
		Node<Cook*>* readyCook = NORMALcook.getHead();
		while (readyCook) {
			if (readyCook->getItem()->getStatus() && !readyCook->getItem()->isBreak() && !readyCook->getItem()->isBreak() && !readyCook->getItem()->getpreparing())
				return readyCook->getItem();
			readyCook = readyCook->getNext();
		}
	}
	return nullptr;
}
Cook* Restaurant::getFirstCookBreak() {
	//this function returns the first cook that is on a break
	Node<Cook*>* breakCook = VIPcook.getHead();
	while (breakCook) {
		if (breakCook->getItem()->isBreak() && breakCook->getItem()->getpreparing() == nullptr && !breakCook->getItem()->isHurt())
			return breakCook->getItem();
		breakCook = breakCook->getNext();
	}
	if (!breakCook) { // if there isn't a VIP cook on a break , look for a normal cook on a break
		breakCook = NORMALcook.getHead();
		while (breakCook) {
			if (breakCook->getItem()->isBreak() && breakCook->getItem()->getpreparing() == nullptr && !breakCook->getItem()->isHurt())
				return breakCook->getItem();
			breakCook = breakCook->getNext();
		}

	}
	if (!breakCook) { // if there isn't a VIP cook on a break , look for a normal cook on a break
		breakCook = VEGANcook.getHead();
		while (breakCook) {
			if (breakCook->getItem()->isBreak() && breakCook->getItem()->getpreparing() == nullptr && !breakCook->getItem()->isHurt())
				return breakCook->getItem();
			breakCook = breakCook->getNext();
		}

	}
	if (!breakCook) {
		return nullptr;
	}
	else {
		return breakCook->getItem();
	}


}
Cook* Restaurant::getFirstCookInj() {
	//this function returns the first cook that is injured
	Node<Cook*>* breakCook = VIPcook.getHead();
	while (breakCook) {
		if (breakCook->getItem()->isHurt() && !breakCook->getItem()->getpreparing()) {
			return breakCook->getItem();
		}
		breakCook = breakCook->getNext();
	}
	if (!breakCook) {
		breakCook = NORMALcook.getHead();
		while (breakCook) {
			if (breakCook->getItem()->isHurt() && !breakCook->getItem()->getpreparing()) {
				return breakCook->getItem();
			}
			breakCook = breakCook->getNext();
		}

	}
	if (!breakCook) {
		breakCook = VEGANcook.getHead();
		while (breakCook) {
			if (breakCook->getItem()->isHurt() && !breakCook->getItem()->getpreparing()) {
				return breakCook->getItem();
			}
			breakCook = breakCook->getNext();
		}

	}
	if (!breakCook) {
		return nullptr;
	}
	else {
		return breakCook->getItem();
	}
}

void Restaurant::adjustCookCooldown() {
	Node<Cook*>* travVIP = VIPcook.getHead();
	while (travVIP) {
		//if(travVIP->getItem()->getpreparing()){
			//if(travVIP->getItem()->getpreparing()->Get_finishtime()==TS){//hamzawy
		travVIP->getItem()->checkCd(TS);
		//}
		//}
		travVIP = travVIP->getNext();

	}
	Node<Cook*>* travVGAN = VEGANcook.getHead();
	while (travVGAN) {
		//if(travVGAN->getItem()->getpreparing()){
			//if(travVGAN->getItem()->getpreparing()->Get_finishtime()==TS){//hamzawy
		travVGAN->getItem()->checkCd(TS);
		//}
		//}
		travVGAN = travVGAN->getNext();

	}
	Node<Cook*>* travNRM = NORMALcook.getHead();
	while (travNRM) {
		//if(travNRM->getItem()->getpreparing()){
			//if(travNRM->getItem()->getpreparing()->Get_finishtime()==TS){//hamzawy
		travNRM->getItem()->checkCd(TS);
		//}
		//}
		travNRM = travNRM->getNext();
	}

}
void Restaurant::checkVIPtoUrgent() {
	rNode<Order*>* trav = VIPorder.getPtrToFront();
	if (!trav) {
		return;
	}
	while (trav) {
		if ((TS - trav->getItem()->getPromTime() >= VIP_WT || (TS - trav->getItem()->Get_Arrtime() >= VIP_WT && trav->getItem()->getPromTime() == INT_MAX)) && !trav->getItem()->getUrgency()) {
			/* old condition :
			(TS - (trav->getItem()->getPromTime()) >= VIP_WT || (TS - (trav->getItem()->Get_Arrtime()) >= VIP_WT)) && !trav->getItem()->getUrgency()
			*/
			trav->getItem()->setUrgency(true);
			if (trav->getItem()->getPromTime() != INT_MAX) {
				trav->getItem()->setPriority(INT_MAX - trav->getItem()->getPromTime());
				trav->setPriority(INT_MAX - trav->getItem()->getPromTime());
			}
			else {
				trav->getItem()->setPriority(INT_MAX - trav->getItem()->Get_Arrtime());
				trav->setPriority(INT_MAX - trav->getItem()->Get_Arrtime());
			}

			trav->getItem()->Set_ORD_Type(TYPE_URG); // to change color
			cout << "Order with id " << trav->getItem()->GetID() << " is now urgent" << endl;
			VIPorder.reQueue();
			trav = VIPorder.getPtrToFront();
			NoUrgent++;


		}
		trav = trav->getNext();
	}
}
void Restaurant::checkNormaltoVIP() {
	Node<Order*>* trav = normalorder.getPtrToFront();
	if (!trav) {
		return;
	}
	while (trav) {
		if ((TS - (trav->getItem()->Get_Arrtime()) >= AutoP) && trav->getItem()->getPromTime() == INT_MAX)
		{
			Order* currentOrder = trav->getItem();
			trav = trav->getNext();
			currentOrder->Set_ORD_Type(TYPE_VIP);
			currentOrder->setPromTime(TS);
			currentOrder->calc_priority();
			normalorder.dequeue(currentOrder);
			VIPorder.enqueue(currentOrder, currentOrder->GetPriority());
			//AddToVIPArray(currentOrder);
			NoAutoPromoted++;
		}
		else

			trav = trav->getNext();
	}
}
void Restaurant::adjustBreak() {
	Node<Cook*>* trav = VIPcook.getHead();
	while (trav && trav->getItem()->getStatus() && !trav->getItem()->isBreak() && !trav->getItem()->isHurt() && !trav->getItem()->getpreparing()) {
		if (trav->getItem()->getOrdersServed() == BO && trav->getItem()->getOrdersServed() != 0) {
			trav->getItem()->goOnAbreak(TS);
			trav->getItem()->setOrdersServed(0);
		}
		trav = trav->getNext();
	}
	trav = NORMALcook.getHead();
	while (trav && trav->getItem()->getStatus() && !trav->getItem()->isBreak() && !trav->getItem()->isHurt() && !trav->getItem()->getpreparing()) {
		if (trav->getItem()->getOrdersServed() % BO == 0 && trav->getItem()->getOrdersServed() != 0) {
			trav->getItem()->goOnAbreak(TS);
			trav->getItem()->setOrdersServed(0);
		}
		trav = trav->getNext();
	}
	trav = VEGANcook.getHead();
	while (trav && trav->getItem()->getStatus() && !trav->getItem()->isBreak() && !trav->getItem()->isHurt() && !trav->getItem()->getpreparing()) {
		if (trav->getItem()->getOrdersServed() % BO == 0 && trav->getItem()->getOrdersServed() != 0) {
			trav->getItem()->goOnAbreak(TS);
			trav->getItem()->setOrdersServed(0);
		}
		trav = trav->getNext();
	}
}

void Restaurant::OutputOrder(Order* O) {
	Ofile << O->Get_finishtime() << "\t" << O->GetID() << "\t" << O->Get_Arrtime() << "\t" << O->Get_servetime() - O->Get_Arrtime() << "\t" << O->Get_finishtime() - O->Get_servetime() << endl;
	WaitingTime += O->Get_servetime() - O->Get_Arrtime();
	ServiceTime += O->Get_finishtime() - O->Get_servetime();
}
void Restaurant::cooksHealthEmergencyProblems() {

	Node<Cook*>* c = CooksInService.getHead();//get first
	int x = 0;
	if (!c) {
		return;
	}


	//busy cook and if R<or=ingprob then make this cook injured by decreasing its speed to half and make him rest for a rest period
	srand(time(0));
	float R = ((rand() % 100));
	R = R / 100;
	while (x == 0 && c) {
		Cook* q = c->getItem();

		if ((R <= InjProb) && (!q->isHurt())) {
			if ((q->getpreparing()->Get_finishtime() != TS)) {
				q->setHurt(true);
				NoInj++;
				q->decreasespeedtohalf();
				if (q->getpreparing()) {
					q->getpreparing()->Set_finishTime(TS + (q->getpreparing()->Get_finishtime() - TS) * 2);
					q->setCd(q->getpreparing()->Get_finishtime() + RstPrd);
				}

				cout << "cook with id " << q->GetID() << " of type " << q->GetType() << " got injured " << " and will come back at timestep " << q->getpreparing()->Get_finishtime() + RstPrd << endl;
				x++;
			}

			/*if (q->getpreparing()->Get_finishtime()==TS) {
				q->setCd(RstPrd + TS);
			}*/

		}

		c = c->getNext();
	}
}


Cook* Restaurant::getFirstveganCookinBreak() {
	Node<Cook*>* breakCook = VEGANcook.getHead();
	while (breakCook && breakCook->getItem()->isBreak() == false) {
		breakCook = breakCook->getNext();
	}
	if (!breakCook) {
		return nullptr;
	}
	else {
		return breakCook->getItem();
	}
}
Cook* Restaurant::getFirstveganCookInj() {
	Node<Cook*>* breakCook = VEGANcook.getHead();
	while (breakCook && breakCook->getItem()->isHurt() == false) {
		breakCook = breakCook->getNext();
	}
	if (!breakCook) {
		return nullptr;
	}
	else {
		return breakCook->getItem();
	}
}

