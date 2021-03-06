#version 460 core
in vec2 TexCoords;
out vec4 color;

uniform sampler2D ourTexture;
uniform vec3 aColor;
uniform float alpha;

void main()
{    
    //vec4 sampled = vec4(1.0, 1.0, 1.0, texture(text, TexCoords).r);
    //color = texture(ourTexture, TexCoords) * vec4(aColor, 1.0);// * sampled;
    color = texture(ourTexture, TexCoords) * vec4(aColor, 1.0 - alpha);// * sampled;
    //color =  vec4(1, 1, 1, 0.5);// * sampled;
}  