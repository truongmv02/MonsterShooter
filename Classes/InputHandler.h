#pragma once
#include "cocos2d.h"
#include "Definitions.h"

USING_NS_CC;



class InputHandler
{
public:
	enum MouseButton {
		BUTTON_LEFT = 0,
		BUTTON_RIGHT = 1,
		BUTTON_MIDDLE = 2,
	};
	static InputHandler* getInstance();
	inline	void onKeyDown(int key) { keys[key] = true; }
	inline void onKeyUp(int key) { keys[key] = false; }
	inline	bool isKeyPress(int key) { return keys[key]; }
	inline bool isMouseDown(MouseButton mouseBtn) { return mouseButton[int(mouseBtn)]; }
	inline Vec2 getMouseLocation() { return mouseLocation; }
	void onMouseDown(EventMouse* event);
	void onMouseMove(EventMouse* event);
	void onMouseUp(EventMouse* event);
private:
	static	InputHandler* instance;
	InputHandler();
	bool keys[165] = { 0 };
	bool mouseButton[3] = { 0 };
	EventMouse* eventMouse = nullptr;
	Vec2 mouseLocation;
};


