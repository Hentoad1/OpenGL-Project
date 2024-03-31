#version 330 core
out vec4 FragColor;

in vec3 fPos;
in vec2 fUV;
in vec3 fNormal;

#define NUM_TEXTURE_TYPES 3

uniform sampler2D Textures[NUM_TEXTURE_TYPES];
uniform bool TexturesExist[NUM_TEXTURE_TYPES];
uniform vec4 Colors[NUM_TEXTURE_TYPES];

uniform vec3 viewPos;


uniform vec3 lightPos;

#define DIFFUSE_INDEX 0
#define SPECULAR_INDEX 1
#define AMBIENT_INDEX 2
#define EMISSIVE_INDEX 3
#define TRANSPARENT_INDEX 4
#define REFLECTIVE_INDEX 5

const float shininess = 1;

const vec4 lightColor = vec4(1);
const float lightPower = 10000;

void main()
{

    //---------------------- Load Colors ----------------------

    vec4 TextureColors[NUM_TEXTURE_TYPES];

    for (int i = 0; i < NUM_TEXTURE_TYPES; i++){
        if (TexturesExist[i]){
            TextureColors[i] = texture(Textures[i], fUV);
        }else{
            TextureColors[i] = Colors[i];
        }
    }

    //----------------------- Distances -----------------------

    // Normal of the computed fragment, in camera space
     vec3 n = normalize( fNormal );

     // Direction of the light (from the fragment to the light)
     vec3 l = normalize( lightPos - fPos );

    // Cosine of the angle between the normal and the light direction,
    // clamped above 0
    //  - light is at the vertical of the triangle -> 1
    //  - light is perpendicular to the triangle -> 0
    float cosTheta = clamp(dot( n, l ), 0, 1);


    // Eye vector (towards the camera)
    vec3 E = normalize( viewPos - fPos );

    // Direction in which the triangle reflects the light
    vec3 R = reflect(-l,n);

    // Cosine of the angle between the Eye vector and the Reflect vector,
    // clamped to 0
    //  - Looking into the reflection -> 1
    //  - Looking elsewhere -> < 1
    float cosAlpha = clamp( dot( E,R ), 0,1 );


    // Distance fragment is from light source squared
    float distanceFromLightSqrd = pow(distance(lightPos, fPos), 2);

    //---------------------- Light Color ----------------------

    //Diffuse Light
    vec4 DiffuseColor = TextureColors[DIFFUSE_INDEX];


    //Ambient Light
    vec4 AmbientColor = TextureColors[AMBIENT_INDEX];
    

    //Specular Light
    vec3 lightDir = normalize(lightPos - fPos);
    vec3 viewDir = normalize(viewPos - fPos);
    vec3 halfwayDir = normalize(lightDir + viewDir);

    float spec = pow(max(dot(fNormal, halfwayDir), 0.0), shininess);
    vec4 SpecularColor = TextureColors[SPECULAR_INDEX] * spec;

    //All of them together
    FragColor = 
        AmbientColor + 
        (DiffuseColor * lightColor * lightPower * cosTheta / distanceFromLightSqrd) + 
        (SpecularColor * lightColor * lightPower * pow(cosAlpha, 5) / distanceFromLightSqrd);
}