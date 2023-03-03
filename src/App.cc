/*
 * @Author: ccysam
 * @E-Mail: ccysam@hotmail.com
 * @Date: 2022-11-24 23:52:55
 * @LastEditTime: 2022-12-18 21:18:00
 * @Description:
 * @Copyright: Copyright (c) 2022 by ccysam, All Rights Reserved.
 */
#include "App.h"

namespace
{

}

namespace App
{

    // Variables

    bool demo = false;

    // Functions

    void
    start(int argc, char **argv)
    {
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_RESIZABLE, false);
#ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

        glfwWindowHint(GLFW_SAMPLES, 4);

        // Create the window
        GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "App", NULL, NULL);
        if (window == NULL)
        {
            glfwTerminate();
            throw std::runtime_error("Failed to create window");
        }

        glfwMakeContextCurrent(window);
        glfwSwapInterval(1);
        glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

        // Load the OpenGL function pointers
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            throw std::runtime_error("Failed to initialize GLAD");
        }

        // Enable Anti-aliasing (MSAAx4)
        glEnable(GL_MULTISAMPLE);

        // Prepare Objects
        EasyGL::Shader s4l("res\\1.vsh", "res\\Green.fsh");
        EasyGL::Shader all("res\\screen.vsh", "res\\CustomColor.fsh");
        EasyGL::Texture tex1("res\\umaru.jpeg");
        EasyGL::TextureA tex2("res\\AUST logo.png", GL_LINEAR);
        EasyGL2D::Line l1(0.0f, 0.0f, 128.0f, 128.0f, 2.0f);
        EasyGL2D::Rectangle r1(400.0, 300.0, 128.0, 128.0);
        EasyGL2D::Triangle t1(500.0f, 500.0f, 200.0f, 270.0f, 120.0f, 160.0f);
        EasyGL2D::Disc d1(900.0f, 400.0f, 96.0f);
        EasyGL2D::Rectangle r2(1030.0f, 140.0f, 30.0f, 40.0f);
        EasyGL2D::Ring ri1(960.0f, 560.0f, 64.0f, 12);
        EasyGL2D::PicCard p1(40.0f, 480.0f, 200.0f, 200.0f);
        EasyGL2D::PicCard austLogo(1523.0, 950.0, 397.0, 130.0);
        EasyGL2D::Disc n1(346.0, 258.0, 64.0);
        EasyGL2D::Disc n2(346.0, 741.0, 64.0);
        EasyGL2D::Disc n3(652.0, 741.0, 64.0);
        EasyGL2D::Disc n4(844.0, 258.0, 64.0);
        EasyGL2D::Disc n5(1043.0, 530.0, 64.0);
        EasyGL2D::Disc n6(1342.0, 253.0, 64.0);
        EasyGL2D::Disc n7(1342.0, 741.0, 64.0);
        l1.setColor("66CCFF");
        r1.setColor("F2F2F2");
        t1.setColor("4CF2DE");
        d1.setColor("66CCFF");
        r2.setColor("65C365");
        ri1.setColor("FFFF22");
        n1.setColor("66CCFF");
        n2.setColor("66CCFF");
        n3.setColor("66CCFF");
        n4.setColor("66CCFF");
        n5.setColor("66CCFF");
        n6.setColor("66CCFF");
        n7.setColor("66CCFF");

        p1.setTexture(tex1.create());
        austLogo.setTexture(tex2.create());
        EasyGL2D::Line L1(346.0, 258.0, 346.0, 741.0, 4.0f);
        EasyGL2D::Line L2(346.0, 258.0, 652.0, 741.0, 4.0f);
        EasyGL2D::Line L3(844.0, 258.0, 1043.0, 530.0, 4.0f);
        EasyGL2D::Line L4(1342.0, 253.0, 1043.0, 530.0, 4.0f);
        EasyGL2D::Line L5(1342.0, 253.0, 1342.0, 741.0, 4.0f);
        L1.setColor("222222");
        L2.setColor("222222");
        L3.setColor("222222");
        L4.setColor("222222");
        L5.setColor("222222");
        UI AppUI;
        AppUI.Init(window);

        // Main Loop

        while (!glfwWindowShouldClose(window))
        {
            // input
            processInput(window);

            // Render
            glClearColor(0.79f, 1.0f, 0.84f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            {
                AppUI.drawBG();

                // l1.draw(all.create());
                // r1.draw(all.create());
                // t1.draw(all.create());
                // r2.draw(all.create());
                // d1.draw(all.create());
                // p1.draw(all.create());
                austLogo.draw(all.create());
                // L1.draw(all.create());
                // L2.draw(all.create());
                // L3.draw(all.create());
                // L4.draw(all.create());
                // L5.draw(all.create());
                // n1.draw(all.create());
                // n2.draw(all.create());
                // n3.draw(all.create());
                // n4.draw(all.create());
                // n5.draw(all.create());
                // n6.draw(all.create());
                // n7.draw(all.create());
                //  Render(window, WIDTH, HEIGHT);

                AppUI.drawWidgets();
            }

            // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
            glfwSwapBuffers(window);
            glfwPollEvents();
        }

        // Cleanup
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();

        glfwDestroyWindow(window);
        glfwTerminate();
    }

    void framebuffer_size_callback(GLFWwindow *window, int width, int height)
    {
        glViewport(0, 0, WIDTH, HEIGHT);
    }

    void processInput(GLFWwindow *window)
    {
    }

    void Render(GLFWwindow *window, int width, int height)
    {
        // t1.draw(taShader.create());
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        // ImGui::Begin("Hello World");
        // ImGui::Text("Hello World!");
        // ImGui::End();
        // ImGui::Render();
        // ImGui::ShowDemoWindow(&demo);
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }
}
