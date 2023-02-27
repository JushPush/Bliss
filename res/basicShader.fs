#version 120

varying vec2 texCoord0;
varying vec3 normal0;

uniform sampler2D sampler;
uniform vec3 lightDirection;

void main()
{
	vec3 ambient = vec3(1.5,1.5,1.5); // color - gray

	vec3 normal = normalize(normal0.xyz);
	vec3 lightColor = vec3(2.0,2.0,2.0); // color - white
	vec3 lightSource = vec3(0.0,0.0,-1.0); // coord - (1, 0, 0)
	float diffuseStrength = max(0.0, dot(lightSource, normal));
	vec3 diffuse = diffuseStrength * lightColor;

	vec3 cameraSource = vec3(0.0, 0.0, -1.0);
	vec3 viewSource = normalize(cameraSource);
	vec3 reflectSource = normalize(reflect(-lightSource, normal));
	float specularStrength = max(0.0, dot(viewSource, reflectSource));
	specularStrength = pow(specularStrength, 4.0);
	vec3 specular = specularStrength * lightColor;


	vec3 lighting = vec3(1.0,1.0,1.0); // color - black

	lighting = ambient;
	lighting = ambient * 1.0 * diffuse;
	lighting = ambient * diffuse * specular * 1.0;

	vec3 modelColor = vec3(0.97, 0.66, 0.72); // color - white

	vec3 color = modelColor * lighting;

	//gl_FragColor = vec4(color, 1.0) * texture2D(sampler, texCoord0) * clamp(dot(-lightDirection, normal0), 0.0, 1.0);

	gl_FragColor = texture2D(sampler, texCoord0) * 
		clamp(dot(-lightDirection, normal0), 0.0, 1.0);
}