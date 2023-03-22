//
// Created by mestan on 19.03.2023.
//

#include <ctype.h>
#include <stdio.h>

#define T_NUMBER 0
#define T_OPERATOR 1
#define T_BRACKET 2
#define T_BLANK 3


typedef struct{
     char name[128];
     int value;
} identifier;

typedef struct{
    int value;
} constant;



typedef struct {
    int type;
    int value;
} token;


int tokenizer(token *t){





}
#ifndef HW1_PARSER_H
#define HW1_PARSER_H

#endif //HW1_PARSER_H
