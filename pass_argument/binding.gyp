{
  "targets": [
    {
      "target_name": "pass_argument",
      "sources": [ "pass_argument.cc" ],
      "include_dirs": ["<!(node -e \"require('nan')\")"]
    }
  ]
}
