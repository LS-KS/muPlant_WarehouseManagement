StocktakingPlugin
==================

Diese Ansicht rendert die Daten des viewmodels :py:class:`stockmodel` in einer Tabelle und :py:class:`tablemodel` in einer Listenansicht.
Da die viewmodels während des Inventurprozesses aktualisiert werden, werden die Daten in der Ansicht automatisch durch das 'dataChanged'-Signal aktualisiert.
Es sind einfache Funktionen implementiert, die verschiedene Icons auf Grund von Bedingungen anzeigen.
sie spiegeln wieder, ob eine Inventur stattgefunden hat und ob die Erfassung durch die Inventur zu dem gleichen oder einem
anderen Ergebnis gekommen ist.
Der Benutzer hat die Möglichkeiten manuell die Kamera des Greifers und der Übersichtskamere auszurufen.
Er kann zudem einen Inventurvorgang auslösen oder die automatische Inventur starten.

.. literalinclude:: ../../src/view/StocktakingPlugin.qml
    :language: javascript
    :linenos: