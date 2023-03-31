//
// Created by mestan on 19.03.2023.
//
#ifndef HW1_PARSER_H
#define HW1_PARSER_H
#define MAX 256

#include <ctype.h>
#include <stdio.h>
#include "structs.h"

#define T_BLANK 0
#define T_NUMBER 1
#define T_LETTER 2
#define T_BRACKET_OPEN 3
#define T_EQUALS 4
#define T_OPERATOR 5
#define T_BRACKET_CLOSE 6
#define T_COMA 7

#define EL_PLUS 1
#define EL_SUB -1
#define EL_MUL 0
#define EL_OPXOR 22
#define EL_OPLS 33
#define EL_OPRS 44
#define EL_OPLR 55
#define EL_OPRR 66
#define EL_OPNOT 77
#define EL_NONE -1




int tokenize(char *string, struct token *t){
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
    else if(e==44){
        t->type = T_COMA;
        t->value = e;
        status =1;
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
        t->value= e-48;
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

struct element bitwiseCheck(char name[],char **bit,struct token **t){
    struct element bit_op;
    struct token *tp = *t;
    struct token bit_t[256];
    struct token *bit_pt = &bit_t;


    int num_name =0;
    char *c = *bit;
    bit_op.type = EL_NONE;

    if(strcmp(name,"xor")==0) {
        bit_op.type = T_NUMBER;
        bit_op.opr = EL_OPXOR;
        num_name=3;
    }
    else if(strcmp(name,"ls")==0) {
        bit_op.type = T_NUMBER;
        bit_op.opr = EL_OPLS;
        num_name=2;
    }
    else if(strcmp(name,"rs")==0) {
        bit_op.type = T_NUMBER;
        bit_op.opr = EL_OPRS;
        num_name=2;
    }
    else if(strcmp(name,"lr")==0) {
        bit_op.type = T_NUMBER;
        bit_op.opr = EL_OPLR;
        num_name=2;
    }
    else if(strcmp(name,"rr")==0) {
        bit_op.type = T_NUMBER;
        bit_op.opr = EL_OPRR;
        num_name=2;
    }
    else if(strcmp(name,"not")==0) {
        bit_op.type = T_NUMBER;
        bit_op.opr = EL_OPNOT;
        num_name=3;
    }
    if(bit_op.type == EL_NONE){
        return bit_op;
    }
    for(int i = 0;i<num_name+1;i++){
        tp->type=0;
        tp->value=0;
        *tp--;
    }
    struct element el1;
    struct element el2;

    int bracketCounter = 1;
    int blank = 0;
    *c++;
    int coma =0;
    while(bracketCounter != 0){
        int last_type = T_BRACKET_OPEN;
        int result = tokenize(c,bit_pt);
        if(bit_pt->type == T_EQUALS){
            bit_op.type=-EL_NONE;
            break;
        }
        if(ruleCheck(last_type,bit_pt->type,result,blank)==0){
            bit_op.type=-EL_NONE;
            break;
        }
        if(bit_pt->type == T_COMA){
            coma +=1;
        }

        blank = bit_pt->type==0 ? 1 : 0;
        last_type = bit_pt->type==0 ? last_type : (bit_pt->type);
        printf("%d",result);
        if(bit_pt->type == T_BRACKET_OPEN)
            bracketCounter= bracketCounter +1;
        if(bit_pt->type == T_BRACKET_CLOSE)
            bracketCounter= bracketCounter -1;

        *c++;
        *bit_pt++;

    }
    if(coma!=1){
        bit_op.type=-EL_NONE;
    }



    return bit_op;
}

char* takeInput(int *p_len){  // length of input
    char line[MAX];            // array which holds input
    fgets(line,MAX,stdin);
    //taking input
    if (line[MAX-1] == '\0'){
        *p_len = 0;
        while(line[*p_len] != '\n'){
            *p_len+=1;
        }
    }
    else{
        *p_len = MAX;    // deciding length of input
    }

    return line;
}

struct token* tokenization(char* string,int len_command){
    char line[256];


    int bracketCounter =0;
    int blank = 0;
    int last_type=-1;           // holding token of last char
    //Values - Variables - Numbers

    struct token t[256];
    struct token *tp = &t;
    struct element el;
    char *c = string;
    int num_equal = 0;

    for(int k=0;k<len_command;k++){

        int result = tokenize(c,tp);
        if(last_type == -1 && (tp->type == 6 || tp->type == 4 || tp->type == 5)){
            printf("ERROR!");
            return 0;
        }
        if(tp->type == 3){
            bracketCounter = bracketCounter+1;
        }
        if(tp->type == 6){
            if(bracketCounter == 0){
                printf("bracket wrong");
                break;
            }
            bracketCounter= bracketCounter -1;
        }
        // checking if rules are valid
        if(ruleCheck(last_type,tp->type,result,blank)==0){
            printf("ERROR!");
            return 0;

        }

        if(tp->type == 4){
            num_equal+=1;
        }
        printf("type : %d,value: %d , char = %c \n",tp->type,tp->value,tp->value);
        blank = tp->type==0 ? 1 : 0;
        last_type = tp->type==0 ? last_type : (tp->type);
        *tp++;
        *c++;
    }


    if(last_type == 3 || last_type == 4 || last_type == 5){
        printf("ERROR !");
        return 0;
    }
    if(num_equal !=0 && num_equal !=1){
        printf("wrong amount of equals");
        return 0;
    }
    if(bracketCounter !=0){
        printf("bracket wrong");
        return 0;
    }
    return &t;

}

void elementizer(){

}





struct element* elementCreator(struct token** pt,struct element* p_el,char *p_var,char *p_num, double *p_val){
    int last_type = -1;
    struct token* P_t = pt;

    char temp_variable[MAX] = {};
    char *varr = p_var;
    char *numm = p_num;
    double *vall = p_val;


    if(last_type == -1 && P_t->type == 2){
        strcpy(temp_variable,"");
        strncat(temp_variable,&P_t->value,1);
    }
    if(last_type != 2 && last_type !=-1 && P_t->type == 2){

        strcpy(temp_variable,"");
        strncat(temp_variable,&P_t->value,1);

    }
    if(last_type ==2 && P_t->type == 2){
        strncat(temp_variable,&P_t->value,1);
    }

    if(last_type == 2 && blank == 0 && tp->type == 3){
        bracketCounter= bracketCounter -1;
        struct element bit_elem = bitwiseCheck(temp_variable,&c,&tp);
        if (bit_elem.type==EL_NONE){
            printf("Error!");
            return 0;
        }

    }
    if(last_type == 2 && blank==0 && tp->type !=2){
        int var_idx = 0;
        for(int i = 0;i<128;i++){
            if(*varr =='\0'){
                strcpy(varr,temp_variable);
                *vall = 0;
                var_idx = i;
                break;
            }
            if(strcmp(varr,temp_variable)==0){
                var_idx = i;
                printf("aha valla aynısı \n");
                break;
            }
            varr = varr + MAX;
            *vall +=1;
        }
        printf("var_idx : %d\n",var_idx);
    }

    if(last_type == 2){
        int var_idx = 0;
        for(int i = 0;i<128;i++){
            if(*varr =='\0'){
                strcpy(varr,temp_variable);
                *vall = 0;
                var_idx = i;
                break;
            }
            if(strcmp(varr,temp_variable)==0){
                var_idx = i;
                printf("aha valla aynısı \n");
                break;
            }
            varr = varr + MAX;
            *vall += 1;
        }
        printf("var_idx : %d\n",var_idx);
    }







}








#endif //HW1_PARSER_H
