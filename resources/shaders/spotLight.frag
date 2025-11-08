#version 420 core
out vec4 FragColor;

in vec3 outPos;

layout(std140, binding = 3) uniform SpotLightUBO {
    vec3 position;
    float cutOff;      // cos(угол внутреннего конуса)

    vec3 direction;
    float outerCutOff; // cos(угол внешнего конуса)
    float linear;
    float constant;
    float quadratic;
    vec3 lightColor;
    float intensity;
} SpotLight;

void main() {
    vec3 lightToFrag = normalize(SpotLight.position - outPos);

    float theta = dot(normalize(-SpotLight.direction), lightToFrag);

    float epsilon = SpotLight.cutOff - SpotLight.outerCutOff;
    float intensity = clamp((theta - SpotLight.outerCutOff) / epsilon, 0.0, 1.0);

    vec3 result = SpotLight.lightColor;
    result += SpotLight.lightColor * SpotLight.intensity * intensity;

    FragColor = vec4(result, 1.0);
}
