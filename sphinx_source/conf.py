import os
import sys
sys.path.insert(0, os.path.abspath('..'))

# Configuration file for the Sphinx documentation builder.
#
# For the full list of built-in configuration values, see the documentation:
# https://www.sphinx-doc.org/en/master/usage/configuration.html

# -- Project information -----------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#project-information

project = 'µPlant Warehouse Management'
copyright = '2023, Lennart Schink'
author = 'Lennart Schink'
release = '01.10.2023'

# -- General configuration ---------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#general-configuration

extensions = [ 'sphinx.ext.autodoc','sphinx.ext.viewcode', 'sphinx_copybutton']
# extensions = [ 'sphinx.ext.autodoc','sphinx.ext.viewcode']


templates_path = ['_templates']
exclude_patterns = []
modindex_common_prefix = ['src.']


# -- Options for HTML output -------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#options-for-html-output

html_theme = 'alabaster'
# html_static_path = ['_static']
html_static_path = []