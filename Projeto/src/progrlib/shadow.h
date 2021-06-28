#ifndef LIB_PROGRSHADOW_H
#define LIB_PROGRSHADOW_H

#include "../svg/line.h"
#include "./meteor.h"

typedef struct shadow* Shadow;

Shadow createShadow(lineT line, Meteor meteor);

lineT shadowGetGeneratingWall(Shadow shadow);

Meteor shadowGetMeteor(Shadow shadow);

void destroyShadow(Shadow shadow);

#endif