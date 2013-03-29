#ifdef GL_ES
precision highp float;
#endif

vec2 resolution = vec2(800, 600);
uniform float u_time;
uniform sampler2D u_texture;


void main(void)
{
    vec2 p = -1.0 + 2.0 * gl_FragCoord.xy / resolution.xy;
    vec2 uv;
   
    float a = atan(p.y,p.x);
    float r = sqrt(dot(p,p));

    uv.x = .75*u_time+.1/r;
    uv.y = a/3.1416;

    vec3 col =  texture2D(u_texture,uv).xyz;

    gl_FragColor = vec4(col*r,1.0);
}
