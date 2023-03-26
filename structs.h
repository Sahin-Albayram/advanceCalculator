//
// Created by mestan on 25.03.2023.
//

#include "parser.h"

#define EXPRESSION 0
#define TERM 1
#define FACTOR 2
#define IDENTIFIER 3
#define CONSTANT 4
#define OPERATION 5
#define EQUAL 6

#define PLUS 1
#define SUB -1
#define MUL 0
#define OPAND 2
#define OPOR 3
#define OPXOR 4





typedef struct element{
    int type;
    struct element *elements[256];
    int opr;
};

// element : type = 0 , elements = [element1, element2],
#ifndef HW1_STRUCTS_H
#define HW1_STRUCTS_H

#endif //HW1_STRUCTS_H
