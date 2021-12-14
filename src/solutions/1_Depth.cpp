#include <cstdio>

#include "Solutions.hpp"


/*
To do this, count the number of times a depth measurement increases from the previous measurement. (There is no measurement before the first measurement.) 
*/

double Solutions::getDepth(const std::vector<double>& input)
{
    double lastOne = static_cast<double>(0xFFFFFF);
    double counter = 0;
    for(size_t i=0; i<input.size(); i++)
    {
        if(input[i] > lastOne)
        {
            counter++;
            // printf("%f: (increased)\n", input[i]);
        }
        // else {
            // printf("%f: (decreased)\n", input[i]);
        // }
        lastOne = input[i];
    }

    return counter;
}

double Solutions::getDepthByWindow(const std::vector<double>& input)
{
    double counter = 0;
    double previousSum = 0xFFFFFF;

    for(size_t i=0; i < input.size() - 2; i++)
    {
        double sum = input[i] + input[i + 1] + input[i + 2];
        if(sum > previousSum) {
            counter++;
        }
        previousSum = sum;
    }

    return counter;
}