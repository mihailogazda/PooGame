

#ifdef GL_ES
precision highp float;
#endif

vec2 resolution = vec2(800, 600);
uniform float u_time;
uniform sampler2D u_texture;
varying vec2 v_texCoord;

//	Light
uniform vec2 lightpos = vec2(100, 100);
uniform vec3 lightColor = vec3(200, 80, 100);
uniform float screenHeight = 800;
uniform vec3 lightAttenuation = vec3(1, 1, 1);
uniform float radius = 5;


void main(void)
{
	vec4 m_color=texture2D(u_texture, v_texCoord).rgba;
	gl_FragColor = m_color;	
	return; // kill shader

	vec2 pixel=gl_FragCoord.xy;		
	pixel.y=screenHeight-pixel.y;	
	vec2 aux=lightpos-pixel;
	float distance=length(aux);
	float attenuation=1.0/(lightAttenuation.x+lightAttenuation.y*distance+lightAttenuation.z*distance*distance);	
	vec4 color=vec4(attenuation,attenuation,attenuation,1.0)*vec4(lightColor,1.0);	
	gl_FragColor = color;//*texture2D(u_texture,gl_TexCoord[0].st);

	return; // light



    vec2 q = gl_FragCoord.xy / resolution.xy;
    vec2 uv = 0.5 + (q-0.5)*(0.9 + 0.1*sin(0.2*u_time));

    vec3 oricol = texture2D(u_texture,vec2(q.x,1.0-q.y)).xyz;
    vec3 col;

    col.r = texture2D(u_texture,vec2(uv.x+0.003,-uv.y)).x;
    col.g = texture2D(u_texture,vec2(uv.x+0.000,-uv.y)).y;
    col.b = texture2D(u_texture,vec2(uv.x-0.003,-uv.y)).z;

    col = clamp(col*0.5+0.5*col*col*1.2,0.0,1.0);

    col *= 0.5 + 0.5*16.0*uv.x*uv.y*(1.0-uv.x)*(1.0-uv.y);

    col *= vec3(0.8,1.0,0.7);

    col *= 0.9+0.1*sin(10.0*u_time+uv.y*1000.0);

    col *= 0.97+0.03*sin(110.0*u_time);

    float comp = smoothstep( 0.2, 0.7, sin(u_time) );
    col = mix( col, oricol, clamp(-2.0+2.0*q.x+3.0*comp,0.0,1.0) );

    gl_FragColor = vec4(col,1.0);
}