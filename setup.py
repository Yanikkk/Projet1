from distutils.core import setup, Extension

projetModule = Extension('Noyau', sources = ['Noyau.cc','Env.cpp','Matiere.cpp','Case.cpp','Air.cpp','Eau.cpp','Sol.cpp', 'Polluant.cpp'], libraries = [])

setup(name = 'Simulation d une riviere',
      version = '1.0',
      description = 'Module du projet de simulation.',
      ext_modules = [projetModule]);

# Pour compiler et installer ce module, lancez
#   python3 setup.py build

