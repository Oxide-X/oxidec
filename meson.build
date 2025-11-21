project(
  'oxidec',
  'cpp',
  version: '0.1.0',
  default_options: ['cpp_std=c++23', 'warning_level=3', 'werror=false', 'optimization=2'],
)

lexer_src = files('src/lexer/lexer.cpp')

exe = executable('oxidec', 'src/main.cpp', lexer_src, install: false)
