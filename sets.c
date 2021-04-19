#include "sets.h"

// Возвращает дескриптор на множество элементы которого могут принимать
// значения от min до max
set createSet(int_fast32_t min, int_fast32_t max){
    size_t len, size, bit_size;
    len = max - min + 1;
    bit_size = sizeof(int_fast32_t) * 8;
    size = len / bit_size + (int)(len % bit_size != 0);
    int_fast32_t *pa = (int_fast32_t*)calloc(size, sizeof(int_fast32_t));

    set r = {pa, min, max, bit_size, size, 0};
    return r;
}

// Добавляет value в множество по адресу s
void add(set *s,int_fast32_t value){
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

// Считывает n элементов, добавляет их в множество s
void inputSet(set *s, int_fast32_t n){
    for(size_t i = 0; i < n; i++){
        int_fast32_t val;
        scanf("%d", &val);
        add(s, val);
    }
}

// Выводит элементы множества s
void outputSet(set s){
    printf("{");

    if (s.power > 0) {
        int_fast32_t elem = s.min;
        for (size_t i = 0; i < s.size; i++) {
            if (s.pa[i] != 0) {
                for (size_t j = 0; j < s.bit_size;j++) {
                    if(elem <= s.max) {
                        int_fast32_t bit;
                        bit = s.pa[i] & (1 << (s.bit_size - j + 1));
                        if (bit) {
                            printf("%d, ", elem);
                        }
                        elem++;
                    } else break;
                }
            } else
                elem += s.bit_size;
        }
        printf("\b\b");
    }

    printf("}");
}

// Возвращает "ИСТИНА", если все элементы множества a содержатся в
// множестве b, иначе возвращает "ЛОЖЬ"
bool inclusion(set a, set b){
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

// Возвращает "ИСТИНА", если все элементы множества a содержатся в
// множестве b и a равно b, иначе возвращает "ЛОЖЬ"
bool strictInclusion(set a, set b){
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

// Возвращает количество едениц в двоичном коде числа n
static size_t cntOne(int_fast32_t n){
    size_t cnt = 0;
    int_fast32_t mask = 1;
    for(size_t i = 1; i <= 32; i++){
        if(n & mask) cnt++;
        mask <<= 1;
    }
    return cnt;
}

// Возвращает множество, которое является дополнением до универсума
// множества s
set toUniverse(set s){
    set comp;
    comp = createSet(s.min, s.max);
    for(size_t i = 0; i < s.size; i++){
        comp.pa[i] = ~s.pa[i];
        comp.power += cntOne(comp.pa[i]);
    }
    return comp;
}

// Возвращает множество, которое является результатом
// объединения множеств a и b
set association(set a, set b){
    set c;
    c = createSet(a.min, b.max);
    if(a.min == b.min || a.max == b.max) {
        for (size_t i = 0; i < a.size; i++) {
            c.pa[i] = a.pa[i] | b.pa[i];
            c.power += cntOne(c.pa[i]);
        }

    } else {
        fprintf(stderr, "Допустимые диапазоны множеств не совпадают!");
    }
    return c;
}

// Возвращает множество, которое является результатом
// пересечения множеств a и b
set intersection(set a, set b){
    set c;
    c = createSet(a.min, b.max);
    if(a.min == b.min || a.max == b.max) {
        for (size_t i = 0; i < a.size; i++) {
            c.pa[i] = a.pa[i] & b.pa[i];
            c.power += cntOne(c.pa[i]);
        }
    } else {
        fprintf(stderr, "Допустимые диапазоны множеств не совпадают!");
    }
    return c;
}

// Возвращает множество, которое является результатом
// разности множеств a и b
set difference(set a, set b){
    set c;
    c = createSet(a.min, a.max);
    if(a.min == b.min || a.max == b.max) {
        for (size_t i = 0; i < a.size; i++) {
            c.pa[i] = a.pa[i] & ~(b.pa[i]);
            c.power += cntOne(c.pa[i]);
        }
    } else {
        fprintf(stderr, "Допустимые диапазоны множеств не совпадают!");
    }
    return c;
}

// Возвращает множество, которое является результатом
// симметрической разности множеств a и b
set symmetricDifference(set a, set b){
    set c;
    c = createSet(a.min, a.max);
    if(a.min == b.min || a.max == b.max) {
        for (size_t i = 0; i < a.size; i++) {
            c.pa[i] = a.pa[i] ^ b.pa[i];
            c.power += cntOne(c.pa[i]);
        }
    } else {
        fprintf(stderr, "Допустимые диапазоны множеств не совпадают!");
    }
    return c;
}

//Возвращает ИСТИНА, если множества a и b равны, иначе ЛОЖЬ
bool isEqual(set a, set b){

    if(a.min == b.min || a.max == b.max) {
        for (size_t i = 0; i < a.size; i++) {
            if(a.pa[i] != b.pa[i])
                return false;
        }
    } else {
        fprintf(stderr, "Допустимые диапазоны множеств не совпадают!");
    }
    return true;
}

//Добавляет в множество s элементы массива a размера n
void addArray(set *s, int_fast32_t *a, size_t n){
    for (int i = 0; i < n; ++i) {
        add(s,a[i]);
    }
}

int_fast32_t *toArray(set s){
    int_fast32_t *pa = (int_fast32_t*)malloc(s.power * sizeof(int_fast32_t));
    size_t pos = 0;

    int_fast32_t elem = s.min;
    for (size_t i = 0; i < s.size; i++) {
        if (s.pa[i] != 0) {
            for (size_t j = 0; j < s.bit_size;j++) {
                if(elem <= s.max) {
                    int_fast32_t bit;
                    bit = s.pa[i] & (1 << (s.bit_size - j + 1));
                    if (bit) {
                        pa[pos++] = elem;
                    }
                    elem++;
                } else break;
            }
        } else
            elem += s.bit_size;
    }

    return pa;
}