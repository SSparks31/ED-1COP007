#ifndef LIB_PROGRPERSON_H
#define LIB_PROGRPERSON_H

#include "../svg/circle.h"

typedef struct person* Person;

Person createPerson(circleT circle);

circleT personGetCircle(Person person);

double personGetRadiation(Person person);

void personAddRadiation(Person person, double radiation);

int personIsDead(Person person);

void killPerson(Person person);

void destroyPerson(Person person);


#endif