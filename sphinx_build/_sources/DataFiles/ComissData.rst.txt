Kommissionsdaten
================

Kommissionsdaten sind in der Datei 'CommissData.db' gespeichert.
Da das .db Format schlecht lesbar und zu verarbeiten ist, wird diese Datei nicht mehr verwendet.
Aktuelle Kommissionsdatenbank ist CommissionData.yaml

.. literalinclude:: ../../src/data/CommissData.db
   :linenos:

In der aktuellen implementierung 'CommissionData.yaml' werden die Daten in einem YAML Format gespeichert.
In der Datei selbst sind die Daten nach Key/Value Paaren gespeichert und lassen sich somit leicht lesen.

.. literalinclude:: ../../src/data/CommissionData.yaml
    :linenos: