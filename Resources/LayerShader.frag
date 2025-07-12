#extension GL_ARB_texture_rectangle : enable
uniform sampler2DRect src_tex_unit0;
uniform sampler2D tex;
uniform float contrast;
uniform float brightness;
uniform float saturation;


void main()
{
	vec2 st = gl_TexCoord[0].st;
    
	vec4 pixel = texture2DRect(src_tex_unit0, st);
    vec3 color1 = pixel.xyz;
    
	const float AvgLumR = 0.5;
	const float AvgLumG = 0.5;
	const float AvgLumB = 0.5;
	
	const vec3 LumCoeff = vec3(0.2125, 0.7154, 0.0721);

	vec3 AvgLumin = vec3(AvgLumR, AvgLumG, AvgLumB);
	vec3 brtColor = color1 * brightness;
	
	vec3 intensity = vec3(dot(brtColor, LumCoeff));
	vec3 satColor = mix(intensity, brtColor, saturation);
	vec3 conColor = mix(AvgLumin, satColor, contrast);

	gl_FragColor = vec4(conColor, pixel.a);
}
