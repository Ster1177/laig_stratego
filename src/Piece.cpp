/*
 * Piece.cpp
 *
 *  Created on: Dec 18, 2012
 *      Author: ster
 */

#include "Piece.h"

Piece::Piece() {
	piece = new Cylinder(0.1,0.3,0.25,30,30);
	tex = CGFtexture("textures/wood1.jpg");
}


void Piece::put() {
	glEnable(GL_TEXTURE_2D);
	glPushMatrix();
	glRotated(90,1,0,0);
	glTranslated(0.75,0.75,-0.25);
	tex.apply();
	piece->draw();
	glPopMatrix();

}








