#pragma once

#include "cocos2d.h"
#include "Definitions.h"

USING_NS_CC;
using namespace std;

namespace Utility {
	class UI {
	public:
		static	Vec2 getScreenCenter();
		static void addCenterBackgroundToScene(string filePath, Scene* scene);
		static void addCenterBackgroundToLayer(string filePath, Layer* layer);
	};

	class CCUtility {
	public:
		static Animation* createAnimation(string frameName, int frameCount, float delay, int loop = 1);
		static Animation* createAnimation(string frameName, float delay, int loop = 1);
		static Animate* getAnimate(string animateName, int frameCount, float delay, int loop = 1);
		static Animate* getAnimate(string animateName, float delay, int loop = 1);
		static Animate* getAnimate(string animateName);
		static Action* createActionReverse(Animate* animate, bool repeatForever = true);
		static Action* getAction(Animate* animate1, Animate* animate2, bool repeatForever = true);
		static float changingAngleAccordingToCoordinateSystem(float calculatedAngle);
		static void setDir(Vec2 dirMove, Vec2& dir);
		static bool checkTile(Vec2 position, std::string layerName, std::string property);
		static Vec2 positionToIndex(Vec2 position);
	};

}