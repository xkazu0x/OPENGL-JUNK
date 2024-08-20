#version 460 core

struct Material {
	sampler2D ambient;
	sampler2D diffuse;
	sampler2D specular;
	float shininess;
};

struct DirectLight {
	vec3 direction;
	vec3 color;

	float ambient;
	float diffuse;
	float specular;
};

struct PointLight {
	vec3 position;
	vec3 color;

	float ambient;
	float diffuse;
	float specular;
};

struct SpotLight {
	vec3 position;
	vec3 direction;
	vec3 color;

	float inCutOff;
	float outCutOff;

	float ambient;
	float diffuse;
	float specular;
};

out vec4 color;

in vec3 vPos;
in vec3 vNormal;
in vec2 vTexCoord;

uniform Material material;

uniform PointLight pointLight;
uniform DirectLight directLight;
uniform SpotLight spotLight;

uniform vec3 viewPos;

vec3 CalcDirectLight(vec3 normal, vec3 viewDirection, vec3 ambientMap, vec3 diffuseMap, vec3 specularMap);
vec3 CalcPointLight(vec3 normal, vec3 viewDirection, vec3 ambientMap, vec3 diffuseMap, vec3 specularMap);
vec3 CalcSpotLight(vec3 normal, vec3 viewDirection, vec3 ambientMap, vec3 diffuseMap, vec3 specularMap);

void main() {
	vec3 normal = normalize(vNormal);
	vec3 viewDirection = normalize(viewPos - vPos);
	vec3 ambientMap = vec3(texture(material.ambient, vTexCoord));
	vec3 diffuseMap = vec3(texture(material.diffuse, vTexCoord));
	vec3 specularMap = vec3(texture(material.specular, vTexCoord).r);

	vec3 result;
	result += CalcPointLight(normal, viewDirection, ambientMap, diffuseMap, specularMap);
	result += CalcSpotLight(normal, viewDirection, ambientMap, diffuseMap, specularMap);

	color = vec4(result, 1.0);
}

vec3 CalcDirectLight(vec3 normal, vec3 viewDirection, vec3 ambientMap, vec3 diffuseMap, vec3 specularMap) {
	// Ambient
	vec3 ambient = directLight.ambient * directLight.color * ambientMap;

	// Diffuse
	vec3 lightDirection = normalize(-directLight.direction);
	float diff = max(dot(lightDirection, normal), 0.0);
	vec3 diffuse = directLight.diffuse * directLight.color * (diff * diffuseMap);

	// Specular
	vec3 reflectDirection = reflect(-lightDirection, normal);
	float spec = max(dot(viewDirection, reflectDirection), 0.0);
	spec = pow(spec, material.shininess * 16);
	vec3 specular = directLight.specular * directLight.color * (spec * specularMap);

	return vec3(ambient + diffuse + specular);
}

vec3 CalcPointLight(vec3 normal, vec3 viewDirection, vec3 ambientMap, vec3 diffuseMap, vec3 specularMap) {
	// Ambient
	vec3 ambient = pointLight.ambient * pointLight.color * ambientMap;

	// Diffuse
	vec3 lightDirection = normalize(pointLight.position - vPos);
	float diff = max(dot(lightDirection, normal), 0.0);
	diff = pow(diff, 2);
	vec3 diffuse = pointLight.diffuse * pointLight.color * (diff * diffuseMap);

	// Specular
	vec3 reflectDirection = reflect(-lightDirection, normal);
	float spec = max(dot(viewDirection, reflectDirection), 0.0);
	spec = pow(spec, material.shininess * 16);
	vec3 specular = pointLight.specular * pointLight.color * (spec * specularMap);

	float distance = length(pointLight.position - vPos);
	float attenuation = 1.0 / (1.0 + 0.2 * distance + 0.1 * (distance * distance));

	return vec3(ambient + diffuse + specular) * attenuation;
}

vec3 CalcSpotLight(vec3 normal, vec3 viewDirection, vec3 ambientMap, vec3 diffuseMap, vec3 specularMap) {
	vec3 lightDirection = normalize(spotLight.position - vPos);
	float theta = dot(lightDirection, normalize(-spotLight.direction));

	// Ambient
	vec3 ambient = spotLight.ambient * spotLight.color * ambientMap;

	if (theta > spotLight.outCutOff) {
		// Diffuse
		float diff = max(dot(lightDirection, normal), 0.0);
		vec3 diffuse = spotLight.diffuse * spotLight.color * (diff * diffuseMap);

		// Specular
		vec3 reflectDirection = reflect(-lightDirection, normal);
		float spec = max(dot(viewDirection, reflectDirection), 0.0);
		spec = pow(spec, material.shininess * 16);
		vec3 specular = spotLight.specular * spotLight.color * (spec * specularMap);

		float intensity = (theta - spotLight.outCutOff) / (spotLight.inCutOff - spotLight.outCutOff);
		intensity = clamp(intensity, 0.0, 1.0);
		diffuse *= intensity;
		specular *= intensity;

		float distance = length(spotLight.position - vPos);
		float attenuation = 1.0 / (1.0 + 0.8 * distance + 0.5 * (distance * distance));

		return vec3(ambient + diffuse + specular) * attenuation;
	}
	else {
		return ambient;
	}
}