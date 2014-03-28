#include <node.h>
#include <v8.h>

#include <CL/cl.hpp>

using namespace cl;

#include <iostream> 
#include <vector>
#include <string>
#include <sstream>

using namespace v8;

Handle<Value> Method(const Arguments& args) {
  HandleScope scope;


  std::vector<Platform> platforms;
  Platform::get(&platforms);

  if(platforms.size() == 0)
  {
	std::cerr << "No OpenCL device found!" << std::endl;
  }
  
  return scope.Close(String::New("world"));
}

void init(Handle<Object> target) {
  target->Set(String::NewSymbol("hello"),
      FunctionTemplate::New(Method)->GetFunction());
}
NODE_MODULE(nodecompute, init)