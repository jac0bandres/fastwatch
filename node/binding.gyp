{
  "targets": [
    {
      "target_name": "fastwatch",
      "sources": [
        "addon.cpp"
      ],
      "include_dirs": [
        "../c_api",
        "<!(node -p \"require('node-addon-api').include\")"
      ],
      "libraries": [
        "-L<(module_root_dir)/../build",
        "-lfastwatch"
      ],
      "ldflags": [
        "-L<(module_root_dir)/../build",
        "-lfastwatch"
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
