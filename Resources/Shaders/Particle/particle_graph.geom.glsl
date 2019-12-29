# version 440 core
layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

out vec2 ColorTexCoord;

uniform vec3 campos;
uniform mat4 view;
uniform mat4 projection;

void main() {

    vec3 position = gl_in[0].gl_Position.xyz;
    vec3 position_to_cam  = normalize(campos - position);
    vec3 front = position_to_cam;
    vec3 up = vec3(0.0, 1.0, 0.0);
    vec3 right = normalize(cross(position_to_cam, up));
    vec3 updir = normalize(cross(right, front));
    gl_Position = projection * view * vec4(position, 1.0);
    EmitVertex();
    
    position +=   (gl_in[1].gl_Position.x - gl_in[0].gl_Position.x) * right 
                + (gl_in[1].gl_Position.y - gl_in[0].gl_Position.y) * updir
                + (gl_in[1].gl_Position.z - gl_in[0].gl_Position.z) * front;

    gl_Position = projection * view * vec4(position, 1.0);
    EmitVertex();
    
    position +=   (gl_in[2].gl_Position.x - gl_in[1].gl_Position.x) * right 
                + (gl_in[2].gl_Position.y - gl_in[1].gl_Position.y) * updir
                + (gl_in[2].gl_Position.z - gl_in[1].gl_Position.z) * front;
    gl_Position = projection * view * vec4(position, 1.0);
    EmitVertex();
}