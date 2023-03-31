#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "calculations.h"
#include "parser.h"
#include "structs.h"


#define MAX 256
#define EXPRESSION 0
#define TERM 1
#define FACTOR 2
#define IDENTIFIER 3
#define CONSTANT 4
#define OPERATION 5
#define EQUAL 6

#define EL_PLUS 1
#define EL_SUB -1
#define EL_MUL 0
#define EL_OPXOR 22
#define EL_OPLS 33
#define EL_OPRS 44
#define EL_OPLR 55
#define EL_OPRR 66
#define EL_OPNOT 77

struct token;
int main() {
//
//    //VARIABLE DEFINITION PART
//            //Getting input part
//    int len_command = 0;   // length of input
//    char line[MAX];            // array which holds input
//    fgets(line,MAX,stdin);      //taking input
//    int bracketCounter =0;
//    char *string = &line;
//            // Tokenize part
//    int blank = 0;
//
//    int last_type=-1;           // holding token of last char
//            //Values - Variables - Numbers
//    char variables[128][MAX] = {};
//    char numbers[128][MAX] = {};
//    char temp_variable[MAX] = {};
//    double variable_value[128] = {};
//    char temp_number[MAX]= {};
//
//    if (line[MAX-1] == '\0'){
//        len_command = 0;
//        while(line[len_command] != '\n'){
//            len_command++;
//        }
//    }
//    else{
//        len_command = MAX;    // deciding length of input
//    }
//    struct token t[256];
//    struct token *tp = &t;
//    struct element el;
//    char *c = string;
//    int num_equal = 0;
//
//
//
//    for(int k=0;k<len_command;k++){
//
//        int result = tokenize(c,tp);
//        if(last_type == -1 && (tp->type == 6 || tp->type == 4 || tp->type == 5)){
//            printf("ERROR!");
//            return 0;
//        }
//        if(tp->type == 3){
//            bracketCounter = bracketCounter+1;
//        }
//        if(tp->type == 6){
//            if(bracketCounter == 0){
//                printf("bracket wrong");
//                break;
//            }
//            bracketCounter= bracketCounter -1;
//        }
//        // checking if rules are valid
//        if(ruleCheck(last_type,tp->type,result,blank)==0){
//            break;
//        }
//        if(last_type == 2 && blank == 0 && tp->type == 3){
//            bracketCounter= bracketCounter -1;
//            struct element bit_elem = bitwiseCheck(temp_variable,&c,&tp);
//            if (bit_elem.type==EL_NONE){
//                printf("Error!");
//                return 0;
//            }
//
//        }
//        if(last_type == 2 && blank==0 && tp->type !=2){
//            int var_idx = 0;
//            for(int i = 0;i<128;i++){
//                if(variables[i][0]=='\0'){
//                    strcpy(variables[i],temp_variable);
//                    variable_value[i] = 0;
//                    var_idx = i;
//                    break;
//                }
//                if(strcmp(variables[i],temp_variable)==0){
//                    var_idx = i;
//                    printf("aha valla aynısı \n");
//                    break;
//                }
//            }
//            printf("var_idx : %d\n",var_idx);
//        }
//        if(tp->type == 4){
//            num_equal+=1;
//        }
//        if(last_type == -1 && tp->type == 1){
//            strcpy(temp_number,"");
//            strncat(temp_number,&tp->value,1);
//        }
//
//        if(last_type !=1 && last_type !=-1 && tp->type == 1){
//            strcpy(temp_number,"");
//            strncat(temp_number,&tp->value,1);
//        }
//
//
//
//        if(last_type == -1 && tp->type == 2){
//            strcpy(temp_variable,"");
//            strncat(temp_variable,&tp->value,1);
//        }
//        if(last_type != 2 && last_type !=-1 && tp->type == 2){
//
//            strcpy(temp_variable,"");
//            strncat(temp_variable,&tp->value,1);
//
//        }
//        if(last_type ==2 && tp->type == 2){
//            strncat(temp_variable,&tp->value,1);
//        }
//        printf("type : %d,value: %d , char = %c \n",tp->type,tp->value,tp->value);
//        blank = tp->type==0 ? 1 : 0;
//        last_type = tp->type==0 ? last_type : (tp->type);
//        *tp++;
//        *c++;
//    }
//    if(last_type == 2){
//        int var_idx = 0;
//        for(int i = 0;i<128;i++){
//            if(variables[i][0]=='\0'){
//                strcpy(variables[i],temp_variable);
//                variable_value[i] = 0;
//                var_idx = i;
//                break;
//            }
//            if(strcmp(variables[i],temp_variable)==0){
//                var_idx = i;
//                printf("aha valla aynısı \n");
//                break;
//            }
//        }
//        printf("var_idx : %d\n",var_idx);
//    }
//    if(last_type == 3 || last_type == 4 || last_type == 5){
//        printf("ERROR !");
//        return 0;
//    }
//    if(num_equal !=0 && num_equal !=1){
//        printf("wrong amount of equals");
//        return 0;
//    }
//    if(bracketCounter !=0){
//        printf("bracket wrong");
//        return 0;
//    }
//
    char variables[128][MAX] = {};
    char numbers[128][MAX] = {};
    double variable_value[128] = {};

    char *p_var = &variables[0][0];
    char *p_num = &numbers[0][0];
    double *p_val = &variable_value[0];

    struct element elements[MAX];
    struct element* p_el = &elements;





    int len;
    int* p_len = &len;
    char *input;
    struct token *P_t;
    input = takeInput(p_len);
    tokenization(input,*p_len);
    elementCreator(P_t,p_el,p_var,p_num,p_val);






    //char a = '!';
    //strcpy(variables[0], "hello world");
    //strncat(variables[0], &a,1);




 //   printf("t.type : %d ,value: %d",t.type,t.value);

    return 0;
}

