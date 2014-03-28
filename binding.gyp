{
  "targets": [
    {
      "target_name": "nodecompute",
      "sources": [ "src/nodecompute.cc" ],
      "libraries": [ "/opt/AMDAPP/lib/x86_64/libOpenCL.so" ]
    }
  ],

'include_dirs': [
  '/opt/AMDAPP/include',
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