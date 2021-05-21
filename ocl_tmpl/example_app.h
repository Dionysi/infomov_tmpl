#pragma once
#include "application.h"
#include "cl_helper.h"

class ExampleApp :
    public Application {

public:
	
	ExampleApp(int width, int height);
	~ExampleApp();

	/** Simple coloring of the screen.
	* @param[in] dt		Time since previous update call.
	*/
    void Tick(float dt) override;


private:
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
	void InitOpenCL();
};

