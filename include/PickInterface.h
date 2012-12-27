#ifndef PickInterface_H
#define PickInterface_H
#include "Scene.h"
#include <utility>
#include "cgf/CGFinterface.h"
#include "cgf/CGFapplication.h"

class PickInterface: public CGFinterface {
	public:
		GLuint * selec;
		virtual void processMouse(int button, int state, int x, int y);	
		void performPicking(int x, int y);
		void processHits(GLint hits, GLuint buffer[]);
		GLuint * getSelected(GLuint * sel);
		~PickInterface(){};
};


#endif
