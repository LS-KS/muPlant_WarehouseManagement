Data Model
==========

Datenmodelle sind so implementiert, dass sie da wo nötig Referenzen in beide Richtungen abbilden. 
Der Datenfluss ist somit jederzeit geregelt und die Fehleranfälligkeit wird minimiert.

DataModel.py
------------

Es bildet alle nötigen Python-Objekte ab die für die Hauptanwndung, der Warenfluss durch die Lagerzelle der muPlant, notwendig sind.

.. automodule:: src.model.DataModel
  :members:
  :undoc-members:
  :show-inheritance:

CommissionModel.py
------------------

In dieser Datenklasse werden die Kommissionsaufträge gespeichert und der Anwendung zur Verfügung gestellt.

.. automodule:: src.model.CommissionModel
  :members:
  :undoc-members:
  :show-inheritance:

Preferences.py
--------------

In dieser Datenklasse werden die Einstellungen der Anwendung gespeichert und der Anwendung zur Verfügung gestellt.

.. automodule:: src.model.Preferences
  :members:
  :undoc-members:
  :show-inheritance: