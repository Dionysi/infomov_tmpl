#pragma once
#include <CL/cl.h>
#include <stdio.h>
#include <exception>

#define CHECK_CL_ERROR CLhelper::CheckCLError

class CLhelper {

public:

	/** Print information about the given device.
	 *	@param deviceIDPtr	Pointer to the ID of the device the information should be printed of.
	*/
	static void PrintDeviceInfo(cl_device_id& device);
	/** Get the most optimal to use platform and device.
	 *	@param platformId		Pointer to where the platform ID of the chosen platform should be stored.
	 *	@param deviceId			Pointer to where the device ID of the chosen device should be stored.
	*/
	static void GetPlatformAndDevice(cl_platform_id& platformId, cl_device_id& deviceId);
	/* Creates an OpenCL context from the given platform and device.
	* @param[out] context		The OpenCL context.
	* @param[in] platformId		cl_platform.
	* @param[in] deviceId		cl_device.
	*/
	static void CreateContext(cl_context& context, cl_platform_id& platformId, cl_device_id* deviceId);
	/** Create an OpenCL command queue for the given context and device.
	* @param[out] queue			cl_command_queue value for the created command queue.
	* @param[in] context		The cl_context for which to create the command queue.
	* @param[in] deviceId		The cl_device_id of the device for which the command queue is created.
	* @param[in] properties		Command queue properties.
	*/
	static void CreateCommandQueue(cl_command_queue& queue, cl_context context, cl_device_id deviceId, cl_command_queue_properties properties);
	/** Create a cl_program form the given source.
	 * @param[out] program		cl_program.
	 * @param[in] context		OpenCL context.
	 * @param[in] fileCount		Amount of sources used.
	 * @param[in] source		Source code for the application.
	 * @param[in] lengths		Lengths of the different source strings.
	*/
	static void CreateProgram(cl_program& program, cl_context context, size_t filecount, const char** source, const size_t* lengths);
	/** Reserves graphics memory for the given context by creating an OpenCL memory buffer.
	 * @param[out] buffer		The cl_mem object to which the buffer pointer will be written.
	 * @param[in] context		A valid OpenCL context used to create the buffer object.
	 * @param[in] flags			A bit-field that is used to specify allocation and usage information such as the memory area that should be used to allocate the buffer object and how it will be used.
	 * @param[in] size			The size in bytes of the buffer memory object to be allocated.
	*/
	static void CreateMemoryBuffer(cl_mem& buffer, cl_context context, cl_mem_flags flags, size_t size, void* data = NULL);
	/** Creates an OpenCL memory buffer from a GLTexture.
	 * @param[out] buffer		The cl_mem object to which the buffer pointer will be written.
	 * @param[in] context		OpenCL context.
	 * @param[in] glTexID		Texture id of the GL texture.
	*/
	static void CreateCLBufferFromGLTexture(cl_mem& buffer, cl_context context, unsigned int glTexID);
	/** Builds the cl_program.
	* @param[in] program	cl_program.
	* @param[in] deviceId	device.
	*/
	static void BuildProgram(cl_program program, cl_device_id& deviceId);

	/** Releases the device associated with the device id.
	* @param[in] device		Device to release.
	*/
	static void ReleaseDevice(cl_device_id& device);
	/** Releases the cl_context.
	* @param[in] context		Context to release.
	*/
	static void ReleaseContext(cl_context& context);
	/** Releases the cl_program.
	* @param[in] program		Program to release.
	*/
	static void ReleaseProgram(cl_program& program);
	/** Releases the command queue.
	* @param[in] queue		Command queue to release.
	*/
	static void ReleaseCommandQueue(cl_command_queue& queue);
	/** Decrements the reference kernel count.
	* @param[in] kerel		The kernel to release.
	*/
	static void ReleaseKernel(cl_kernel& kernel);
	/** Frees the DRAM occupied by the specified memory buffer.
	* @param[in] buffer.
	*/
	static void ReleaseMemoryBuffer(cl_mem& buffer);

	/** Creates a kernel from the kernel name.
	* @param[out] kernel		The created kernel.
	* @param[in] program		cl_program to create the kernel from.
	* @param[in] kernelName		Name of the kernel.
	*/
	static void CreateKernel(cl_kernel& kernel, cl_program program, const char* kernelName);
	/** Sets a kernel argument for a specific kernel.
	* @param[in] kernel			The kernel for which to set the argument.
	* @param[in] idx			Index of the argument.
	* @param[in] size			Size of the argument to write.
	* @param[in] value			Pointer to the argument.
	*/
	static void SetKernelArg(cl_kernel kernel, cl_uint idx, size_t size, const void* value);
	/** Write the values in the host memory to graphics memory.
	 * @param[in] queue			Refers to the command-queue in which the write command will be queued. command_queue and buffer must be created with the same OpenCL context.
	 * @param[in] buffer		Refers to a valid buffer object.
	 * @param[in] numBytes		The size in bytes of data being written.
	 * @param[in] data			Pointer to the values in host memory.
	 * @param[in] offset		The offset in bytes in the buffer object to write to.
	*/
	static void WriteCLBuffer(cl_command_queue queue, cl_mem buffer, size_t numBytes, const void* data, size_t offset = 0);
	/** Enqueue a kernel.
	* @param[in] queue					A valid command-queue. The kernel will be queued for execution on the device associated with command_queue.
	* @param[in] kernel					A valid kernel object. The OpenCL context associated with kernel and command_queue must be the same.
	* @param[in] workDim				The number of dimensions used to specify the global work-items and work-items in the work-group. work_dim must be greater than zero and less than or equal to three.
	* @param[in] globalWorkSize			Points to an array of work_dim unsigned values that describe the number of global work-items in work_dim dimensions that will execute the kernel function. The total number of global work-items is computed as global_work_size[0] *...* global_work_size[work_dim - 1].
	* @param[in] localWorkSize			Points to an array of work_dim unsigned values that describe the number of work-items that make up a work-group (also referred to as the size of the work-group) that will execute the kernel specified by kernel. The total number of work-items in a work-group is computed as local_work_size[0] *... * local_work_size[work_dim - 1]. The total number of work-items in the work-group must be less than or equal to the CL_DEVICE_MAX_WORK_GROUP_SIZE value specified in table of OpenCL Device Queries for clGetDeviceInfo and the number of work-items specified in local_work_size[0],... local_work_size[work_dim - 1] must be less than or equal to the corresponding values specified by CL_DEVICE_MAX_WORK_ITEM_SIZES[0],.... CL_DEVICE_MAX_WORK_ITEM_SIZES[work_dim - 1]. The explicitly specified local_work_size will be used to determine how to break the global work-items specified by global_work_size into appropriate work-group instances. If local_work_size is specified, the values specified in global_work_size[0],... global_work_size[work_dim - 1] must be evenly divisable by the corresponding values specified in local_work_size[0],... local_work_size[work_dim - 1].
	* @param[in] globalWorkOffset		Must currently be a NULL value. In a future revision of OpenCL, global_work_offset can be used to specify an array of work_dim unsigned values that describe the offset used to calculate the global ID of a work-item instead of having the global IDs always start at offset (0, 0,... 0).
	*/
	static void EnqueueKernel(cl_command_queue queue, cl_kernel kernel, cl_uint workDim, size_t* globalWorkSize, size_t* localWorkSize = NULL, size_t globalWorkOffset = NULL);
	/** Enforces the GPU to finish before the code continues its execution.
	 * @param[in] queue		The command queue on which we must wait.
	*/
	static void WaitForQueueToFinish(cl_command_queue queue);
	/** Acquire OpenGL objects.
	 * @param[in] queue				A valid command-queue. All devices used to create the OpenCL context associated with command_queue must support acquiring shared CL/GL objects. This constraint is enforced at context creation time.
	 * @param[in] numObjects		The number of memory objects to be acquired in mem_objects.
	 * @parma[in] memObjects		A pointer to a list of CL memory objects that correspond to GL objects.
	*/
	static void AcquireGLObjects(cl_command_queue queue, cl_uint numObjects, cl_mem* memObjects);
	/** Release OpenGL objects.
	* @param[in] queue				A valid command-queue. All devices used to create the OpenCL context associated with command_queue must support acquiring shared CL/GL objects. This constraint is enforced at context creation time.
	* @param[in] numObjects		The number of memory objects to be released in mem_objects.
	* @parma[in] memObjects		A pointer to a list of CL memory objects that correspond to GL objects.
	*/
	static void ReleaseGLObjects(cl_command_queue queue, cl_uint numObjects, cl_mem* memObjects);

	/** Reads an OpenCL file and does some funky pre-processing. No idea where this method came from.
	 * @param[out] sourceCode	Array with the source code of the OpenCL program.
	 * @param[in] filePath		File path to the OpenCL file.
	 * @param[in] size			Pointer to where the size of the string should be stored. Can not be NULL. I think.
	*/
	static char* ReadSource(const char* filePath, size_t* size);

private:
	static inline bool CheckCLError(cl_int error, const char* msg) {
		if (error == CL_SUCCESS) return true;

		printf(msg);
		printf("\nError code %i.\n", error);
		throw std::exception(msg);
		return false;
	}
};
