#include "./person.h"

struct person {
    circleT circle;
    double radiation;
    int dead;
};

Person createPerson(circleT circle) {
    if (!circle) {
        return NULL;
    }

    Person person = malloc(sizeof(struct Person));
    if (!person) {
        return NULL;
    }

    person->circle = circle;
    person->radiation = 0;
    person->dead = 0;

    return person;
}

circleT personGetCircle(Person person) {
    if (!person) {
        return NULL;
    }

    return person->circle;
}

double personGetRadiation(Person person) {
    if (!person) {
        return -1;
    }

    return person->radiation;
}

void personAddRadiation(Person person, int radiation) {
    if (!person || radiation < 0) {
        return;
    }

    person->radiation += radiation;
}

int personIsDead(Person person) {
    return person && person->dead;
}

void killPerson(Person person) {
    if (!person) {
        return;
    }

    person->dead = 1;
}

void destroyPerson(Person person) {
    if (!person) {
        return;
    }

    circleT circle = personGetCircle(person);
    destroyCircle(circle);

    free(person);
}