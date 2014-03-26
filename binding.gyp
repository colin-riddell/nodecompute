{
  "targets": [
    {
      "target_name": "hello",
      'type': 'shared_library',
      "sources": [ "src/hello.cpp" ]
    }
  ],

'include_dirs': [
  '/opt/AMDAPP/include',
],
'libraries': [
  '-lOpenCL', '-L/opt/AMDAPP/lib/x86/lib'
]

}