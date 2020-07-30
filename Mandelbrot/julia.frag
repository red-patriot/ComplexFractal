#version 330 core

in vec2 z;

out vec4 color;

uniform int max_iterations;
uniform vec3 div;
uniform vec2 c;

// helper functions
vec2 complex_multiply(const vec2 lh, const vec2 rh) {
    return vec2(lh.x*rh.x - lh.y*rh.y, lh.y*rh.x + lh.x*rh.y);
}

vec4 calculate_color(int escape_time) {
    if (escape_time == max_iterations) {
        return vec4(0.0, 0.0, 0.0, 1.0);
    } else {
        // TODO: Change this part to color based on the number of iterations
        return vec4((-cos(escape_time/div.x) + 1)/2.0,
                    (-cos(escape_time/div.y) + 1)/2.0, 
                    (-cos(escape_time/div.z) + 1)/2.0, 
                    1.0f);
    }
} 

void main() {
    if (distance(c, z) <= 0.01) {
        color = vec4(1.0f, 1.0f, 1.0f, 1.0f);
        return;
    }
    int count = 0;
    vec2 _z = z;

    while (count < max_iterations) {
        ++count;
        _z = complex_multiply(_z, _z) + c;

        if (_z.x*_z.x + _z.y*_z.y >= 4.0f) {
            break;
        }
    }

    color = calculate_color(count);
}
