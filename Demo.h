#pragma once
#include "RenderEngine.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/vector_angle.hpp>
#include <SOIL/SOIL.h>

class Demo :
	public RenderEngine
{
public:
	Demo();
	~Demo();
private:
	bool lightOn;
	int oldKeyState = GLFW_RELEASE;
	float lightColR, lightColG, lightColB, lightX, lightY, lightZ;
	float viewCamX, viewCamY, viewCamZ, upCamX, upCamY, upCamZ, posCamX, posCamY, posCamZ, CAMERA_SPEED, fovy;
	GLuint backgroundVBO, backgroundVAO, backgroundEBO, texBackgroundID;
	GLuint tVBO, tVAO, tEBO, ttexture, stexture;
	GLuint atapVBO, atapVAO, atapEBO, texAtapID, texNormAtapID;
	GLuint wallVBO, wallVAO, wallEBO, texWallID, texNormWallID;
	GLuint pondasiVBO, pondasiVAO, pondasiEBO, texPondasiID, texNormPondasiID;
	GLuint tanggaVBO, tanggaVAO, tanggaEBO, texTanggaID, texNormTanggaID;
	GLuint pintuVBO, pintuVAO, pintuEBO, texPintuID, texNormPintuID;
	GLuint kipasVBO, kipasVAO, kipasEBO, texKipasID, texNormKipasID;
	GLuint lantai2VBO, lantai2VAO, lantai2EBO, texLantai2ID, texNormLantai2ID, railShaderProg;
	GLuint railVBO, railVAO, railEBO, texRailID, texNormRailID;
	GLuint activeProgram;
	bool toggleTextured = true;
	virtual void Init();
	virtual void DeInit();
	virtual void Update(double deltaTime);
	virtual void Render();
	virtual void ProcessInput(GLFWwindow *window);
	void MoveCamera(float speed);
	void StrafeCamera(float speed);
	void RotateCamera(float speed);
	void InitCamera();
	void BuildTexturedCube();
	void DrawTexturedCube(float x, float y, float z, float deg, int rotX, int rotY, int rotZ);
	void BuildWallCube();
	void DrawWallCube();
	void BuildAtap();
	void DrawAtap();
	void BuildPondasi();
	void DrawPondasi();
	void BuildPintu();
	void DrawPintu();
	void BuildTangga();
	void DrawTangga(float locX, float locY, float locZ);
	void BuildKipas();
	void DrawKipas(float x, float y, float z, float deg, int rotX, int rotY, int rotZ);
	void BuildLantai2();
	void DrawLantai2();
	void BuildRailLt2();
	void DrawRailLt2();
	void BuildBackground();
	void DrawBackground(float x, float y, float z, float scalex, float scaley, float scalez);
};

