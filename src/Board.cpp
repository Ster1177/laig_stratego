#include "Board.h"

Board::Board() {
	this->step = 100;
	this->init_points();
	tex = CGFtexture("textures/10x10.jpg");
}

void Board::init_points() {
	ctrlpoints[0][0] = 0.0; ctrlpoints[0][1] = 0.0; ctrlpoints[0][2] = 1.0;
	ctrlpoints[1][0] = 0.0; ctrlpoints[1][1] = 0.0; ctrlpoints[1][2] = 0.0;
	ctrlpoints[2][0] = 1.0; ctrlpoints[2][1] = 0.0; ctrlpoints[2][2] = 1.0;
	ctrlpoints[3][0] = 1.0; ctrlpoints[3][1] = 0.0; ctrlpoints[3][2] = 0.0;

	colorpoints[0][0] = colorpoints[0][1] = colorpoints[0][2] = colorpoints[0][3] = 0.0;
	colorpoints[1][0] = colorpoints[1][1] = colorpoints[1][2] = colorpoints[1][3] = 0.0;
	colorpoints[2][0] = colorpoints[2][1] = colorpoints[2][2] = colorpoints[2][3] = 0.0;
	colorpoints[3][0] = colorpoints[3][1] = colorpoints[3][2] = colorpoints[3][3] = 0.0;


	texpoints[0][0] = 0.0; texpoints[0][1] = 0.0;
	texpoints[1][0] = 0.0; texpoints[1][1] = 1.0;
	texpoints[2][0] = 1.0; texpoints[2][1] = 0.0;
	texpoints[3][0] = 1.0; texpoints[3][1] = 1.0;

}

void Board::draw() {
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	tex.apply();

	glScalef(13,1,13);


//	glColor3f(1.0,1.0,1.0);
	glMap2f(GL_MAP2_VERTEX_3, 0.0, 1.0, 3, 2,  0.0, 1.0, 6, 2,  &ctrlpoints[0][0]);
	glMap2f(GL_MAP2_TEXTURE_COORD_2,  0.0, 1.0, 2, 2,  0.0, 1.0, 4, 2,  &texpoints[0][0]);
	// os interpoladores activam-se:
	glEnable(GL_MAP2_VERTEX_3);
	glEnable(GL_AUTO_NORMAL);
	glEnable(GL_MAP2_TEXTURE_COORD_2);

	glMapGrid2f(this->step, 0.0,1.0, this->step, 0.0,1.0);
	glEvalMesh2(GL_FILL, 0,this->step, 0,this->step);		// GL_POINT, GL_LINE, GL_FILL

	glPopMatrix();

}




