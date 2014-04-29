#version 130 

in vec3 fs_color;
in vec3 fs_light;
in vec3 fs_normal;
in float fs_selected;

// per-fragment interpolated values from vertex shader
in vec3 fN;
in vec3 fL;
in vec3 fE;

out vec4 out_Color;

void main() {
   // Normalize the input lighting vectors
   vec3 N = normalize(fN);
   vec3 E = normalize(fE);
   vec3 L = normalize(fL);
   
   vec3 H = normalize( L + E );

   vec4 ambient = vec4(fs_color * 0.1, 1.0);

   // check to see if it is selected
   // if so light it up!!
   if(fs_selected > 0.5) {
      ambient = ambient * 10;
   }

   vec4 light_diffuse = vec4(1.0, 1.0, 0.9, 1.0);
   vec4 material_diffuse = vec4(fs_color, 1.0);
   vec4 DiffuseProduct = light_diffuse * material_diffuse;
   float Kd = max(dot(L,N), 0.0);
   vec4 diffuse = Kd * DiffuseProduct;

   vec4 light_specular = vec4(1.0, 1.0, 0.8, 1.0);
   vec4 material_specular = vec4(1.0, 1.0, 1.0, 1.0);
   vec4 SpecularProduct = light_specular * material_specular;
   float Shininess = 64.0;
   float Ks = pow(max(dot(N,H), 0.0), Shininess);
   vec4 specular = Ks*SpecularProduct;

   // discard the specular highlight if the light's behind the vertex
   if (dot(L,N) < 0.0) {
      specular = vec4(0.0, 0.0, 0.0, 1.0);
   }

   out_Color = ambient + diffuse + specular;
   out_Color.a = 1.0;


//   vec3 ambientContrib = fs_color * 0.1;
//   vec4 diffuseColor = vec4(fs_color, 1.0);

//	  float diffuseTerm = max(dot(fs_light, fs_normal), 0.0);

    
//   out_Color = diffuseTerm * diffuseColor + ambientContrib;
}