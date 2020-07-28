#version 440 core

// TODO: Add periodicity checking?

in vec2 c;

out vec4 color;

uniform int max_iterations;
uniform vec3 div;

// helper functions
vec2 complex_multiply(const vec2 lh, const vec2 rh) {
    return vec2(lh.x*rh.x - lh.y*rh.y, lh.y*rh.x + lh.x*rh.y);
}

vec4 calculate_color(int escape_time) {
    if (escape_time == max_iterations) {
        return vec4(0.0, 0.0, 0.0, 0.0);
    } else {
    // TODO: Precalculate these values and make this a table lookup
        return vec4((-cos(escape_time/div.r) + 1)/2.0,
                    (-cos(escape_time/div.g) + 1)/2.0,
                    (-cos(escape_time/div.b) + 1)/2.0, 
                    1.0f);
    }
} 

void main() {
    int count = 0;
       
    // check if the point is within the cardiod or period-2 bulb first
    float x = c.x, y = c.y;
    float q = (x-.25)*(x-.25) + y*y;
    if ((q*(q + (x-.25))) <= (.25*y*y) || ((x+1)*(x+1) + y*y) <= .0625) {
        count = max_iterations;
    }

    vec2 z = vec2(0.0f,  0.0f);
    
    // perform the iterated calculation
    while (count < max_iterations) {
        ++count;
        z = complex_multiply(z, z) + c;

        if (z.x*z.x + z.y*z.y >= 4.0f) {
            break;
        }
    }

    color = calculate_color(count);
}
