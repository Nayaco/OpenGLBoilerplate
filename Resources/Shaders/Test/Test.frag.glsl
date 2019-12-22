#version 440 core
// in vec3 ourPosition;
out vec4 FragColor;

void main()
{
    FragColor = vec4(1.0);    // note how the position value is linearly interpolated to get all the different colors
}
