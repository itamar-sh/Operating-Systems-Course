//
// Created by itama on 18/09/2022.
//

#include <cstdlib>
#include <cstdio>
#include "BasicOperation.h"
int main() {
    // basic_lst_manipulation
    int lst1[] = {5 ,4,3,2,1,0,-1,-2};  // init
    int* res1 = basic_lst_manipulation(lst1, 8);
    for (int i = 0; i < 8; i++){
        printf("%d ", res1[i]);  // 25 16 9 4 1 0 1 4
    }
    printf("\n");
    // basic_queue_manipulation
    q_index = 0;
    queue = (void*)malloc(10*sizeof(char));  // 10 chars in queue
    char a = 'a';
    basic_queue_manipulation_push((void*)&a);
    printf("%c", *((char*)basic_queue_manipulation_pop()));  // 'a'
    printf("\n");
}
/** learn about using array of int */
int* basic_lst_manipulation(int* lst, int size){
    int* new_lst = (int *)malloc(sizeof (int)*size);
    for (int i =0 ; i< size; i++){
        *(new_lst+i) = *(lst+i) * *(lst+i);
    }
    return new_lst;
}
/** learn how to use queue with global variables */
void basic_queue_manipulation_push(void* element){
    *((char*)queue+q_index) = *((char*)element);
    q_index += 1;
}
void* basic_queue_manipulation_pop(){
    q_index -= 1;
    return (void*)((char*)queue+q_index);
}

