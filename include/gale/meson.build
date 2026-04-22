conf_data = configuration_data()
conf_data.set_quoted('VERSION', meson.project_version())
# XXX: Make optional
conf_data.set('HAVE_ADNS', 1)
configure_file(output: 'config.h', configuration: conf_data)
