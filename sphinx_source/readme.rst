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