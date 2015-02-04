{
  'targets': [
    {
      'target_name': 'nodecompute',
      'sources': [ 'src/nodecompute.cc','src/ocl.cpp' ],
      'libraries': [ '/opt/AMDAPP/lib/x86_64/libOpenCL.so' ],
      'cflags': [ '--std=c++11' ],
      'include_dirs': [
        '/opt/AMDAPP/include',
        './external/include',
        './'
      ],
    }
  ],
  
  'libraries': [
    '-lOpenCL', '-L/opt/AMDAPP/lib/x86'
  ],
  'link_settings': {
        'libraries': [
            '-lOpenCL'
        ]
}

}