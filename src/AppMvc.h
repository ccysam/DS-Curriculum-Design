/*
 * @Author: ccysam
 * @E-Mail: ccysam@hotmail.com
 * @Date: 2022-12-18 21:15:45
 * @LastEditTime: 2022-12-18 21:20:01
 * @Description: 
 * @Copyright: Copyright (c) ${now_year} by ccysam, All Rights Reserved. 
 */
/*
 * @Author: ccysam
 * @E-Mail: ccysam@hotmail.com
 * @Date: 2022-12-18 21:15:45
 * @LastEditTime: 2022-12-18 21:17:33
 * @Description:
 * @Copyright: Copyright (c) ${now_year} by ccysam, All Rights Reserved.
 */
#pragma once

#ifndef __MVC__
#define __MVC__

#include <string.h>

namespace MVC
{
    typedef struct Node
    {
        short ID;
        char name[1024];
        int Color;
        int Icon;
        float coord[2];
        Node(short ID, const char *name, int Color, int Icon, float coord[2]);
    } Node;
    typedef struct Path
    {
        int Start, End;
        float weight;
    } Path;
}

#endif