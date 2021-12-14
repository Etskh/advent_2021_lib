#pragma once

#include <node.h>

namespace types {

enum EDirectionCommand {
    FORWARD,
    UP,
    DOWN,
    UNKNOWN,
};

typedef std::pair<EDirectionCommand, double> CommandLine;

class BingoBoard
{
public:
    int HasWonAt(const std::vector<int>& calledNumbers);

private:
    int matrix[25];
};

class BingoBoardSets
{
public:
    

private:
    std::vector<int> _calledNumbers;
    std::vector<BingoBoard> _boards;
};

}