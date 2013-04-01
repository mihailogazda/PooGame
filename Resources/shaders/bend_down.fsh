#ifdef GL_ES
precision mediump float;
#endif

varying vec2 v_texCoord;
uniform sampler2D u_texture;
uniform float u_time;

uniform float u_touch1PosX;
uniform float u_touch1PosY;

uniform float u_touch2PosX;
uniform float u_touch2PosY;

const float speed = 0.5;
const float maxBendFactor = 0.08;
void main()
{    
	float bendFactor = maxBendFactor;//min(maxBendFactor, sin(u_time));

    float height = v_texCoord.y;
    float offset = pow(height, 2.5);
    offset *= (sin(u_time * speed) * bendFactor);
    
    gl_FragColor = texture2D(u_texture, fract(vec2(v_texCoord.x + offset, v_texCoord.y))).rgba;
}