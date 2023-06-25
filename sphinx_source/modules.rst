.. µPlant Warehouse Management documentation master file, created by
   sphinx-quickstart on Thu Jun 22 11:20:28 2023.
   You can adapt this file completely to your liking, but it should at least
   contain the root `toctree` directive.

Main File
---------
.. literalinclude:: ../main.py


Data Model
----------

.. automodule:: src.model.DataModel
    :members:

Controller
----------

.. automodule:: src.controller.invController
    :members:

Service
-------

.. automodule:: src.service.EventlogService
   :members:

ViewModel
---------

.. automodule:: src.viewmodel.productlistViewModel
    :members:

.. automodule:: src.viewmodel.productSummaryViewModel
    :members:

.. automodule:: src.viewmodel.storageViewModel
    :members:

View
----

.. literalinclude:: ../src/view/main.qml


Constants
---------

.. literalinclude:: ../src/constants/Constants.py

Data Files
----------

Produkte.db:
Speichert alle möglichen Produktvarianten mit Id und Bezeichnung

.. literalinclude:: ../src/data/Produkte.db

StorageData.db
Speichert ein Abbild des Regalinhalts.

.. literalinclude:: ../src/data/StorageData.db

CommissData.db
Speichert aktuelle Kommissionsaufträge
.. literalinclude:: ../src/data/CommissData.db
