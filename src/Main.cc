/*
 * @Author: ccysam
 * @E-Mail: ccysam@hotmail.com
 * @Date: 2022-11-24 23:52:10
 * @LastEditTime: 2022-12-12 14:35:02
 * @Description:
 * @Copyright: Copyright (c) 2022 by ccysam, All Rights Reserved.
 */
#include "App.h"


int main(int argc, char **argv)
{
    try
    {
        App::start(argc, argv);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
        return -1;
    }
    return 0;
}