//
// Created by mestan on 19.03.2023.
//

#include <ctype.h>
#include <stdio.h>

#define T_BLANK 0
#define T_NUMBER 1
#define T_LETTER 2
#define T_BRACKET_OPEN 3
#define T_EQUALS 4
#define T_OPERATOR 5
#define T_BRACKET_CLOSE 6

typedef struct token {
    int type;
    int value;
};


int tokenizer(char *string, struct token *t){
    int e = (int)(*string);
    int status = 0;

    if((65<=e && 90>=e)  || (97<=e && 122>=e)){
        t->type = T_LETTER;
        t->value = e;
        status = 1;
    }
    else if(e==37){
        t->type = -1;
        t->value = e;
        status = -1;
    }
    else if(e==32){
        t->type = T_BLANK;
        t->value = e;
        status = 1;
    }
    else if(e==42 || e==43 || e==45|| e==38 || e==124){
        t->type=T_OPERATOR;
        t->value = e;
        status = 1;
    }
    else if(e==40){
        t->type = T_BRACKET_OPEN;
        t->value = e;
        status = 1;
    }
    else if(e==41){
        t->type= T_BRACKET_CLOSE;
        t->value = e;
        status = 1;
    }
    else if(e==61){
        t->type = T_EQUALS;
        t->value = e;
        status = 1;
    }
    else if(e>=0 || e<=9){
        t->type = T_NUMBER;
        t->value= e;
        status = 1;
    }




    return status;

}

int ruleCheck(int last_type, int type,int result,int blank){
    int check = 1;
    if(result == 0){
        printf("error cannot tokenized. \n");
        check = 0;
    }
    if(result == -1){
        check = 0;
    }

    if((type) * last_type == 25 ||(type) * last_type ==16){
        printf("two operator cannot be adjacent \n");
        check = 0;
    }
    if(last_type == 1 && type == 1 && blank == 1){
        printf("there cannot be space between two number \n");
        check = 0;
    }
    if(last_type == 2 && type == 2 && blank ==1){
        printf("there cannot be space between two letter \n");
        check = 0;
    }
    if(last_type == 2 && type == 3 && blank == 1){
        printf("delete the blaaank \n");
        check = 0;
    }




    return check;
}







#ifndef HW1_PARSER_H
#define HW1_PARSER_H

#endif //HW1_PARSER_H
