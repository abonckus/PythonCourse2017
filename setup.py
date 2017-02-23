from distutils.core import setup
from distutils.core import Extension

MOD = "myextension"

module = Extension(MOD, sources = ["myextensionmodule.c"])

setup(name = MOD, ext_modules = [module])