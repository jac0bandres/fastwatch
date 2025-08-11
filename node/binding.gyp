{
  "targets": [
    {
      "target_name": "fastwatch",
      "sources": [
        "addon.cpp"
      ],
      "include_dirs": [
        "<(module_root_dir)/../c_api",
        "<!(node -p \"require('node-addon-api').include\")"
      ],
      "libraries": [
        "<(module_root_dir)/../build/libfastwatch.a"
      ],
      "dependencies": [
        "<!(node -p \"require('node-addon-api').gyp\")"
      ],
      "defines": [
        "NAPI_DISABLE_CPP_EXCEPTIONS"
      ],
      "cflags_cc": [
        "-std=c++17"
      ]
    }
  ]
}
