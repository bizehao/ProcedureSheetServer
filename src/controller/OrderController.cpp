#include "OrderController.h"

void OrderController::exec() {

#define CLASS_TYPE OrderController
	APPEND_REQUEST(SV("/order/submit_order", HttpPost, submitOrder))
}

std::string OrderController::submitOrder() {
	return "submit_order";
}
