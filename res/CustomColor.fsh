#version 330 core

out vec4 FragColor;

in vec2 TexCoord;

uniform vec4 targetColor;
uniform bool isTexture;
uniform sampler2D texture1;

void main ()
{
    if (isTexture)
    {
        // vec3 color = texture (texture1 , TexCoord).xyz;
        // if ((color.x == 1.0) && (color.y == 0.0) && (color.z == 1.0))
        // {
        //     FragColor = vec4 (0.0 , 0.0 , 0.0 , 0.0);
        // }
        // else
        // {
        //     FragColor = vec4 (color , 1.0f);
        // }
        FragColor = texture (texture1 , TexCoord);
    }
    else
    {
        FragColor = targetColor;
    }

}