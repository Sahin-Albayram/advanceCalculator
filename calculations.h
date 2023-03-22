//
// Created by mestan on 15.03.2023.
//

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
#ifndef HW1_CALCULATIONS_H
#define HW1_CALCULATIONS_H

#endif //HW1_CALCULATIONS_H
