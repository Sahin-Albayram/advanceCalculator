//
// Created by mestan on 25.03.2023.
//
#ifndef HW1_STRUCTS_H
#define HW1_STRUCTS_H
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

typedef struct token {
    int type;
    int value;
} ;

typedef struct element{
    int type;
    struct token tokens[MAX];
    int opr;
    int value;
};



typedef struct logic{
    struct element elements[MAX];
    int opr;
    struct logic *l1;
    struct logic *l2;
};
typedef struct expression{
    struct element elements[MAX];
    int opr;
    struct logic *l1;
    struct logic *l2;
};
typedef struct term{
    struct element elements[MAX];
    int opr;
    struct logic *l1;
    struct logic *l2;
};
typedef struct factor{
    struct element el;
    int type;
    double value;
    struct logic *l;
};





// element : type = 0 , elements = [element1, element2],


#endif //HW1_STRUCTS_H
