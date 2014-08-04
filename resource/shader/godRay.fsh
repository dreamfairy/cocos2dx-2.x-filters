#ifdef GL_ES
precision mediump float;
#endif

uniform sampler2D u_texture;
varying vec2 v_texCoord;
varying vec4 v_fragmentColor;

uniform float u_time;
uniform int u_useParamPos;
uniform vec2 u_localPos;
uniform int u_num_sample;
uniform float u_Weight;

float Density = 1.0;
float Exposure = 0.5;
float Decay = 0.98;

void main(void)
{
	vec2 newTex = vec2(v_texCoord.x,v_texCoord.y);
	vec2 SceneLightPos = vec2(0.5 + 0.2 * sin(u_time),0.5 + 0.2 * cos(u_time));

	if(u_useParamPos == 1){
		SceneLightPos.x = u_localPos.x;
		SceneLightPos.y = u_localPos.y;
	}

	vec2 deltaTexCoord = newTex - SceneLightPos;
	float f_numSamlpe = float(u_num_sample);
	deltaTexCoord = deltaTexCoord / (f_numSamlpe * Density);
	vec4 color = texture2D(u_texture,newTex);
	float illuminationDecay = 1.0;

	for(int i = 0; i < u_num_sample; i++)
	{
		newTex.x = newTex.x - deltaTexCoord.x;
		newTex.y = newTex.y - deltaTexCoord.y;
		vec4 sample = texture2D(u_texture,newTex);
		sample = illuminationDecay * u_Weight * sample;
		color = sample + color;
		illuminationDecay = illuminationDecay * Decay;
	}

	color = color * Exposure;
	gl_FragColor = color;
}