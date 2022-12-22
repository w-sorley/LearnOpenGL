#version 330 core
layout (points) in; // 输入点图元
layout (line_strip, max_vertices = 2) out;  // 输出包含两点的线图元

void main() {
    gl_Position = gl_in[0].gl_Position + vec4(-0.1, 0.0, 0.0, 0.0);
    EmitVertex();
    gl_Position = gl_in[0].gl_Position + vec4(0.1, 0.0, 0.0, 0.0);
    EmitVertex();

    EndPrimitive();
}
