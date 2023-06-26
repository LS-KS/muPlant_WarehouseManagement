from PySide6.QtCore import Signal, Slot, QObject
from datetime import datetime





class EventlogService (QObject):
    """

    Can be instanciated in any other class.
    creates an event string from two entered strings and emitss a signal.
    writeEvent() can be called from python object or form qml engine

    """
    def __init__(self):
        """
        Initialize class
        """
        super().__init__()
        self.messages = []

    newSignal = Signal(str)

    def createMessage(self,source, message):
        """

        Creates a string from provided source-string and source-message.

        :param source: Can be any String
        :type source: str
        :param message: Can be any string
        :type message: str
        :return: formatted message

        """
        time = datetime.now()
        return f"[{time}] [{source}]: {message}"

    @Slot(str, str)
    def writeEvent(self, source, message):
        """
        obtains two strings, creates an event message from it and emits the formatted string as signal.
        :param source: can be any string
        :type source: str
        :param message: can be any string
        :type message: str
        :return: None
        """
        #print("Eventcontroller: "+message)
        msg = self.createMessage(source, message)
        self.messages.append(msg)
        self.newSignal.emit(msg)