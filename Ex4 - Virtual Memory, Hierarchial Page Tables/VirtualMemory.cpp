//
// Created by diama on 17/05/2022.
//

#include <cstdio>
#include "VirtualMemory.h"
#include "PhysicalMemory.h"
#include <cstdlib> //todo check if ok to use


// helper functions
uint64_t get_part_address(int i, uint64_t address);

uint64_t findFrame(uint64_t cur_table, int cur_depth);

int legalAddress(uint64_t address);

uint64_t findEmptyTable(uint64_t full_way_address, uint64_t cur_table, int cur_depth, uint64_t virtualAddress
                        ,int* is_empty);

bool notPartOfVirtualAdderess(uint64_t cur_address, uint64_t cur_virtualAddress, int cur_depth);

uint64_t findMaxIndex(uint64_t cur_table, int cur_depth, int biggest_frame);

uint64_t findPageToSwap(uint64_t full_way_address_without_offset, uint64_t cur_table, int cur_depth,
                        uint64_t virtualAddress);

int get_value_of_full_way_address(uint64_t full_way_address);

void resetFrame(uint64_t frame_index);

bool notPartOfAdderess(uint64_t virtualAddress, int temp_address, int cur_depth);

/**
 * "According to this design, VMInitialize() only has to clear frame 0" (last row in page 4 of the exrecise)
 */
void VMinitialize(){
    for (uint64_t i = 0; i < PAGE_SIZE; i++){
        PMwrite(i, 0);
    }
}

uint64_t get_table_to_read_or_write(uint64_t virtualAddress){
    word_t last_address = 0;
    word_t cur_address = 0;
    // run on each table and get the next table
    for (uint64_t i = 0; i < TABLES_DEPTH; i++){
        uint64_t part_address = get_part_address(i, virtualAddress);
        PMread(last_address + part_address, &cur_address);
        /**
        "Now, if during any step of the translation we reach a row that contains the number 0, we
        know that this is not a real frame index and we have reached a page fault". (last paragraph in page 3 of the exrecise)
        */
        if(cur_address == 0){
            //frame = pageFault(last_address, virtualAddress);
            uint64_t frame_address = findFrame(virtualAddress, i);
            if (frame_address == 0){
                return 0;
            }
            // we want to restore only the page himself and only in the end of the recursion
            if(i == TABLES_DEPTH-1){
                PMrestore(frame_address, virtualAddress >> OFFSET_WIDTH); // todo check correctness
            }
            PMwrite(last_address + part_address, frame_address);
            cur_address = frame_address;
        }
        last_address = cur_address*PAGE_SIZE;

    }
    return last_address;
}


int VMread(uint64_t virtualAddress, word_t* value){
    if (legalAddress(virtualAddress) == 0){
        return 0;
    }
    uint64_t last_address = get_table_to_read_or_write(virtualAddress);
    // cur_address holds the info off the page himself to read from
    uint64_t part_address = get_part_address(TABLES_DEPTH, virtualAddress);
    PMread(last_address + part_address , value);
    return 1;
}

int VMwrite(uint64_t virtualAddress, word_t value){
    if (legalAddress(virtualAddress) == 0){
        return 0;
    }
    uint64_t last_address = get_table_to_read_or_write(virtualAddress);
    // cur_address holds the info off the page himself to read from
    uint64_t part_address = get_part_address(TABLES_DEPTH, virtualAddress);
    PMwrite(last_address + part_address , value);
    return 1;
}

/**
 * Legal address will be: (1) - in the length by bits of VIRTUAL_ADDRESS_WIDTH
 *                        (2) - # todo
 * @param address
 * @return
 */
int legalAddress(uint64_t address) {
    uint64_t address_shifted_right = address >> VIRTUAL_ADDRESS_WIDTH;
    return address_shifted_right == 0;
}

/**
 * We try to find a free frame.
 * There is free frame: we ??
 * There isn't free frame: we evict a frame already chosen as min_helpful_frame.
 * @param table_depth
 * @return
 */
uint64_t findFrame(uint64_t virtualAddress, int cur_depth) {
    int is_empty = 0;
    // find empty - send the address of the main table(0) the depth of the main table(0) and our address(third argument)
    uint64_t empty_table_index = findEmptyTable(0, 0, 0, virtualAddress, &is_empty);
    if(empty_table_index != 0){
        return empty_table_index;
    }
    uint64_t max_index = findMaxIndex(0, 0, 0);
    if(max_index != NUM_FRAMES-1){
        if (cur_depth != TABLES_DEPTH-1) {
            for (uint64_t i = 0; i < PAGE_SIZE; i++) {
                PMwrite((max_index + 1) * PAGE_SIZE + i, 0);
            }
        }
        return max_index + 1;
    }
    uint64_t address_of_page_to_swap_index = findPageToSwap(0, 0,0, virtualAddress);
    int page_to_swap_index  = get_value_of_full_way_address(address_of_page_to_swap_index);
    PMevict(page_to_swap_index , address_of_page_to_swap_index); //todo not sure
    resetFrame(page_to_swap_index);
    return page_to_swap_index;
}

/**
 * return the biggest address in the physical memory that have a pointer to him.
 * @param cur_table
 * @param cur_depth
 * @param biggest_frame
 * @return
 */
uint64_t findMaxIndex(uint64_t cur_table, int cur_depth, int biggest_frame) {
    // condition for the end of the recursion - it's a page and not a table. (page its one level beyond all the tables)
    if (cur_depth == (TABLES_DEPTH)) {
        return cur_table;
    }
    int temp_address = 0;
    for (int i = 0; i < PAGE_SIZE; i++) {
        PMread(cur_table*PAGE_SIZE + i, &temp_address);
        if (temp_address != 0) {
            if (temp_address > biggest_frame){
                biggest_frame = temp_address;
            }
            // go inside to the next sub-table and find max table there
            int temp_frame = findMaxIndex(temp_address, cur_depth + 1, biggest_frame);
            if (temp_frame > biggest_frame){
                biggest_frame = temp_frame;
            }
        }
    }
    return biggest_frame;
}

/**
 * We want to return the index of the frame of the page with the maximum cyclic distance from virtualAddress.
 * First: we
 * @param full_way_address_without_offset - An address of 16 bits (VM width - page width) - representing the current
 * address we run on without the last 4 digits.
 * @param cur_table - the address of the current table we run on.
 * @param cur_depth - the depth of the current table we run on.
 * @param virtualAddress  - the address we want to read or write from, using the frame we will find.
 * @return the VM address of the page to swap
 */
uint64_t findPageToSwap(uint64_t full_way_address_without_offset, uint64_t cur_table, int cur_depth, uint64_t virtualAddress) {
    //  in case we get a page - we return his address without the last 4 digits
    if (cur_depth == (TABLES_DEPTH)) {
        //return the value in the cur_depth
        return full_way_address_without_offset;
    }
    // we use 'temp_full_way_address' for the exact address
    uint64_t temp_full_way_address = 0;

    int temp_address = 0; // Address we will use to get deeper inside the table.
    uint64_t virtualAddressWithoutOffset =  virtualAddress >> OFFSET_WIDTH;
    uint64_t biggest_distance = 0;
    uint64_t address_of_biggest_distance = 0;
    // In this loop we run on each son of the table. temp_full_way_address will give us what we need to calculate min
    for (int i = 0; i < PAGE_SIZE; i++) {
        PMread(cur_table + i, &temp_address);
        if (temp_address != 0) {
            temp_full_way_address = (full_way_address_without_offset << OFFSET_WIDTH) + i;
            // go inside to the next sub-table uif go to the finish depth get the value and check if is bigger
            uint64_t temp_full_way_address_without_offset = findPageToSwap(temp_full_way_address,
                                                             temp_address*PAGE_SIZE, cur_depth + 1,
                                                             virtualAddress);

            //check if this is real address or empty table(the table that call to this function)
            if (temp_full_way_address_without_offset != 0 || notPartOfAdderess(virtualAddress, temp_address,cur_depth)){
                // check min of distance of the current son
                uint64_t second_value = abs(virtualAddressWithoutOffset - temp_full_way_address_without_offset);
                uint64_t first_value = NUM_PAGES - second_value;
                uint64_t candidate_for_biggest_address = 0;
                if (first_value > second_value){
                    candidate_for_biggest_address = second_value;
                }
                else {
                    candidate_for_biggest_address = first_value;
                }
                //check if the distance is bigger than the biggest_distance
                if (candidate_for_biggest_address > biggest_distance) {
//                    if(cur_depth == 0){
//                        temp_full_way_address_without_offset << OFFSET_WIDTH;
//                    }
                    biggest_distance = candidate_for_biggest_address;
                    address_of_biggest_distance = temp_full_way_address_without_offset;
                }
            }
        }
    }
    // in case of main table - we want to translate the answer to the address
    // for this we need 1: to add some offset for the final answer
    //                  2: convert the instruction in binary to pointer for address
//    if(cur_depth == 0){
//        address_of_biggest_distance = address_of_biggest_distance << OFFSET_WIDTH;
//    }
    return address_of_biggest_distance;
}

//for page swap check if the table is in the way that we create now
bool notPartOfAdderess(uint64_t virtualAddress, int temp_address, int cur_depth) {
    int offset_in_table;
    int value_in_the_table = 0;
    for (int i = 0; i < cur_depth + 1; i++){
        offset_in_table = get_part_address(i, virtualAddress);
        PMread(value_in_the_table*PAGE_SIZE + offset_in_table, &value_in_the_table);
    }
    if (value_in_the_table == temp_address){
        return false;
    }
    return true;
}

int get_value_of_full_way_address(uint64_t full_way_address){
    int offset_in_table;
    int value_in_the_table = 0;
    int value_to_remove = 0;
    full_way_address = full_way_address << OFFSET_WIDTH;
    //get the address + and the offset and read the next address and in the last time
    //read the value
    for (int i =0; i < TABLES_DEPTH; i++){
        offset_in_table = get_part_address(i, full_way_address);
        PMread(value_in_the_table*PAGE_SIZE + offset_in_table, &value_in_the_table);
        if (i == (TABLES_DEPTH-2)){
            value_to_remove = value_in_the_table;
        }
    }
    PMwrite(value_to_remove*PAGE_SIZE + offset_in_table, 0);
    return value_in_the_table;
}


/**
 * we want to take the i'th interval of bits that decide the current table.
 * @param i int from 0 to TABLES_DEPTH. when 0 is the main table and TABLES_DEPTH is the a word in a page.
 * @param address
 * @return
 */
uint64_t get_part_address(int i, uint64_t address) {
    uint64_t cur_value = address;
    int to_shift_right = (TABLES_DEPTH - i) * OFFSET_WIDTH ;
    cur_value = cur_value >> to_shift_right;
    cur_value = cur_value & (PAGE_SIZE -1);
    return cur_value;
}

/**
 * We try to find a table that his all entries are 0.
 * case 1: all my child's are 0. I return 1;
 * case 2: my own child is an empty table. I got 1 from FindEmptyTable and return the address of my child.
 * case 3: my grandchild is an empty table. I got an address from FindEmptyTable and return it.
 * case 4: I'm a page. I return -1. I'm not empty table.
 * case 5: My own child is a page. I got -1 from FindEmptyTable. I will ignore it and check my other childs.
 * case 6: None of my childs are empty tables but I'm not an empty table. I return -1.
 *
 * @param table_depth
 * @return pointer to the new empty frame
 * or -1 if there isn't an empty table.
 */
uint64_t findEmptyTable(uint64_t full_way_address, uint64_t cur_table, int cur_depth, uint64_t virtualAddress,
                        int* is_empty) {
    // condition for the end of the recursion - it's a page and not a table.
    if (cur_depth == (TABLES_DEPTH)) {
        return 0;
    }
    bool is_empty_table = true;
    uint64_t new_frame;
    int temp_address = 0;
    for (int i = 0; i < PAGE_SIZE; i++) {
        PMread(cur_table + i, &temp_address);
        if (temp_address != 0) {
            is_empty_table = false;
            // go inside to the next sub-table and find empty table there
//            full_way_address = (full_way_address << OFFSET_WIDTH) + i;
            new_frame = findEmptyTable((full_way_address << OFFSET_WIDTH) + i, temp_address*PAGE_SIZE,
                                       cur_depth + 1, virtualAddress, is_empty);
            // we found an empty table and is not part of our virtual address
            if (new_frame != 0 || *is_empty == 1) {
                // case 1: the son is the empty table
                if (*is_empty == 1) {
                    if (notPartOfVirtualAdderess((full_way_address << OFFSET_WIDTH) + i, virtualAddress,cur_depth+1)){
                        PMwrite(cur_table + i, 0); // delete from memory
                        new_frame = temp_address; // this is the location of the empty table in the RAM

                    }
                    else{
                        *is_empty = 0;
                        new_frame = 0;
                        continue;
                    }
                    *is_empty = 0;
                }
                return new_frame;
            }
        }
    }
    if (is_empty_table && cur_depth != 0) {
        *is_empty = 1;
    }
    return 0;
}

bool notPartOfVirtualAdderess(uint64_t full_way_address, uint64_t virtualAddress, int cur_depth){
    uint64_t first_result ;
    uint64_t sec_result;
    for (int i =0; i < cur_depth; i++){
        first_result = get_part_address(i, virtualAddress);
        sec_result = (full_way_address >> (OFFSET_WIDTH*(cur_depth - i - 1))) & (PAGE_SIZE -1);
        if (first_result != sec_result){
            return true;
        }
    }
    return false;
}

void resetFrame(uint64_t frame_index) {
    for(int i = 0; i < PAGE_SIZE;i++){
        PMwrite(frame_index*PAGE_SIZE + i, 0);
    }
}
//min(65536 - |61440 - x|, |61440 - x|);

// 960 =          0000 0011 1100 0000

// 4096 =         0001 0000 0000 0000
// 8192 =         0010 0000 0000 0000
//12288 =         0011 0000 0000 0000
//16384 =         0100 0000 0000 0000
//20480 =         0101 0000 0000 0000
//28762 =         0111 0000 0000 0000
//32768 =         1000 0000 0000 0000
//36864 =         1001 0000 0000 0000  - best from 61440

//61440 =         1111 0000 0000 0000

// 65536  =  0001 0000 0000 0000 0000
// 131072 =  0010 0000 0000 0000 0000
// 262144 =  0100 0000 0000 0000 0000
// 524288 =  1000 0000 0000 0000 0000

// 983040 =  1111 0000 0000 0000 0000

