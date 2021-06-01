#include "cl_helper.h"

#include <string>
#include <CL/cl_gl.h>
#include <glew/glew.h>
#include <Windows.h>

#define CHECK_CL_ERROR CLhelper::CheckCLError

static const char* errorCodeStrings[] = {
	// Error Codes
	  "CL_SUCCESS"                                  //   0
	, "CL_DEVICE_NOT_FOUND"                         //  -1
	, "CL_DEVICE_NOT_AVAILABLE"                     //  -2
	, "CL_COMPILER_NOT_AVAILABLE"                   //  -3
	, "CL_MEM_OBJECT_ALLOCATION_FAILURE"            //  -4
	, "CL_OUT_OF_RESOURCES"                         //  -5
	, "CL_OUT_OF_HOST_MEMORY"                       //  -6
	, "CL_PROFILING_INFO_NOT_AVAILABLE"             //  -7
	, "CL_MEM_COPY_OVERLAP"                         //  -8
	, "CL_IMAGE_FORMAT_MISMATCH"                    //  -9
	, "CL_IMAGE_FORMAT_NOT_SUPPORTED"               //  -10
	, "CL_BUILD_PROGRAM_FAILURE"                    //  -11
	, "CL_MAP_FAILURE"                              //  -12
	, "CL_MISALIGNED_SUB_BUFFER_OFFSET"             //  -13
	, "CL_EXEC_STATUS_ERROR_FOR_EVENTS_IN_WAIT_LIST"//  -14
	, "CL_COMPILE_PROGRAM_FAILURE"                  //  -15
	, "CL_LINKER_NOT_AVAILABLE"                     //  -16
	, "CL_LINK_PROGRAM_FAILURE"                     //  -17
	, "CL_DEVICE_PARTITION_FAILED"                  //  -18
	, "CL_KERNEL_ARG_INFO_NOT_AVAILABLE"            //  -19

	, ""    //  -20
	, ""    //  -21
	, ""    //  -22
	, ""    //  -23
	, ""    //  -24
	, ""    //  -25
	, ""    //  -26
	, ""    //  -27
	, ""    //  -28
	, ""    //  -29

	, "CL_INVALID_VALUE"                            //  -30
	, "CL_INVALID_DEVICE_TYPE"                      //  -31
	, "CL_INVALID_PLATFORM"                         //  -32
	, "CL_INVALID_DEVICE"                           //  -33
	, "CL_INVALID_CONTEXT"                          //  -34
	, "CL_INVALID_QUEUE_PROPERTIES"                 //  -35
	, "CL_INVALID_COMMAND_QUEUE"                    //  -36
	, "CL_INVALID_HOST_PTR"                         //  -37
	, "CL_INVALID_MEM_OBJECT"                       //  -38
	, "CL_INVALID_IMAGE_FORMAT_DESCRIPTOR"          //  -39
	, "CL_INVALID_IMAGE_SIZE"                       //  -40
	, "CL_INVALID_SAMPLER"                          //  -41
	, "CL_INVALID_BINARY"                           //  -42
	, "CL_INVALID_BUILD_OPTIONS"                    //  -43
	, "CL_INVALID_PROGRAM"                          //  -44
	, "CL_INVALID_PROGRAM_EXECUTABLE"               //  -45
	, "CL_INVALID_KERNEL_NAME"                      //  -46
	, "CL_INVALID_KERNEL_DEFINITION"                //  -47
	, "CL_INVALID_KERNEL"                           //  -48
	, "CL_INVALID_ARG_INDEX"                        //  -49
	, "CL_INVALID_ARG_VALUE"                        //  -50
	, "CL_INVALID_ARG_SIZE"                         //  -51
	, "CL_INVALID_KERNEL_ARGS"                      //  -52
	, "CL_INVALID_WORK_DIMENSION"                   //  -53
	, "CL_INVALID_WORK_GROUP_SIZE"                  //  -54
	, "CL_INVALID_WORK_ITEM_SIZE"                   //  -55
	, "CL_INVALID_GLOBAL_OFFSET"                    //  -56
	, "CL_INVALID_EVENT_WAIT_LIST"                  //  -57
	, "CL_INVALID_EVENT"                            //  -58
	, "CL_INVALID_OPERATION"                        //  -59
	, "CL_INVALID_GL_OBJECT"                        //  -60
	, "CL_INVALID_BUFFER_SIZE"                      //  -61
	, "CL_INVALID_MIP_LEVEL"                        //  -62
	, "CL_INVALID_GLOBAL_WORK_SIZE"                 //  -63
	, "CL_INVALID_PROPERTY"                         //  -64
	, "CL_INVALID_IMAGE_DESCRIPTOR"                 //  -65
	, "CL_INVALID_COMPILER_OPTIONS"                 //  -66
	, "CL_INVALID_LINKER_OPTIONS"                   //  -67
	, "CL_INVALID_DEVICE_PARTITION_COUNT"           //  -68
};

void CLhelper::PrintDeviceInfo(cl_device_id& device) {
	char vendor[256];				// Vendor.
	char name[256];					// Name.
	cl_bool	available;				// Availability.
	cl_device_type deviceType;		// Type.

	cl_uint coreCount;				// Amount of compute units.
	size_t maxWarpSize;				// Maximum work-group size.
	cl_uint clockFrequency;			// Clock frequency.

	cl_long memorySize;				// Size of the (global) memory.
	cl_ulong maxAllocatableMemory;	// Maximum allocatable memory.
	cl_ulong localMemorySize;		// Size of the local memory.
	cl_uint cacheLineSize;			// Cache line size.
	cl_ulong cacheSize;				// Cache size.
	cl_device_mem_cache_type cacheType; // Cache type.

	cl_bool imageSupport;
	size_t maxHeight, maxWidth, maxCount;


	clGetDeviceInfo(device, CL_DEVICE_NAME, sizeof(name), name, NULL);
	clGetDeviceInfo(device, CL_DEVICE_VENDOR, sizeof(vendor), vendor, NULL);
	clGetDeviceInfo(device, CL_DEVICE_AVAILABLE, sizeof(available), &available, NULL);
	clGetDeviceInfo(device, CL_DEVICE_TYPE, sizeof(deviceType), &deviceType, NULL);

	clGetDeviceInfo(device, CL_DEVICE_MAX_COMPUTE_UNITS, sizeof(coreCount), &coreCount, NULL);
	clGetDeviceInfo(device, CL_DEVICE_MAX_WORK_GROUP_SIZE, sizeof(maxWarpSize), &maxWarpSize, NULL);
	clGetDeviceInfo(device, CL_DEVICE_MAX_CLOCK_FREQUENCY, sizeof(clockFrequency), &clockFrequency, NULL);

	clGetDeviceInfo(device, CL_DEVICE_GLOBAL_MEM_SIZE, sizeof(memorySize), &memorySize, NULL);
	clGetDeviceInfo(device, CL_DEVICE_MAX_MEM_ALLOC_SIZE, sizeof(maxAllocatableMemory), &maxAllocatableMemory, NULL);
	clGetDeviceInfo(device, CL_DEVICE_LOCAL_MEM_SIZE, sizeof(localMemorySize), &localMemorySize, NULL);
	clGetDeviceInfo(device, CL_DEVICE_GLOBAL_MEM_CACHELINE_SIZE, sizeof(cacheLineSize), &cacheLineSize, NULL);
	clGetDeviceInfo(device, CL_DEVICE_GLOBAL_MEM_CACHE_SIZE, sizeof(cacheSize), &cacheSize, NULL);
	clGetDeviceInfo(device, CL_DEVICE_GLOBAL_MEM_CACHE_TYPE, sizeof(cacheType), &cacheType, NULL);

	clGetDeviceInfo(device, CL_DEVICE_IMAGE_SUPPORT, sizeof(imageSupport), &imageSupport, NULL);
	clGetDeviceInfo(device, CL_DEVICE_IMAGE2D_MAX_WIDTH, sizeof(maxWidth), &maxWidth, NULL);
	clGetDeviceInfo(device, CL_DEVICE_IMAGE2D_MAX_HEIGHT, sizeof(maxHeight), &maxHeight, NULL);
	clGetDeviceInfo(device, CL_DEVICE_IMAGE_MAX_ARRAY_SIZE, sizeof(maxCount), &maxCount, NULL);


	printf("============= Device info: =============\n");
	printf("\tGeneral:\n");
	printf("\t\tName:\t\t\t\t%s\n", name);
	printf("\t\tVendor:\t\t\t\t%s\n", vendor);
	printf("\t\tAvailable:\t\t\t%s\n", available ? "Yes" : "No");
	printf("\t\tDevice Type Flags:\t\t%s%s%s%s\n", deviceType & CL_DEVICE_TYPE_CPU ? "CPU " : "", deviceType & CL_DEVICE_TYPE_GPU ? "GPU " : "", deviceType & CL_DEVICE_TYPE_ACCELERATOR ? "Accelerator " : "", deviceType & CL_DEVICE_TYPE_DEFAULT ? "Default " : "");

	printf("\tComputing Power:\n");
	printf("\t\tCompute Units:\t\t\t%u\n", coreCount);
	printf("\t\tMax. Work-Group Size:\t\t%zu\n", maxWarpSize);
	printf("\t\tClock Frequency:\t\t%u mHz\n", clockFrequency);

	printf("\tMemory:\n");
	printf("\t\tGlobal Memory:\t\t\t%0.00f MB\n", (double)memorySize / 1048576.0);
	printf("\t\tMax. Allocatable Memory:\t%0.00f MB\n", (double)maxAllocatableMemory / 1048576.0);
	printf("\t\tLocal Memory:\t\t\t%0.00f KB\n", (double)localMemorySize / 1024.0);
	printf("\t\tCache Line Size:\t\t%u B\n", cacheLineSize);
	printf("\t\tCache Type:\t\t\t%s\n", cacheType == CL_READ_ONLY_CACHE ? "Read-Only" : cacheType == CL_READ_WRITE_CACHE ? "Read-Write" : "None");
	if (cacheType != CL_NONE)
		printf("\t\tCache Size:\t\t\t%0.00f KB\n", (double)cacheSize / 1024.0);

	printf("\tImages:\n");
	printf("\t\tImage support:\t\t\t%s\n", imageSupport ? "Yes" : "No");
	printf("\t\tMax. Image2D size:\t\t(%i, %i)\n", maxWidth, maxHeight);
	printf("\t\tMax. image array size:\t\t%i\n", maxCount);

	printf("\n");
}

void CLhelper::GetPlatformAndDevice(cl_platform_id& platformId, cl_device_id& deviceId) {
	// Retrieve all platforms for the system.
	cl_uint platformCount;
	CHECK_CL_ERROR(clGetPlatformIDs(0, NULL, &platformCount), "unable to retrieve platforms");

	cl_platform_id* platforms = (cl_platform_id*)malloc(platformCount * sizeof(cl_platform_id*));
	CHECK_CL_ERROR(clGetPlatformIDs(platformCount, platforms, NULL), "unable to retrieve platforms");

	// Retrieve the first Nvidia or AMD GPU that we can find.
	char pInfo[512];
	for (cl_uint i = 0; i < platformCount; i++) {
		if (CHECK_CL_ERROR(clGetPlatformInfo(platforms[i], CL_PLATFORM_VENDOR, 512, &pInfo, NULL), "unable to retrieve platform info"))
			if (strstr(pInfo, "NVIDIA") || strstr(pInfo, "AMD"))
				if (CHECK_CL_ERROR(clGetDeviceIDs(platforms[i], CL_DEVICE_TYPE_GPU, 1, &deviceId, NULL), "unable to retrieve devices")) {
					platformId = platforms[i];
					return;
				}
	}

	free(platforms);
	free(pInfo);

	throw std::exception("unable to find a suitable GPU");
}

void CLhelper::CreateContext(cl_context& context, cl_platform_id& platformId, cl_device_id* deviceId) {


	cl_context_properties properties[]{
		CL_GL_CONTEXT_KHR, (cl_context_properties)wglGetCurrentContext(),
		CL_WGL_HDC_KHR, (cl_context_properties)wglGetCurrentDC(),
		CL_CONTEXT_PLATFORM, (cl_context_properties)platformId,
		0
	};

	cl_int errorCode;
	context = clCreateContext(properties, 1, deviceId, NULL, NULL, &errorCode);
	CHECK_CL_ERROR(errorCode, "could not create cl_context");
}

void CLhelper::CreateCommandQueue(cl_command_queue& queue, cl_context context, cl_device_id deviceId, cl_command_queue_properties properties) {

	// Error code.
	cl_int errorCode;
	// Try to create the command queue.
	queue = clCreateCommandQueue(context, deviceId, properties, &errorCode);

	CHECK_CL_ERROR(errorCode, "failed to create command queue");
}

void CLhelper::CreateProgram(cl_program& program, cl_context context, size_t filecount, const char** source, const size_t* lengths) {

	// Error code.
	cl_int errorCode;
	// Try to create the program.
	program = clCreateProgramWithSource(context, filecount, source, lengths, &errorCode);

	// Check for errors.
	CHECK_CL_ERROR(errorCode, "could not create cl program.");
}

void CLhelper::CreateMemoryBuffer(cl_mem& buffer, cl_context context, cl_mem_flags flags, size_t size, void* data) {
	// Error code.
	cl_int errorCode;
	// Try to create the memory buffer.
	buffer = clCreateBuffer(context, flags, size, data, &errorCode);

	// Check for errors.
	CHECK_CL_ERROR(errorCode, "could not create memory buffer");
}

void CLhelper::ReleaseMemoryBuffer(cl_mem& buffer) {
	CHECK_CL_ERROR(clReleaseMemObject(buffer), "could not release memory buffer");
}

void CLhelper::CreateCLBufferFromGLTexture(cl_mem& buffer, cl_context context, unsigned int glTexID) {
	// Error code.
	cl_int errorCode;
	// Try to create the memory buffer from the GLTexture.
	buffer = clCreateFromGLTexture(context, CL_MEM_WRITE_ONLY, GL_TEXTURE_2D, 0, glTexID, &errorCode);

	// Check for errors.
	CHECK_CL_ERROR(errorCode, "could not create opencl buffer from opengl texture");
}

void CLhelper::BuildProgram(cl_program program, cl_device_id& deviceId) {
	cl_int buildStatus =
		clBuildProgram(program, 1, &deviceId,
					   "-cl-fast-relaxed-math -cl-mad-enable -cl-denorms-are-zero -cl-no-signed-zeros -cl-unsafe-math-optimizations -cl-finite-math-only",
					   NULL, NULL
		);

	// Check for errors during building.
	if (buildStatus != CL_SUCCESS) {
		char* log = new char[100 * 1024]; // Error log can be pretty large.
		log[0] = 0;
		clGetProgramBuildInfo(program, deviceId, CL_PROGRAM_BUILD_LOG, 100 * 1024, log, NULL);
		log[2048] = 0; // Truncate very long logs.
		printf("\n%s\n", log);

		throw std::exception("Error building program");
	}

	printf("Build finished with status code %i.\n", buildStatus);
}


void CLhelper::ReleaseDevice(cl_device_id& device) {
	cl_int errorCode = clReleaseDevice(device);
	CHECK_CL_ERROR(errorCode, "could not release device");
}

void CLhelper::ReleaseContext(cl_context& context) {
	cl_int errorCode = clReleaseContext(context);
	CHECK_CL_ERROR(errorCode, "could not release context");
}

void CLhelper::ReleaseProgram(cl_program& program) {
	cl_int errorCode = clReleaseProgram(program);
	CHECK_CL_ERROR(errorCode, "could not release program");
}

void CLhelper::ReleaseCommandQueue(cl_command_queue& queue) {
	cl_int errorCode = clReleaseCommandQueue(queue);
	CHECK_CL_ERROR(errorCode, "could not release queue");
}

void CLhelper::ReleaseKernel(cl_kernel& kernel) {
	cl_int errorCode = clReleaseKernel(kernel);
	CHECK_CL_ERROR(errorCode, "could not release kernel");
}


void CLhelper::CreateKernel(cl_kernel& kernel, cl_program program, const char* kernelName) {

	cl_int errorCode;
	kernel = clCreateKernel(program, kernelName, &errorCode);

	CHECK_CL_ERROR(errorCode, "could not create kernel");
}

void CLhelper::SetKernelArg(cl_kernel kernel, cl_uint idx, size_t size, const void* value) {
	// Try to set the kernel argument.
	cl_int errorCode = clSetKernelArg(kernel, idx, size, value);
	// Check for errors.
	CHECK_CL_ERROR(errorCode, "could not set kernel argument");
}

void CLhelper::WriteCLBuffer(cl_command_queue queue, cl_mem buffer, size_t numBytes, const void* data, size_t offset) {
	cl_int errorCode = clEnqueueWriteBuffer(queue, buffer, CL_TRUE, offset, numBytes, data, 0, NULL, NULL);
	// Check for errors.
	CHECK_CL_ERROR(errorCode, "could not write to cl buffer.");
}

void CLhelper::ReadCLBuffer(cl_command_queue queue, cl_mem buffer, cl_bool blocking, size_t numBytes, void* dst, size_t offset) {
	cl_int errorCode = clEnqueueReadBuffer(queue, buffer, blocking, offset, numBytes, dst, 0, 0, 0);
	CHECK_CL_ERROR(errorCode, "could not read from cl buffer.");
}

void CLhelper::EnqueueKernel(cl_command_queue queue, cl_kernel kernel, cl_uint workDim, size_t* globalWorkSize, size_t* localWorkSize, size_t globalWorkOffset) {
	// Try to set the kernel argument.
	cl_int errorCode = clEnqueueNDRangeKernel(queue, kernel, workDim, NULL, globalWorkSize, localWorkSize, 0, NULL, NULL);
	// Check for errors.
	CHECK_CL_ERROR(errorCode, "could not enqueue kernel");
}

void CLhelper::WaitForQueueToFinish(cl_command_queue queue) {
	cl_int errorCode = clFinish(queue);
	// Check for errors.
	CHECK_CL_ERROR(errorCode, "could not issue wait command for queue to finish");
}

void CLhelper::AcquireGLObjects(cl_command_queue queue, cl_uint numObjects, cl_mem* memObjects) {

	cl_int errorCode = clEnqueueAcquireGLObjects(queue, numObjects, memObjects, 0, NULL, NULL);
	// Check for errors.
	CHECK_CL_ERROR(errorCode, "could not acquire GL objects");
}

void CLhelper::ReleaseGLObjects(cl_command_queue queue, cl_uint numObjects, cl_mem* memObjects) {
	cl_int errorCode = clEnqueueReleaseGLObjects(queue, numObjects, memObjects, 0, NULL, NULL);
	// Check for errors.
	CHECK_CL_ERROR(errorCode, "could not release GL objects");
}

char* CLhelper::ReadSource(const char* filePath, size_t* size) {
	std::string source;
	// extract path from source file name
	char path[2048];
	strcpy_s(path, filePath);
	char* marker = path, * fileName = (char*)filePath;
	while (strstr(marker + 1, "\\")) marker = strstr(marker + 1, "\\");
	while (strstr(marker + 1, "/")) marker = strstr(marker + 1, "/");
	while (strstr(fileName + 1, "\\")) fileName = strstr(fileName + 1, "\\");
	while (strstr(fileName + 1, "/")) fileName = strstr(fileName + 1, "/");
	if (fileName != filePath) fileName++;
	*marker = 0;
	// load source file
	FILE* f;
	fopen_s(&f, filePath, "r");
	if (!f) throw std::exception("Error loading source");
	char line[8192];
	int lineNr = 0;
	while (!feof(f)) {
		line[0] = 0;
		fgets(line, 8190, f);
		lineNr++;
		// clear source file line
		while (line[0]) {
			if (line[strlen(line) - 1] > 32) break;
			line[strlen(line) - 1] = 0;
		}
		// expand error commands
		char* err = strstr(line, "Error(");
		if (err) {
			char rem[8192], cmd[128];
			strcpy_s(rem, err + 6);
			*err = 0;
			sprintf_s(cmd, "Error_( %i, %i,", 0, lineNr);
			strcat_s(line, cmd);
			strcat_s(line, rem);
		}
		// expand assets
		char* as = strstr(line, "Assert(");
		if (as) {
			char rem[8192], cmd[128];
			strcpy_s(rem, as + 7);
			*as = 0;
			sprintf_s(cmd, "Assert_( %i, %i,", 0, lineNr);
			strcat_s(line, cmd);
			strcat_s(line, rem);
		}
		// handle include files
		char* inc = strstr(line, "#include");
		if (inc) {
			char* start = strstr(inc, "\"");
			if (!start) throw std::exception("Preprocessor error in #include statement line");
			char* end = strstr(start + 1, "\"");
			if (!end) throw std::exception("Preprocessor error in #include statement line");
			char file[2048];
			*end = 0;
			strcpy_s(file, path);
			strcat_s(file, "/");
			strcat_s(file, start + 1);
			char* incText = ReadSource(file, size);
			source.append(incText);
		}
		else {
			source.append(line);
			source.append("\n");
		}
	}
	*size = strlen(source.c_str());
	char* t = (char*)malloc(*size + 1);
	strcpy_s(t, INT32_MAX, source.c_str());
	fclose(f);
	return t;
}

/** Error codes taken from: https://github.com/martijnberger/clew/blob/master/src/clew.c. */
bool CLhelper::CheckCLError(cl_int error, const char* msg) {
	if (error == CL_SUCCESS) return true;

	static const int num_errors = sizeof(errorCodeStrings) / sizeof(errorCodeStrings[0]);

	if (error == -1001) {
		return "CL_PLATFORM_NOT_FOUND_KHR";
	}

	if (error > 0 || -error >= num_errors) {
		return "Unknown OpenCL error";
	}

	printf(msg);
	printf("\nError code %i: %s.\n", error, errorCodeStrings[-error]);
	throw std::exception(msg);
	return false;
}
