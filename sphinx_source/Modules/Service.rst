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
-----------

Dieser Service bildet die Inventurprozesse ab. Vom CameraService gelieferte Bilder werden hier
verarbeitet und ermittelt wie viele Becher in der Lagerzelle wo vorhanden sind.

.. automodule:: src.service.stocktaking
    :members:
    :undoc-members:
    :show-inheritance:

DetectorOptimizationService
---------------------------
Kann verwendet werden um die 31 Parameter für die Markererkennung zu optimieren.
Bei der Optimierung wird wie folgt unterschieden:

.. list-table::
    :header-rows: 1

    * - Attribut
      - Wertebereich
      - Erläuterung
    * - Typ
      - 'gray', 'binary'
      - Legt fest ob Parameter für binärwertige oder graustufige Bilder verwendet werden sollen
    * - Objektart
      - 'pallet', 'cup'
      - Legt fest ob Parameter verwendet werden sollen, die auf Paletten oder Becher optimiert sind
    * - Bereich
      - 0 bis 4
      - 0 = Parameter sind auf das ganze Regal optimiert
        1 = Bereich oben links (L1-L3, L7-L9)
        2 = Bereich oben rechts (L4-L6, L10-L12)
        3 = Bereich unten rechts (L10-L12, L16-L18)
        4 = Bereich unten links (L7-L9, L13-L15)

Die verschiedenen Bereiche unterscheiden sich in Kontrast und Helligkeit.
Anwendung:

1.)

.. topic:: Bilder erzeugen

    Die Bilderkennung im CameraService muss einmalig gelaufen sein, sodass sich im Ordner 'service' Einzelbilder befinden.

2.)

.. topic:: Bereiche anpassen

    In der '__main__' Methode der o.g. Python Datei befinden sich zwei for-Schleifen, die die entsprechenden Bilder laden.
    In dem Datentupel der Forschleife kann der Bereich des Lagers angepasst werden. z.B. (0,1,2,6,7,8) für den Bereich oben links.

3.)

.. topic:: Deteinamen und -pfade anpassen

    In den unteren beiden code-blocks sind die Dateipfade und -Namen der Ausgabe als string als Argument der Funtion
    'dump_parameters' angegeben. Diese müssen entsprechend der Pfadliste in dem Modul src/constants/Constant.py angepasst werden.
    ACHTUNG: Bereits existierende Dateien werden ggf. überschrieben. Im Zweifel müssen diese gesondert gesichert werden.


.. automodule:: src.service.DetectionOptimizationService
    :members:
    :undoc-members:
    :show-inheritance:
