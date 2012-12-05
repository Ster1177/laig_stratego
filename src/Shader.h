/*
 * Shader.h
 *
 */

#ifndef SHADER_H_
#define SHADER_H_

#include <GL/glew.h>
#include "cgf/CGFshader.h"
#include "cgf/CGFtexture.h"
#include <iostream>
#include <string>




class Shader: public CGFshader {
private:
	CGFtexture * baseTexture;
	CGFtexture * secTexture;

	GLint baseImageLoc;
	GLint secImageLoc;

	GLint scaleLoc;
	float normScale;
public:
	//	 heightmap, texturemap, fragmentshader, vertexshader;
	Shader(string,string,string,string);

	virtual void bind(void);
	virtual ~Shader();
};

#endif /* SHADER_H_ */
