#version 330 core
out vec4 FragColor;

uniform float iTime;
uniform vec2 iResolution;

float hash(vec2 p) { return fract(sin(dot(p, vec2(127.1,311.7)))*43758.5453); }
float noise(vec2 p) {
    vec2 i = floor(p);
    vec2 f = fract(p);
    vec2 u = f*f*(3.0-2.0*f);
    return mix(
        mix(hash(i + vec2(0.4,6.0)), hash(i + vec2(1.0,0.6)), u.x),
        mix(hash(i + vec2(3.0,1.0)), hash(i + vec2(0.3,4.0)), u.x),
        u.y
    );
}

void main() {
    vec2 uv = gl_FragCoord.xy / iResolution.xy * 2.0 - 1.0;
    uv.x *= iResolution.x / iResolution.y;
    uv *= 0.3; // zoom out

    float t = iTime * 0.1;
    float angle = atan(uv.y, uv.x) + t ;
    float radius = length(uv);

    vec2 swirl = vec2(cos(angle), sin(angle)) * radius * 10.0;
    vec2 swirl2 = vec2(cos(angle*1.3 + 1.0), sin(angle*1.3 + 1.0)) * radius * 10.5;

    float n = noise(swirl + t*5.0);
    n += 0.3 * noise(swirl2 + t*5.0);

    //Stars fading in and out
    //density and distribution of the stars, higher means more density
    float starNoise = noise(swirl * 30.0 + t * 0.5);
    //brightness and desity as well, lower means more stars
    float stars = step(0.98, starNoise);
    //randomness and fade of stars, higher is faster fade 6.28
    //speed of the fade, lower is slower 0.1
    stars *= 0.5 + 0.5 * sin(iTime * 0.1 + starNoise * 6.28);
    //clamp values from sine so stars dont look dumb
    stars = clamp(stars, 0.0, 1.0);


    // color map with pulsing
    vec3 col = vec3(0.0);
    col += n * vec3(0.3, 0.0, 0.6);
    col += pow(n, 3.0) * vec3(1.0, 0.2, 0.5);
    col *= 0.5 + 0.5*sin(iTime + radius*5.0);
    col += vec3(stars);

    FragColor = vec4(col, 1.0);
}

