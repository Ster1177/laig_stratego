/*
 * Terrain.h
 */

#ifndef TERRAIN_H_
#define TERRAIN_H_
#include "Shader.h"
#include "cgf/CGFobject.h"

#include "Plane.h"
#include <string.h>

class Terrain: public CGFobject {
	Shader* shader;
	Plane* plane;

	string heightmap;
	string texturemap;
	string fragmentshader;
	string vertexshader;

public:

	Terrain(elem*);

	void draw();

	virtual ~Terrain();
};

#endif /* TERRAIN_H_ */
