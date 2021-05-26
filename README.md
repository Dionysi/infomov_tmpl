# ocl_tmpl
Simple OpenCL template for C++ applications with OpenGL interop.

# Project setup

To setup the project, we must perform the following steps:
1. Make sure that you install OpenCL SDK for your platform. For Nvidia, this is included int he CUDA toolkit. Also see: https://streamhpc.com/blog/2015-03-16/how-to-install-opencl-on-windows/

2. In the project directory, add two folders 'include' and 'lib'.

3. We must download the following binaries:
    - GLFW: https://www.glfw.org/download. Download the 64-bit Windows binaries. From the corresponding vc-folder copy the 'glfw3.lib' file to the lib directory in your project. Include the entire GLFW folder from the glfw-include folder to your project's include directory.
    - Glew: http://glew.sourceforge.net/. Download the 'Windows 32-bit and 64-bit' binaries. Copy the glew32.lib file from lib\Release\x64 to you 'lib' folder in the project directory. Similarly, copy the entire content from the GL folder from \include\GL to a new directory in your 'include' directory of your project named 'glew' (you must create this directory yourself).

Your project directory should now contain the following folders:
- $(ProjectDir)/glew/[contents from the glew_download_folder/include/GL]
- $(ProjectDir)/glfw/[contents from the glfw_download_folder/include/GLFW]
- $(ProjectDir)/KHR/...
- $(ProjectDir)/glad/...

4. Go to your project properties in Visual Studio (make sure you select the x64 platform and both configurations). Here we must do the following:
    - In [C/C++ -> General] add these additional include directories:
        - $(CUDA_PATH)/include (for AMD: $(AMDAPPSDKROOT)/include and Intel $(INTELOCLSDKROOT)/include)
        - $(ProjectDir)/include
    - In [Linker -> General] add these additional library directories:
        - $(CUDA_PATH)/lib/x64 (for AMD: $(AMDAPPSDKROOT)/lib/x86_64 and Intel $(INTELOCLSDKROOT)/lib/x64)
        - $(ProjectDir)/lib
    - In [Linker -> Input] add these additional depencies:
        - OpenCL.lib
        - glew32.lib
        - glfw3.lib
        - opengl32.lib

You should now be all set-up.

# How to use?
The class 'Application' implements the functionality for creating a Window, creating an OpenGL texture used for rendering, rendering a textured quad and an application-loop. In the CLhelper class, you can find implementations with error checks for commonly used OpenCL calls. Use the OpenGL texture - called renderTexture, in the Application class - to render to. 

To implement your own functionality, create a new class that inherits from the Application class. In this class, you can overwrite the 'Tick(float dt)' function to implement your desired behavior. 
