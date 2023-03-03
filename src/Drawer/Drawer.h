/*
 * @Author: ccysam
 * @E-Mail: ccysam@hotmail.com
 * @Date: 2022-12-12 08:46:34
 * @LastEditTime: 2022-12-19 19:17:32
 * @Description:
 * @Copyright: Copyright (c) ${now_year} by ccysam, All Rights Reserved.
 */
#pragma once
#ifndef __DRAWER_H_
#define __DRAWER_H_

#include <Utils/EasyGL.hpp>

#include "../Algorithm/Kruskal.h"
#include "../Algorithm/Prim.h"

#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_glfw.h"
#include "../imgui/imgui_impl_opengl3.h"

#include "../AppMvc.h"

using namespace MVC;

class Drawer
{
private:
    typedef struct Node2Draw
    {
        EasyGL2D::Disc NodeCircle;
        EasyGL2D::PicCard NodeIcon;
        std::string Text[2];
        float Position[2] = {0.0};
    } Node2Draw;
    typedef struct Path2Draw
    {
        EasyGL2D::Line PathLine;
        std::string Text;
        float Position[2] = {0.0};
    } Path2Draw;
    EasyGL::Shader drawerShader;
    EasyGL::TextureA IconTerminal;
    EasyGL::TextureA IconBuilding;
    ImGuiWindowFlags tagFlags = 0;
    bool isNodesInitialized = false;
    bool isPathsInitialized = false;
    std::vector<Path2Draw>::iterator it;

    std::vector<Node> Nodes;
    std::vector<Path> Paths;
    std::vector<Node2Draw> Nodes2Draw;
    std::vector<Path2Draw> Paths2Draw;
    std::vector<Path2Draw> AnimationPaths2Draw;

    void DrawText(std::string, ImVec2);

public:
    Drawer();
    bool isAnimationFinished = true;

    void init();
    void drawNodes(bool, bool, bool);
    void drawPaths();
    void drawTexts(bool, bool);
    void setNodes(std::vector<Node>);
    void setPaths(std::vector<Path>);
    void setPaths2Draw(std::vector<Path>);
    void addNode(Node);
    void addPath(Path);
    void updateNodes();
    void updatePaths();
    void clearNodes();
    void clearPaths();
    void playAnimation();
    void Animation();
};

#endif