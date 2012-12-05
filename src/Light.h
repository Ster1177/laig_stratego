/*
 * Light.h
 *
 *  Created on: Oct 13, 2012
 *      Author: ciberwizz
 */

#ifndef LIGHT_H_
#define LIGHT_H_

#include "cgf/CGFlight.h"
#include "parser.h"

class Light {
private:
	//TODO static initial..
	CGFlight *light;
	unsigned int id;
	string name_id;
	const float* exponent;
	bool enabled;
	float direct[4];
	float ambient[4];
	float diffuse[4];
	float specular[4];
	float angle;
	float pos[4];
	bool spot;
public:
	Light(unsigned int lightid, elemContainer * elc);
	void draw();
	CGFlight* getCGFlight();
	unsigned int getId();
	string getName();
	bool isEnabled();
	void setEnabled(bool);
	void init();
	virtual ~Light();
};

#endif /* LIGHT_H_ */
