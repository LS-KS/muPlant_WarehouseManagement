Eventlog
========

Events die über den EventlogService.py erstellt wurden, werden über das Signal/Slot Prinzip des Qt-Frameworks 
an das GUI gesendet und als StackLayout in dem QML Type 'StackLayoutView.qml' angezeigt.
Das LAyout dafür ist in der Datei 'EventView.qml' definiert: 

.. literalinclude:: ../../src/view/EventView.qml
   :language: javascript
   :linenos:


EventDelegate
-------------

Die einzelnen Events werden in dem QML Type 'EventDelegate.qml' dargestellt.
Das Layout dafür ist in der Datei 'EventDelegate.qml' definiert:

.. literalinclude:: ../../src/view/EventDelegate.qml
   :language: javascript
   :linenos: