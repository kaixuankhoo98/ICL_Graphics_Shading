//vertex position in world coordinates
attribute vec3 vertex_worldSpace;
//surface normal at the vertex in world coordinates
attribute vec3 normal_worldSpace;
//texture coordinates at that vertex
attribute vec2 textureCoordinate_input;

//model Matrix (Identity in our case)
uniform mat4 mMatrix;
//view Matrix
uniform mat4 vMatrix;
//projection Matrix
uniform mat4 pMatrix;

// ========= Added variables ============
#define PI 3.1415926589793238462643383
varying vec4 v_color; // writes to fragment shader
// from the spec
uniform vec3 cameraPos;
uniform vec4 ambient;
uniform vec4 diffuse;
uniform vec4 specular;
// constants, defined as uniform to be changed in uniforms tab
uniform float k_d; // diffuse coefficient
uniform float k_s; // specular coefficient
uniform float s; // heuristic constant
uniform float shininess;
uniform float phi;

//main program for each vertex
void main() {
  vec4 vertex_camSpace = vMatrix * mMatrix * vec4(vertex_worldSpace, 1.0);
  
  // this took me a while lol
  vec3 vertex_pos = vec3(mMatrix * vec4(vertex_worldSpace, 1.0));
  // normal is a direction vector starting at origin
  vec3 normal = normalize(vec3(mMatrix * vec4(normal_worldSpace, 0.0)));

  vec3 lightPosition = cameraPos; // headlight
  vec3 viewDirection = lightPosition - vertex_pos;
  vec3 lightDirection = lightPosition - vertex_pos;
  vec3 lightDir_normal = normalize(lightDirection);
  float d = length(lightDirection);

  // ambient component
  vec4 ambient_component = ambient;
  // diffuse component
  float diff_val = (k_d * max(dot(normal, lightDir_normal), 0.0));
  vec4 diffuse_component = diff_val * diffuse;
  // specular component
  vec3 refl = reflect(-lightDir_normal, normal);
  float spec_val = k_s * pow((max(dot(normalize(viewDirection), refl), 0.0)), shininess);
  vec4 specular_component = specular * spec_val;

  // distance attenuation
  float d_a = phi / (4.0 * PI * (d * s));

  v_color = (ambient_component + diffuse_component + specular_component) * d_a;
  gl_Position = pMatrix * vertex_camSpace;
}
