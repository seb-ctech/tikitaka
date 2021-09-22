#version 150
precision highp float;

uniform int amount;
uniform vec2 ball;
uniform sampler2DRect tex0;
uniform sampler2DRect tex1;
uniform sampler2DRect tex2;
uniform vec2 res;

void main(){
  vec2 coords = gl_FragCoord.xy / res;
  vec2 p = ball / res;
  float minDist1 = 1.0;
  float minDist2 = 1.0;
  for (int i = 0; i < amount; i ++) {
    // Extract the Position Values from the Color Channels of the Pixels of a Non-Power-Of-2 Rectangular Texture that contains the      position buffer.
    vec2 posSample = texture2DRect(tex1, vec2(i, 0) + vec2(0.5, 0.5)).rg; 
    float dist = distance(posSample, coords);
    if(dist < minDist1) {
      minDist1 = dist;
    }
  }
  float out1 = minDist1;
  for (int i = 0; i < amount; i ++) {
    // Extract the Position Values from the Color Channels of the Pixels of a Non-Power-Of-2 Rectangular Texture that contains the      position buffer.
    vec2 posSample = texture2DRect(tex2, vec2(i, 0) + vec2(0.5, 0.5)).rg; 
    float dist = distance(posSample, coords);
    // Distance function
    if(dist < minDist2) {
      minDist2 = dist;
    }
  }
  // Shaping function
  float out2 = minDist2;
  float out3 = step(0.02, distance(p, coords));
  gl_FragColor = vec4(out1, out2, out3, 1.0);
}