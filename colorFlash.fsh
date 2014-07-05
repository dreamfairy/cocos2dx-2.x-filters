#ifdef GL_ES
precision mediump float;
#endif
uniform sampler2D u_texture;
varying vec2 v_texCoord;
varying vec4 v_fragmentColor;
uniform vec3 u_color;

float Density = 4.0f;
float Exposure = 1.0f;
void main(void)
{
	vec4 color = texture2D(u_texture, v_texCoord);
	color.rgb *= u_color.rgb;
	gl_FragColor = color;
}