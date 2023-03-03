/*
 * @Author: ccysam
 * @E-Mail: ccysam@hotmail.com
 * @Date: 2022-12-18 13:05:44
 * @LastEditTime: 2022-12-18 13:07:55
 * @Description:
 * @Copyright: Copyright (c) ${now_year} by ccysam, All Rights Reserved.
 */
#include "Algorithm.h"

namespace Algorithm
{
    Result::Result(int NodeCount, int PathCount)
    {
        this->NodeCount = NodeCount;
        this->PathCount = PathCount;
        Weight = 0;
    }

    void Result::setPaths(std::vector<std::pair<int_pair, float>> Paths)
    {
        this->Paths = Paths;
    }
}