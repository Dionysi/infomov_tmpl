#pragma once
#include <glew/glew.h>
#include <glfw/glfw3.h>



class Application {
	
public:
	Application(uint32_t width, uint32_t height);
	~Application();

	/** Starts the application's main-loop. */
	void Run();

	/** Tick function, getting called every frame.
	* @param[in] dt		Time since previous update call.
	*/
	virtual void Tick(float dt) = 0;

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

};

