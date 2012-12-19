/*
 * Board.h
 *
 *  Created on: Dec 17, 2012
 *      Author: ster
 */

#ifndef BOARD_H_
#define BOARD_H_

#include <iostream>
#include <string>
#include "cgf/CGFobject.h"
#include "cgf/CGFtexture.h"
#include "parser.h"


using namespace std;

class Board: public CGFobject {
private:
	GLuint step;
	GLfloat ctrlpoints[4][3];
	GLfloat colorpoints[4][4];
	GLfloat texpoints[4][2];
	CGFtexture tex;

public:
	Board();
	void init_points();
	void draw();
	virtual ~Board(){};
};

#endif /* BOARD_H_ */
