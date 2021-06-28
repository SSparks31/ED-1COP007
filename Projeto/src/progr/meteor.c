#include "./meteor.h"

struct meteor {
    circleT circle;
    double radiation;
};

Meteor createMeteor(circleT circle, double radiation) {
    if (!circle || radiation <= 0) {
        return NULL;
    }

    Meteor meteor = malloc(sizeof(struct meteor));
    if (!meteor) {
        return NULL;
    }

    meteor->circle = circle;
    meteor->radiation = radiation;

    return meteor;
}

circleT meteorGetCircle(Meteor meteor) {
    if (!meteor) {
        return NULL;
    }

    return meteor->circle;
}

double meteorGetRadiation(Meteor meteor) {
    if (!meteor) {
        return -1;
    }

    return meteor->radiation;
}

void destroyMeteor(Meteor meteor) {
    if (!meteor) {
        return;
    }

    circleT circle = meteorGetCircle(meteor);
    destroyCircle(circle);

    free(meteor)
}
