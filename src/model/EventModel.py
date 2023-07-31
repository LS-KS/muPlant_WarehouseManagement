from datetime import datetime
class EventMessage:

    def __init__(self, source, message):
        self.time = datetime.now()
        self.source = source
        self.message = message