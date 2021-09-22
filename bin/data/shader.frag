#version 150
precision highp float;

uniform int amount;
uniform vec2 ball;
uniform sampler2DRect tex0;
uniform sampler2DRect tex1;
uniform sampler2DRect tex2;
uniform vec2 res;

// Group Functions: Take a tex as input and return a single value

float group_basicSDF(sampler2DRect tex, vec2 st){
  float minDist = 1.0;
  for (int i = 0; i < amount; i ++) {
    // Extract the Position Values from the Color Channels of the Pixels of a Non-Power-Of-2 Rectangular Texture that contains the      position buffer.
    vec2 posSample = texture2DRect(tex, vec2(i, 0) + vec2(0.5, 0.5)).rg; 
    float dist = distance(posSample, st);
    minDist = min(minDist, dist);
  }
  return minDist;
}

// Interaction Functions: Take three values: 1) From tex1 2) from tex2 3) from p;

void main(){
  vec2 coords = gl_FragCoord.xy / res;
  coords.y = 1 - coords.y;
  vec2 p = ball / res;
  float out1 = group_basicSDF(tex1, coords);
  float out2 = group_basicSDF(tex2, coords);
  float out3 = step(0.02, distance(p, coords));
  gl_FragColor = vec4(out1, out2, out3, 1.0);
}