liboop_srcs = [
  'adns.c',
  'alloc.c',
  'read-fd.c',
  'read-mem.c',
  'read.c',
  'select.c',
  'signal.c',
  'sys.c'
  ]
liboop = static_library('oop', liboop_srcs, dependencies: libadns)
liboop_dep = declare_dependency(include_directories: incdirs, link_with: liboop, dependencies: libadns)
core_deps += [liboop_dep]

executable('test-oop', 'test-oop.c', dependencies: liboop_dep)
