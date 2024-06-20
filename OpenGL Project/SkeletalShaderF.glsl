#version 330 core
out vec4 FragColor;

in vec3 fPos;
in vec2 fUV;
in vec3 fNormal;

/*    Light Sources    */


struct SceneLight{
    vec3 direction;
  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct LightSource{
    
    //if the light source is loaded or not.
    bool loaded;

    //position of the light source.
    vec3 position;
    
    // strength of the light.
    float strength;

    //Factor for decreasing light spread linearly.
    float linear;

    //Factor for decreasing light spread quadratically.
    float quadratic;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform SceneLight sceneLight;
uniform LightSource LightSources[10];

/*    Material Information    */


#define NUM_TEXTURE_TYPES 3

#define DIFFUSE_INDEX 0
#define SPECULAR_INDEX 1
#define AMBIENT_INDEX 2
#define EMISSIVE_INDEX 3
#define TRANSPARENT_INDEX 4
#define REFLECTIVE_INDEX 5

uniform sampler2D Textures[NUM_TEXTURE_TYPES];
uniform bool TexturesExist[NUM_TEXTURE_TYPES];
uniform vec4 Colors[NUM_TEXTURE_TYPES];

const float shininess = 1;


/*    Camera Information    */

uniform vec3 viewPos;


/*    Functions    */

void main()
{

    //---------------------- Load Colors ----------------------

    vec4 MaterialColors[NUM_TEXTURE_TYPES];

    for (int i = 0; i < NUM_TEXTURE_TYPES; i++){
        if (TexturesExist[i]){
            MaterialColors[i] = texture(Textures[i], fUV);
        }else{
            MaterialColors[i] = Colors[i];
        }
    }

    //----------------------- Variables -----------------------

    // Normal of the computed fragment, in camera space
    vec3 n = normalize( fNormal );
     
    // Eye vector (towards the camera)
    vec3 E = normalize( viewPos - fPos );



    //--------------------- Scene Lighting --------------------

    // Direction of the light (from the fragment to the light)
    vec3 l = normalize( sceneLight.direction );


    // Cosine of the angle between the normal and the light direction,
    // clamped above 0
    //  - light is at the vertical of the triangle -> 1
    //  - light is perpendicular to the triangle -> 0
    float cosTheta = clamp(dot( n, l ), 0, 1);

        
    // Direction in which the triangle reflects the light.
    vec3 R = reflect(-l, n);


    // Calculation for specular light.
    float spec = pow(max(dot(E, R), 0.0), shininess);
    

    // Combine results
    vec3 ambient  = sceneLight.ambient * MaterialColors[DIFFUSE_INDEX].xyz;
    vec3 diffuse  = sceneLight.diffuse * cosTheta * MaterialColors[DIFFUSE_INDEX].xyz;
    vec3 specular = sceneLight.specular * spec * MaterialColors[SPECULAR_INDEX].xyz;

    
    vec3 FragmentColor = (ambient + diffuse + specular); 





    //--------------------- Light Sources ---------------------

    for (int i = 0; i < 10; i++){

        LightSource light = LightSources[i];

        if (!light.loaded){
            continue;
        }


        // Direction of the light (from the fragment to the light)
        vec3 l = normalize( light.position - fPos );


        // Cosine of the angle between the normal and the light direction,
        // clamped above 0
        //  - light is at the vertical of the triangle -> 1
        //  - light is perpendicular to the triangle -> 0
        float cosTheta = clamp(dot( n, l ), 0, 1);

        
        // Direction in which the triangle reflects the light.
        vec3 R = reflect(-l, n);


        // Calculation for specular light.
        float spec = pow(max(dot(E, R), 0.0), shininess);


        // Attenuation, decrease of light at farther distances.
        float d = length(light.position - fPos);
        float attenuation = 1.0 / (1.0 + light.linear * d + 
  			         light.quadratic * (d * d));
    

        // Combine results
        vec3 ambient  = light.ambient * MaterialColors[DIFFUSE_INDEX].xyz;
        vec3 diffuse  = light.diffuse * cosTheta * MaterialColors[DIFFUSE_INDEX].xyz;
        vec3 specular = light.specular * spec * MaterialColors[SPECULAR_INDEX].xyz;
    

        ambient *= attenuation;
        diffuse *= attenuation;
        specular *= attenuation;

    
        FragmentColor += (ambient + diffuse + specular) * light.strength;
    }

    FragColor = vec4(FragmentColor, 1);
}