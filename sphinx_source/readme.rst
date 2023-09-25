README
------
Getting Started
_______________

Use

.. code-block:: bash

    pip install -r requirements.txt

to install all necessary python packages.

Preparations for IDS Camera usage
_________________________________

Following Cameras are used:

- IDS UI-5180SE-C-HQ which is a 5MP camera with USB2 interface meant to be mounted on the gripper

- IDS GV-5800SE-C-HQ which is a 22MP GigE camera meant to be mounted in a upper corner of the storage cell

Software Installation
=====================

First install IDS Software Suite >4.95

Then install IDS Peak >2.5. Important note:
While selecting installation options enable uEye Transport Layer to allow uEye cameras to be processed by IDS Peak

Enable Python SDK packages
==========================
When installed under Windows, api Packages is located in e.g.:
C:\Program Files\IDS\ids_peak\generic_sdk\api\binding\python\wheel\x86_64
open this path in powerShell or cmd and enter the following command:

.. code-block::

        pip install ids-peak-1.6.1.0-cp311-cp311-win_amd64.whl

(or corresponding python version)

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