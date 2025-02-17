#extension GL_ARB_texture_rectangle : enable
uniform sampler2DRect src_tex_unit0;
uniform sampler2D tex;
uniform float blurH;
uniform float blurV;


void main()
{
    vec2 st = gl_TexCoord[0].st;
    
    vec4 color1;
    color1 = vec4(0,0,0,0);
    
    color1        += 1.0 * texture2DRect(src_tex_unit0, st + vec2(blurH * -4.0, 0.0));
    color1        += 2.0 * texture2DRect(src_tex_unit0, st + vec2(blurH * -3.0, 0.0));
    color1        += 3.0 * texture2DRect(src_tex_unit0, st + vec2(blurH * -2.0, 0.0));
    color1        += 4.0 * texture2DRect(src_tex_unit0, st + vec2(blurH * -1.0, 0.0));
    color1        += 5.0 * texture2DRect(src_tex_unit0, st + vec2(blurH, 0));
    color1        += 4.0 * texture2DRect(src_tex_unit0, st + vec2(blurH * 1.0, 0.0));
    color1        += 3.0 * texture2DRect(src_tex_unit0, st + vec2(blurH * 2.0, 0.0));
    color1        += 2.0 * texture2DRect(src_tex_unit0, st + vec2(blurH * 3.0, 0.0));
    color1        += 1.0 * texture2DRect(src_tex_unit0, st + vec2(blurH * 4.0, 0.0));
    color1 /= 25.0;
    
    vec4 color2;
    color2 = vec4(0,0,0,0);
    color2        += 1.0 * texture2DRect(src_tex_unit0, st + vec2(0.0, blurV * 4.0));
    color2        += 2.0 * texture2DRect(src_tex_unit0, st + vec2(0.0, blurV * 3.0));
    color2        += 3.0 * texture2DRect(src_tex_unit0, st + vec2(0.0, blurV * 2.0));
    color2        += 4.0 * texture2DRect(src_tex_unit0, st + vec2(0.0, blurV * 1.0));
    color2        += 5.0 * texture2DRect(src_tex_unit0, st + vec2(0.0, blurV) );
    color2        += 4.0 * texture2DRect(src_tex_unit0, st + vec2(0.0, blurV * -1.0));
    color2        += 3.0 * texture2DRect(src_tex_unit0, st + vec2(0.0, blurV * -2.0));
    color2        += 2.0 * texture2DRect(src_tex_unit0, st + vec2(0.0, blurV * -3.0));
    color2        += 1.0 * texture2DRect(src_tex_unit0, st + vec2(0.0, blurV * -4.0));
    color2 /= 25.0;
    
    vec3 color3;
    color3 = mix(vec3(color1[0], color1[1],color1[2]), vec3(color2[0], color2[1],color2[2]), 0.5);
    
    gl_FragColor = vec4(color3[0], color3[1], color3[2], 1);
}
