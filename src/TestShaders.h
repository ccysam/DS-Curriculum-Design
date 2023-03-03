/*
 * @Author: ccysam
 * @E-Mail: ccysam@hotmail.com
 * @Date: 2022-11-25 23:48:25
 * @LastEditTime: 2022-11-26 23:56:21
 * @Description:
 * @Copyright: Copyright (c) ${now_year} by ccysam, All Rights Reserved.
 */
#pragma once
#ifndef __TEST_SHADERS__
#define __TEST_SHADERS__
namespace TestShaders
{
    static const char *TestVS1 = "#version 330 core\nlayout(location = 0) in vec3 Position\n void main()\n{\ngl_Position = vec4(Position.x, Position.y, Position.z, 1.0);\n}\n ";
    static const char *TestFS1 = "#version 330 core\nout vec4 outColor;\n void main()\n{\noutColor = vec4(1.0f,0.5f,0.2f,1.0f);\n}\n ";
} // namespace TestShaders
#endif