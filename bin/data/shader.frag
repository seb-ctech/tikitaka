#version 120
precision highp float;

#define amount 10
uniform vec2 ball;
uniform float att[amount];
uniform float def[amount];
uniform vec2 res;

void main(){
  vec2 st = gl_FragCoord.xy / res;
  vec2 test = ball / res;
  float testValue = step(att[1], st.y);
  gl_FragColor = vec4(0, testValue, 0, 1);
}