#ifndef SETS_SETS_H
#define SETS_SETS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

 typedef struct {
    int_fast32_t *pa;
    int_fast32_t min, max;
    size_t bit_size, size, power;
} set;// Тип, который задает множество


set createSet(int_fast32_t min, int_fast32_t max);

void add(set *s,int_fast32_t value);

void addArray(set *s, int_fast32_t *a, size_t n);

void inputSet(set *s, int_fast32_t n);

void outputSet(set s);


bool inclusion(set a, set b);

bool strictInclusion(set a, set b);

bool isEqual(set a, set b);


set toUniverse(set s);

set association(set a, set b);

set intersection(set a, set b);

set difference(set a, set b);

set symmetricDifference(set a, set b);

int_fast32_t *toArray(set s);

#endif //SETS_SETS_H
