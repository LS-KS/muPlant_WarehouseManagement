ViewModel
=========

Die Nachfolgenden Module sind ViewModel und erben von den entsprechenden Datenmodel - Klassen des Qt Frameworks.
Sie sind notwendig, damit die QML-Engine die Daten in QML Items wie z.B. ListView rendern kann.
Um die Daten sortierbar, bzw. filterbar zu machen, muss ein QSortFilerProxyModel verwendet werden.

productlistViewModel
--------------------

Das ViewModel für die Produktliste. Es erbt von QAbstractListModel und stellt die Daten für die Produktliste bereit.
Die Produktliste kann als separates Fenster für den Benutzer als Referenz eingeblendet werden.

.. automodule:: src.viewmodel.productlistViewModel
    :members:
    :undoc-members:
    :show-inheritance:

productSummaryViewModel
-----------------------

Das ViewModel stellt die Produktliste zusammen mit den vorhandenen Lagermengen bereit. 

.. automodule:: src.viewmodel.productSummaryViewModel
    :members:
    :undoc-members:
    :show-inheritance:

storageViewModel
----------------

Das storageViewModel bildet die Datengrundlage des Lager-Regals der Lagerzelle ab. 
Es hat eine feste Größe (18 Slots) in denen je eine Palette engelaqgert werden kann.
Jede Palette kann wiederum 0-2 Cup- Objekte speichern.
Die Daten werden in einer TableView gelistet. Jede Zelle der TableView enthält ein ProduktView Item.

.. automodule:: src.viewmodel.storageViewModel
    :members:
    :undoc-members:
    :show-inheritance:

commissionViewModel
-------------------

Das commissionViewModel stellt die Daten der Kommissionsliste als QAbstractListModel bereit.

.. automodule:: src.viewmodel.commissionViewModel
    :members:
    :undoc-members:
    :show-inheritance:
