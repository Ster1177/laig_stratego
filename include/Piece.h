/*
 * Piece.h
 *
 *  Created on: Dec 18, 2012
 *      Author: ster
 */

#ifndef PIECE_H_
#define PIECE_H_

#include "primitives.h"
#include "cgf/CGFtexture.h"

class Piece {

public:
	Cylinder * piece;
	CGFtexture tex;
	Piece();
	void put();
	virtual ~Piece(){};
};

#endif /* PIECE_H_ */
