Main File
=========

Das main-File ist der Einsprungspunkt des Programms. Es werden eine Instanz der Application und der QML-Engine erstellt. 
Sämtliche Controller und Datenmodelle werden initialisiert.
Diese Instanzen der Python-Objekte werden als RootContext der QML-Engine hinzugefügt, sodass Sie über den QML-Inhalt angesprochen werden können.

.. literalinclude:: ../../main.py
    :language: python
    :linenos:
