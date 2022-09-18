//
// Created by itama on 18/09/2022.
//

#ifndef OPERATING_SYSTEMS_COURSE_HUJI_67808_BASICOPERATION_H
#define OPERATING_SYSTEMS_COURSE_HUJI_67808_BASICOPERATION_H
/**
 * Gets list of int, return new list with squared value of the int.
 * Use of malloc.
 */
int* basic_lst_manipulation(int* lst, int size);
void* queue;
int q_index;
void basic_queue_manipulation_push(void* element);
void* basic_queue_manipulation_pop();

#endif //OPERATING_SYSTEMS_COURSE_HUJI_67808_BASICOPERATION_H
