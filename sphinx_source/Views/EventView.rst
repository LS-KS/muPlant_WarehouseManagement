Eventlog
========

Events die über den EventlogService.py erstellt wurden, werden über das Signal/Slot Prinzip des Qt-Frameworks 
an das GUI gesendet und als StackLayout in dem QML Type 'StackLayoutView.qml' angezeigt.
Das LAyout dafür ist in der Datei 'EventView.qml' definiert: 

.. literalinclude:: ../../src/view/EventView.qml
   :language: javascript