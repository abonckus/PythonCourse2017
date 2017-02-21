from distutils.core import setup
from distutils.core import Extension

MOD = "myextention"

module = Extension(MOD, sources = ["myextentionmodule.c"])

setup(name = MOD, ext_modules = [module])