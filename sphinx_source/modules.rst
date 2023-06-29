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
    :undoc-members:
    :show-inheritance:

Controller
----------

.. automodule:: src.controller.invController
    :members:
    :undoc-members:
    :show-inheritance:

Service
-------

.. automodule:: src.service.EventlogService
    :members:
    :undoc-members:
    :show-inheritance:

ViewModel
---------

.. automodule:: src.viewmodel.productlistViewModel
    :members:
    :undoc-members:
    :show-inheritance:

.. automodule:: src.viewmodel.productSummaryViewModel
    :members:
    :undoc-members:
    :show-inheritance:

.. automodule:: src.viewmodel.storageViewModel
    :members:
    :undoc-members:
    :show-inheritance:

View
----
Die Nachfolgenden Dateien stellen den Quellcode für das GUI dar.

Hauptfenster:
main.qml

.. literalinclude:: ../src/view/main.qml

Banner mit Logo und Programmtitel:
HeaderLine.qml

.. literalinclude:: ../src/view/HeaderLine.qml


Ansicht mit mobilem Roboter inklusive Becher und Sensoren:
TurtleView.qml

.. literalinclude:: ../src/view/TurtleView.qml

Ansicht eines Bechers mit ID und Produktname
CupView.qml

.. literalinclude:: ../src/view/CupView.qml

Ansicht einer Palette mit Becher:
PalletteView.qml

.. literalinclude:: ../src/view/PalletteView.qml

Alternative Ansicht einer Palette mit zwei Becher:
ProductView.qml

.. literalinclude:: ../src/view/ProductView.qml

Visualisierung des Anlagenschemas der Lagerzelle:
ProcessView.qml

.. literalinclude:: ../src/view/ProcessView.qml

Visualisierung des gesamten Lagerregals:
StorageView.qml

.. literalinclude:: ../src/view/StorageView.qml

Visualisierung des Eventloggers:
EventView.qml

.. literalinclude:: ../src/view/EventView.qml


Dialogs
_______
Dialogvisualisierung um das Lager manuell zu bearbeiten.
StorageDialog.qml

.. literalinclude:: ../src/view/StorageDialog.qml


Constants
---------

Speichert alle URI's zu Dateien und PlugIn's

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
