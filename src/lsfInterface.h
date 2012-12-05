/*
 * lsfInterface.h
 *
 *  Created on: Oct 15, 2012
 *      Author: ciberwizz
 */

#ifndef LSFINTERFACE_H_
#define LSFINTERFACE_H_

#include "cgf/CGFinterface.h"

class lsfInterface: public CGFinterface {
public:
	lsfInterface(int s): test(s){};
	void iniGUI();
	void processKeyboard(unsigned char k, int x, int y);
	virtual ~lsfInterface();
	int test;
};

#endif /* LSFINTERFACE_H_ */
