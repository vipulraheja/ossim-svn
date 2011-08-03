#!/usr/bin/python

from distutils.core import setup, Extension

pyossim_modules=Extension('_pyossim',sources=['/home/vipul/ossim-svn/src/pyossim/swig/master_wrap.cxx'],swig_opts=['-Wall','-I/home/vipul/ossim-svn/src/ossim/include/'])

setup(name='PyOSSIM',
      version='1.0',
      description='Python wrappings for OSSIM',
      author="Vipul Raheja",
      author_email='vipul.iiith@gmail.com',
      url='https://github.com/vipulraheja/ossim-svn/tree/master/src/pyossim',
      ext_modules=[pyossim_modules],
      py_modules=["pyossim"],
      scripts=["runner"],
     )
