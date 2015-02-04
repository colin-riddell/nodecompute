#include <node.h>
#include <v8.h>
#include <stdio.h>

//#include <CL/cl.hpp>

//using namespace cl;

#include <iostream> 
#include <vector>
#include <string>
#include <sstream>
#include <cstddef>


#include <CL/cl.h>
using namespace v8;




Handle<Value> Method(const Arguments& args) {
  HandleScope scope; // This is needed by node.

  const std::string hw("Hello World\n");

  cl_uint platformIdCount = 0;
  clGetPlatformIDs (0, NULL, &platformIdCount);

  std::vector<cl_platform_id> platformIds (platformIdCount);
  clGetPlatformIDs (platformIdCount, platformIds.data (), NULL);

  cl_uint deviceIdCount = 0;
  clGetDeviceIDs (platformIds [0], CL_DEVICE_TYPE_ALL, 0, NULL, &deviceIdCount);
  std::vector<cl_device_id> deviceIds (deviceIdCount);
  clGetDeviceIDs (platformIds [0], CL_DEVICE_TYPE_ALL, deviceIdCount, deviceIds.data (), NULL);
  std::cout << platformIdCount <<std::endl;
  std::cout << deviceIdCount <<std::endl;


  /*
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
  std::cout << "Test print cout... working" <<std::endl;
	char * outH = new char[hw.length()+1];






  return scope.Close(String::New("world"));
}

void init(Handle<Object> target) {
  NODE_SET_METHOD(target, "nodecompute", Method);
}

NODE_MODULE(nodecompute, init);