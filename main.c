#include <stdio.h>
#include <string.h>
#include "calculations.h"
#include "parser.h"
//#include "structs.h"
#define MAX 256
int main() {


    //VARIABLE DEFINITION PART
            //Getting input part
    int len_command = 0;   // length of input
    char line[MAX];            // array which holds input
    fgets(line,MAX,stdin);      //taking input
    int bracketCounter =0;
    char *string = &line;
            // Tokenize part
    int blank = 0;
    struct token t[len_command]; // tokens for each char in input
    struct token *tp = &t;
    int last_type=-1;           // holding token of last char
            //Values - Variables - Numbers
    char variables[128][MAX];
    char numbers[128][MAX];
    char temp_variable[MAX];
    double variable_value[128];
    char temp_number[MAX];




    printf("%s \n",line);
    if (line[MAX-1] == '\0'){
        len_command = 0;
        while(line[len_command] != '\n'){
            len_command++;
        }
    }
    else{
        len_command = MAX;    // deciding length of input
    }



    for(char* c=string; *c !='\0';c++){         // tokenize process**************************************************
        int result = tokenizer(c,tp);
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
            break;
        }
        if(last_type == -1 && tp->type == 2){
            strcpy(temp_variable,"");
            strncat(temp_variable,&tp->value,1);
        }
        if(last_type != 2 && last_type !=-1 && tp->type == 2){
            int var_idx = 0;
            for(int i = 0;i<128;i++){
                if(variables[i][0]=='\0'){
                    strcpy(variables[i],temp_variable);
                    var_idx = i;
                    break;
                }
                if(strcmp(variables[i],temp_variable)==0){
                    var_idx = i;
                    printf("aha valla aynısı \n");
                    break;
                }
            }
            printf("var_idx : %d\n",var_idx);
            strcpy(temp_variable,"");
            strncat(temp_variable,&tp->value,1);

        }
        if(last_type ==2 && tp->type == 2){
            strncat(temp_variable,&tp->value,1);
        }
        printf("type : %d,value: %d , char = %c \n",tp->type,tp->value,tp->value);
        blank = tp->type==0 ? 1: 0;
        last_type = tp->type==0 ? last_type : (tp->type);
        *tp++;
    }
    if(bracketCounter !=0){
        printf("bracket wrong");
        return 0;
    }




    char a = '!';
    strcpy(variables[0], "hello world");
    strncat(variables[0], &a,1);




    printf("t.type : %d ,value: %d",t->type,t->value);

    return 0;
}

