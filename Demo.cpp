#include "Demo.h"



Demo::Demo() {

}

Demo::~Demo() {
}

void Demo::Init() {
	// build and compile our shader program
	// ------------------------------------
	lightColR = 0.5f;
	lightColG = 0.5f;
	lightColB = 0.5f;
	lightX = 0;
	lightY = 5;
	lightZ = -6;
	lightOn = true;
	activeProgram = BuildShader("vertexShader.vert", "fragmentShader.frag", nullptr);
	UseShader(this-> activeProgram);
	BuildTexturedCube();
	BuildBackground();
	BuildWallCube();
	BuildAtap();
	BuildPintu();
	BuildPondasi();
	BuildKipas();
	BuildTangga();
	BuildLantai2();
	BuildRailLt2();
	InitCamera();
}

void Demo::DeInit() {
	// optional: de-allocate all resources once they've outlived their purpose:
	// ------------------------------------------------------------------------
	
	glDeleteVertexArrays(1, &tVAO);
	glDeleteBuffers(1, &tVBO);
	glDeleteBuffers(1, &tEBO);
	glDeleteVertexArrays(1, &wallVAO);
	glDeleteBuffers(1, &wallVBO);
	glDeleteBuffers(1, &wallEBO);
	glDeleteVertexArrays(1, &atapVAO);
	glDeleteBuffers(1, &atapVBO);
	glDeleteBuffers(1, &atapEBO);
	glDeleteVertexArrays(1, &pondasiVAO);
	glDeleteBuffers(1, &pondasiVBO);
	glDeleteBuffers(1, &pondasiEBO);
	glDeleteVertexArrays(1, &pintuVAO);
	glDeleteBuffers(1, &pintuVBO);
	glDeleteBuffers(1, &pintuEBO);
	glDeleteVertexArrays(1, &tanggaVAO);
	glDeleteBuffers(1, &tanggaVBO);
	glDeleteBuffers(1, &tanggaEBO);
	glDeleteVertexArrays(1, &kipasVAO);
	glDeleteBuffers(1, &kipasVBO);
	glDeleteBuffers(1, &kipasEBO);
	glDeleteVertexArrays(1, &railVAO);
	glDeleteBuffers(1, &railVBO);
	glDeleteBuffers(1, &railEBO);
	glDeleteVertexArrays(1, &lantai2VAO);
	glDeleteBuffers(1, &lantai2VBO);
	glDeleteBuffers(1, &lantai2EBO);
	glDeleteVertexArrays(1, &backgroundVAO);
	glDeleteBuffers(1, &backgroundVBO);
	glDeleteBuffers(1, &backgroundEBO);

}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void Demo::MoveCamera(float speed)
{
	float x = viewCamX - posCamX;
	float z = viewCamZ - posCamZ;
	// forward positive cameraspeed and backward negative -cameraspeed.
	posCamX = posCamX + x * speed;
	posCamZ = posCamZ + z * speed;
	viewCamX = viewCamX + x * speed;
	viewCamZ = viewCamZ + z * speed;
}
void Demo::StrafeCamera(float speed)
{
	float x = viewCamX - posCamX;
	float z = viewCamZ - posCamZ;
	float orthoX = -z;
	float orthoZ = x;

	// left positive cameraspeed and right negative -cameraspeed.
	posCamX = posCamX + orthoX * speed;
	posCamZ = posCamZ + orthoZ * speed;
	viewCamX = viewCamX + orthoX * speed;
	viewCamZ = viewCamZ + orthoZ * speed;
}
void Demo::RotateCamera(float speed)
{
	float x = viewCamX - posCamX;
	float z = viewCamZ - posCamZ;
	viewCamZ = (float)(posCamZ + glm::sin(speed) * x + glm::cos(speed) * z);
	viewCamX = (float)(posCamX + glm::cos(speed) * x - glm::sin(speed) * z);
}
void Demo::InitCamera()
{
	posCamX = -3.0f;
	posCamY = 1.0f;
	posCamZ = 5.0f;
	viewCamX = 1.0f;
	viewCamY = 1.5f;
	viewCamZ = -3.0f;
	upCamX = 0.0f;
	upCamY = 1.0f;
	upCamZ = 0.0f;
	CAMERA_SPEED = 0.001f;
	fovy = 45.0f;
	glfwSetInputMode(this->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void Demo::ProcessInput(GLFWwindow *window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
	int newKeyState = glfwGetKey(window, GLFW_KEY_SPACE);
	if (newKeyState == GLFW_RELEASE && oldKeyState == GLFW_PRESS) {
		toggleTextured = !toggleTextured;
		if (lightOn == true) {
			lightColR = 0.2f;lightColG = 0.2f;lightColB = 0.2f;
		}
		else {
			lightColR = 0.5f;lightColG = 0.5f;lightColB = 0.5f;
		}
		lightOn = !lightOn;
	}
	oldKeyState = newKeyState;
	// zoom camera
	// -----------
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {
		if (fovy < 90) {
			fovy += 0.0001f;
		}
	}

	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
		if (fovy > 0) {
			fovy -= 0.0001f;
		}
	}

	// update camera movement 
	// -------------
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		MoveCamera(CAMERA_SPEED);
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		MoveCamera(-CAMERA_SPEED);
	}

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		StrafeCamera(-CAMERA_SPEED);
	}

	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		StrafeCamera(CAMERA_SPEED);
	}

	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
		posCamY += 0.01f;
	}
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
		posCamY -= 0.01f;
	}
	if (glfwGetKey(window, GLFW_KEY_J)) {
		lightX += 0.01f;
	}
	if (glfwGetKey(window, GLFW_KEY_L)) {
		lightX -= 0.01f;
	}
	if (glfwGetKey(window, GLFW_KEY_I)) {
		lightZ += 0.01f;
	}
	if (glfwGetKey(window, GLFW_KEY_K)) {
		lightZ -= 0.01f;
	}
	if (glfwGetKey(window, GLFW_KEY_R)) {
		lightColR = 1.0f;
		lightColG = 0.5f;
		lightColB = 0.5f;
	}
	if (glfwGetKey(window, GLFW_KEY_B) ){
		lightColR = 0.5f;
		lightColG = 0.5f;
		lightColB = 1.0f;
	}
	if (glfwGetKey(window, GLFW_KEY_N)) {
		lightColR = 0.5f;
		lightColG = 0.5f;
		lightColB = 0.5f;
	}

	// update camera rotation
	// ----------------------
	double mouseX, mouseY;
	double midX = screenWidth / 2;
	double midY = screenHeight / 2;
	float angleY = 0.0f;
	float angleZ = 0.0f;

	// Get mouse position
	glfwGetCursorPos(window, &mouseX, &mouseY);
	if ((mouseX == midX) && (mouseY == midY)) {
		return;
	}

	// Set mouse position
	glfwSetCursorPos(window, midX, midY);

	// Get the direction from the mouse cursor, set a resonable maneuvering speed
	angleY = (float)((midX - mouseX)) / 1000;
	angleZ = (float)((midY - mouseY)) / 1000;

	// The higher the value is the faster the camera looks around.
	viewCamY += angleZ * 2;

	// limit the rotation around the x-axis
	if ((viewCamY - posCamY) > 8) {
		viewCamY = posCamY + 8;
	}
	if ((viewCamY - posCamY) < -8) {
		viewCamY = posCamY - 8;
	}
	RotateCamera(-angleY);
}

void Demo::Update(double deltaTime) {
}

void Demo::Render() {
	glViewport(0, 0, this->screenWidth, this->screenHeight);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);

	// Pass perspective projection matrix
	glm::mat4 projection = glm::perspective(45.0f, (GLfloat)this->screenWidth / (GLfloat)this->screenHeight, 0.1f, 100.0f);
	GLint projLoc = glGetUniformLocation(this->activeProgram, "projection");
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

	// LookAt camera (position, target/direction, up)
	glm::mat4 view = glm::lookAt(glm::vec3(posCamX, posCamY, posCamZ), glm::vec3(viewCamX, viewCamY, viewCamZ), glm::vec3(upCamX, upCamY, upCamZ));
	GLint viewLoc = glGetUniformLocation(this->activeProgram, "view");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

	// set lighting attributes
	GLint lightPosLoc = glGetUniformLocation(this->activeProgram, "lightPos");
	glUniform3f(lightPosLoc, lightX, lightY, lightZ);

	GLint viewPosLoc = glGetUniformLocation(this->activeProgram, "viewPos");
	glUniform3f(viewPosLoc, 0, 2, 3);

	GLint lightColorLoc = glGetUniformLocation(this->activeProgram, "lightColor");
	glUniform3f(lightColorLoc, lightColR, lightColG, lightColB);

	DrawBackground(0, 0, -0, 10, 10, 10);
	DrawBackground(0, 0, 0, 10, 10, -10);
	DrawAtap();
	DrawWallCube();
	DrawKipas(2, 6, -7, 2 * glfwGetTime(), 0, 0, 1);
	DrawKipas(0, 6, -7, 2 * glfwGetTime(), 0, 0, 1);
	DrawKipas(-2, 6, -7, 2 * glfwGetTime(), 0, 0, 1);
	DrawPintu();
	DrawLantai2();
	DrawRailLt2();
	DrawTangga(-12, 0, 0);
	DrawTangga(-12, 1, 1);
	DrawTangga(-12, 2, 2);
	DrawTangga(-12, 3, 3);
	DrawTangga(-12, 4, 4);
	DrawTangga(-12, 5, 5);
	DrawTangga(-12, 6, 6);
	DrawTexturedCube(5, 0.5, -6, 2.0f, 0, 1, 0);
	DrawTexturedCube(5, 1.5, -6, 0, 0, 1, 0);
	DrawTexturedCube(5, 0.5, -5, 0, 0, 1, 0);
	DrawTexturedCube(5, 0.5, -4, 0, 0, 1, 0);
	DrawTexturedCube(5, 1.5, -4, 1, 0, 1, 0);
	DrawTexturedCube(4, 0.5, -6, 0, 0, 1, 0);
	DrawTexturedCube(4, 1.5, -6, 0.2f, 0, 1, 0);
	DrawPondasi();
	
	glDisable(GL_DEPTH_TEST);
}

void Demo::BuildAtap() 
{
	glGenTextures(1, &texAtapID);
	glBindTexture(GL_TEXTURE_2D, texAtapID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height;
	unsigned char* image = SOIL_load_image("TexAtapTexture.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);
	float atapVerts[] = {
		4.666666, 		5.333333,	7.38, 	-0.606989, 			-0.7947103,				0,		1.01455,			0.8022169,
		7, 				3,			-7.38,	-0.7071068,			-0.7071068,				0,		8.74259e-5f, 		0.9999127,
		4.666667, 		5.333333,	-7.38,	-0.606989, 			-0.7947103,				0,		8.74893e-5f,		0.8022168,
		-2.333333, 		6.666666,	7.38, 	0.3245381, 			-0.9458727,				0,		1.01455,			0.3587887,
		0, 				7,			-7.38,	0,					-1,						0,		8.74259e-5f,		0.5000001,
		-2.333333, 		6.666666,	-7.38,	0.3245381, 			-0.9458727,				0,		8.74893e-5f,		0.3587888,
		0, 				7,			7.38, 	0,					-1,						0,		1.01455, 			0.5,
		2.333333, 		6.666666,	-7.38,	-0.3245381,			-0.9458727,				0, 		8.74893e-5f,		0.6412113,
		0, 				7,			-7.38,	0,					-1,						0,		8.74259e-5f,		0.5000001,
		2.333333, 		6.666666,	7.38, 	-0.3245381,			-0.9458727,				0, 		1.01455, 			0.6412112,
		4.666667, 		5.333333,	-7.38,	-0.606989, 			-0.7947103,				0,		8.74893e-5f,		0.8022168,
		2.333333, 		6.666666,	-7.38,	-0.3245381,			-0.9458727,				0, 		8.74893e-5f,		0.6412113,
		-7,				3,			7.38, 	0.7071068,			-0.7071068,				0,		1.01455, 			8.74259e-5f,
		-4.666666, 		5.333333,	-7.38,	0.606989,			-0.7947103,				0,		8.74259e-5f,		0.1977833,
		-7,				3,			-7.38,	0.7071068,			-0.7071068,				0,		8.74259e-5f,		8.74576e-5f,
		-4.666667, 		5.333333,	7.38, 	0.606989,			-0.7947103,				0,		1.01455, 			0.1977832,
		-2.333333, 		6.666666,	-7.38,	0.3245381, 			-0.9458727,				0,		8.74893e-5f,		0.3587888,
		-4.666666, 		5.333333,	-7.38,	0.606989,			-0.7947103,				0,		8.74259e-5f,		0.1977833,
		4.666666, 		5.333333,	7.38, 	-0.606989, 			-0.7947103,				0,		1.01455, 			0.8022169,
		7, 				3,			7.38, 	-0.7071068,			-0.7071068,				0,		1.01455, 			0.9999127,
		7, 				3,			-7.38,	-0.7071068,			-0.7071068,				0,		8.74259e-5f,		0.9999127,
		-2.333333, 		6.666666,	7.38, 	0.3245381, 			-0.9458727,				0,		1.01455, 			0.3587887,
		0, 				7,			7.38, 	0,					-1,						0,		1.01455, 			0.5,
		0, 				7,			-7.38,	0,					-1,						0,		8.74259e-5f,		0.5000001,
		0, 				7,			7.38, 	0,					-1,						0,		1.01455, 			0.5,
		2.333333, 		6.666666,	7.38, 	-0.3245381,			-0.9458727,				0, 		1.01455, 			0.6412112,
		2.333333, 		6.666666,	-7.38,	-0.3245381,			-0.9458727,				0, 		8.74893e-5f,		0.6412113,
		2.333333, 		6.666666,	7.38, 	-0.3245381,			-0.9458727,				0, 		1.01455, 			0.6412112,
		4.666666, 		5.333333,	7.38, 	-0.606989, 			-0.7947103,				0,		1.01455, 			0.8022169,
		4.666667, 		5.333333,	-7.38,	-0.606989, 			-0.7947103,				0,		8.74893e-5f,		0.8022168,
		-7,				3,			7.38, 	0.7071068,			-0.7071068,				0,		1.01455, 			8.74259e-5f,
		-4.666667, 		5.333333,	7.38, 	0.606989,			-0.7947103,				0,		1.01455, 			0.1977832,
		-4.666666, 		5.333333,	-7.38,	0.606989,			-0.7947103,				0,		8.74259e-5f,		0.1977833,
		-4.666667, 		5.333333,	7.38, 	0.606989,			-0.7947103,				0,		1.01455, 			0.1977832,
		-2.333333, 		6.666666,	7.38, 	0.3245381, 			-0.9458727,				0,		1.01455, 			0.3587887,
		-2.333333, 		6.666666,	-7.38,	0.3245381, 			-0.9458727,				0,		8.74893e-5f, 		0.3587888,
	};
	unsigned int  atapIdx[] = {
		2, 1, 0,		5, 4, 3,
		8, 7, 6,		11, 10, 9,
		14, 13, 12,		17, 16, 15,
		20, 19, 18,		23, 22, 21,
		26, 25, 24,		29, 28, 27,
		32, 31, 30,		35, 34, 33,

	};

	glGenVertexArrays(1, &atapVAO);
	glGenBuffers(1, &atapVBO);
	glGenBuffers(1, &atapEBO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(atapVAO);

	glBindBuffer(GL_ARRAY_BUFFER, atapVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(atapVerts), atapVerts, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, atapEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(atapIdx), atapIdx, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(0));
	glEnableVertexAttribArray(0);

	// define normal pointer layout 2
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
void Demo::DrawAtap() {
	UseShader(this->activeProgram);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texAtapID);
	glUniform1i(glGetUniformLocation(this->activeProgram, "material.diffuse"), 0);

	GLint shininessMatLoc = glGetUniformLocation(this->activeProgram, "material.shininess");
	glUniform1f(shininessMatLoc, 0.4f);

	GLint flatTex = glGetUniformLocation(this->activeProgram, "flatTex");
	glUniform1f(flatTex, 0.0f);

	glBindVertexArray(atapVAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

	glm::mat4 model;
	model = glm::translate(model, glm::vec3(0, 0, 0));

	GLint modelLoc = glGetUniformLocation(this->activeProgram, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

void Demo::BuildPondasi() 
{
	glGenTextures(1, &texPondasiID);
	glBindTexture(GL_TEXTURE_2D, texPondasiID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height;
	unsigned char* image = SOIL_load_image("TexPondasiTexture.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	float pondasiVerts[] =
	{
		-0.4,		7.000001,		-0.4, 			-1,			0,			 0,				0.9330922,			1.953125,
		-0.4, 		0,				0.4, 			-1,			0,			 0,				0.7136629, 			6.75917e-5f,
		-0.4,		0,				-0.4, 			-1,			0,			 0,				0.9330925, 			6.75917e-5f,
		-0.4, 		7.000001,		0.4, 			0,			0,			 1,				0.7136628, 			1.953125,
		0.4, 		0,				0.4, 			0,			0,			 1,				0.4942334, 			6.75917e-5f,
		-0.4, 		0,				0.4, 			0,			0,			 1,				0.7136629, 			6.75917e-5f,
		0.4, 		7.000001,		0.4, 			1, 			0,			 0,				0.4942333, 			1.953125,
		0.4, 		0,				-0.4,			1, 			0,			 0,				0.2748038, 			6.76513e-5f,
		0.4, 		0,				0.4, 			1, 			0,			 0,				0.4942334, 			6.75917e-5f,
		0.4,		7.000001,		-0.4, 			0, 			0,			 -1,			0.2748039, 			1.953125,
		-0.4,		0,				-0.4, 			0, 			0,			 -1,			0.0553742, 			6.76513e-5f,
		0.4, 		0,				-0.4,			0, 			0,			 -1,			0.2748038, 			6.76513e-5f,
		-0.4,		7.000001,		-0.4, 			-1,			0,			 0,				0.9330922, 			1.953125,
		-0.4, 		7.000001,		0.4, 			-1,			0,			 0,				0.7136628, 			1.953125,
		-0.4, 		0,				0.4, 			-1,			0,			 0,				0.7136629, 			6.75917e-5f,
		-0.4, 		7.000001,		0.4, 			0,			0,			 1,				0.7136628, 			1.953125,
		0.4, 		7.000001,		0.4, 			0,			0,			 1,				0.4942333, 			1.953125,
		0.4, 		0,				0.4, 			0,			0,			 1,				0.4942334, 			6.75917e-5f,
		0.4, 		7.000001,		0.4, 			1, 			0,			 0,				0.4942333, 			1.953125,
		0.4,		7.000001,		-0.4, 			1, 			0,			 0,				0.2748039, 			1.953125,
		0.4, 		0,				-0.4,			1, 			0,			 0,				0.2748038, 			6.76513e-5f,
		0.4,		7.000001,		-0.4, 			0, 			0,			 -1,			0.2748039, 			1.953125,
		-0.4,		7.000001,		-0.4, 			0, 			0,			 -1,			0.0553745, 			1.953125,
		-0.4,		0,				-0.4, 			0, 			0,			 -1,			0.0553742, 			6.76513e-5f,
	};
	unsigned int pondasiIdx[] = 
	{
		2, 1, 0,		5, 4, 3,  
		8, 7, 6,		11, 10, 9,
		14, 13, 12,		17,	16, 15, 
		20, 19, 18,		23, 22,21,
	};
	glGenVertexArrays(1, &pondasiVAO);
	glGenBuffers(1, &pondasiVBO);
	glGenBuffers(1, &pondasiEBO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(pondasiVAO);

	glBindBuffer(GL_ARRAY_BUFFER, pondasiVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(pondasiVerts), pondasiVerts, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, pondasiEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(pondasiIdx), pondasiIdx, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(0));
	glEnableVertexAttribArray(0);

	// define normal pointer layout 2
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
void Demo::DrawPondasi() 
{
	UseShader(this->activeProgram);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texPondasiID);
	glUniform1i(glGetUniformLocation(this->activeProgram, "material.diffuse"), 0);

	GLint shininessMatLoc = glGetUniformLocation(this->activeProgram, "material.shininess");
	glUniform1f(shininessMatLoc, 0.4f);

	GLint flatTex = glGetUniformLocation(this->activeProgram, "flatTex");
	glUniform1f(flatTex, 0.0f);

	glBindVertexArray(pondasiVAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

	glm::mat4 model;
	model = glm::translate(model, glm::vec3(0, 0, 0));

	GLint modelLoc = glGetUniformLocation(this->activeProgram, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glDrawElements(GL_TRIANGLES, 24, GL_UNSIGNED_INT, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

void Demo::BuildTangga() 
{
	glGenTextures(1, &texTanggaID);
	glBindTexture(GL_TEXTURE_2D, texTanggaID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height;
	unsigned char* image = SOIL_load_image("TexTanggaTexture.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	float vertices[] =
	{
		1, 			1,		0, 						0, 0, 1,			0.9960938,		0.2929946,
		-1, 		1,		1, 						0, 0, 1,			1.54396e-4,		0.585526,
		-1, 		1,		0, 						0, 0, 1,			1.54396e-4,		0.2929946,

		1,			0.5,	-0.5,					0, 0, 1,			0.9960938,		1.54413e-4,
		-1,			0.5,	0.5,					0, 0, 1,			1.54413e-4,		0.2926858,
		-1,			0.5,	-0.5, 					0, 0, 1,			1.54396e-4,		1.54396e-4,

		1,			0, 		0,						-1, 0, 0,			0,				0.9998456,
		1, 			1,		0, 						-1, 0, 0,			0.9960938,		0.7929946,
		1, 			1,		1, 						-1, 0, 0,			0.9960938,		0.9998455,

		-1,			1, 		0,						-1, 0, 0,			0.9960938,		0.585526,
		-1, 		0,		0, 						-1, 0, 0,			0,				0.7926858,
		-1, 		0,		-1, 					-1, 0, 0,			1.54396e-4,		0.5858349,

		1, 			1,		0, 						0, 0, 1,			0.9960938,		0.2929946,
		1, 			1,		1, 						0, 0, 1,			0.9960938,		0.585526,
		-1, 		1,		1, 						0, 0, 1,			1.54396e-4,		0.585526,

		1,			0.5,	-0.5,					0, 0, 1,			0.9960938,		1.54413e-4,
		1,			0.5,	0.5,					0, 0, 1,			0.9960938,		0.2926858,
		-1,			0.5,	0.5,					0, 0, 1,			1.54413e-4,		0.2926858,

		1,			0,		0,						-1, 0, 0,			0,				0.9998456,
		1,			0,		-1, 					-1, 0, 0,			1.54396e-4,		0.7929947,
		1, 			1,		0, 						-1, 0, 0,			0.9960938,		0.7929946,

		-1,			1,		0,						-1, 0, 0,			0.9960938,		0.585526,
		-1,			1,		1, 						-1, 0, 0,			0.9960938,		0.7926857,
		-1, 		0,		0, 						-1, 0, 0,			0,				0.7926858,
		
		
	};
	unsigned int indices[] =
	{
		2, 1, 0,		5, 4, 3,
		8, 7, 6,		9, 10, 11,
		14, 13, 12,		17,	16, 15,
		20, 19, 18,		21, 22,23,
	};
	glGenVertexArrays(1, &tanggaVAO);
	glGenBuffers(1, &tanggaVBO);
	glGenBuffers(1, &tanggaEBO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(tanggaVAO);

	glBindBuffer(GL_ARRAY_BUFFER, tanggaVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, tanggaEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(0));
	glEnableVertexAttribArray(0);

	// define normal pointer layout 2
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


}
void Demo::DrawTangga(float locX, float locY, float locZ) 
{
	UseShader(this->activeProgram);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texTanggaID);
	glUniform1i(glGetUniformLocation(this->activeProgram, "material.diffuse"), 0);

	GLint shininessMatLoc = glGetUniformLocation(this->activeProgram, "material.shininess");
	glUniform1f(shininessMatLoc, 0.4f);

	GLint flatTex = glGetUniformLocation(this->activeProgram, "flatTex");
	glUniform1f(flatTex, 0.0f);

	glBindVertexArray(tanggaVAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

	glm::mat4 model;


	model = glm::scale(model, glm::vec3(0.5, 0.5, 0.5));
	model = glm::rotate(model, (glm::mediump_float)1.56f, glm::vec3(0, 1, 0));
	model = glm::translate(model, glm::vec3(locX, locY, locZ));

	GLint modelLoc = glGetUniformLocation(this->activeProgram, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glDrawElements(GL_TRIANGLES, 24, GL_UNSIGNED_INT, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

void Demo::BuildWallCube()
{
	// load image into texture memory
	// ------------------------------
	// Load and create a texture 
	glGenTextures(1, &texWallID);
	glBindTexture(GL_TEXTURE_2D, texWallID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	int width, height;
	unsigned char* image = SOIL_load_image("TexRuanganTexture.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	glGenTextures(1, &texNormWallID);
	glBindTexture(GL_TEXTURE_2D, texNormWallID);
	
	image = SOIL_load_image("TexRuangan.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	
	
	float vertices[] = {
		// pos xyz												norm xyz,										 uv

		-6,			0,			-6.937562,		1, 			0,				0,				0.2089325,			0.7101406,
		-6,			5,			7,				1, 			0,				0,				0.7910674,			0.9189775,
		-6,			5,			-6.937562,		1, 			0,				0,				0.2089325,			0.9189773,

		-6,			0,			7,				0, 			0,				-1,				0.7910675,			0.7101408,
		6,			5,			7,				0, 			0,				-1,				0.9999041,			0.2089326,
		-6, 		5,			7,				0, 			0,				-1,				0.9999042,			0.7101408,

		6, 			0,			7, 				-1, 		0,				0,				0.7910676,			0.2089326,
		6, 			5,			-6.937562,		-1, 		0,				0,				0.2089326,			9.58491e-5f,
		6,			5,			7,				-1, 		0,				0,				0.7910676,			9.58491e-5f,

		6, 			0,			-6.937562, 		0, 			0,				1,				0.2089325,			0.2089325,
		-6, 		5,			-6.937562, 		0, 			0,				1,				9.58491e-5f,		0.7101406,
		6, 			5,			-6.937562, 		0, 			0,				1,				9.58491e-5f,		0.2089325,

		6, 			0,			-6.937562, 		0, 			1,				0,				0.2089325,			0.2089325,
		-6,			0,			7,				0, 			1,				0,				0.7910675,			0.7101408,
		-6,			0,			-6.937562,		0, 			1,				0,				0.2089325,			0.7101406,

		-6,			0,			-6.937562,		1, 			0,				0,				0.2089325,			0.7101406,
		-6,			0,			7,				1, 			0,				0,				0.7910675,			0.7101408,
		-6,			5,			7,				1, 			0,				0,				0.7910674,			0.9189775,

		-6,			0,			7,				0, 			0,				-1,				0.7910675,			0.7101408,
		6, 			0,			7, 				0, 			0,				-1,				0.7910676,			0.2089326,
		6,			5,			7,				0, 			0,				-1,				0.9999041,			0.2089326,

		6, 			0,			7, 				-1, 		0,				0,				0.7910676,			0.2089326,
		6, 			0,			-6.937562, 		-1, 		0,				0,				0.2089325,			0.2089325,
		6, 			5,			-6.937562,		-1, 		0,				0,				0.2089326,			9.58491e-5f,

		6, 			0,			-6.937562, 		0, 			0,				1,				0.2089325,			0.2089325,
		-6,			0,			-6.937562,		0, 			0,				1,				0.2089325,			0.7101406,
		-6, 		5,			-6.937562, 		0, 			0,				1,				9.58491e-5f,		0.7101406,

		6, 			0,			-6.937562, 		0, 			1,				0,				0.2089325,			0.2089325,
		6, 			0,			7, 				0, 			1,				0,				0.7910676,			0.2089326,
		-6,			0,			7,				0, 			1,				0,				0.7910675,			0.7101408,
	};

	unsigned int indices[] = {
		
		//0, 1, 2,		3, 4, 5,	
		2, 1, 0,		5, 4, 3,

		//6, 7, 8,		9, 10, 11,
		8, 7, 6,		11, 10, 9,

		//12, 13, 14,		15, 16, 17,		
		14, 13, 12,		17, 16, 15,

		//18, 19, 20,		21, 22, 23,
		20, 19, 18,		23, 22, 21,

		//24, 25, 26,		27, 28, 29,
		26, 25, 24,		29, 28, 27,
	
	};
	glGenVertexArrays(1, &wallVAO);
	glGenBuffers(1, &wallVBO);
	glGenBuffers(1, &wallEBO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(wallVAO);

	glBindBuffer(GL_ARRAY_BUFFER, wallVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, wallEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	
	// define position pointer layout 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(0));
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	
	

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);

	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
void Demo::DrawWallCube()
{
	UseShader(this->activeProgram);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texWallID);
	glUniform1i(glGetUniformLocation(this->activeProgram, "material.diffuse"), 0);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texNormWallID);
	glUniform1i(glGetUniformLocation(this->activeProgram, "material.specular"), 1);

	GLint shininessMatLoc = glGetUniformLocation(this->activeProgram, "material.shininess");
	glUniform1f(shininessMatLoc, 0.4f);

	GLint flatTex = glGetUniformLocation(this->activeProgram, "flatTex");
	glUniform1f(flatTex, 0.0f);

	glBindVertexArray(wallVAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

	glm::mat4 model;
	model = glm::translate(model, glm::vec3(0, 0, 0));

	GLint modelLoc = glGetUniformLocation(this->activeProgram, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glDrawElements(GL_TRIANGLES, 30, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

void Demo::BuildPintu() {
	glGenTextures(1, &texPintuID);
	glBindTexture(GL_TEXTURE_2D, texPintuID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height;
	unsigned char* image = SOIL_load_image("TexPintuTexture.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	glGenTextures(1, &texNormPintuID);
	glBindTexture(GL_TEXTURE_2D, texNormPintuID);

	image = SOIL_load_image("TexPintuNormal.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------


	float vertices[] = {
		// pos xyz												norm xyz,										 uv

		-1.4,	2,	0,			0, 0, 1,	0.9917837, 0.9999026,
		1.4,	0,	0,			0, 0, 1,	9.71814e-5, 9.73344e-5f,
		-1.4,	0,	0,			0, 0, 1,	0.9917837, 9.72152e-5f,
		-1.4,	2,	0,			0, 0, 1,	0.9917837, 0.9999026,
		1.4,	2,	0,			0, 0, 1,	9.73427e-5f, 0.9999027,
		1.4,	0,	0,			0, 0, 1,	9.71814e-5f, 9.73344e-5f,
	};

	unsigned int indices[] = {

		2, 1, 0, 5, 4, 3

	};
	glGenVertexArrays(1, &pintuVAO);
	glGenBuffers(1, &pintuVBO);
	glGenBuffers(1, &pintuEBO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(pintuVAO);

	glBindBuffer(GL_ARRAY_BUFFER, pintuVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, pintuEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// define position pointer layout 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(0));
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);



	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);

	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
void Demo::DrawPintu() {
	UseShader(this->activeProgram);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texPintuID);
	glUniform1i(glGetUniformLocation(this->activeProgram, "material.diffuse"), 0);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texNormPintuID);
	glUniform1i(glGetUniformLocation(this->activeProgram, "material.specular"), 1);

	GLint shininessMatLoc = glGetUniformLocation(this->activeProgram, "material.shininess");
	glUniform1f(shininessMatLoc, 0.4f);

	GLint flatTex = glGetUniformLocation(this->activeProgram, "flatTex");
	glUniform1f(flatTex, 0.0f);

	glBindVertexArray(pintuVAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

	glm::mat4 model;
	model = glm::translate(model, glm::vec3(0, 0, -6.925509));

	GLint modelLoc = glGetUniformLocation(this->activeProgram, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glDrawElements(GL_TRIANGLES, 30, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

void Demo::BuildTexturedCube() {

	glGenTextures(1, &ttexture);
	glBindTexture(GL_TEXTURE_2D, ttexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height;
	unsigned char* image = SOIL_load_image("crate_diffusemap.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	glGenTextures(1, &stexture);
	glBindTexture(GL_TEXTURE_2D, stexture);

	image = SOIL_load_image("crate_specularmap.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);



	float vertices[] = {
	// format position, tex coords
	// front
	-0.5, -0.5, 0.5, 0, 0, 0.0f,  0.0f,  1.0f, // 0
	0.5, -0.5, 0.5, 1, 0,  0.0f,  0.0f,  1.0f, // 1
	0.5,  0.5, 0.5, 1, 1,  0.0f,  0.0f,  1.0f, // 2
	-0.5,  0.5, 0.5, 0, 1, 0.0f,  0.0f,  1.0f, // 3

	// right
	0.5,  0.5,  0.5, 0, 0, 1.0f,  0.0f,  0.0f, // 4
	0.5,  0.5, -0.5, 1, 0, 1.0f,  0.0f,  0.0f, // 5
	0.5, -0.5, -0.5, 1, 1, 1.0f,  0.0f,  0.0f, // 6
	0.5, -0.5,  0.5, 0, 1, 1.0f,  0.0f,  0.0f, // 7

	// back
	-0.5, -0.5, -0.5, 0, 0, 0.0f,  0.0f,  -1.0f, // 8 
	0.5,  -0.5, -0.5, 1, 0, 0.0f,  0.0f,  -1.0f, // 9
	0.5,   0.5, -0.5, 1, 1, 0.0f,  0.0f,  -1.0f, // 10
	-0.5,  0.5, -0.5, 0, 1, 0.0f,  0.0f,  -1.0f, // 11

											   // left
	-0.5, -0.5, -0.5, 0, 0, -1.0f,  0.0f,  0.0f, // 12
	-0.5, -0.5,  0.5, 1, 0, -1.0f,  0.0f,  0.0f, // 13
	-0.5,  0.5,  0.5, 1, 1, -1.0f,  0.0f,  0.0f, // 14
	-0.5,  0.5, -0.5, 0, 1, -1.0f,  0.0f,  0.0f, // 15

	// upper
	0.5, 0.5,  0.5, 0, 0,   0.0f,  1.0f,  0.0f, // 16
	-0.5, 0.5, 0.5, 1, 0,   0.0f,  1.0f,  0.0f, // 17
	-0.5, 0.5, -0.5, 1, 1,  0.0f,  1.0f,  0.0f, // 18
	0.5, 0.5, -0.5, 0, 1,   0.0f,  1.0f,  0.0f, // 19

	// bottom
	-0.5, -0.5, -0.5, 0, 0, 0.0f,  -1.0f,  0.0f, // 20
	0.5, -0.5, -0.5, 1, 0,  0.0f,  -1.0f,  0.0f, // 21
	0.5, -0.5,  0.5, 1, 1,  0.0f,  -1.0f,  0.0f, // 22
	-0.5, -0.5,  0.5, 0, 1, 0.0f,  -1.0f,  0.0f, // 23
	};

	unsigned int indices[] = {
		0,  1,  2,  0,  2,  3,   // front
		6,  5,  4,  7,  6,  4,   // right
		10,  9,  8, 11,  10, 8,  // back
		13, 14, 12, 14, 15, 12,  // left
		16, 18, 17, 16, 19, 18,  // upper
		22, 21, 20, 20, 22, 23   // bottom
	};

	glGenVertexArrays(1, &tVAO);
	glGenBuffers(1, &tVBO);
	glGenBuffers(1, &tEBO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(tVAO);

	glBindBuffer(GL_ARRAY_BUFFER, tVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, tEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


	// define position pointer layout 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);

	// define texcoord pointer layout 1
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	// define normal pointer layout 2
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(5 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}
void Demo::DrawTexturedCube(float x, float y, float z, float deg, int rotX, int rotY, int rotZ) {
	UseShader(this->activeProgram);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, ttexture);
	glUniform1i(glGetUniformLocation(this->activeProgram, "material.diffuse"), 0);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, stexture);
	glUniform1i(glGetUniformLocation(this->activeProgram, "material.specular"), 1);

	GLint shininessMatLoc = glGetUniformLocation(this->activeProgram, "material.shininess");
	glUniform1f(shininessMatLoc, 0.4f);

	GLint flatTex = glGetUniformLocation(this->activeProgram, "flatTex");
	glUniform1f(flatTex, 0.0f);

	glBindVertexArray(tVAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

	glm::mat4 model;

	
	model = glm::translate(model, glm::vec3(x, y, z));
	model = glm::rotate(model, (glm::mediump_float)deg, glm::vec3(rotX, rotY, rotZ));

	GLint modelLoc = glGetUniformLocation(this->activeProgram, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glDrawElements(GL_TRIANGLES, 30, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

void Demo::BuildKipas() {
	// Load and create a texture 
	glGenTextures(1, &texKipasID);
	glBindTexture(GL_TEXTURE_2D, texKipasID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height;
	unsigned char* image = SOIL_load_image("texKipasTexture.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	glGenTextures(1, &texNormKipasID);
	glBindTexture(GL_TEXTURE_2D, texNormKipasID);

	image = SOIL_load_image("TexKipasNormal.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);


	// Build geometry
	GLfloat vertices[] = {
		// format position, tex coords
		// bottom
		-0.09375,		0.09375,		0,			0,  0,	1,		0.4117822, 0.5882176,
		0.09375,		-0.09375,		0,			0,  0,	1,		0.5882175, 0.4117823,
		- 0.09375,		-0.09375,		0,			0,  0,	1,		0.4117822, 0.4117823,

		0.53125,		0.09375,		0,			0,  0,	1,		0.9998997, 0.5882176,
		0.09375,		-0.09375,		0,			0,  0,	1,		0.5882175, 0.4117823,
		0.09375,		0.09375,		0,			0,  0,	1,		0.5882175, 0.5882176,

		-0.09375,		0.53125,		0,			0,  0,	1,		0.4117822, 0.9998999,
		0.09375,		0.09375,		0,			0,  0,	1,		0.5882175, 0.5882176,
		- 0.09375,		0.09375,		0,			0,  0,	1,		0.4117822, 0.5882176,

		-0.53125,		-0.09375,		0,			0,  0,	1,		9.998e-5,	0.4117823,
		- 0.09375,		0.09375,		0,			0,  0,	1,		0.4117822,	0.5882176,
		- 0.09375,		-0.09375,		0,			0,  0,	1,		0.4117822,	0.4117823,

		0.09375,		-0.53125,		0,			0,  0,	1,		0.5882174, 9.998e-5,
		- 0.09375,		-0.09375,		0,			0,  0,	1,		0.4117822, 0.4117823,
		0.09375,		-0.09375,		0,			0,  0,	1,		0.5882175, 0.4117823,

		-0.09375,		0.09375,		0,			0,  0,	1,		0.4117822f,		0.5882176f,
		0.09375,		0.09375,		0,			0,  0,	1,		0.5882175f,		0.5882176f,
		0.09375,		-0.09375,		0,			0,  0,	1,		0.5882175f,		0.4117823f,

		0.53125,		0.09375,		0,			0,  0,	1,		0.9998997f,		0.5882176f,
		0.53125,		-0.09375,		0,			0,  0,	1,		0.9998997f,		0.4117823f,
		0.09375,		-0.09375,		0,			0,  0,	1,		0.5882175f,		0.4117823f,

		-0.09375,		0.53125,		0,			0,  0,	1,		0.4117822f,		0.9998999f,
		0.09375,		0.53125,		0,			0,  0,	1,		0.5882175f,		0.9998998f,
		0.09375,		0.09375,		0,			0,  0,	1,		0.5882175f,		0.5882176f,

		-0.53125,		-0.09375,		0,			0,  0,	1,		9.998e-5f,		0.4117823f,
		-0.53125,		0.09375,		0,			0,  0,	1,		9.998e-5f,		0.5882176f,
		-0.09375,		0.09375,		0,			0,  0,	1,		0.4117822f,		0.5882176f,

		0.09375,		-0.53125,		0,			0,  0,	1,		0.5882174f,		9.998e-5f,
		-0.09375,		-0.53125,		0,			0,  0,	1,		0.4117821f,		1.00092e-4f,
		-0.09375,		-0.09375,		0,			0,  0,	1,		0.4117822f,		0.4117823f,
		
	};

	GLuint indices[] = {
		2, 1, 0, 
		5, 4, 3,
		8, 7, 6,
		11, 10, 9,
		14, 13, 12,
		17, 16, 15,
		20, 19, 18,
		23, 22, 21,
		26, 25, 24,
		29, 28, 27};

	glGenVertexArrays(1, &kipasVAO);
	glGenBuffers(1, &kipasVBO);
	glGenBuffers(1, &kipasEBO);

	glBindVertexArray(kipasVAO);

	glBindBuffer(GL_ARRAY_BUFFER, kipasVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, kipasEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), 0);
	glEnableVertexAttribArray(0);
	// TexCoord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);
	// Normal attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);


	glBindVertexArray(0); // Unbind VAO

}
void Demo::DrawKipas(float x, float y, float z, float deg, int rotX, int rotY, int rotZ) {
	UseShader(this->activeProgram);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texKipasID);
	glUniform1i(glGetUniformLocation(this->activeProgram, "ourTexture"), 0);

	GLint flatTex = glGetUniformLocation(this->activeProgram, "flatTex");
	glUniform1f(flatTex, 0.0f);

	glBindVertexArray(kipasVAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

	glm::mat4 model;
	model = glm::translate(model, glm::vec3(x, y, z));
	model = glm::rotate(model, (glm::mediump_float)deg, glm::vec3(rotX, rotY, rotZ));

	GLint modelLoc = glGetUniformLocation(this->activeProgram, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glDrawElements(GL_TRIANGLES, 30, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

void Demo::BuildRailLt2() {
	glGenTextures(1, &texRailID);
	glBindTexture(GL_TEXTURE_2D, texRailID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height;
	unsigned char* image = SOIL_load_image("texRailTextureV2.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);
	

	// Build geometry
	GLfloat vertices[] = {
		
		-3.116032,	0,			-4.390927,					0, -1, 0,					5.83862,		0.03779292,
		-0.6933129,	1.030126,	-4.390927,					0, -1, 0,					4.579566,		0.9674903,
		-0.6933129,	0,			-4.390927,					0, -1, 0,					4.579566,		0.03779304,

		-3.116032,	0,			-7.144633,  				-1, 0, 0,					7.269684,		0.0377928,
		-3.116032,	1.030126,	-4.390927,					-1, 0, 0,					5.83862,		0.96749,
		-3.116032,	 0,			-4.390927,					-1, 0, 0,					5.83862,		0.03779292,

		-0.6933129,	0,			-4.390927,					-1, 0, 0,					4.579566,		0.03779304,
		-0.6933129,	1.030126,	4.467858,					-1, 0, 0,					-0.02422285,	0.967491,
		-0.6933129,	0,			4.467858,					-1, 0, 0,					-0.02422285,	0.03779792,

		-3.116032,	0,			-4.390927,					0, -1, 0,					5.83862,		0.03779292,
		-3.116032,	1.030126,	-4.390927,					0, -1, 0,					5.83862,		0.96749,
		-0.6933129,	1.030126,	-4.390927,					0, -1, 0,					4.579566,		0.9674903,

		-3.116032,	0,			-7.144633, 					-1, 0, 0,					7.269684,		0.0377928,
		-3.116032, 	1.030126,	-7.144633,					-1, 0, 0,					7.269684,		0.9674898,
		-3.116032,	1.030126,	-4.390927, 					-1, 0, 0,					5.83862,		0.96749,

		-0.6933129,	0,			-4.390927, 					-1, 0, 0,					4.579566,		0.03779304,
		-0.6933129,	1.030126,	-4.390927, 					-1, 0, 0,					4.579566,		0.9674903,
		-0.6933129,	1.030126,	4.467858,					-1, 0, 0,					- 0.02422285,	0.967491,

	};

	GLuint indices[] = {
		2, 1, 0,
		5, 4, 3,
		8, 7, 6,
		11, 10, 9,
		14, 13, 12,
		17, 16, 15 
	};

	glGenVertexArrays(1, &railVAO);
	glGenBuffers(1, &railVBO);
	glGenBuffers(1, &railEBO);

	glBindVertexArray(railVAO);

	glBindBuffer(GL_ARRAY_BUFFER, railVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, railEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), 0);
	glEnableVertexAttribArray(0);
	// TexCoord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);
	// Normal attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);


	glBindVertexArray(0); // Unbind VAO
}
void Demo::DrawRailLt2() {
	UseShader(this->activeProgram);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texRailID);
	glUniform1i(glGetUniformLocation(this->activeProgram, "material.diffuse"), 0);

	GLint flatTex = glGetUniformLocation(this->activeProgram, "flatTex");
	glUniform1f(flatTex, 0.0f);

	glBindVertexArray(railVAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

	glm::mat4 model;
	model = glm::translate(model, glm::vec3(4, 3.5, 0.3));

	GLint modelLoc = glGetUniformLocation(this->activeProgram, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glDrawElements(GL_TRIANGLES, 30, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

void Demo::BuildLantai2() {
	glGenTextures(1, &texLantai2ID);
	glBindTexture(GL_TEXTURE_2D, texLantai2ID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height;
	unsigned char* image = SOIL_load_image("texLantai2Texture.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);


	// Build geometry
	GLfloat vertices[] = {

		-0.6933129,	0,		- 4.390927, 				0, 1, 0,					0.1642138, 0.813361,
		-3.116032,	0,		- 7.144633,					0, 1, 0,					6.84943e-5, 0.9999315,
		-3.116032,	0,		- 4.390927,					0, 1, 0,					6.85266e-5, 0.813361,
		-0.6933129,	0,		- 4.390927, 				0, 1, 0,					0.1642138, 0.813361,
		3.809345,	0,		7.612959,					0, 1, 0,					0.46928, 6.84943e-5,
		3.809345,	0,		- 7.144633, 				0, 1, 0,					0.46928, 0.9999314,
		-0.6933129,	0,		- 4.390927, 				0, 1, 0,					0.1642138, 0.813361,
		3.809345,	0,		- 7.144633, 				0, 1, 0,					0.46928, 0.9999314,
		-3.116032,	0,		- 7.144633, 				0, 1, 0,					6.84943e-5, 0.9999315,
		-0.6933129,	0,		- 4.390927, 				0, 1, 0,					0.1642138, 0.813361,
		-0.6933129,	0,		7.612959,	 				0, 1, 0,					0.1642138, 6.84943e-5,
		03.809345,	0,		7.612959,		 			0, 1, 0,					0.46928, 6.84943e-5,
					
					
					
					
					
					

	};

	GLuint indices[] = {
		2, 1, 0,
		5, 4, 3,
		8, 7, 6,
		11, 10, 9
	};

	glGenVertexArrays(1, &lantai2VAO);
	glGenBuffers(1, &lantai2VBO);
	glGenBuffers(1, &lantai2EBO);

	glBindVertexArray(lantai2VAO);

	glBindBuffer(GL_ARRAY_BUFFER, lantai2VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, lantai2EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), 0);
	glEnableVertexAttribArray(0);
	// TexCoord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);
	// Normal attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);


	glBindVertexArray(0); // Unbind VAO
}
void Demo::DrawLantai2() {
	UseShader(this->activeProgram);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texLantai2ID);
	glUniform1i(glGetUniformLocation(this->activeProgram, "material.diffuse"), 0);

	GLint shininessMatLoc = glGetUniformLocation(this->activeProgram, "material.shininess");
	glUniform1f(shininessMatLoc, 0.4f);

	GLint flatTex = glGetUniformLocation(this->activeProgram, "flatTex");
	glUniform1f(flatTex, 0.0f);

	glBindVertexArray(lantai2VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

	glm::mat4 model;
	model = glm::translate(model, glm::vec3(4, 3.5, 0.3));

	GLint modelLoc = glGetUniformLocation(this->activeProgram, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glDrawElements(GL_TRIANGLES, 30, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

void Demo::BuildBackground() {
	glGenTextures(1, &texBackgroundID);
	glBindTexture(GL_TEXTURE_2D, texBackgroundID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height;
	unsigned char* image = SOIL_load_image("texBackground.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);


	float verts[] = {
		14.56359,	11.3778,	0,			9.998e-5,			0.9999,
		0,			-11.3778,	-7,			0.5,				1.00003e-4,
		0,			11.3778,	-7,			0.5,				0.9999001,
		0,			11.3778,	-7,			0.5,				0.9999001,
		-14.56359,	-11.3778,	0,			0.9999,				9.998e-5,
		-14.56359,	11.3778,	0,			0.9999,				0.9999001,
		14.56359,	11.3778,	0,			9.998e-5,			0.9999,
		14.56359,	-11.3778,	0,			9.998e-5,			1.00027e-4,
		0,			-11.3778,	-7,			0.5,				1.00003e-4,
		0,			11.3778,	-7,			0.5,				0.9999001,
		0,			-11.3778,	-7,			0.5,				1.00003e-4,
		-14.56359,	-11.3778,	0,			0.9999,				9.998e-5,
	};
	unsigned int indices[] = {
		2, 1, 0,  5, 4, 3,
		8, 7, 6, 11, 10, 9
	};

	glGenVertexArrays(1, &backgroundVAO);
	glGenBuffers(1, &backgroundVBO);
	glGenBuffers(1, &backgroundEBO);

	glBindVertexArray(backgroundVAO);

	glBindBuffer(GL_ARRAY_BUFFER, backgroundVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, backgroundEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), 0);
	glEnableVertexAttribArray(0);
	// TexCoord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);
	// Normal attribute


	glBindVertexArray(0);

}
void Demo::DrawBackground(float x, float y, float z, float scaleX, float scaleY, float scaleZ) 
{
	UseShader(this->activeProgram);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texBackgroundID);
	glUniform1i(glGetUniformLocation(this->activeProgram, "material.diffuse"), 0);

	GLint flatTex = glGetUniformLocation(this->activeProgram, "flatTex");
	glUniform1f(flatTex, 1.0f);

	glBindVertexArray(backgroundVAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

	glm::mat4 model;
	model = glm::translate(model, glm::vec3(x, y, z));
	model = glm::scale(model, glm::vec3(scaleX, scaleY, scaleZ));
	

	GLint modelLoc = glGetUniformLocation(this->activeProgram, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

int main(int argc, char** argv) {
	RenderEngine &app = Demo();
	app.Start("Tugas Akhir Grafkom", 800, 600, false, false);
}