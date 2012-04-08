varying vec2 v_texCoord2D;
varying vec4 v_color;
uniform float time;

void main()
{
    v_texCoord2D = gl_MultiTexCoord0.xy;
	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
    v_color = gl_Color;
}
