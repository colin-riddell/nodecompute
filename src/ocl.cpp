#include <stdio.h>
#include <iostream> 
#include <vector>
#include <string>
#include <sstream>
#include <fstream>

#include <CL/cl.h>


#include "ocl.h"


namespace ocl
{
  const  bool ocl_setup()
  {
    cl_uint platformIdCount = 0;
    cl_int errorcode_ret = 666;


    errorcode_ret = clGetPlatformIDs (0, NULL, &platformIdCount);
    if (errorcode_ret !=0)
        std::cout <<"Error! clGetPlatformIDs failed with " << errorcode_ret << std::endl;

    std::vector<cl_platform_id> platformIds (platformIdCount);
    clGetPlatformIDs (platformIdCount, platformIds.data (), NULL);

    cl_uint deviceIdCount = 0;
    clGetDeviceIDs (platformIds [0], CL_DEVICE_TYPE_ALL, 0, NULL, &deviceIdCount);
    std::vector<cl_device_id> deviceIds (deviceIdCount);
    clGetDeviceIDs (platformIds [0], CL_DEVICE_TYPE_ALL, deviceIdCount, deviceIds.data (), NULL);
    std::cout << platformIdCount <<std::endl;
    std::cout << deviceIdCount <<std::endl;

    cl_context context = clCreateContext(0, 1, &deviceIds[0], NULL, NULL, &errorcode_ret);
    if (errorcode_ret !=0)
        std::cout <<"Error! clCreateContext failed with " << errorcode_ret << std::endl;
    ocl_build(&context, errorcode_ret);

    

    /*
    const std::string hw("Hello World\n");
    std::string dev_name;

    
    std::vector<Platform> platforms;
    std::vector<cl::Device> devices;


    //Get the OpenCL platforms.
    Platform::get(&platforms);
    if(platforms.size() == 0)
    {
      std::cerr << "No OpenCL device found!" << std::endl;
    }
    std::cout << "Platforms: " <<platforms.size() <<std::endl;
    // Make the 0th platform default
    cl::Platform default_platform = platforms[0];

    //Get the vendor name.
    std::string vendor;
    int err = default_platform.getInfo((cl_platform_info)CL_PLATFORM_VENDOR, &vendor);
    std::cout <<"Vendor:   " << vendor <<std::endl;

    //Get avaialbe devices
    err = default_platform.getDevices((cl_device_type)CL_DEVICE_TYPE_CPU,&devices);
    if(devices.size()==0){
      std::cout<<" No devices found. Check OpenCL installation!\n";
      exit(1);
    }
    cl::Device default_device = devices[0];
    err = default_device.getInfo((cl_device_info)CL_DEVICE_NAME, &dev_name);


    std::cout<< "Device name:   "<< dev_name <<std::endl;

    cl::Context context({default_device});

    */
  }
  
const cl_kernel ocl_build(cl_context* pContext, cl_int errorcode_ret)
{
  std::cout << "In build" <<std::endl;

  cl_program program = CreateProgram(LoadKernel("kernel.cl"), *pContext, errorcode_ret);

  errorcode_ret = clBuildProgram(program, 0, NULL, "-cl-mad-enable", NULL, NULL);
  if (errorcode_ret != 0)
    std::cout <<"Error! clBuildProgram failed with " << errorcode_ret << std::endl;

  cl_kernel kernel = clCreateKernel(program, "foo", &errorcode_ret);
  if (errorcode_ret != 0)
    std::cout <<"Error! clCreateKernel failed with " << errorcode_ret << std::endl;  
  
  int length  = 100;
  char *inbuff = (char*)calloc(length,sizeof(char));
  char *outbuff = (char*)calloc(length,sizeof(char));

  cl_mem in_clmem = clCreateBuffer(*pContext, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR, length, inbuff, &errorcode_ret);
  cl_mem out_clmem = clCreateBuffer(*pContext, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR, length, outbuff, &errorcode_ret);

  clSetKernelArg(kernel, 0, sizeof(cl_mem), &in_clmem);
  clSetKernelArg(kernel, 1, sizeof(cl_mem), &out_clmem);
//  clSetKernelArg(kernel, 2, sizeof(cl_mem), &d_c);
//  clSetKernelArg(kernel, 3, sizeof(unsigned int), &n);
  return kernel;
}

std::string LoadKernel(const char* name) {
    std::ifstream in(name);
  std::string result((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
  return result;
}

cl_program CreateProgram(const std::string& source, cl_context context, cl_int errorcode_ret) {
    size_t lengths[1] = { source.size() };
  const char* sources[1] = { source.data() };
  cl_program program = clCreateProgramWithSource(context, 1, sources, NULL, &errorcode_ret);
  if (errorcode_ret !=0)
    std::cout <<"Error! clCreateProgramWithSource failed with " << errorcode_ret << std::endl;

  return program;
}




} // namespace ocl