#ifndef LIB_PROGRPERSON_H
#define LIB_PROGRPERSON_H

#include "../svg/circle.h"

typedef struct meteor* Meteor;

Meteor createMeteor(circleT circle, double radiation);

circleT meteorGetCircle(Meteor meteor);

double meteorGetRadiation(Meteor meteor);

void destroyMeteor(Meteor meteor);


#endif