// Shader-ul de fragment / Fragment shader 

#version 330 core

in vec4 ex_Color;

out vec4 out_Color;

uniform int codColShader;

void main(void)
{
	switch(codColShader) {
		case 0:
		{
			out_Color = ex_Color;
			break;
		}
		case 1:
		{
			out_Color = vec4(1.0, 1.0, 1.0, 1.0);
			break;
		}
		case 2: // headlights
		{
			out_Color = vec4(0.969, 0.969, 0.004, 1.0);
			break;
		}
		case 3: // break lights
		{
			out_Color = vec4(0.565, 0.0, 0.0, 1.0);
			break;
		}
		default:
		{
			out_Color = ex_Color;
			break;
		}
	}
}
