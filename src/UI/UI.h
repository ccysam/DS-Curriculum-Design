/*
 * @Author: ccysam
 * @E-Mail: ccysam@hotmail.com
 * @Date: 2022-12-06 22:15:55
 * @LastEditTime: 2022-12-19 19:13:44
 * @Description:
 * @Copyright: Copyright (c) ${now_year} by ccysam, All Rights Reserved.
 */
#pragma once
#ifndef __UI_H_
#define __UI_H_

#include <io.h>
#include <Utils/CSVReader.hpp>

#include "../Drawer/Drawer.h"

using namespace MVC;

class UI
{
private:
    EasyGL::Shader GeneralUIShader;
    EasyGL::Texture bgTexture;
    EasyGL::TextureA MainPaneTexture;
    EasyGL::TextureA WorldMapTexture;
    EasyGL2D::PicCard bg;
    EasyGL2D::PicCard MainBG;
    EasyGL2D::PicCard WorldMap;
    EasyGL2D::Rectangle MainPane;
    CSVReader::Table target4Saving;
    bool isDemo = true;
    bool isShowNewFile = false;
    bool isShowQuit = false;
    bool isPaneMain = true;
    bool haveFile = false;
    bool isSaving = false;
    bool isShowIcon = true;
    bool isShowID = false;
    bool isShowName = true;
    bool isPlaying = false;
    char CurrentFileName[256] = "目前没有打开的文件";
    std::vector<Node> NodeList;
    std::vector<Path> PathList;
    float lastTimeSpent = 0.0f;
    float resultWeight = 0.0f;

    void loadStyle();
    void loadMainMenuBar();
    void loadWidgets();
    void crateNewFile(char *filename);
    void LoadDataFolder();
    void OpenFile(const char *filename);
    void SaveCurrentFile();
    float findWeight(int start, int end);

    Drawer drawer;

public:
    void Init(GLFWwindow *);
    void drawBG();
    void drawWidgets();
    void ShowFileMenu();
    void ShowGraphMenu();
    void ShowHelpMenu();
};

#endif