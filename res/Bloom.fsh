#version 330 core

const float tgreshold = 0.5;
const int blurSize = 3;
const float blurSigma = 1.0;
const float darkness = 0.5;

void main ()
{
    vec2 texCoord = gl_FragCoord.xy / resolution.xy;
    vec3 color = texture2D (u_texture , texCoord).rgb;
    
}