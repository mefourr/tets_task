{
  "targets": [
    {
      "target_name": "addon",
      "sources": [ "addon.cpp" ],
      "include_dirs": [
        "<!@(node -p \"require('node-addon-api').include\")"
      ],
      "dependencies": [
        "<!(node -p \"require('node-addon-api').gyp\")"
      ],
      "defines": [ "NAPI_DISABLE_CPP_EXCEPTIONS" ],
      "libraries": [ "Netapi32.lib" ],  
      "conditions": [
        ['OS=="win"', {
          "defines": [ "_WIN32_WINNT=0x0601" ]  
        }]
      ]
    }
  ]
}
