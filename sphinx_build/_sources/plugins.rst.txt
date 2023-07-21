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

Die Daten werden in der Klasse `RFIDModel` des nachfolgenden Moduls verwaltet.

.. automodule:: src.model.RfidModel
    :members:
    :undoc-members:
    :show-inheritance:


Controller
==========

Die Controllerlogik wird in der Klasse `RFIDController` des nachfolgenden Moduls implementiert.

.. automodule:: src.controller.RfidController
    :members:
    :undoc-members:
    :show-inheritance:

ViewModels
==========

Für den Rfid Server ist sowohl ein QAbstractListModel als auch ein QSortFilterProxyModel implementiert.

.. automodule:: src.viewmodel.RfidViewModel
    :members:
    :undoc-members:
    :show-inheritance:

Views
=====

Das Rfid Server Plugin wird im Programm über die Menubar aufgerufen:
Tools -> RFID Server. 
Für die Darstellung sind zwei QML Dateien zuständig.
RFIDServerPlugin.qml rendert das Hauptfenster. Es enthölt eine ListView, die die Daten des QAbstractListModel über das QSortFilterProxyModel darstellt.
Die Daten werden in dem Delegate RfidDelegate.qml dargestellt.

.. literalinclude:: ../src/view/RFIDServerPlugin.qml
    :linenos:


.. literalinclude:: ../src/view/RfidDelegate.qml
    :linenos:

Manual Commission Control
_________________________

Manual Commission Control wird benötigt um die Kommissionsliste zu manipulieren.
Dadurch können von dem Warehouse Management Programm manuell Transportaufforderungen an den
Industrieroboter ABB IRB 120 gesendet werden.
Der Funktionsumfang ist dabei durch die verfügbaren commands des Roboters begrenzt.

Data Model
==========

Die Kommissionsliste wird in der Klasse `CommissionModel` des nachfolgenden Moduls verwaltet.
Es handelt sich dabei um das im Hauptteil der Software verwendete Datenmodell.

Controller
==========

Funktionen die das DatenModell betreffen, werden in der Klasse `CommissionController` des nachfolgenden Moduls implementiert.
Es handelt sich dabei um den Controller, der im Hauptteil der Software verwendet (und auch dort beschrieben) wird.

ViewModels
==========

Daten des Datenmodells werden über das Modul `commissionViewModel` bereitgestellt.
Es handelt sich dabei um das im Hauptteil der Software verwendete und beschriebene ViewModel.

Views
=====

Das Hauptfenster des PlugIns wird im Programm über die Menubar aufgerufen:
Tools -> Manual Commission Control
MCCPlugin.qml

.. literalinclude:: ../src/view/MCCPlugin.qml
    :linenos:
