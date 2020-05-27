//#include "Drawing.h"
#include "Rest\Restaurant.h"
#include "GUI\GUI.h"
#include"Generic_DS\priorityQueue.h"
int main()
{

	Restaurant* pRest = new Restaurant;
	pRest->RunSimulation();

	delete pRest;

	return 0;
	//	priorityQueue<int> help;
	//	help.enqueue(0, 4);
	//	help.enqueue(1, 5);
	//	help.enqueue(2, 4);
	//	help.printQueueData();
}
