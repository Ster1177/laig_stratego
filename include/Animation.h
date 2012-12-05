/*
 * Animation.h
 *
 *  Created on: Nov 7, 2012
 *      Author: ster
 */

#ifndef ANIMATION_H_
#define ANIMATION_H_
#include <GL/glui.h>
#include <GL/glut.h>
#include <math.h>
#include <cmath>
#include "GraphNode.h"

using namespace std;

class Animation {
protected:
	float xi,yi,zi;
	float xf,yf,zf;
public:
	float xyzi[2];
	float xyzf[2];
	GraphNode* node;
	long span;
	bool end;
	long time;
	Animation(GraphNode*, long);
	virtual void CenterObject();
	virtual void myInitTransforms(unsigned int mili_secs);
	virtual void myUpdateTransforms();
	virtual void myObjectTransforms();
	virtual void Reset();
	virtual void updateTime(long _time);
	virtual ~Animation();
};

#endif /* ANIMATION_H_ */
