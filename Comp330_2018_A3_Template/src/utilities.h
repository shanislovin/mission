/*
 * File: utilities.h
 * Author: Peter Reeves
 * Date 27 April 2018
 */

struct Rect {
	int bottomLeftX;
	int bottomLeftY;
	int topRightX;
	int topRightY;
};

struct Vector2 {
	float x;
	float y;
};

struct Vector3 {
	float x;
	float y;
	float z;
};

// Returns a random float between 0 and 1
float randFloat () {
	int r = rand();
	return (float) r / (float) RAND_MAX;
}

int loadGLTexture (const char *fileName) {
	const unsigned int index = SOIL_load_OGL_texture (
		fileName,
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y | SOIL_FLAG_MIPMAPS | SOIL_FLAG_TEXTURE_REPEATS
	);

	if(index == 0) {
		std::cerr << fileName << " : " << SOIL_last_result();
		return -1;
	}

	return index;
}

void drawString (std::string s) {
	glRasterPos2f(0, 0);
	for (unsigned int i = 0; i < s.size(); i += 1) {
		glutBitmapCharacter(GLUT_BITMAP_8_BY_13, s.at(i));
	}
}

// All parameters are 0 to 1 except for shininess which is 0 to 128
void setMaterial (
		float diffuseR, float diffuseG, float diffuseB,
		float specularR, float specularG, float specularB,
		float shininess,
		float emissionR, float emissionG, float emissionB
	) {
	const float materialColour [4] = { diffuseR, diffuseG, diffuseB, 1.0f };
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, materialColour);

	const float materialSpecular [4] = { specularR, specularG, specularB, 1.0f };
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, materialSpecular );

	const float materialShininess [1] = { shininess };
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, materialShininess);

	const float materialEmission [4] = { emissionR, emissionG, emissionB, 1.0f };
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, materialEmission);
}
