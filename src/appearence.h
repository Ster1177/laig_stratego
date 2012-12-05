

#ifndef APPEARENCE_H_
#define APPEARENCE_H_

#include "cgf/CGFappearance.h"
#include "parser.h"

class appearence: public CGFappearance {
private:
	float emissive[4];
public:
	appearence(Elems *);
	void apply();
	virtual ~appearence();
};

#endif /* APPEARENCE_H_ */
