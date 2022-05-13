//for better performance less precision
precision mediump float;

varying vec4 v_color; // reads from vertex shader

//main program for each fragment = pixel candidate
void main() {
  gl_FragColor = v_color;
}