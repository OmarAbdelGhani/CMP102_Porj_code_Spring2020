#include "PromotionEvent.h"
#include "../Restaurant/Rest/Restaurant.h"

PromotionEvent::PromotionEvent(int eventTime, int ID, double m) :Event(eventTime, ID) {
	MoneyPaid = m;
}
void PromotionEvent::Execute(Restaurant* r) {
	Order* O = r->CancelById(OrderID);
	if (O) {
		O->calc_priority();
		r->AddToVIPArray(O);
		O->Set_ORD_Type(TYPE_VIP);
		O->setPromTime(EventTime);
		cout << "Order with id " << OrderID << " has been promoted to VIP" << endl;
	}
}

PromotionEvent::~PromotionEvent(void)
{
}
double PromotionEvent::GetMoneyPaid() {
	return MoneyPaid;
}