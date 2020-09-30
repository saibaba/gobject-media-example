# rm -rf build && meson build && cd build && ninja

project('media', 'c', version: '1.0')

glib = dependency('glib-2.0')
gobj = dependency('gobject-2.0')
deps = [glib, gobj]

srcs = ['gex-media.c', 'main.c']

test(
  'test_media',
  executable('media', srcs, dependencies: deps),
  env: [
    'G_TEST_SRCDIR=@0@'.format(meson.current_source_dir()),
    'G_TEST_BUILDDIR=@0@'.format(meson.current_build_dir()),
  ],
)
