Service
=======

EventlogService
---------------

Der EventlogService ermögicht es der gesamten Anwendung Strings entgegenzunehmen und als Events in 
der QML View Eventlog zu rendern. 

.. automodule:: src.service.EventlogService
    :members:
    :undoc-members:
    :show-inheritance:

AgentService
------------

Bildet die Implementierung des AgentService von Lers Kistner ab. 

.. automodule:: src.service.AgentService
    :members:
    :undoc-members:
    :show-inheritance:
    
OpcuaService
------------

Hostet einen OPC UA Server und Client für die Kommunikation mit der muPlant

.. automodule:: src.service.OpcuaService
    :members:
    :undoc-members:
    :show-inheritance:

CameraService
-------------
Der CameraService nutzt die IDS Peaks und IDS Peaks IPL Api.
Auf Anfrage des Stocktaking Moduls liefert der Bilder der beiden Kameras.

.. automodule:: src.service.CameraService
    :members:
    :undoc-members:
    :show-inheritance:

Stocktaking
___________

Dieser Service bildet die Inventurprozesse ab. Vom CameraService gelieferte Bilder werden hier
verarbeitet und ermittelt wie viele Becher in der Lagerzelle wo vorhanden sind.

.. automodule:: src.service.stocktaking
    :members:
    :undoc-members:
    :show-inheritance:
