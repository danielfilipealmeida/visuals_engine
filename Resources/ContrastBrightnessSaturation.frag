/*
 Implements Brightness, Contrast, Saturation filters
 Values range from 0 to 2.
 
 ```markdown
 | Variable      | Min | Max | Default |
 |---------------|-----|-----|---------|
 | brightness    | 0   | 2   | 1       |
 | saturation    | 0   | 2   | 1       |
 | contrast      | 0   | 2   | 1       |
 ```
 */

#extension GL_ARB_texture_rectangle : enable
uniform sampler2DRect src_tex_unit0;
uniform sampler2D tex;
uniform float contrast;
uniform float brightness;
uniform float saturation;


void main()
{
    vec2 st = gl_TexCoord[0].st;
    
    vec3 color = texture2DRect(src_tex_unit0, st)
   
     const float AvgLumR = 0.5;
     const float AvgLumG = 0.5;
     const float AvgLumB = 0.5;
     
     const vec3 LumCoeff = vec3(0.2125, 0.7154, 0.0721);
     
     vec3 AvgLumin = vec3(AvgLumR, AvgLumG, AvgLumB);
     vec3 brtColor = color * brightness;
     
     vec3 intensity = vec3(dot(brtColor, LumCoeff));
     vec3 satColor = mix(intensity, brtColor, saturation);
     vec3 conColor = mix(AvgLumin, satColor, contrast);
     
    gl_FragColor = vec4(conColor[0], conColor[1], conColor[2], 1);
}
