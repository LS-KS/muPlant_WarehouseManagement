Manual Commission Control
=========================

Manual Commission Control wird benötigt um die Kommissionsliste zu manipulieren.
Dadurch können von dem Warehouse Management Programm manuell Transportaufforderungen an den
Industrieroboter ABB IRB 120 gesendet werden.
Der Funktionsumfang ist dabei durch die verfügbaren commands des Roboters begrenzt.

Data Model
__________

Die Kommissionsliste wird in der Klasse `CommissionModel` des nachfolgenden Moduls verwaltet.
Es handelt sich dabei um das im Hauptteil der Software verwendete Datenmodell.

Controller
__________

Funktionen die das DatenModell betreffen, werden in der Klasse `CommissionController` des nachfolgenden Moduls implementiert.
Es handelt sich dabei um den Controller, der im Hauptteil der Software verwendet (und auch dort beschrieben) wird.

ViewModels
__________

Daten des Datenmodells werden über das Modul `commissionViewModel` bereitgestellt.
Es handelt sich dabei um das im Hauptteil der Software verwendete und beschriebene ViewModel.

Views
_______

Das Hauptfenster des PlugIns wird im Programm über die Menubar aufgerufen:
Tools -> Manual Commission Control
MCCPlugin.qml

.. literalinclude:: ../src/view/MCCPlugin.qml
    :linenos:
