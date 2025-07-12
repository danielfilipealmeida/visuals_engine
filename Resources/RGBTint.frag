/*
 Implementes tinting.
 Values range from 0 to 2.
 
 
 ```markdown
 | Variable   | Min | Max | Default |
 |------------|-----|-----|---------|
 | redTint    | 0   | 2   | 1       |
 | greenTint  | 0   | 2   | 1       |
 | blueTint   | 0   | 2   | 1       |
 ```
 */

#extension GL_ARB_texture_rectangle : enable
uniform sampler2DRect src_tex_unit0;
uniform sampler2D tex;
uniform float redTint;
uniform float greenTint;
uniform float blueTint;


void main()
{
    vec2 st = gl_TexCoord[0].st;
    vec4 color = texture2DRect(src_tex_unit0, st);
    
    color[0] = color[0] * redTint;
    color[1] = color[1] * greenTint;
    color[2] = color[2] * blueTint;
     

    gl_FragColor = vec4(color[0], color[1], color[2], 1);
}
