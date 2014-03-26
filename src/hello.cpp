#include <node.h>
#include <v8.h>

#include <CL/cl.h>
using namespace v8;

Handle<Value> Method(const Arguments& args) {
  HandleScope scope;

  cl_device_id device_id;
  cl_uint num_devices = 1u;
  const cl_uint num_entries = 3;
  cl_platform_id platforms;
  cl_uint num_platforms = 0;
  int errcode_ret =1;
  
  errcode_ret = clGetPlatformIDs(
    num_entries,
    &platforms,
    &num_platforms);

   errcode_ret = clGetDeviceIDs(platforms,
    CL_DEVICE_TYPE_CPU,  //TODO: Make selectable for QPU
    1u,
    &device_id,
    &num_devices);
     
  return scope.Close(String::New("world"));
}

void init(Handle<Object> target) {
  target->Set(String::NewSymbol("hello"),
      FunctionTemplate::New(Method)->GetFunction());
}
NODE_MODULE(hello, init)