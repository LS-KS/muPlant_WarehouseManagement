Controller
==========

Controller stellen die Schnittstelle zwischen ViewModel und Model dar. Sie sind für die Verarbeitung der Daten zuständig. 
Die einzelnen Controller werden in den folgenden Abschnitten beschrieben.

Inventory Controller
____________________

Der Inventory Controller verbindet die Klassen des DataModel Moduls mit den Viewmodels productlistViewModel, productSummaryViewModel und 
storageViewModel. 

.. automodule:: src.controller.invController
    :members:
    :undoc-members:
    :show-inheritance:

CommissionController
____________________

Der CommissionController verbindet die Klassen CommissionModel und das ViewModel commissionViewModel.

.. automodule:: src.controller.CommissionController
    :members:
    :undoc-members:
    :show-inheritance:

PreferenceController
____________________

Der PreferenceController stellt die Programmeinstellungen aus der Datenklasse Preferences der Anwendung zur Verfügung. 
Es gibt kein ViewModel, jedoch werden die Daten über Signal und Slot an PreferenceDialog übergeben.

.. automodule:: src.controller.PreferenceController
    :members:
    :undoc-members:
    :show-inheritance: