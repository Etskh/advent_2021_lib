#include "Solutions.hpp"


double Solutions::getBitAverageThing(const std::vector<int>& input)
{
    int gamma = 0;
    int epsilon = 0;
    int largestValue = 0;
    for(size_t b=0; b < sizeof(int)*8 - 1; b++)
    {
        int totalBits = 0;
        int currentBit = (1 << b);
        for(size_t i=0; i<input.size(); i++)
        {
            // Save the largest value
            if(input[i] > largestValue)
            {
                largestValue = input[i];
            }

            // Is the bit set in this number
            if( input[i] & currentBit)
            {
                totalBits += 1;
            }
        }

        // Now that we've gone through the array, we can leave when no numbers
        // are as big as the currentBit (eg: b10000 vs b01011)
        if(largestValue < currentBit) {
            break;
        }

        // If the total bits in this column is bigger than half, then
        // we have the most bits in this column
        if(totalBits > input.size() / 2)
        {
            gamma += currentBit;
            printf("        Column %d is bigger than half, adding %d to gamma\n", b, currentBit);
        }
        else
        {
            epsilon += currentBit;
            printf("        Column %d is smaller than half, adding %d to epsilon\n", b, currentBit);
        }
    }
    printf("        gamma:%d    epsilon:%d\n", gamma, epsilon);

    return gamma * epsilon;
}