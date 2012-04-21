uniform sampler2D baseNoise;
uniform float persistence;
uniform float amplitude;
uniform int octaveSetter;
uniform float magicNumber1;
uniform float magicNumber2;
uniform int size_x;
uniform int size_y;
varying vec2 texCoord;
varying vec4 v_color;

// Great explanation of this stuff: http://devmag.org.za/2009/04/25/perlin-noise/

float interpolate(float x0, float x1, float alpha)
{
    float interpolation = x0 * (1.0 - alpha) + alpha * x1; // what the eff is with these GLSL duplicate variable names?
    return interpolation;
}

float noise2(vec2 input_coords, int octave)
{
    float out1 = 0.0f;
    float i = input_coords.s;   // 0...1
    float j = input_coords.t;   // 0...1
    
    // Get noise location related to the native texture size instea of using OpenGL texture space range 0...1
    int i_resize = int(input_coords.s * size_x);    // 0...1024
    int j_resize = int(input_coords.t * size_y);    // 0...1024
    
    int samplePeriod = 1 << octave;         // 2^n, defines the step size, how large our gradients are
    float frequency = 1.0f / samplePeriod;  // 1/2^n
    
    // Starting point of our gradient
    // Note that that this is not the same as just i_resize due to flooring math
    // The produced value is the largest multiple if samplePeriod that is smaller than i_resize
    int sample_i0 = (i_resize / samplePeriod) * samplePeriod;
    // Ending point of the gradient. If > 1024, wrap around to 0
    int sample_i1 = (sample_i0 + samplePeriod) % size_x;
    
    // Defines the alpha for our linear interpolation on X-axis
    // If we are close to the left end of the gradient, alpha is close to 0
    // If we are close to the right end of the gradient, alpha is close to 1
    float horizontal_blend = (i_resize - sample_i0) * frequency;
    
    // The starting point of our gradient (Y-axis)
    int sample_j0 = (j_resize / samplePeriod) * samplePeriod;
    // Ending point (Y-axis)
    int sample_j1 = int(sample_j0 + samplePeriod) % size_y;
    
    // After we are done with our interpolation for top row and bottom row, this
    // value is used for interpolating on Y-axis
    float vertical_blend = (j_resize - sample_j0) * frequency;
    
    // Transform to OpenGL texture coordinate space 0...1
    float coord1 = float(sample_i0) / 1024;
    float coord2 = float(sample_i1) / 1024;
    float coord3 = float(sample_j0) / 1024;
    float coord4 = float(sample_j1) / 1024;
    
    // Make sure values are in range 0...1
    float top = interpolate(texture2D(baseNoise, vec2(coord1,coord3)).r, texture2D(baseNoise, vec2(coord2, coord3)).r, horizontal_blend);
    float bottom = interpolate(texture2D(baseNoise, vec2(coord1, coord4)).r, texture2D(baseNoise, vec2(coord2, coord4)).r, horizontal_blend);
    out1 = interpolate(top, bottom, vertical_blend);
    
    return out1;
}

void main( void )
{
    float noiseOctaves[20];
    float persistence_copy = persistence;
    float amplitude_copy = amplitude;
    float totalAmplitude = 0.0f;
  
    for (int i = 0; i < octaveSetter && i < 20; i++)
    {
        noiseOctaves[i] = noise2(texCoord.st, i);
    }
    
    float finalColor = 0.0f;
    
    for (int i = octaveSetter-1; i >= 0; i--)
    {
        amplitude_copy *= persistence_copy;
        totalAmplitude += amplitude_copy;
        finalColor += (noiseOctaves[i] * amplitude_copy);
    }
    
    // Normalize the noise
    //finalColor = finalColor / totalAmplitude;
    
    float n = finalColor;
    vec4 col = vec4(n,n,n,1.0f);
    gl_FragColor = v_color * col;
}
