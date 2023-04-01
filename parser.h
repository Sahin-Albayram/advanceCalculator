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


#define EL_VARIABLE 101
#define EL_NUMBER 102
#define EL_OPERATOR 103
#define EL_BITOPR 104
#define EL_EQUALS 105
#define EL_BRACKET_OPEN 106
#define EL_BRACKET_CLOSE 107

#define EL_PLUS 1
#define EL_SUB -1
#define EL_MUL 0
#define EL_AND 2
#define EL_OR 3


#define EL_OPXOR 22
#define EL_OPLS 33
#define EL_OPRS 44
#define EL_OPLR 55
#define EL_OPRR 66
#define EL_OPNOT 77
#define EL_NONE -1


int element_size(struct element *p_el);

int tokenize(char *string, struct token *t) {                   // Tokenize step of each char. Main point is comparing char result with
    int e = (int) (*string);
    int status = 0;

    if ((65 <= e && 90 >= e) || (97 <= e && 122 >= e)) {
        t->type = T_LETTER;
        t->value = e;
        status = 1;
    } else if (e == 37) {
        t->type = -1;
        t->value = e;
        status = -1;
    } else if (e == 44) {
        t->type = T_COMA;
        t->value = e;
        status = 1;
    } else if (e == 32) {
        t->type = T_BLANK;
        t->value = e;
        status = 1;
    } else if (e == 42 || e == 43 || e == 45 || e == 38 || e == 124) {
        t->type = T_OPERATOR;
        t->value = e;
        status = 1;
    } else if (e == 40) {
        t->type = T_BRACKET_OPEN;
        t->value = e;
        status = 1;
    } else if (e == 41) {
        t->type = T_BRACKET_CLOSE;
        t->value = e;
        status = 1;
    } else if (e == 61) {
        t->type = T_EQUALS;
        t->value = e;
        status = 1;
    } else if (e >= 0 || e <= 9) {
        t->type = T_NUMBER;
        t->value = e;
        status = 1;
    }

    return status;      // status =0 if unknown symbol

}

int ruleCheck(int last_type, int type, int result, int blank) { //Rule check function. Main idea is looking for current token type last token type and blank if it occurs
    int check = 1;
    if (result == 0) {
        check = 0;
    }

    if (result == -1) {
        check = 0;
    }
    if(last_type == T_BRACKET_OPEN && type == T_BRACKET_CLOSE){
        check=0;
    }
    if (last_type == T_BRACKET_OPEN && type == T_OPERATOR) {
        check = 0;
    }
    if ((last_type == T_NUMBER && type == T_LETTER) || (last_type == T_LETTER && type == T_NUMBER)) {
        check = 0;
    }
    if ((type) * last_type == 25 || (type) * last_type == 16) {
        check = 0;
    }
    if (last_type == T_NUMBER && type == T_NUMBER && blank == 1) {
        check = 0;
    }
    if (last_type == T_LETTER && type == T_LETTER && blank == 1) {
        check = 0;
    }
    if (last_type == T_LETTER && type == T_BRACKET_OPEN && blank == 1) {
        check = 0;
    }
    if (last_type == T_NUMBER && type == T_BRACKET_OPEN) {
        check = 0;
    }
    if (type == T_NUMBER && last_type == T_BRACKET_CLOSE) {
        check = 0;
    }

    return check;
}


double calculate_bit(double num1, double num2, int bit_op) { //bitwise operation calculation function
    if (bit_op == EL_OPXOR) {
        return (double) bit_xor(num1, num2);
    }
    if (bit_op == EL_OPLS) {
        return (double) bit_shift_left(num1, num2);
    }
    if (bit_op == EL_OPRS) {
        return (double) bit_shift_right(num1, num2);
    }
    if (bit_op == EL_OPLR) {
        return (double) bit_rotate_left(num1, num2);
    }
    if (bit_op == EL_OPRR) {
        return (double) bit_rotate_right(num1, num2);
    }
    if (bit_op == EL_OPNOT) {
        return (double) bit_not(num1);
    }
}

int bitwiseCheck(char name[]) {                     // bitwise operation type decidier

    if (strcmp(name, "xor") == 0) {
        return EL_OPXOR;
    } else if (strcmp(name, "ls") == 0) {
        return EL_OPLS;
    } else if (strcmp(name, "rs") == 0) {
        return EL_OPRS;
    } else if (strcmp(name, "lr") == 0) {
        return EL_OPLR;
    } else if (strcmp(name, "rr") == 0) {
        return EL_OPRR;
    } else if (strcmp(name, "not") == 0) {
        return EL_OPNOT;
    } else {
        return -666;
    }
}

char *takeInput(int *p_len) {                    //Input taker
    char line[MAX];
    fgets(line, MAX, stdin);
    //taking input
    if (line[MAX - 1] == '\0') {
        *p_len = 0;
        while (line[*p_len] != '\n') {
            *p_len += 1;
        }
    } else {
        *p_len = MAX;
    }

    return &line;
}

struct token *tokenization(char *string, int len_command, struct token *t_p) { // Tokenization loop tokenizes each char checks rules.
    char line[256];


    int bracketCounter = 0;
    int blank = 0;
    int last_type = -1;           // holding token of last char
    //Values - Variables - Numbers

    struct token *tp = t_p;
    struct element el;
    char *c = string;
    int num_equal = 0;

    for (int k = 0; k < len_command; k++) {

        int result = tokenize(c, tp);
        if(result == 0){
            return NULL;
        }
        if (last_type == -1 && (tp->type == 6 || tp->type == 4 || tp->type == 5)) {
            return NULL;
        }
        if(tp->type == -1){
            return &t_p;
        }
        if (tp->type == 3) {
            bracketCounter = bracketCounter + 1;
        }
        if (tp->type == 6) {
            if (bracketCounter == 0) {
                return NULL;
            }
            bracketCounter = bracketCounter - 1;
        }
        // checking if rules are valid
        if (ruleCheck(last_type, tp->type, result, blank) == 0) {
            return NULL;

        }

        if (tp->type == 4) {
            num_equal += 1;
        }

        blank = tp->type == 0 ? 1 : 0;
        last_type = tp->type == 0 ? last_type : (tp->type);
        *tp++;
        *c++;
    }

    if (last_type == 3 || last_type == 4 || last_type == 5) {
        return NULL;
    }
    if (num_equal != 0 && num_equal != 1) {
        return NULL;
    }
    if (bracketCounter != 0) {
        return NULL;
    }
    return &t_p;

}

double factor_parser(struct element *p_el) {                    //Factor parser it only gives value of element because even though it is variable code can still achieve its value.
    return p_el->value;
}

double term_parser(struct element *p_el, int len) {               //term parser looks for multiplication operation
    struct element *P_el = p_el;
    struct term tm_;
    tm_.p_el = &tm_.elements;
    for (int i = 0; i < len; i++) {                         // len of term


        if (P_el->type == EL_OPERATOR && P_el->opr == EL_MUL) {
            *P_el++;
            tm_.l1_result = factor_parser(p_el);                // takes left part and rigth part and multiply it
            tm_.l2_result = factor_parser(P_el);
            return tm_.l1_result * tm_.l2_result;
        }
        *P_el++;
    }
    return factor_parser(p_el);

}


double expression_parser(struct element *p_el, int bool_equal, int len, double *p_val) {        // expression parser. In order to prevent infix calculation problem reverse parsing is the option that I choosed
    struct element *P_el = p_el;                                                                // for exp: 26 -3 -50 = 73 if parser go front to back but = -27 from back to front
    double *vall = p_val;
    int bracket_surplus = 0;
    if (bool_equal == 1) {
        for (int i = 0; i < P_el->opr; i++) {
            vall = vall + 1;
        }
        *vall = expression_parser(P_el, 0, len - 2, p_val); // if equal occurs first element is equal other elements calculation
        return 0;
    }
    if (bool_equal == 0) {
        struct expression exp_;
        exp_.p_el = &exp_.elements;


        struct expression *exp_start = P_el; //p_el
        for (int i = 0; i < len; i++) {   //for(int i=0;i<len;i++){
            int go_back = 0;
            if (P_el->type == EL_BRACKET_CLOSE) {   //if(P_el->type == EL_BRACKET_OPEN){                // since going reverse I check for close-bracket first
                struct element *br_el = P_el;
                *br_el--;                                                       // pointer going reverse
                int br_count = 1;
                for (int j = 0; j < len; j++) {
                    if (br_el->type == EL_BRACKET_CLOSE) //if(br_el->type == EL_BRACKET_OPEN)
                        br_count += 1;
                    if (br_el->type == EL_BRACKET_OPEN) //CLOSE
                        br_count -= 1;
                    if (br_count == 0) {
                        struct element br_element;
                        br_element.type = EL_NUMBER;
                        br_el = P_el;
                        *br_el--; //++
                        br_element.value = expression_parser(br_el, 0, j, p_val);
                        *exp_.p_el = br_element;
                        go_back = j + 2;                //since elements inside bracket is expression there is no need to calculate it more than once therefore there is need to jump already looked ones
                        break;
                    }
                    *br_el--;
                }
            }

            if (go_back != 0) {
                bracket_surplus = bracket_surplus + go_back - 1;
                for (int k = 0; k < go_back; k++) {
                    *P_el--;//++
                    i++;
                }
                i--;
                *exp_.p_el++; // burayi da cevirmem lazim galiba

                continue;
            } else if (P_el->type == EL_OPERATOR && (P_el->opr == EL_PLUS || P_el->opr == EL_SUB)) {            //checks for plus and subtraction operators
                int plus = 0;
                if (P_el->opr == EL_PLUS) {
                    plus = 1;
                }
                *P_el--;
                exp_.l1_result = expression_parser(exp_start, 0, i, p_val);                     // one side of operator
                exp_.l2_result = expression_parser(P_el, 0, len - i - 1, p_val);                // other side of operator
                if (plus == 1) {
                    return (double) exp_.l1_result + exp_.l2_result;
                } else
                return (double) exp_.l2_result - exp_.l1_result;

            } else if (P_el->type == EL_OPERATOR && (P_el->opr == EL_AND || P_el->opr == EL_OR)) {              // checks for 'and' and 'or' operation logic is same with + -
                int andd = 0;
                if (P_el->opr == EL_AND) {
                    andd = 1;
                }
                *P_el--;
                exp_.l1_result = expression_parser(exp_start, 0, i, p_val);
                exp_.l2_result = expression_parser(P_el, 0, len - i - 1, p_val);
                if (andd == 1) {
                    return (double) bit_and(exp_.l1_result, exp_.l2_result);
                } else
                return (double) bit_or(exp_.l2_result, exp_.l1_result);
            }


            *exp_.p_el = *P_el;
            *exp_.p_el++;
            *P_el--;//++
        }
        return (double) term_parser(&exp_.elements, len - bracket_surplus);
    }
}


double elementCreator(struct token *pt, struct element *p_el, char *p_var, int bit_status, int bit_op, double *p_val) {             //Element creator is most important function of code it decide elements and
    int last_type = -1;                                                                                                             //turning bitwise operation into single value by calculating them
    struct token *P_t = pt;
    struct token *temp_t = P_t;
    int bool_equal = 0;
    char temp_variable[MAX] = {};
    char temp_number[MAX] = {};
    char *varr = p_var;
    double *vall = p_val;
    int bracketCounter = 0;
    int bit_bracketCounter = 0;
    int blank = 0;
    char *dt;
    struct element *P_el = p_el;

    while (P_t->type != 0 || P_t->value != 0) {             // until there is token go


        if (last_type == -1 && P_t->type == 1) {
            strcpy(temp_number, "");
            strncat(temp_number, &P_t->value, 1);
        }

        if (last_type == -1 && P_t->type == 2) {
            strcpy(temp_variable, "");
            strncat(temp_variable, &P_t->value, 1);
        }

        if (last_type != 1 && last_type != -1 && P_t->type == 1) {
            strcpy(temp_number, "");
            strncat(temp_number, &P_t->value, 1);
        }
        if (last_type != 2 && last_type != -1 && P_t->type == 2) {

            strcpy(temp_variable, "");
            strncat(temp_variable, &P_t->value, 1);

        }
        if (last_type == 1 && P_t->type == 1) {
            strncat(temp_number, &P_t->value, 1);
        }

        if (last_type == 2 && P_t->type == 2) {
            strncat(temp_variable, &P_t->value, 1);
        }

        if (last_type == 1 && blank == 0 && P_t->type != 1) { // if (last_type == 1 && blank == 0 && P_t->type != 1){
            struct element el_;
            int type = P_t->type;
            int value = P_t->value;
            el_.type = EL_NUMBER;
            el_.value = strtod(temp_number, &dt);
            *P_el = el_;
            *P_el++;
            strcpy(temp_number, "");       //strcpy(temp_number,""); !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
            P_t->type = type;
            P_t->value = value;
        }
        if (last_type == 2 && blank == 0 && P_t->type != 2 &&
            P_t->type != 3) { // if (last_type == 2 && blank == 0 && P_t->type != 2) {
            int var_idx = 0;
            varr = p_var;
            vall = p_val;
            for (int i = 0; i < 128; i++) {
                if (*varr == '\0') {
                    strcpy(varr, temp_variable);
                    *vall = 0;
                    var_idx = i;

                    struct element el_;
                    el_.type = EL_VARIABLE;
                    el_.opr = var_idx;
                    el_.value = *vall;
                    *P_el = el_;
                    *P_el++;
                    break;
                }
                if (strcmp(varr, temp_variable) == 0) {
                    var_idx = i;
                    struct element el_;
                    el_.type = EL_VARIABLE;
                    el_.opr = var_idx;
                    el_.value = *vall;
                    *P_el = el_;
                    *P_el++;
                    break;
                }
                varr = varr + MAX;
                *vall += 1;
            }
        }
        if (P_t->type == T_EQUALS){
            bool_equal=1;
        }

        if (P_t->type == T_COMA && bit_status != 1) {
            printf("ERROR!\n");
            return -666;
        }
        if (P_t->type == T_COMA && bit_status == 1) {
            return bool_equal;



        }
        if (last_type == 2 && blank == 0 && P_t->type == 3) {
            int bool_equall =0;
            struct token* bit_t = P_t;
            int bit_opp = bitwiseCheck(temp_variable);
            if(bit_opp == EL_OPNOT){
                bit_status = 2;
            }
            else
                bit_status = 1;
            bit_bracketCounter = 1;
            *bit_t++;
            struct token* first= bit_t;
            struct element elements_of_1[MAX] = {};
            struct element *p1_el = &elements_of_1;
            bool_equall = elementCreator(bit_t, p1_el, p_var, bit_status, bit_opp, p_val);
            if (bool_equall == -666) {
                return bool_equall;
            }
            int len_elements = element_size(p1_el);
            struct element *P1_el = &elements_of_1;
            for (int i = 0; i < len_elements - 1; i++) {   // NULL
                *P1_el++;
            }

            double result1 = expression_parser(P1_el, bool_equall, len_elements, p_val);
            if(bit_opp == EL_OPNOT){
                struct element b_el;
                b_el.value = bit_not(result1);
                b_el.type = EL_NUMBER;
                *P_el = b_el;
                *P_el++;

                for(int i=0;i<len_elements+1;i++){
                    *P_t++;
                }
            }
            else {
                while (bit_t->type != T_COMA) {
                    *bit_t++;
                }
                *bit_t++;
                struct element elements_of_2[MAX] = {};
                struct element *p2_el = &elements_of_2;

                bool_equall = elementCreator(bit_t, p2_el, p_var, 2, bit_opp, p_val);
                if (bool_equall == -666) {
                    return bool_equall;
                }
                len_elements = element_size(p2_el);
                struct element *P2_el = p2_el;
                for (int i = 0; i < len_elements - 1; i++) {   // NULL
                    *P2_el++;
                }
                double result2 = expression_parser(P2_el, bool_equall, len_elements, p_val);
                struct element b_el;
                b_el.type = EL_NUMBER;
                b_el.value = (double) calculate_bit(result1, result2, bit_opp);
                *P_el = b_el;
                *P_el++;
                P_t = first;
                while(bit_bracketCounter>0 && (P_t->type!=0 && P_t->value!=0)){
                    if(P_t->type==T_BRACKET_OPEN){
                        bit_bracketCounter+=1;
                    }
                    if(P_t->type==T_BRACKET_CLOSE){
                        bit_bracketCounter-=1;
                    }
                    *P_t++;
                }
                last_type = 6;
            }
        }


        if (P_t->type == T_BRACKET_OPEN) {
            bracketCounter += 1;
            struct element el_;
            el_.type = EL_BRACKET_OPEN;
            *P_el = el_;
            *P_el++;
        } else if (P_t->type == T_BRACKET_CLOSE && bracketCounter >= 1) {
            struct element el_;
            el_.type = EL_BRACKET_CLOSE;
            *P_el = el_;
            *P_el++;
        } else if (P_t->type == T_BRACKET_CLOSE && bracketCounter == 0 && bit_status == 2) {
            return bool_equal;
            int len_elements = element_size(p_el);
            P_el = p_el;
            for (int i = 0; i < len_elements - 1; i++) {   // NULL
                *P_el++;
            }
            double result = expression_parser(P_el, 0, len_elements, p_val);
            return (double) result;
        } else if (P_t->type == T_BRACKET_CLOSE && bracketCounter == 0 && bit_op == EL_OPNOT) {
            int len_elements = element_size(p_el);
            P_el = p_el;
            for (int i = 0; i < len_elements - 1; i++) {   // NULL
                *P_el++;
            }
            double result = expression_parser(P_el, 0, len_elements, p_val);
            struct element elll;
            elll.type=EL_NUMBER;
            elll.value=(double) calculate_bit(result, 0, bit_op);
            *P_el = elll;
            P_el++;
        } else if (P_t->type == T_OPERATOR) {
            struct element el_;
            el_.type = EL_OPERATOR;
            if (P_t->value == 43) {
                el_.opr = EL_PLUS;
            } else if (P_t->value == 42) {
                el_.opr = EL_MUL;
            } else if (P_t->value == 45) {
                el_.opr = EL_SUB;
            } else if (P_t->value == 38) {
                el_.opr = EL_AND;
            } else if (P_t->value == 124) {
                el_.opr = EL_OR;
            }
            *P_el = el_;
            *P_el++;
        } else if (P_t->type == T_EQUALS) {
            bool_equal = 1;
            struct element el_;
            el_.type = EL_EQUALS;
            *P_el = el_;
            *P_el++;
        }


        last_type = P_t->type == 0 ? last_type : (P_t->type);
        blank = P_t->type == 0 ? 1 : 0;
        *P_t++;
    }

    if (last_type == 2) {
        int var_idx = 0;
        vall = p_val;
        varr = p_var;
        for (int i = 0; i < 128; i++) {
            if (*varr == '\0') {
                strcpy(varr, temp_variable);
                *vall = 0;
                var_idx = i;
                struct element el_;
                el_.type = EL_VARIABLE;
                el_.value = *vall;
                *P_el = el_;
                *P_el++;
                break;
            }
            if (strcmp(varr, temp_variable) == 0) {
                var_idx = i;
                struct element el_;
                el_.type = EL_VARIABLE;
                el_.value = *vall;
                *P_el = el_;
                *P_el++;
                break;
            }
            varr = varr + MAX;
            *vall += 1;
        }

    }
    if (last_type == 1) {
        struct element el_;
        el_.type = EL_NUMBER;
        el_.value = strtod(temp_number, &dt);
        *P_el = el_;
        *P_el++;
    }
    return bool_equal;

}

int element_size(struct element *p_el) {
    struct element *P_el = p_el;
    int counter = 0;
    for (int i = 0; i < MAX; i++) {
        if (P_el->type == 0 && P_el->value == 0) {
            break;
        }
        counter += 1;
        *P_el++;
    }
    return counter;
}


#endif //HW1_PARSER_H
