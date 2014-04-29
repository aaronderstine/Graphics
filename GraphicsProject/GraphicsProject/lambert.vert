#version 130

uniform mat4 u_modelMatrix;
uniform mat4 u_projMatrix;
uniform vec4 u_lightPos;
uniform mat4 u_cameraMatrix;
uniform float u_selected;

in vec4 vs_position;
in vec3 vs_color;
in vec4 vs_normal;

out vec3 fs_color;
out vec3 fs_light;
out vec3 fs_normal;
out float fs_selected;

// output values that will be interpolated per-fragment
out vec3 fN;
out vec3 fE;
out vec3 fL;

void main() { 
   //fN = vs_normal.xyz;
   //fE = vs_position.xyz;
   //fL = u_lightPos.xyz;

   // transform the model into camera space
   mat4 cameraSpace = u_cameraMatrix * u_modelMatrix;
   vec4 lightCameraSpace = u_cameraMatrix * u_lightPos;

	fs_color = vs_color;
	//fs_normal = normalize((cameraSpace * vs_normal).xyz);
   fN = (cameraSpace * vs_normal).xyz;

   // multiplies the position by the camera/model matrix
   vec4 finalPos = cameraSpace * vs_position;
   fE = -(cameraSpace * vs_position).xyz;

	//Calculate a normal vector pointing from the vertex to the light source
   //fs_light = normalize(lightCameraSpace - finalPos).xyz;
   fL = (lightCameraSpace - finalPos).xyz;
    
    //built-in things to pass down the pipeline
    gl_Position = u_projMatrix * finalPos;
    
    fs_selected = u_selected;
}