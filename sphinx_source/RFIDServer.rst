RFID Server
===========

RFID Server wird benötigt um die RFID Reader der Firma Feig Electronic GmbH anzusteuern.
Dabei werden alle RFID Reader der µPlant über Modbus ausgelesen und die ausgelesenen Daten
visualisiert. Die Daten werden außerdem über OPCUA im ganzen Netz zur Verfügung gestellt.

Data Model
__________

Die Daten werden in der Klasse `RFIDModel` des nachfolgenden Moduls verwaltet.

.. automodule:: src.model.RfidModel
    :members:
    :undoc-members:
    :show-inheritance:


Controller
__________

Die Controller -Logik wird in der Klasse `RFIDController` des nachfolgenden Moduls implementiert.

.. automodule:: src.controller.RfidController
    :members:
    :undoc-members:
    :show-inheritance:

Service
__________

Das Plugin nutzt die Serviceklasse `rfid_service` um für einen oder mehrere Listeneinträge der View einen Thread zum
Auslesen des Lesegeräts zu erstellen.

.. automodule:: src.service.rfid_service
    :members:
    :undoc-members:
    :show-inheritance:

ViewModels
__________

Für den Rfid Server ist sowohl ein QAbstractListModel als auch ein QSortFilterProxyModel implementiert.

.. automodule:: src.viewmodel.RfidViewModel
    :members:
    :undoc-members:
    :show-inheritance:

Views
_______

Das Rfid Server Plugin wird im Programm über die Menubar aufgerufen:
Tools -> RFID Server. 
Für die Darstellung sind zwei QML Dateien zuständig.
RFIDServerPlugin.qml rendert das Hauptfenster. Es enthölt eine ListView, die die Daten des QAbstractListModel über das QSortFilterProxyModel darstellt.
Die Daten werden in dem Delegate RfidDelegate.qml dargestellt.

.. literalinclude:: ../src/view/RFIDServerPlugin.qml
    :linenos:


.. literalinclude:: ../src/view/RfidDelegate.qml
    :linenos: