#version 150
precision highp float;

#define PI 3.14159265

uniform int amount;
uniform vec2 ball;
uniform sampler2DRect tex0;
uniform sampler2DRect tex1;
uniform sampler2DRect tex2;
uniform vec2 res;
uniform float v1;
uniform float v2;

// Helper functions

vec3 hash3( vec2 p ){
    vec3 q = vec3( dot(p,vec2(127.1,311.7)), 
				   dot(p,vec2(269.5,183.3)), 
				   dot(p,vec2(419.2,371.9)) );
	return fract(sin(q)*43758.5453);
}

float length2(vec2 p){
    return dot(p,p);
}

//Generate some noise to scatter points.
float noise(vec2 p){
	return fract(sin(fract(sin(p.x) * (43.13311)) + p.y) * 31.0011);
}

// Shaping Functions: Return a final float value;

// TODO: Find examples of shaping functions and their results 

float parabola( float x, float k )
{
    return pow( 4.0*x*(1.0-x), k );
}

float isolateValue(float value, float lower, float upper){
  return max(lower, min(value, upper));
}

float expStep( float x, float k, float n )
{
    return exp( -k*pow(x,n) );
}

float gain(float x, float k) 
{
    float a = 0.5*pow(2.0*((x<0.5)?x:1.0-x), k);
    return (x<0.5)?a:1.0-a;
}

float pcurve( float x, float a, float b )
{
    float k = pow(a+b,a+b)/(pow(a,a)*pow(b,b));
    return k*pow(x,a)*pow(1.0-x,b);
}

/* Group Functions: Take a PositionBuffer and the Point on the canvas as input 
They represent the combined effect of all points in relation to one point on the canvas 
TODO: Find examples how to use a certain amount of points to build shapes and structures in relation to 1 fragment
*/

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

/* Single Position Function: Take a Position and the Point on the canvas as input
represents the ball on the canvas */

// TODO: Find examples hot to create interesting effects from a vector2

float worley(vec2 coord, vec2 p){
  vec2 tp = floor(p) + coord;
  float d = length2(p - tp - noise(coord));
	return 3.0*exp(-4.0*abs(2.5*d - 1.0));
}


/* Composition Functions, Take three values: 
  1) Value in Relation to group 1 output
  2) Value in Relation to group 2 output
  3) Value in Relation to P -> Ball
Returns a Color*/

// TODO: Find examples how to compute interesting color schemes from some values

vec3 Palettization1(float o1, float o2, float d){
  vec3 color1 = vec3(0.502, 0.102, 0.102);
  vec3 color2 = vec3(0.4588, 0.5059, 0.6667);
  vec3 color3 = vec3(0.8941, 0.2902, 0.2902);
  return mix(color3, color1, max(o1, o2));
}

vec3 Spotlight(float o1, float o2, float d){
  vec3 color0 = vec3(0,0,0);
  vec3 color1 = vec3(0.3294, 0.4275, 0.3804);
  vec3 color2 = vec3(1.0, 0.6353, 0.1569);
  float spot = pow(1 - d, 0.2);
  float spotCenter = pow(1 - d, 24.0);
  float a = pow(parabola(o1, 4.0), o2); // parabola(o1, spot)
  float b = a;
  b = pcurve(b, 0.6, 0.4);
  return vec3(mix(mix(color0, color1, b), color2 * b, spotCenter));
}


void main(){
  // Get Screen coords and flip Y.
  vec2 coord = gl_FragCoord.xy / res;
  coord.y = 1 - coord.y;
  // Do something with the Ball Position.
  vec2 p = ball / res;
  float d = pow(distance(coord, p), 2.0);
  // Do something with group 1
  float out1 = group_basicSDF(tex1, coord);
  // Do something with group 2
  float out2 = 1 - pcurve(group_basicSDF(tex2, coord), 2, 4);
  // Combine to final color
  vec3 color = Spotlight(out1, out2, d);
  gl_FragColor = vec4(color, 1.0);
}