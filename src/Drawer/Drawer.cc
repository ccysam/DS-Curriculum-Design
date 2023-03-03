/*
 * @Author: ccysam
 * @E-Mail: ccysam@hotmail.com
 * @Date: 2022-12-12 08:46:54
 * @LastEditTime: 2022-12-19 19:32:47
 * @Description:
 * @Copyright: Copyright (c) ${now_year} by ccysam, All Rights Reserved.
 */

#include "Drawer.h"

void Drawer::init()
{

    // Initialize Nodes
    if (!isNodesInitialized && (!Nodes.empty()))
    {
        for (Node node : Nodes)
        {
            EasyGL2D::Disc disc(node.coord[0] + 584.0, node.coord[1] + 115.0, 36);
            switch (node.Color)
            {
            case 0:
                disc.setColor("FDD3E1");
                break;
            case 1:
                disc.setColor("FFC603");
                break;
            case 2:
                disc.setColor("66CCFF");
                break;
            case 3:
                disc.setColor("00CD00");
                break;
            }
            EasyGL2D::PicCard icon(node.coord[0] - 24.0 + 584.0, node.coord[1] - 24.0 + 115.0, 48.0, 48.0);
            switch (node.Icon)
            {
            case 0:
                icon.setTexture(IconTerminal.create());
                break;
            case 1:
                icon.setTexture(IconBuilding.create());
                break;
            }
            Nodes2Draw.push_back({disc, icon, {std::string(node.name), std::to_string(node.ID)}, {(node.coord[0] + 584.0f), (node.coord[1] + 115.0f)}});
        }
        isNodesInitialized = true;
    }
    // Initialize Paths
    if (!isPathsInitialized && (!Paths.empty()))
    {
        for (Path path : Paths)
        {
            EasyGL2D::Line line(Nodes[path.Start].coord[0] + 584.0f, Nodes[path.Start].coord[1] + 115.0f, Nodes[path.End].coord[0] + 584.0f, Nodes[path.End].coord[1] + 115.0f, 2.0f);
            line.setColor("FFFF00");
            float x = (Nodes[path.Start].coord[0] + Nodes[path.End].coord[0]) / 2.0;
            float y = (Nodes[path.Start].coord[1] + Nodes[path.End].coord[1]) / 2.0;
            Paths2Draw.push_back({line, std::to_string(path.weight), {x + 584.0f, y + 115.0f}});
        }
        isPathsInitialized = true;
    }
}

void Drawer::drawNodes(bool isIcon, bool isID, bool isName)
{
    if (!Nodes2Draw.empty())
    {
        for (Node2Draw n : Nodes2Draw)
        {
            n.NodeCircle.draw(drawerShader.create());
            if (isIcon)
                n.NodeIcon.draw(drawerShader.create());
            if (isID)
                ;
            // DrawText(n.Text[1], ImVec2(n.Position[0] - 32.0, n.Position[1] + 32.0));
            if (isName)
                ;
            // DrawText(n.Text[0], ImVec2(n.Position[0] - 10.0, n.Position[1] + 32.0));
        }
    }
}

void Drawer::drawPaths()
{
    if (!Paths2Draw.empty())
    {
        if (isAnimationFinished)
        {
            for (Path2Draw p : Paths2Draw)
            {
                p.PathLine.draw(drawerShader.create());
                // DrawText(p.Text, ImVec2(p.Position[0], p.Position[1]));
            }
        }
        else
        {
            for (Path2Draw p : AnimationPaths2Draw)
            {
                p.PathLine.draw(drawerShader.create());
            }
        }
    }
}

void Drawer::drawTexts(bool isID, bool isName)
{
    // Texts for Nodes
    if (!Nodes2Draw.empty())
    {
        for (Node2Draw n : Nodes2Draw)
        {
            if (isID)
                DrawText(n.Text[1], ImVec2(n.Position[0] - 32.0, n.Position[1] + 32.0));
            if (isName)
                DrawText(n.Text[0], ImVec2(n.Position[0] - 10.0, n.Position[1] + 32.0));
        }
    }

    // Texts for Paths
    if (!Paths2Draw.empty())
    {
        if (isAnimationFinished)
        {
            for (Path2Draw p : Paths2Draw)
            {
                DrawText(p.Text, ImVec2(p.Position[0], p.Position[1]));
            }
        }
        else
        {
            for (Path2Draw p : AnimationPaths2Draw)
            {
                DrawText(p.Text, ImVec2(p.Position[0], p.Position[1]));
            }
        }
    }
}

void Drawer::setNodes(std::vector<Node> ns)
{
    Nodes.clear();
    Nodes = ns;
    updateNodes();
}

void Drawer::setPaths(std::vector<Path> ps)
{
    Paths.clear();
    Paths = ps;
    updatePaths();
}

void Drawer::setPaths2Draw(std::vector<Path> ps)
{
    Paths2Draw.clear();
    for (Path path : ps)
    {
        EasyGL2D::Line line(Nodes[path.Start].coord[0] + 584.0f, Nodes[path.Start].coord[1] + 115.0f, Nodes[path.End].coord[0] + 584.0f, Nodes[path.End].coord[1] + 115.0f, 2.0f);
        line.setColor("FFFF00");
        float x = (Nodes[path.Start].coord[0] + Nodes[path.End].coord[0]) / 2.0;
        float y = (Nodes[path.Start].coord[1] + Nodes[path.End].coord[1]) / 2.0;
        Paths2Draw.push_back({line, std::to_string(path.weight), {x + 584.0f, y + 115.0f}});
    }
    isPathsInitialized = true;
}

void Drawer::addNode(Node n)
{
    Nodes.push_back(n);
}

void Drawer::addPath(Path p)
{
    Paths.push_back(p);
}

void Drawer::updateNodes()
{
    isNodesInitialized = false;
    Nodes2Draw.clear();
}

void Drawer::updatePaths()
{
    isPathsInitialized = false;
    Paths2Draw.clear();
}

void Drawer::clearNodes()
{
    Nodes.clear();
    Nodes2Draw.clear();
}

void Drawer::clearPaths()
{
    Paths.clear();
    Paths2Draw.clear();
}

void Drawer::playAnimation()
{
    isAnimationFinished = false;
    AnimationPaths2Draw.clear();
    it = Paths2Draw.begin();
}

void Drawer::Animation()
{
    if (!isAnimationFinished)
    {
        
        
        float elapsedTime = glfwGetTime();
        static float lastLineTime = 0.0f;
        if (elapsedTime - lastLineTime >= 0.5f)
        {
            AnimationPaths2Draw.push_back({it->PathLine, it->Text, {it->Position[0], it->Position[1]}});
            lastLineTime = elapsedTime;
            it++;
        }
        if (it == Paths2Draw.end())
        {
            isAnimationFinished = true;
            AnimationPaths2Draw.clear();
        }
    }
}

Drawer::Drawer()
{
    Nodes.clear();
    Paths.clear();
    Nodes2Draw.clear();
    Paths2Draw.clear();
    drawerShader = EasyGL::Shader("res\\screen.vsh", "res\\CustomColor.fsh");
    IconBuilding = EasyGL::TextureA("res\\Building.png");
    IconTerminal = EasyGL::TextureA("res\\Terminal.png");
    tagFlags |= ImGuiWindowFlags_NoMove;
    tagFlags |= ImGuiWindowFlags_NoBackground;
    tagFlags |= ImGuiWindowFlags_NoTitleBar;
    tagFlags |= ImGuiWindowFlags_NoCollapse;
    tagFlags |= ImGuiWindowFlags_NoResize;
}

void Drawer::DrawText(std::string content, ImVec2 pos)
{
    std::string name = content + std::to_string(pos.x) + std::to_string(pos.y);
    ImGui::SetNextWindowPos(pos);
    ImGui::SetNextWindowBgAlpha(0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    ImGui::Begin(name.c_str(), NULL, tagFlags);
    ImGui::Text(content.c_str());
    ImGui::End();
    ImGui::PopStyleVar(1);
}
