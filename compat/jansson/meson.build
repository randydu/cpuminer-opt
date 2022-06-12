srcs = [
  'dump.c', 'error.c', 'hashtable.c', 'load.c', 'memory.c', 'pack_unpack.c', 'strbuffer.c', 'strconv.c', 'utf.c', 'value.c',
]
lib_jansson = static_library('jansson', srcs)
jansson_dep = declare_dependency(link_with: lib_jansson, include_directories: '.')