{
  "targets": [
    {
      "target_name": "hello",
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