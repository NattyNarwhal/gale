project('gale', 'c', version: '1.2')

gale_sys_dir = get_option('sysconfdir') + '/gale'
add_global_arguments('-DGALE_SYS_DIR="' + gale_sys_dir + '"', language : 'c')

core_deps = [
  dependency('dl'),
  dependency('libcrypto'),
  dependency('libssl'),
  dependency('bdw-gc'),
  dependency('curses'),
  dependency('readline')
  ]

# adns provides no pkg-config
cc = meson.get_compiler('c')
libadns = cc.find_library('adns', required: false)
if libadns.found()
  add_global_arguments('-DHAVE_ADNS=1', language: 'c')
  core_deps += [libadns]
endif

iconv_dep = dependency('iconv', required: false)
if iconv_dep.found()
  add_global_arguments('-DHAVE_ICONV=1', language: 'c')
  core_deps += [iconv_dep]
  # meson doesn't check for iconv constiness
  iconv_const_test = '''
  #include <iconv.h>
  size_t iconv (iconv_t cd, const char** inbuf, size_t *inbytesleft, char** outbuf, size_t *outbytesleft);
  '''
  if cc.compiles(iconv_const_test, name: 'iconv() prototype uses const')
    add_global_arguments('-DICONV_CONST=const', language: 'c')
  else
    add_global_arguments('-DICONV_CONST=', language: 'c')
  endif
endif

incdirs = include_directories(['include', 'liboop'])

install_data = configuration_data()
install_data.set('prefix', get_option('prefix'))
install_data.set('exec_prefix', get_option('prefix'))
install_data.set('sysconfdir', get_option('sysconfdir'))
install_data.set('sbindir', get_option('sbindir'))
install_data.set('bindir', get_option('bindir'))
configure_file(
  input: 'gale-install.in',
  output: 'gale-install',
  configuration: install_data,
  install: true,
  install_dir: get_option('bindir'),
  install_mode: 'rwxr-xr-x'
  )

subdir('include/gale')
subdir('liboop')
subdir('libgale')
subdir('gsub')
subdir('gsend')
subdir('kutils')
subdir('server')
subdir('gdomain')
