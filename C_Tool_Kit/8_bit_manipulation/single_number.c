int singleNumber(int* nums, int numsSize) {
    int bits_array[32];
    for (int num_index = 0; num_index < numsSize; num_index++) {
        long up_bit = 1;
        for (int bit_index = 0; bit_index < 32; bit_index++) {
            if (up_bit & nums[num_index]) {
                bits_array[bit_index]++;
            }
            up_bit = up_bit << 1;
        }
    }
    long up_bit = 1;
    int result = 0;
    for (int bit_index = 0; bit_index < 32; bit_index++) {
        result += up_bit * (bits_array[bit_index] % 3);
        up_bit = up_bit << 1;
    }
    return result;
}