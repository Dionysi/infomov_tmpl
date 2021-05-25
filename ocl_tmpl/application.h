#pragma once
#include <glew/glew.h>
#include <glfw/glfw3.h>

#include "cl_helper.h"


class Application {
	
public:
	Application(uint32_t width, uint32_t height);
	~Application();

	/** Starts the application's main-loop. */
	void Run();

	/** Tick function, getting called every frame.
	* @param[in] dt		Time since previous update call.
	*/
	virtual void Tick(float dt);

protected:
	/** Render width and height (also used as the initial window size). */
	uint32_t width, height;

	/** Quad used for rendering our texture. */
	const GLfloat renderQuad[18] = {
		-1.0f, -1.0f, 0.0f,
		-1.0f, 1.0f, 0.0f,
		1.0f,  1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		-1.0f, -1.0f, 0.0f
	};
	/** UV coordinates used for sampling our texture. */
	const GLfloat uv[12] = {
		0.0f, 0.0f,
		0.0f, 1.0f,
		1.0f, 1.0f,
		1.0f, 1.0f,
		1.0f, 0.0f,
		0.0f, 0.0f
	};

	/** Window handle. */
	GLFWwindow* window;
	/** Render variables. */
	GLuint programID, vertexArrayID, vertexBuffer, uvBuffer;
	/** Texture used for rendering. */
	GLuint renderTexture;

	/** Creates our OpenGL window. */
	GLFWwindow* CreateWindow();
	/** Initializes OpenGL and our window. */
	void InitGL();


	/* ==== EXAMPLE STUFF ==== */
	
	/** Our platform. */
	cl_platform_id platformId;
	/** GPU handle. */
	cl_device_id deviceId;
	/** OpenCL context. */
	cl_context context;
	/** Our main command queue. */
	cl_command_queue queue;
	/** OpenCL program. */
	cl_program program;
	/** OpenCL template. */
	cl_kernel kernel;
	/** OpenGL render target. */
	cl_mem renderBuffer;

	/** Our work sizes. */
	size_t globalDim[2] = { 1, 1 };
	size_t localDim[2] = { 32, 32 };

	int offset = 0;
	float timePassed = 0.0f;
	/** Initializes everything for OpenCL. */
	void InitCL();
};

