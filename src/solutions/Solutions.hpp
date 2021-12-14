#pragma once

#include <vector>
#include <string>

#include "../Types.hpp"

namespace Solutions {
    // 1
    double getDepth(const std::vector<double>& input);
    double getDepthByWindow(const std::vector<double>& input);

    // 2
    double getPositionProduct(const std::vector<types::CommandLine>& input);
    double getPositionWithAim(const std::vector<types::CommandLine>& input);

    // 3
    double getBitAverageThing(const std::vector<int>& input);

    // 4
    double getWinningBingoBoard(const types::BingoBoardSets& boards);
};