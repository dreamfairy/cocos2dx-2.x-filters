#ifdef GL_ES
precision mediump float;
#endif

uniform sampler2D u_texture;
varying vec2 v_texCoord;
varying vec4 v_fragmentColor;

uniform float u_time = 1.0f;
uniform int u_useParamPos = 0;
uniform vec2 u_localPos;

int num_sample = 50;
float Density = 1.0f;
float Exposure = 0.5f;
float Weight = 0.1f;
float Decay = 0.97f;

void main(void)
{
	vec2 newTex = vec2(v_texCoord.x,v_texCoord.y);

	vec2 SceneLightPos = vec2(0.5 + 0.2 * sin(u_time),0.5 + 0.2 * cos(u_time));;

	if(u_useParamPos == 1){
		SceneLightPos.x = u_localPos.x;
		SceneLightPos.y = u_localPos.y;
	}

	vec2 deltaTexCoord = newTex - SceneLightPos;
	deltaTexCoord = deltaTexCoord / (num_sample * Density);
	vec4 color = texture2D(u_texture,newTex);
	float illuminationDecay = 1.0f;

	for(int i = 0; i < num_sample; i++)
	{
		newTex.x = newTex.x - deltaTexCoord.x;
		newTex.y = newTex.y - deltaTexCoord.y;
		vec4 sample = texture2D(u_texture,newTex);
		sample = illuminationDecay * Weight * sample;
		color = sample + color;
		illuminationDecay = illuminationDecay * Decay;
	}

	color = color * Exposure;
	gl_FragColor = color;
}