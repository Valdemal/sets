#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <windows.h>

struct set {
    int_fast32_t *pa;
    int_fast32_t min, max, bit_size, size, power;
};

struct set create_set(int_fast32_t min, int_fast32_t max){
    int_fast32_t len, size, bit_size;
    len = max - min + 1;
    bit_size = sizeof(int_fast32_t) * 8;
    size = len / bit_size + (int)(len % bit_size != 0);
    int_fast32_t *pa = (int_fast32_t*)calloc(size, sizeof(int_fast32_t));

    struct set r = {pa, min, max, bit_size, size, 0};
    return r;
}

void add(struct set *s,int_fast32_t value){
    if (value >= s->min && value <= s->max){
        size_t i, bi;
        int_fast32_t pos;
        pos = (value - s->min);
        i = pos / s->bit_size;
        bi = pos % s->bit_size;
        s->pa[i] |= 1 << (s->bit_size - bi+1);
        s->power++;
    } else {
        fprintf(stderr, "Value is out of range for %d to %d!", s->min, s->max);
    }
}

struct set input(struct set *s, int_fast32_t n){
    for(size_t i = 0; i < n; i++){
        int_fast32_t val;
        scanf("%d", &val);
        add(s, val);
    }
}

void output(struct set s){
    printf("{");
    int_fast32_t elem;
    elem = s.min;
    size_t j = 0;
    for(size_t i = 0;i < s.size; i++){
        if(s.pa[i] != 0) {
            for (j = 0; j < s.bit_size; j++) {
                int_fast32_t bit;
                bit = s.pa[i] & (1 << (s.bit_size - j));
                if (bit) {
                    printf("%d, ", elem);
                }
                elem++;
            }
        } else
            elem += s.bit_size;
    }
    if (j > 0)
        printf("\b\b");
    printf("}");
}

bool includion(struct set a, struct set b){
    if(a.min == b.min || a.max == b.max) {
        if (a.power > b.power)
            return false;

        for (size_t i = 0; i < a.size; i++) {
            for (size_t j = 0; j < a.bit_size; j++) {
                int_fast32_t a_bit;
                a_bit = a.pa[i] & (1 << (a.bit_size - j));
                if (a_bit) {
                    int_fast32_t b_bit;
                    b_bit = b.pa[i] & (1 << (b.bit_size - j));
                    if (b_bit == 0)
                        return false;
                }
            }
        }
    } else {
        fprintf(stderr, "Допустимые диапазоны множеств не совпадают!");
    }
    return true;
}

bool strict_includion(struct set a, struct set b){
    if(a.min == b.min || a.max == b.max) {
        if (a.power >= b.power || a.power == 0)
            return false;

        for (size_t i = 0; i < a.size; i++) {
            for (size_t j = 0; j < a.bit_size; j++) {
                int_fast32_t a_bit;
                a_bit = a.pa[i] & (1 << (a.bit_size - j));
                if (a_bit) {
                    int_fast32_t b_bit;
                    b_bit = b.pa[i] & (1 << (b.bit_size - j));
                    if (b_bit == 0)
                        return false;
                }
            }
        }
    } else {
        fprintf(stderr, "Допустимые диапазоны множеств не совпадают!");
    }
    return true;
}

int_fast32_t cnt_one(int_fast32_t n){
    int_fast32_t cnt = 0;
    while (n != 0){
        if (n % 2 == 1)
            cnt++;
        n /= 2;
    }
    return cnt;
}

struct set to_universe(struct set s){
    for(size_t i = 0; i < s.size; i++){
        s.pa[i] = ~s.pa[i];
    }
    s.power = s.size * s.bit_size - s.power;
    return s;
}

struct set association(struct set a, struct set b){
    struct set c;
    c = create_set(a.min, b.max);
    if(a.min == b.min || a.max == b.max) {
        for (size_t i = 0; i < a.size; i++) {
            c.pa[i] = a.pa[i] | b.pa[i];
            c.power += cnt_one(c.pa[i]);
        }

    } else {
        fprintf(stderr, "Допустимые диапазоны множеств не совпадают!");
    }
    return c;
}

struct set intersection(struct set a, struct set b){
    struct set c;
    c = create_set(a.min, b.max);
    if(a.min == b.min || a.max == b.max) {
        for (size_t i = 0; i < a.size; i++) {
            c.pa[i] = a.pa[i] & b.pa[i];
            c.power += cnt_one(c.pa[i]);
        }
    } else {
        fprintf(stderr, "Допустимые диапазоны множеств не совпадают!");
    }
    return c;
}

struct set difference(struct set a, struct set b){
    struct set c;
    c = create_set(a.min, a.max);
    if(a.min == b.min || a.max == b.max) {
        for (size_t i = 0; i < a.size; i++) {
            c.pa[i] = a.pa[i] & ~(b.pa[i]);
            c.power += cnt_one(c.pa[i]);
        }
    } else {
        fprintf(stderr, "Допустимые диапазоны множеств не совпадают!");
    }
    return c;
}

struct set symmetric_difference(struct set a, struct set b){
    struct set c;
    c = create_set(a.min, a.max);
    if(a.min == b.min || a.max == b.max) {
        for (size_t i = 0; i < a.size; i++) {
            c.pa[i] = a.pa[i] ^ b.pa[i];
            c.power += cnt_one(c.pa[i]);
        }
    } else {
        fprintf(stderr, "Допустимые диапазоны множеств не совпадают!");
    }
    return c;
}


