/*
 * @Author: ccysam
 * @E-Mail: ccysam@hotmail.com
 * @Date: 2022-12-18 13:03:34
 * @LastEditTime: 2022-12-19 16:06:42
 * @Description:
 * @Copyright: Copyright (c) ${now_year} by ccysam, All Rights Reserved.
 */
#pragma once
#ifndef __AGM_H_
#define __AGM_H_

#include <vector>
#include <time.h>

namespace Algorithm
{
    // Define of integer pair for quick use
    typedef std::pair<int, int> int_pair;

    // Structure of the Result returned to the Application
    typedef struct Result
    {
        int NodeCount;
        int PathCount;
        float Weight;
        std::vector<std::pair<int_pair, float>> Paths;

        Result() {}

        // Constructor
        Result(int NodeCount, int PathCount);

        // Functions

        // Set the paths
        void setPaths(std::vector<std::pair<int_pair, float>> Paths);

    } MST, Graph2Show;
}

#endif