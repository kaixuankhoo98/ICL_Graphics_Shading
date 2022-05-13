//for better performance less precision
precision mediump float;

// ========= Added variables ==========
#define PI 3.1415926589793238462643383
varying vec3 vertexPos; // from vertex shader
varying vec3 vertexNorm; // from vertex shader
uniform vec3 cameraPos;

// from the spec
uniform vec4 ambient;
uniform vec4 diffuse;
uniform vec4 specular;
// constants, defined as uniform to be changed in uniforms tab
uniform float k_d; // diffuse coefficient
uniform float k_s; // specular coefficient
uniform float s; // heuristic constant
uniform float shininess;
uniform float phi;

//main program for each fragment = pixel candidate
void main() {
  vec3 norm = normalize(vertexNorm);

  vec3 lightDirection = cameraPos - vertexPos;
  vec3 lightDir_norm = normalize(lightDirection);
  float d = length(lightDirection);

  // ambient
  vec4 ambient_component = ambient;
  // diffuse
  float diff_val = k_d * max(dot(norm, lightDir_norm), 0.0);
  vec4 diffuse_component = diffuse * diff_val;
  // specular
  vec3 reflect = reflect(-lightDir_norm, norm); // reflect about the normal
  vec3 viewDir = cameraPos - vertexPos;
  float spec_val = k_s * pow((max(dot(normalize(viewDir), reflect), 0.0)), shininess);
  vec4 specular_component = specular * spec_val;

  float d_a = phi / (4.0 * PI * (d + s));

  // assign
  gl_FragColor = (ambient_component + diffuse_component + specular_component) * d_a;
}