/*
 * @Author: ccysam
 * @E-Mail: ccysam@hotmail.com
 * @Date: 2022-11-24 23:53:29
 * @LastEditTime: 2022-12-18 21:13:50
 * @Description:
 * @Copyright: Copyright (c) 2022 by ccysam, All Rights Reserved.
 */
#pragma once
#ifndef _APP__H_
#define _APP__H_
// Total includes here
#include <iostream>
#include <fstream>
#include <streambuf>

// Local includes here

#include "TestShaders.h"
#include "UI/UI.h"

// Declare marco definations

#define WIDTH 1920
#define HEIGHT 1080

// Declare things

namespace App
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

    // Functions
    void start(int argc, char **argv);
    void framebuffer_size_callback(GLFWwindow *window, int width, int height);
    void processInput(GLFWwindow *window);
    void Render(GLFWwindow *window, int width, int height);
} // namespace App

#endif