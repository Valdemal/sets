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

struct set create_set(int_fast32_t min, int_fast32_t max);

void add(struct set *s,int_fast32_t value);

void input_set(struct set s, int_fast32_t n);

void output_set(struct set s);

bool inclusion(struct set a, struct set b);

bool strict_inclusion(struct set a, struct set b);

struct set to_universe(struct set s);

struct set association(struct set a, struct set b);

struct set intersection(struct set a, struct set b);

struct set difference(struct set a, struct set b);

struct set symmetric_difference(struct set a, struct set b);

#endif //SETS_SETS_H
