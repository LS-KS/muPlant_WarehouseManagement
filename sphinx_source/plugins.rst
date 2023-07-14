PlugIn's
--------

Die PlugIn's "RFID Server" und "Manual Commission Control" sind nachfolgend beschrieben.

RFID Server
___________

RFID Server wird benötigt um die RFID Reader der Firma Feig Electronic GmbH anzusteuern.
Dabei werden alle RFID Reader der µPlant über Modbus ausgelesen und die ausgelesenen Daten
visualisiert. Die Daten werden außerdem über OPCUA im ganzen Netz zur Verfügung gestellt.

Data Model
==========

Controller
==========

ViewModels
==========

Views
=====

Manual Commission Control
_________________________

Manual Commission Control wird benötigt um die Kommissionsliste zu manipulieren.
Dadurch können von dem Warehouse Management Programm manuell Transportaufforderungen an den
Industrieroboter ABB IRB 120 gesendet werden.
Der Funktionsumfang ist dabei durch die verfügbaren commands des Roboters begrenzt.

Data Model
==========

Die Kommissionsliste wird in der Klasse `CommissionModel` des nachfolgenden Moduls verwaltet.

.. automodule:: src.model.CommissionModel
    :members:
    :undoc-members:
    :show-inheritance:
    :noindex:

Controller
==========

Funktionen die das DatenModell betreffen, werden in der Klasse `CommissionController` des nachfolgenden Moduls implementiert.
Dieses ist aber auch Teil des Hauptprogramms.

.. automodule:: src.controller.CommissionController
    :members:
    :undoc-members:
    :show-inheritance:
    :noindex:


ViewModels
==========

Daten des Datenmodells werden über das Modul `commissionViewModel` bereitgestellt.

.. automodule:: src.viewModel.commissionViewModel
    :members:
    :undoc-members:
    :show-inheritance:

Views
=====

Das Hauptfenster des PlugIns wird im Programm über die Menubar aufgerufen:
Tools -> Manual Commission Control
MCCPlugin.qml

.. literalinclude:: ../../src/view/MCCPlugin.qml
    :linenos:
