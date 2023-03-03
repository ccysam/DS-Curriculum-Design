/*
 * @Author: ccysam
 * @E-Mail: ccysam@hotmail.com
 * @Date: 2022-12-06 22:15:49
 * @LastEditTime: 2022-12-19 19:15:28
 * @Description:
 * @Copyright: Copyright (c) ${now_year} by ccysam, All Rights Reserved.
 */

#include "UI.h"

// namespace UI
// {
//     EasyGL::Shader bgShader;
//     EasyGL::Texture bgTexture;
//     EasyGL2D::PicCard bg;

//     void init(GLFWwindow *window)
//     {
//         // Load Background Image

//         bgShader = EasyGL::Shader("res\\screen.vsh", "res\\CustomColor.fsh");
//         bgTexture = EasyGL::Texture("res\\bg.jpg");
//         bg = EasyGL2D::PicCard(0, 0, 1280, 720);
//         bg.setTexture(bgTexture.create());
//     }

//     void draw()
//     {
//         bg.draw(bgShader.create());
//     }
// }

void UI::Init(GLFWwindow *window)
{
    drawer = Drawer();
    GeneralUIShader = EasyGL::Shader("res\\screen.vsh", "res\\CustomColor.fsh");
    bgTexture = EasyGL::Texture("res\\bg.jpg");
    MainPaneTexture = EasyGL::TextureA("res\\MainBG.png");
    WorldMapTexture = EasyGL::TextureA("res\\WorldMap.png");
    bg = EasyGL2D::PicCard(0, 0, 1920, 1080);
    MainBG = EasyGL2D::PicCard(584, 115, 1280, 826);
    MainBG.setTexture(MainPaneTexture.create());
    WorldMap = EasyGL2D::PicCard(584, 115, 1280, 826);
    WorldMap.setTexture(WorldMapTexture.create());
    bg.setTexture(bgTexture.create());
    MainPane = EasyGL2D::Rectangle(24, 24, 1872, 1032);
    MainPane.setColor("F2F2F2");
    MainPane.setTransparency(0.5);

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void)io;
    // io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    // io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    io.Fonts->AddFontFromFileTTF("res\\SourceHanSansCN-Regular.ttf", 20, NULL, io.Fonts->GetGlyphRangesChineseFull());

    // io.Fonts->AddFontDefault();

    // Setup Dear ImGui style

    ImGui::StyleColorsLight();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");
    bool demo = true;
}

void UI::drawBG()
{
    bg.draw(GeneralUIShader.create());
    MainPane.draw(GeneralUIShader.create());
    if (isPaneMain)
    {
        MainBG.draw(GeneralUIShader.create());
    }
    else
    {
        WorldMap.draw(GeneralUIShader.create());
    }
}

void UI::drawWidgets()
{
    drawer.init();
    drawer.drawPaths();
    drawer.drawNodes(isShowIcon, isShowID, isShowName);
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    // ImGui::ShowDemoWindow(&isDemo);
    drawer.drawTexts(isShowID, isShowName);
    loadStyle();
    loadWidgets();
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void UI::ShowFileMenu()
{

    if (ImGui::MenuItem("新建", "Ctrl+N"))
    {
        isShowNewFile = true;
    }
    if (ImGui::BeginMenu("打开"))
    {
        LoadDataFolder();
        ImGui::EndMenu();
    }
    ImGui::Separator();
    if (ImGui::MenuItem("保存", "Ctrl+S"))
    {
        SaveCurrentFile();
    }
    ImGui::Separator();
    if (ImGui::MenuItem("退出", "Alt+F4"))
    {
        isShowQuit = true;
    }
}

void UI::ShowGraphMenu()
{

    static bool isBlueprint = true;
    static bool isWorldMap = false;
    if (ImGui::MenuItem("显示节点图标", NULL, isShowIcon))
    {
        isShowIcon = isShowIcon ? false : true;
    }
    if (ImGui::MenuItem("显示节点ID", NULL, isShowID))
    {
        isShowID = isShowID ? false : true;
    }
    if (ImGui::MenuItem("显示节点命名", NULL, isShowName))
    {
        isShowName = isShowName ? false : true;
    }
    ImGui::Separator();
    if (ImGui::BeginMenu("当前图类型"))
    {
        if (ImGui::MenuItem("抽象设计图（蓝图背景）", NULL, isBlueprint, isWorldMap))
        {
            isPaneMain = true;
            isBlueprint = true;
            isWorldMap = false;
        }
        if (ImGui::MenuItem("实地规划图（地图背景）", NULL, isWorldMap, isBlueprint))
        {
            isWorldMap = true;
            isPaneMain = false;
            isBlueprint = false;
        }
        ImGui::EndMenu();
    }
}

void UI::ShowHelpMenu()
{
    if (ImGui::MenuItem("帮助", "F1"))
    {
    }
    if (ImGui::MenuItem("关于"))
    {
    }
}

void UI::loadMainMenuBar()
{

    if (ImGui::BeginMenuBar())
    {
        ImGui::SetNextWindowSize(ImVec2(160.0, 0.0));
        if (ImGui::BeginMenu("文件(F)"))
        {
            ShowFileMenu();
            ImGui::EndMenu();
        }
        ImGui::SetNextWindowSize(ImVec2(160.0, 0.0));
        if (ImGui::BeginMenu("图(G)"))
        {
            ShowGraphMenu();
            ImGui::EndMenu();
        }
        ImGui::SetNextWindowSize(ImVec2(160.0, 0.0));
        if (ImGui::BeginMenu("帮助(H)"))
        {
            ShowHelpMenu();
            ImGui::EndMenu();
        }
        ImGui::EndMenuBar();
    }
}

void UI::loadWidgets()
{
    // Main window
    ImGui::SetNextWindowSize(ImVec2(480, 960));
    ImGui::SetNextWindowPos(ImVec2(64, 64));
    ImGuiWindowFlags Main_flags = 0;
    Main_flags |= ImGuiWindowFlags_MenuBar;
    Main_flags |= ImGuiWindowFlags_NoMove;
    Main_flags |= ImGuiWindowFlags_NoTitleBar;
    Main_flags |= ImGuiWindowFlags_NoCollapse;
    Main_flags |= ImGuiWindowFlags_NoResize;
    Main_flags |= ImGuiWindowFlags_NoScrollbar;
    ImGui::Begin("MainPane", NULL, Main_flags);
    loadMainMenuBar();

    // ImGui::AlignTextToFramePadding();
    // ImGui::Text("当前项目名称：");
    // ImGui::SameLine();
    // static char ProjName[256] = "";
    // ImGui::InputText("##ProjName", ProjName, IM_ARRAYSIZE(ProjName));
    // ImGui::SameLine();
    // if (ImGui::Button("确认", ImVec2(48, 0)))
    // {
    //     if (ProjName == "")
    //     {
    //         strcpy(CurrentFileName, "Untitled");
    //         strcpy(ProjName, CurrentFileName);
    //     }
    //     else
    //     {
    //         strcpy(CurrentFileName, ProjName);
    //     }
    // }

    // ImGui::Separator();

    ImGui::AlignTextToFramePadding();
    ImGui::Text("创建节点");
    ImGui::BeginGroup();
    ImGui::AlignTextToFramePadding();
    ImGui::Text("名称：");
    ImGui::SameLine();
    static char NodeName[1024] = "";
    ImGui::InputText("##NodeName", NodeName, IM_ARRAYSIZE(NodeName));
    ImGui::AlignTextToFramePadding();
    ImGui::Text("节点颜色：");
    ImGui::SameLine();
    static const char *NodeColors[] = {"红色", "黄色", "蓝色", "绿色"};
    static int NodeColor_selected = 2;
    ImGui::Combo("##NodeColor", &NodeColor_selected, NodeColors, IM_ARRAYSIZE(NodeColors));

    ImGui::AlignTextToFramePadding();
    ImGui::Text("节点图标：");
    ImGui::SameLine();
    static const char *NodeIcon[] = {"Terminal", "Building"};
    static int NodeIcon_selected = 0;
    ImGui::Combo("##NodeIcon", &NodeIcon_selected, NodeIcon, IM_ARRAYSIZE(NodeIcon));

    static float Coord[2] = {0.0f, 0.0f};
    ImGui::AlignTextToFramePadding();
    ImGui::Text("位置坐标：");
    ImGui::SameLine();
    ImGui::InputFloat2("##NodeCoord", Coord);
    ImGui::EndGroup();
    ImGui::SameLine();
    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.42, 0.840f, 0.55f, 1.0f));
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.557, 0.886f, 0.667f, 1.0f));
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.176f, 0.682f, 0.345f, 1.0f));
    if (ImGui::Button("添加", ImVec2(64, 48)))
    {
        if (NodeName != "" || NodeName == " ")
            NodeList.push_back(Node(NodeList.size(), NodeName, NodeColor_selected, NodeIcon_selected, Coord));
        else
            ImGui::OpenPopup("Failed");
    }
    ImGui::PopStyleColor(3);

    ImGui::Separator();

    ImGui::AlignTextToFramePadding();
    ImGui::Text("创建路径：");
    ImGui::AlignTextToFramePadding();
    ImGui::Text("起点");
    ImGui::SameLine();
    std::string NameString("");
    static int start = 0, end = 0;
    for (Node n : NodeList)
    {
        NameString += n.name;
        NameString += '\0';
    }
    if (!NodeList.empty())
    {
        ImGui::Combo("##PathStart", &start, NameString.c_str());
        ImGui::AlignTextToFramePadding();
        ImGui::Text("终点");
        ImGui::SameLine();
        ImGui::Combo("##PathEnd", &end, NameString.c_str());
    }
    else
    {

        char *EmptyNames[2] = {"\t", "暂无节点"};
        ImGui::Combo("##PathStart", &start, EmptyNames, IM_ARRAYSIZE(EmptyNames));
        ImGui::AlignTextToFramePadding();
        ImGui::Text("终点");
        ImGui::SameLine();
        ImGui::Combo("##PathEnd", &end, EmptyNames, IM_ARRAYSIZE(EmptyNames));
    }
    ImGui::AlignTextToFramePadding();
    ImGui::Text("距离/权重");
    static float weight;
    ImGui::SameLine();
    ImGui::InputFloat("##PathWeight", &weight);
    ImGui::SameLine();
    if (ImGui::Button("添加##Ap", ImVec2(64, 48)))
    {
        bool hasSamePath = false;
        if (start == end)
        {
            ImGui::OpenPopup("SelfWrong");
        }
        else
        {
            for (Path p : PathList)
            {
                if (start == p.Start && end == p.End)
                    hasSamePath = true;
            }
            if (!hasSamePath)
                PathList.push_back({start, end, weight});
            else
                ImGui::OpenPopup("SameWrong");
        }
    }

    ImGui::Separator();

    if (ImGui::Button("删除节点", ImVec2(228, 28)))
    {
        if (!NodeList.empty())
        {
            NodeList.pop_back();
        }
    }
    ImGui::SameLine();
    if (ImGui::Button("删除路径", ImVec2(228, 28)))
    {
        if (!PathList.empty())
        {
            PathList.pop_back();
        }
    }

    // Main table
    static ImGuiTableFlags flags = ImGuiTableFlags_Hideable | ImGuiTableFlags_RowBg | ImGuiTableFlags_BordersOuter | ImGuiTableFlags_BordersV | ImGuiTableFlags_NoBordersInBody | ImGuiTableFlags_ScrollY;
    if (ImGui::BeginTable("MainTable1", 6, flags, ImVec2(0.0f, ImGui::GetTextLineHeightWithSpacing() * 8), 0.0f))
    {
        ImGui::TableSetupColumn("ID");
        ImGui::TableSetupColumn("名称");
        ImGui::TableSetupColumn("图标");
        ImGui::TableSetupColumn("颜色");
        ImGui::TableSetupColumn("坐标X");
        ImGui::TableSetupColumn("坐标Y");
        ImGui::TableHeadersRow();
        if (!NodeList.empty())
        {
            for (Node n : NodeList)
            {
                ImGui::TableNextRow();
                ImGui::TableNextColumn();
                ImGui::Text("%d", n.ID);
                ImGui::TableNextColumn();
                ImGui::Text("%s", n.name);
                ImGui::TableNextColumn();
                if (n.Icon == 0)
                {
                    ImGui::Text("Terminal");
                }
                else
                {
                    ImGui::Text("Building");
                }
                ImGui::TableNextColumn();
                switch (n.Color)
                {
                case 0:
                    ImGui::TextColored(ImVec4(0.99f, 0.827f, 0.882f, 1.0f), "红"); // FDD3E1
                    break;
                case 1:
                    ImGui::TextColored(ImVec4(1.0f, 0.776f, 0.12f, 1.0f), "黄"); // FFC603
                    break;
                case 2:
                    ImGui::TextColored(ImVec4(0.4f, 0.8f, 1.0f, 1.0f), "蓝"); // 66CCFF
                    break;
                case 3:
                    ImGui::TextColored(ImVec4(0.0f, 0.803f, 0.0f, 1.0f), "绿"); // 00CD00
                    break;
                }
                ImGui::TableNextColumn();
                ImGui::Text("%f", n.coord[0]);
                ImGui::TableNextColumn();
                ImGui::Text("%f", n.coord[1]);
            }
        }
        ImGui::EndTable();
    }
    if (ImGui::BeginTable("MainTable2", 3, flags, ImVec2(0.0f, ImGui::GetTextLineHeightWithSpacing() * 14), 0.0f))
    {
        ImGui::TableSetupColumn("起点");
        ImGui::TableSetupColumn("终点");
        ImGui::TableSetupColumn("距离/权重");
        ImGui::TableHeadersRow();
        if (!PathList.empty())
        {
            for (Path p : PathList)
            {
                ImGui::TableNextRow();
                ImGui::TableNextColumn();
                ImGui::Text("%d", p.Start);
                ImGui::TableNextColumn();
                ImGui::Text("%d", p.End);
                ImGui::TableNextColumn();
                ImGui::Text("%f", p.weight);
            }
        }
        ImGui::EndTable();
    }

    ImGui::Separator();

    if (ImGui::Button("绘制", ImVec2(464, 28)))
    {
        if (!NodeList.empty())
        {
            drawer.setNodes(NodeList);
        }
        else
        {
            drawer.clearNodes();
        }
        if (!PathList.empty())
        {
            drawer.setPaths(PathList);
        }
        else
        {
            drawer.clearPaths();
        }
    }

    if (isShowNewFile)
        ImGui::OpenPopup("NewFile");
    if (isShowQuit)
        ImGui::OpenPopup("Quit");

    // Modals

    // NewFile
    ImVec2 center = ImGui::GetMainViewport()->GetCenter();
    ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
    if (ImGui::BeginPopupModal("NewFile", NULL, ImGuiWindowFlags_AlwaysAutoResize))
    {
        ImGui::Text("您将新建一个文件，请在下方输入文件名，当前\n所有数据都将被清空，请做好保存工作，新建的\n文件将会保存在软件根目录的data文件夹下");
        ImGui::Text("文件名");
        static char filename[256] = "";
        ImGui::InputText(".csv", filename, 256);
        ImGui::Separator();
        if (ImGui::Button("OK", ImVec2(120, 0)))
        {

            if (!isSaving)
            {
                crateNewFile(filename);
            }
            else
            {
                std::string file("data\\");
                file += CurrentFileName;
                CSVReader::Write(file.c_str(), target4Saving);
                target4Saving.clear();
                isSaving = false;
            }
            isShowNewFile = false;
            ImGui::CloseCurrentPopup();
        }
        ImGui::SameLine();
        if (ImGui::Button("Cancel", ImVec2(120, 0)))
        {
            isShowNewFile = false;
            ImGui::CloseCurrentPopup();
        }
        ImGui::EndPopup();
    }

    // Quit
    ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
    if (ImGui::BeginPopupModal("Failed", NULL, ImGuiWindowFlags_AlwaysAutoResize))
    {
        ImGui::Text("添加失败，请不要留有空数据！");
        ImGui::Text("##Space1 \t\t");
        ImGui::SameLine();
        if (ImGui::Button("OK", ImVec2(100, 24)))
        {
            ImGui::CloseCurrentPopup();
        }
        ImGui::EndPopup();
    }

    // Self Wrong
    ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
    if (ImGui::BeginPopupModal("SelfWrong", NULL, ImGuiWindowFlags_AlwaysAutoResize))
    {
        ImGui::Text("请不要再无向图中添加指向自己的路径");
        ImGui::Text(" \t\t##Space2");
        ImGui::SameLine();
        if (ImGui::Button("OK", ImVec2(100, 24)))
        {
            ImGui::CloseCurrentPopup();
        }
        ImGui::EndPopup();
    }

    // Same Wrong
    ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
    if (ImGui::BeginPopupModal("SameWrong", NULL, ImGuiWindowFlags_AlwaysAutoResize))
    {
        ImGui::Text("这条路径已经添加过了");
        ImGui::Text(" \t\t##Space2");
        ImGui::SameLine();
        if (ImGui::Button("OK", ImVec2(100, 24)))
        {
            ImGui::CloseCurrentPopup();
        }
        ImGui::EndPopup();
    }

    // Failed to Add
    ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
    if (ImGui::BeginPopupModal("Quit", NULL, ImGuiWindowFlags_AlwaysAutoResize))
    {
        ImGui::Text("确认要退出吗，所有未保存的更改都会丢失！");
        ImGui::Separator();
        if (ImGui::Button("Yes", ImVec2(120, 0)))
        {
            exit(0);
        }
        ImGui::SameLine();
        if (ImGui::Button("No", ImVec2(120, 0)))
        {
            isShowQuit = false;
            ImGui::CloseCurrentPopup();
        }
        ImGui::EndPopup();
    }

    ImGui::End();

    // TitleBar
    ImGui::SetNextWindowSize(ImVec2(1280, 32));
    ImGui::SetNextWindowPos(ImVec2(584, 64));
    ImGuiWindowFlags Title_flags = 0;
    Title_flags |= ImGuiWindowFlags_NoMove;
    Title_flags |= ImGuiWindowFlags_NoTitleBar;
    Title_flags |= ImGuiWindowFlags_NoCollapse;
    Title_flags |= ImGuiWindowFlags_NoResize;
    Title_flags |= ImGuiWindowFlags_NoScrollbar;
    // Title_flags |= ImGuiWindowFlags_NoScrollWithMouse;
    ImGui::SetNextWindowScroll(ImVec2(0, 1.0f));
    ImGui::Begin("TitleBar", NULL, Title_flags);
    ImGui::SetNextWindowSize(ImVec2(1280, 18));
    if (ImGui::BeginTable("TitleTable", 3))
    {
        ImGui::TableNextRow();
        ImGui::TableSetColumnIndex(0);
        ImGui::TextUnformatted("");
        ImGui::TableSetColumnIndex(1);
        ImGui::TextUnformatted(CurrentFileName);
        ImGui::TableSetColumnIndex(2);
        ImGui::TextUnformatted("");
        ImGui::EndTable();
    }
    ImGui::End();

    // DrawBar
    ImGui::SetNextWindowSize(ImVec2(939, 64));
    ImGui::SetNextWindowPos(ImVec2(584, 960));
    ImGuiWindowFlags Draw_flags = 0;
    Draw_flags |= ImGuiWindowFlags_NoMove;
    Draw_flags |= ImGuiWindowFlags_NoTitleBar;
    Draw_flags |= ImGuiWindowFlags_NoCollapse;
    Draw_flags |= ImGuiWindowFlags_NoResize;
    Draw_flags |= ImGuiWindowFlags_NoScrollbar;
    Draw_flags |= ImGuiWindowFlags_NoScrollWithMouse;
    ImGui::Begin("DrawBar", NULL, Draw_flags);
    const char *Algorithms[2] = {"Kruskal", "Prim"};
    static int Algorithm_selected = 0;
    ImGui::BeginGroup();
    ImGui::Text("请选择使用的算法：");
    ImGui::Combo("\t", &Algorithm_selected, Algorithms, IM_ARRAYSIZE(Algorithms));
    ImGui::EndGroup();
    ImGui::SameLine();
    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.427, 0.850f, 0.569f, 1.0f));
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.557, 0.886f, 0.667f, 1.0f));
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.176f, 0.682f, 0.345f, 1.0f));
    if (ImGui::Button("计算并绘制(Enter)", ImVec2(160, 48)))
    {
        if (Algorithm_selected == 0)
        {
            Kruskal::Algorithm al_kr(NodeList.size(), PathList.size());
            for (Path p : PathList)
            {
                al_kr.addEdge(p.Start, p.End, p.weight);
            }
            Algorithm::MST r = al_kr.getResult();
            std::vector<Path> MSTPath;
            std::vector<std::pair<Algorithm::int_pair, float>>::iterator it;
            for (it = r.Paths.begin(); it != r.Paths.end(); it++)
            {
                MSTPath.push_back({it->first.first, it->first.second, it->second});
            }
            lastTimeSpent = al_kr.time_spend;
            resultWeight = r.Weight;
            drawer.clearPaths();
            drawer.playAnimation();
            drawer.setPaths2Draw(MSTPath);
            isPlaying = true;
        }
        if (Algorithm_selected == 1)
        {
            Prim::Algorithm al_pr(NodeList.size(), PathList.size());
            for (Path p : PathList)
            {
                al_pr.addEdge(p.Start, p.End, p.weight);
            }
            Algorithm::MST r = al_pr.getResult();
            std::vector<Path> MSTPath;
            std::vector<std::pair<Algorithm::int_pair, float>>::iterator it;
            float weight = 0.0f;
            for (it = r.Paths.begin(); it != r.Paths.end(); it++)
            {
                MSTPath.push_back({it->first.first, it->first.second, findWeight(it->first.first, it->first.second)});
                weight += findWeight(it->first.first, it->first.second);
            }
            lastTimeSpent = al_pr.time_spend;
            resultWeight = weight;
            drawer.clearPaths();
            drawer.playAnimation();
            drawer.setPaths2Draw(MSTPath);
            isPlaying = true;
        }
    }
    if (isPlaying)
    {
        drawer.Animation();
        if (drawer.isAnimationFinished)
            isPlaying = false;
    }
    ImGui::PopStyleColor(3);
    ImGui::SameLine();
    ImGui::Text("消耗时间: %.3f ms\nMST总权重: %.3f", lastTimeSpent, resultWeight);
    ImGui::End();
}

void UI::crateNewFile(char *filename)
{
    NodeList.clear();
    PathList.clear();
    std::string file = std::string(filename) + ".csv";
    std::string command = "copy /Y res\\Template.csv data\\" + file;
    system("chcp 65001");
    system(command.c_str());
    strcpy(CurrentFileName, file.c_str());
    haveFile = true;
}

void UI::LoadDataFolder()
{
    std::vector<std::string> files;
    long handle;
    struct _finddata_t fileinfo;
    handle = _findfirst("data\\*.csv", &fileinfo);
    if (-1 == handle)
    {
        ImGui::MenuItem("暂无文件");
        return;
    }
    do
    {
        files.push_back(fileinfo.name);
    } while (!_findnext(handle, &fileinfo));
    _findclose(handle);
    for (std::string file : files)
    {
        if (ImGui::MenuItem(file.c_str()))
        {
            OpenFile(file.c_str());
        }
    }
}

void UI::OpenFile(const char *filename)
{
    strcpy(CurrentFileName, filename);
    CSVReader::Table fileContent;
    std::string path = "data\\" + std::string(filename);
    fileContent = CSVReader::Read(path.c_str());
    PathList.clear();
    for (int i = 7; i < fileContent.size(); i++)
    {
        PathList.push_back({atoi(fileContent[i][1].c_str()), atoi(fileContent[i][2].c_str()), (float)atof(fileContent[i][3].c_str())});
    }
    NodeList.clear();
    for (int i = 1; i <= fileContent[0].size() - 1; i++)
    {
        float coord[2] = {(float)atof(fileContent[2][i].c_str()), (float)atof(fileContent[3][i].c_str())};
        NodeList.push_back(Node((short)atoi(fileContent[0][i].c_str()), fileContent[1][i].c_str(), atoi(fileContent[5][i].c_str()), atoi(fileContent[4][i].c_str()), coord));
    }
    haveFile = true;
}

void UI::SaveCurrentFile()
{
    // CSVReader::Table target;
    // std::string path = "res\\Template.csv";
    // target = CSVReader::Read(path.c_str());
    // PathList.clear();
    // for (int i = 7; i < target.size(); i++)
    // {
    //     PathList.push_back({atoi(target[i][1].c_str()), atoi(target[i][2].c_str()), (float)atof(target[i][3].c_str())});
    // }
    std::string tags[10] = {"Cities ID", "Cities", "CoordX", "CoordY", "Icon", "Color", "Path", "Start", "End", "Weight"};
    CSVReader::Table target;
    // target[0][0] = tags[0];
    target.push_back({tags[0]});
    // target[1][0] = tags[1];
    target.push_back({tags[1]});
    // target[2][0] = tags[2];
    target.push_back({tags[2]});
    // target[3][0] = tags[3];
    target.push_back({tags[3]});
    // target[4][0] = tags[4];
    target.push_back({tags[4]});
    // target[5][0] = tags[5];
    target.push_back({tags[5]});
    // target[6][0] = tags[6];
    target.push_back({tags[6]});
    // target[6][1] = tags[7];
    target[6].push_back(tags[7]);
    // target[6][2] = tags[8];
    target[6].push_back(tags[8]);
    // target[6][3] = tags[9];
    target[6].push_back(tags[9]);
    for (int i = 1; i <= target[0].size() - 1; i++)
    {
        float coord[2] = {(float)atof(target[2][i].c_str()), (float)atof(target[3][i].c_str())};
        NodeList.push_back(Node((short)atoi(target[0][i].c_str()), target[1][i].c_str(), atoi(target[5][i].c_str()), atoi(target[4][i].c_str()), coord));
    }
    for (Node n : NodeList)
    {
        target[0].push_back(std::to_string(n.ID));
        target[1].push_back(std::string(n.name));
        target[2].push_back(std::to_string(n.coord[0]));
        target[3].push_back(std::to_string(n.coord[1]));
        target[4].push_back(std::to_string(n.Icon));
        target[5].push_back(std::to_string(n.Color));
    }
    int i = 0;
    for (Path p : PathList)
    {
        target.push_back({std::to_string(i), std::to_string(p.Start), std::to_string(p.End), std::to_string(p.weight)});
    }
    if (haveFile)
    {
        std::string file("data\\");
        file += CurrentFileName;
        CSVReader::Write(file.c_str(), target);
    }
    else
    {
        target4Saving.clear();
        target4Saving = target;
        isSaving = true;
        isShowNewFile = true;
    }
}

float UI::findWeight(int start, int end)
{
    for (Path p : PathList)
    {
        if (p.Start == start && p.End == end)
            return p.weight;
    }
    return -1.0;
}

void UI::loadStyle()
{
    ImGuiStyle &style = ImGui::GetStyle();

    // Sizes
    style.WindowBorderSize = 0.0f;
    style.ChildBorderSize = 1.0f;
    style.PopupBorderSize = 0.0f;
    style.FrameBorderSize = 0.0f;
    style.TabBorderSize = 0.0f;
    style.IndentSpacing = 4.0f;
    style.WindowRounding = 8.0f;
    style.ChildRounding = 8.0f;
    style.FrameRounding = 8.0f;
    style.PopupRounding = 4.0f;
    style.ScrollbarRounding = 8.0f;
    style.GrabRounding = 8.0f;
    style.LogSliderDeadzone = 2.0f;
    style.TabRounding = 8.0f;
    style.WindowPadding = ImVec2(8.0f, 8.0f);
    style.FramePadding = ImVec2(4.0f, 4.0f);
    style.ScrollbarSize = 16.0f;

    // Colors
    style.Colors[2] = ImVec4(0.95f, 0.95f, 0.95f, 0.75f);
    style.Colors[4] = ImVec4(1.0f, 1.0f, 1.0f, 0.9f);
    style.Colors[7] = ImVec4(1.0f, 1.0f, 1.0f, 0.75f);
    style.Colors[10] = ImVec4(0.95f, 0.95f, 0.95f, 0.5f);
    style.Colors[11] = ImVec4(1.0f, 1.0f, 1.0f, 0.75f);
    style.Colors[13] = ImVec4(1.0f, 1.0f, 1.0f, 0.5f);
}
