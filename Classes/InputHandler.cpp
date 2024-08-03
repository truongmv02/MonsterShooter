#include "InputHandler.h"
InputHandler* InputHandler::instance = NULL;
InputHandler::InputHandler() {

}

InputHandler* InputHandler::getInstance() {
	if (instance == NULL) {
		instance = new InputHandler();
	}
	return instance;
}
void InputHandler::onMouseDown(EventMouse* event) {
	auto mouseBtn = (int)event->getMouseButton();
	mouseButton[mouseBtn] = true;
	this->mouseLocation = event->getLocation();
}

void InputHandler::onMouseMove(EventMouse* event) {
	this->mouseLocation = event->getLocation();
}

void InputHandler::onMouseUp(EventMouse* event) {
	auto mouseBtn = (int)event->getMouseButton();
	mouseButton[mouseBtn] = false;
	this->mouseLocation = event->getLocation();
}