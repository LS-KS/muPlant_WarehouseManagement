
class Preferences:
    """
    This class is used to store the preferences of the program

    """
    def __init__(self, ):
        self.modBus = modBusPreferences()
        self.abb = abbPreferences()
        self.plugins = PlugInPreferences()

class modBusPreferences:
    def __init__(self):
        self.ip = None
        self.port = None
        self.maxReconnects = None

    def setIP(self, ip)->bool:
        """
        This method sets the modBus IP address and returns True if valid.
        Returns False if ip syntax is invalid.
        :param ip:
        :return:
        """
        if self.__validateIP(ip):
            self.ip = ip
            return True
        else:
            return False

    def setPort(self, port)->bool:
        """
        This method sets the modBus port and returns True if valid.
        Returns False if port syntax is invalid.
        :param port:
        :return:
        """
        if self.__validatePort(port):
            self.port = port
            return True
        else:
            return False

    def setMaxReconnects(self, tries)->bool:
        if self.__validatemaxTries(tries):
            self.maxReconnects = tries
            return True
        else:
            return False

    def __validatemaxTries(self, tries):
        if isinstance(int(tries), int) and int(tries) > 0:
            return True
        else:
            return False

    def __validateIP(self, ip):
        """
        This method validates the entered IP address syntax and returns True if valid

        :param ip:
        :return: boolean
        """
        if ip == "":
            return False
        elif ip == None:
            return False
        ip = ip.split(".")
        if len(ip) != 4:
            return False
        for idx, i in enumerate(ip):
            if not isinstance(int(i), int):
                return False
            else:
                if int(i) < 0 or int(i) > 255:
                    return False
            if idx == 0:
                if int(i) < 127:
                    return False
        return True

    def __validatePort(self, port):
        """
        This method validates the entered port syntax and returns True if valid

        :param port:
        :return: boolean
        """
        if port == "":
            return False
        elif port == None:
            return False
        if not isinstance(int(port), int):
            return False
        else:
            if int(port) < 0 or int(port) > 65535:
                return False
        return True
class abbPreferences:

    def __init__(self):
        self.ip = None
        self.port = None

    def setIP(self, ip)->bool:
        """
        This method sets the abb IP address and returns True if valid.
        Returns False if ip syntax is invalid.
        :param ip:
        :return:
        """
        if self.__validateIP(ip):
            self.ip = ip
            return True
        else:
            return False

    def setPort(self, port)->bool:
        """
        This method sets the abb port and returns True if valid.
        Returns False if port syntax is invalid.
        :param port:
        :return:
        """
        if self.__validatePort(port):
            self.port = port
            return True
        else:
            return False

    def __validateIP(self, ip)->bool:
        """
        This method validates the entered IP address syntax and returns True if valid

        :param ip:
        :return: boolean
        """
        if ip == "":
            return False
        elif ip == None:
            return False
        ip = ip.split(".")
        if len(ip) != 4:
            return False
        for i in ip:
            if not isinstance(int(i), int):
                return False
            else:
                if int(i) < 0 or int(i) > 255:
                    return False
        return True

    def __validatePort(self, port):
        """
        This method validates the entered port syntax and returns True if valid

        :param port:
        :return: boolean
        """
        if port == "":
            return False
        elif port == None:
            return False
        if not isinstance(int(port), int):
            return False
        else:
            if int(port) < 0 or int(port) > 65535:
                return False
        return True
class PlugInPreferences:
    def __init__(self):
        self.autostartRfidServer = False
        self.autostartMccPlugin = False