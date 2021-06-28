#ifndef LIB_PROGRSHADOW_H
#define LIB_PROGRSHADOW_H

#include "../svg/line.h"

typedef struct shadow* Shadow;

Shadow createPerson( circle);

circleT personGetCircle(Person person);

double personGetRadiation(Person person);

void personAddRadiation(Person person, int radiation);

int personIsDead(Person person);

void killPerson(Person person);

void destroyPerson(Person person);


#endif