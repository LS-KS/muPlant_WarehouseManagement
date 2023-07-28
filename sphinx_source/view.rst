
View
====
Das GUI ist in QML geschrieben und wird durch die QML-Engine des Qt-Frameworks gerendert.

.. toctree::
   :maxdepth: 1
   :caption: Contents:
   :glob:
   
   Views/MainView

   Views/HeaderLine

   Views/Help

   Views/CommissionView

   Views/CupView

   Views/InventoryView

   Views/EventView

   Views/GripperDialog



Hauptfenster:
main.qml

.. literalinclude:: ../src/view/main.qml
    :linenos:

Banner mit Logo und Programmtitel:
HeaderLine.qml

.. literalinclude:: ../src/view/HeaderLine.qml
    :linenos:

Ansicht mit mobilem Roboter inklusive Becher und Sensoren:
TurtleView.qml

.. literalinclude:: ../src/view/TurtleView.qml
    :linenos:


Ansicht einer Palette mit Becher:
PalletteView.qml

.. literalinclude:: ../src/view/PalletteView.qml
    :linenos:

Alternative Ansicht einer Palette mit zwei Becher:
ProductView.qml

.. literalinclude:: ../src/view/ProductView.qml
    :linenos:

Visualisierung des Anlagenschemas der Lagerzelle:
ProcessView.qml

.. literalinclude:: ../src/view/ProcessView.qml
    :linenos:

Visualisierung des gesamten Lagerregals:
StorageView.qml

.. literalinclude:: ../src/view/StorageView.qml
    :linenos:

Visualisierung des Eventloggers:
EventView.qml

.. literalinclude:: ../src/view/EventView.qml
    :linenos:

Visualisierung der Registeransicht:
StackLayoutView.qml

.. literalinclude:: ../src/view/StackLayoutView.qml
    :linenos:

Visualisierung der Kommissionen:
CommissionView.qml

.. literalinclude:: ../src/view/CommissionView.qml
    :linenos:

Visualisierung der Inventarzusammenfassung:
InventoryView.qml

.. literalinclude:: ../src/view/InventoryView.qml
    :linenos:


Eine einfache Produktliste zur Überischt kann im Hauptfenster über
Tools --> Show Productlist aufgerufen werden. Sie wird in einem neuen Fenster gerendert.
ProductListView.qml

.. literalinclude:: ../src/view/ProductList.qml
    :linenos:


Ein Fenster kann über die Menüleiste unter File --> Help aufgerufen werden
um die Code-Dokumentation aufzurufen.

..literalinclude:: ../src/view/Help.qml
    :linenos:
