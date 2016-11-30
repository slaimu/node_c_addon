{
  "targets": [
    {
      "target_name": "callback",
      "sources": [ "callback.cc" ],
      "include_dirs": ["<!(node -e \"require('nan')\")"]
    }
  ]
}
