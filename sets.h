#ifndef SETS_SETS_H
#define SETS_SETS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

 struct set {
    int_fast32_t *pa;
    int_fast32_t min, max;
    size_t bit_size, size, power;
};// Тип, который задает множество


struct set createSet(int_fast32_t min, int_fast32_t max);

void add(struct set *s,int_fast32_t value);

void addArray(struct set *s, int_fast32_t *a, size_t n);

void inputSet(struct set *s, int_fast32_t n);

void outputSet(struct set s);


bool inclusion(struct set a, struct set b);

bool strictInclusion(struct set a, struct set b);

bool isEqual(struct set a, struct set b);


struct set toUniverse(struct set s);

struct set association(struct set a, struct set b);

struct set intersection(struct set a, struct set b);

struct set difference(struct set a, struct set b);

struct set symmetricDifference(struct set a, struct set b);

int_fast32_t *toArray(struct set s);

#endif //SETS_SETS_H
