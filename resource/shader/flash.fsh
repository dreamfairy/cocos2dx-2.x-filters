#ifdef GL_ES
precision mediump float;
#endif
uniform sampler2D u_texture;
varying vec2 v_texCoord;
varying vec4 v_fragmentColor;

uniform float u_alpha;

void main(void)
{
  // Convert to greyscale using NTSC weightings
  vec4 color = texture2D(u_texture, v_texCoord);
  gl_FragColor = vec4(color.r,color.g,color.b,u_alpha);
}