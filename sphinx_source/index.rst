.. µPlant Warehouse Management documentation master file, created by
   sphinx-quickstart on Thu Jun 22 11:20:28 2023.
   You can adapt this file completely to your liking, but it should at least
   contain the root `toctree` directive.

Welcome to µPlant Warehouse Management's documentation!
=======================================================
README
------
Getting Started
_______________

Use

.. code-block:: bash

    pip install -r requirements.txt

to install all necessary python packages.



Updating code documentation
___________________________

to update HTML export use:

.. code-block:: bash

    sphinx-build -b html sphinx_source sphinx_build


to update PDF export use:

.. code-block:: bash

   make latexpdf

Adding content:

- New RST files can be registered in index.rst file's toc-tree
- New Modules can be included with autodoc module in modules.rst


Updating python packages:

As long as using venv use:

.. code-block:: bash

   pip freeze > requirements.txt

to update requirements.txt



.. toctree::
   :maxdepth: 2
   :caption: Contents:

   modules



Indices and tables
==================

* :ref:`genindex`
* :ref:`modindex`
* :ref:`search`
