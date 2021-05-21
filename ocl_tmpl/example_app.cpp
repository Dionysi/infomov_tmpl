#include "example_app.h"

ExampleApp::ExampleApp(int width, int height)
	: Application(width, height) {

	InitOpenCL();

	globalDim[0] = width;
	globalDim[1] = height;
}

ExampleApp::~ExampleApp() {
	Application::~Application();

	// Deallocate GPU memory.
	CLhelper::ReleaseMemoryBuffer(renderBuffer);
	CLhelper::ReleaseKernel(kernel);
	CLhelper::ReleaseCommandQueue(queue);
	CLhelper::ReleaseProgram(program);
	CLhelper::ReleaseContext(context);
	CLhelper::ReleaseDevice(deviceId);
}

void ExampleApp::Tick(float dt) {

	// Compute the offset.
	timePassed += dt;
	if (timePassed > 0.1f)
		timePassed = 0, offset++;

	CLhelper::AcquireGLObjects(queue, 1, &renderBuffer); 
	CLhelper::SetKernelArg(kernel, 2, sizeof(int), &offset);
	CLhelper::EnqueueKernel(queue, kernel, 2, globalDim, localDim);
	CLhelper::ReleaseGLObjects(queue, 1, &renderBuffer);
	CLhelper::WaitForQueueToFinish(queue);

}

void ExampleApp::InitOpenCL() {
	// Select our GPU and create an OpenCL context.
	CLhelper::GetPlatformAndDevice(platformId, deviceId);
	CLhelper::PrintDeviceInfo(deviceId);
	CLhelper::CreateContext(context, platformId, &deviceId);

	// Load and build our OpenCL source code.
	const char* source;
	size_t* sizes = (size_t*)malloc(sizeof(size_t) * 1);
	source = CLhelper::ReadSource("example.cl", sizes);
	CLhelper::CreateProgram(program, context, 1, &source, sizes);
	CLhelper::BuildProgram(program, deviceId);

	// Create required components for our 
	CLhelper::CreateCommandQueue(queue, context, deviceId, CL_QUEUE_PROFILING_ENABLE);

	// Create our buffers.
	CLhelper::CreateCLBufferFromGLTexture(renderBuffer, context, renderTexture);

	CLhelper::CreateKernel(kernel, program, "example");
	CLhelper::SetKernelArg(kernel, 0, sizeof(uint32_t), &width);
	CLhelper::SetKernelArg(kernel, 1, sizeof(uint32_t), &height);
	CLhelper::SetKernelArg(kernel, 2, sizeof(int), &offset);
	CLhelper::SetKernelArg(kernel, 3, sizeof(cl_mem), &renderBuffer);
}
