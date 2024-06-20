#version 330 core
layout(location = 0) in vec3 vPos;
layout(location = 1) in vec2 vUV;
layout(location = 2) in vec3 vNormal;
layout(location = 3) in ivec4 boneIndices;
layout(location = 4) in vec4 boneWeights;

out vec3 fPos;
out vec2 fUV;
out vec3 fNormal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;


//the max amount of bones that can be passed to the shader.
const int MAX_BONES = 100;

//the maximum number of bones that can influence a vertex.
const int MAX_BONE_INFLUENCE = 4;

//this uniform is going to be updated every frame when interpolating.
uniform mat4 finalBonesMatrices[MAX_BONES];



void main()
{
	vec4 totalPosition = vec4(0.0f);

    for(int i = 0; i < MAX_BONE_INFLUENCE; i++) {

        if(boneIndices[i] == -1) 
            continue;

        if(boneIndices[i] >= MAX_BONES) 
        {
            totalPosition = vec4(vPos,1.0f);
            break;
        }

        vec4 localPosition = finalBonesMatrices[boneIndices[i]] * vec4(vPos,1.0f);

        totalPosition += localPosition * boneWeights[i];

        //not in use.
        vec3 localNormal = vNormal * mat3(finalBonesMatrices[boneIndices[i]]);

    }
	
	//gl_Position = projection * view * model * vec4(vPos, 1.0f);
	
    gl_Position = projection * view * model * totalPosition;


    //TODO: fPos is not the same therefore lighting doesnt work
	fPos = vec3(model * vec4(vPos, 1.0f));

	fUV = vUV;
	fNormal = vNormal;
}