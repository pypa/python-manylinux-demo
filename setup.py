from distutils.core import setup, Extension

extension_module = Extension(
    'pymanylinuxdemo.extension',
     sources=['pymanylinuxdemo/extension.c'],
     library_dirs=['/usr/lib64/atlas/', '/usr/lib/atlas'],
     include_dirs=['/usr/include'],
     libraries=['cblas']
)

setup(
    name = 'python-manylinux-demo',
    version = '1.0',
    description = 'This is a demo package with a compiled C extension.',
    ext_modules = [extension_module],
    packages=['pymanylinuxdemo', 'pymanylinuxdemo.tests'],
)
