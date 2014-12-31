varying vec4 ecPos;
varying vec3 normal;
float dist;
 
 
void main()
{
    vec3 n;
    float NdotL;
    vec4 color;
     
    /* a fragment shader can't write a verying variable, hence we need
    a new variable to store the normalized interpolated normal */
    n = normalize(normal);
     
    // Compute the ligt direction
    vec3 lightDir = vec3(gl_LightSource[0].position-ecPos);
     
    /* compute the distance to the light source to a varying variable*/
    dist = length(lightDir);
 
    /* compute the dot product between normal and ldir */
    NdotL = dot(n,normalize(lightDir));

    if (NdotL < 0.0)    color = vec4(0.0, 0.4, 0.0, 1.0);
 
    if (NdotL > 0.0) {
                
            if(NdotL > 0.55)
	color = vec4(0.0, 0.9, 0.0, 1.0);
            else if (NdotL > 0.45)
	color = vec4(0.0, 0.8, 0.0, 1.0);
            else if (NdotL > 0.35)
	color = vec4(0.0, 0.6, 0.0, 1.0);
             else if (NdotL > 0.25)
	color = vec4(0.0, 0.4, 0.0, 1.0);
             else if (NdotL > 0.15)
	color = vec4(0.0, 0.2, 0.0, 1.0);
            else 
	color = vec4(0.0, 0.1, 0.0, 1.0);
        
        
    }
    else if (NdotL == 0.0) {
	color = vec4(0.0, 0.0, 0.0, 1.0);
}

    gl_FragColor = color;
}