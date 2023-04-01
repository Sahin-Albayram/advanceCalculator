//
// Created by mestan on 15.03.2023.
//
#ifndef HW1_CALCULATIONS_H
#define HW1_CALCULATIONS_H

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






int add ( int a ,int b){
    return a+b;
}
int multiply(int a ,int b){
    return a*b;
}
int subtract (int a , int b){
    return a - b;
}
int bit_and ( int a ,int b){
    return a & b;
}
int bit_or(int a,int b){
    return a | b;
}
int bit_xor(int a, int b){
    return a ^ b;
}
int bit_shift_left(int a, int b){
    return a<<b;
}
int bit_shift_right(int a,int b){
    return a>>b;
}
int bit_not(int a){
    return ~a;
}
int bit_rotate_right(int a,int b){
    int right_shift = a>>b;
    int rotated_part = a<<(32-b);
    return right_shift | rotated_part;
}
int bit_rotate_left(int a,int b){
    int left_shift = a<<b;
    int rotated_part = a>>(32-b);
    return left_shift | rotated_part;
}


#endif //HW1_CALCULATIONS_H
