#version 330 core

layout (location = 0) in vec2 aPosition;
layout (location = 1) in vec2 aTexCoord;

out vec2 TexCoord;

void main ()
{
    vec2 ScreenSize = vec2 (1920 , 1080);
    vec2 hSize = ScreenSize / 2.0;
    vec2 targetPixel = vec2 (0.0 , 0.0);
    // I
    if (aPosition.x >= hSize.x && aPosition.y <= hSize.y)
    {
        targetPixel.x = (aPosition.x - hSize.x) / hSize.x;
        targetPixel.y = (hSize.y - aPosition.y) / hSize.y;
    }
    // II
    if (aPosition.x < hSize.x && aPosition.y < hSize.y)
    {
        targetPixel.x = - (hSize.x - aPosition.x) / hSize.x;
        targetPixel.y = (hSize.y - aPosition.y) / hSize.y;
    }
    // III
    if (aPosition.x <= hSize.x && aPosition.y >= hSize.y)
    {
        targetPixel.x = - (hSize.x - aPosition.x) / hSize.x;
        targetPixel.y = - (aPosition.y - hSize.y) / hSize.y;
    }
    // IV
    if (aPosition.x > hSize.x && aPosition.y > hSize.y)
    {
        targetPixel.x = (aPosition.x - hSize.x) / hSize.x;
        targetPixel.y = - (aPosition.y - hSize.y) / hSize.y;
    }

    gl_Position = vec4 (targetPixel , 0.0 , 1.0);
    TexCoord = vec2 (aTexCoord.x , aTexCoord.y);
}