#include <CL/cl.h>

namespace ocl
{
  const  bool ocl_setup();
  std::string LoadKernel(const char* name);
  cl_program CreateProgram(const std::string& source, cl_context context, cl_int errorcode_ret);
  const cl_kernel ocl_build(cl_context* pContext, cl_int errorcode_ret);
 
  



}