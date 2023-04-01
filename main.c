#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "calculations.h"
#include "parser.h"
#include "structs.h"


#define MAX 256              // Codes for Token types
#define EXPRESSION 0
#define TERM 1
#define FACTOR 2
#define IDENTIFIER 3
#define CONSTANT 4
#define OPERATION 5
#define EQUAL 6

#define EL_PLUS 1              // Codes for Element types
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

    char variables[128][MAX] = {};  // char array that holds variable names
    double variable_value[128] = {}; // double array for variable values

    char *p_var = &variables[0][0];     // variable pointer
    double *p_val = &variable_value[0]; // value pointer

    int len;                            //variable for len of input
    int* p_len = &len;                  // pointer forlen
    char *input;
    int bool_equal;                     // =1 if input contains "="
    int len_elements;                   // variable for length of elements array
    int check =1;                       // continue to taking and calculating
    while(check ==1){                   // loop
        int error =0;
        struct token t[256] = {};               //token array
        struct token *p_t = &t;                 //token array pointer
        struct element elements[MAX] = {};      //element array
        struct element* p_el = &elements;       // pointer of element array


        printf("> ");
        input = takeInput(p_len);                                                       //input
        struct token *te= tokenization(input,*p_len,p_t);        //tokenizatin step
        if(te==NULL){                                                                   //error checking
            error = 1;
        }
        bool_equal=elementCreator(p_t,p_el,p_var,0,0,p_val);        //elementatiton step
        if(bool_equal == -666){                                                        //error check
            error =1;
        }
        len_elements=element_size(p_el);                                               // length of elements
        struct element* P_el = p_el;                                                   //reseting pointer to beggining of array
        for(int i=0;i<len_elements-1;i++){   // taking pointer last element of array because I check expressions in reverse in order to prevent infix calculation problems
            *P_el++;
        }
        if(error == 1){
            printf("ERROR!\n");
            continue;
        }
        if(bool_equal==0){                                                                  //if input does not contain equal code will print result
            double result = expression_parser(P_el,bool_equal,len_elements,p_val);
            if(error == 1){
                printf("ERROR!\n");
                continue;
            }

            printf("%lf\n",result);
            continue;
        }
        else {
            expression_parser(P_el, bool_equal, len_elements, p_val);
        }

    }









    //char a = '!';
    //strcpy(variables[0], "hello world");
    //strncat(variables[0], &a,1);




 //   printf("t.type : %d ,value: %d",t.type,t.value);

    return 0;
}

