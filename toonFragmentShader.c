//for better performance less precision
precision mediump float;

// ========= Added variables ==========
varying vec3 vertexPos; // from vertex shader
varying vec3 vertexNorm; // from vertex shader
uniform vec3 cameraPos;

//main program for each fragment = pixel candidate
void main() {
  vec3 norm = normalize(vertexNorm);

  vec3 lightDirection = cameraPos - vertexPos;
  vec3 lightDir_norm = normalize(lightDirection);
  float lighting_toon = max(dot(norm, lightDir_norm), 0.0);

  // assign
  if (lighting_toon > 0.98) {
      gl_FragColor = vec4(0.8,0.8,0.8,1.0);
  } else if (lighting_toon>0.5 && lighting_toon<= 0.98) {
      gl_FragColor = vec4(0.8,0.4,0.4,1.0);
  } else if (lighting_toon>0.25 && lighting_toon<= 0.5) {
      gl_FragColor = vec4(0.6,0.2,0.2,1.0);
  } else {
      gl_FragColor = vec4(0.1,0.1,0.1,1.0);
  }
}