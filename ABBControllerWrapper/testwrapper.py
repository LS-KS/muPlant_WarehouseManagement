import clr
import asyncio


class wrappertester:
    def __init__(self, ip):
        self.ip = ip
        self.connected = False
        self.busy = False
        self.abb_controller = None

    def setup(self):
        dll = "ABBControllerWrapper/bin/Release/net6.0/ABBControllerWrapper"
        clr.AddReference(dll)
        from ABBPythonLinker import ABBLinker
        try:
            self.abb_controller = ABBLinker(str(self.ip))
            self.connected = self.abb_controller.Setup()
        except Exception as e:
            print(f"ABBController: Error during setup: {e}")
            self.abb_controller = None
            self.connected = False

    def move_item(self, source: str, target: str):
        """
        If setup is successful, this method calls the CreateAndExecute method of the ABBLinker class.
        This creates a command task of the SDK and sends an execute command to the controller unit.
        the strings must be formatted accordingly.
        :param source: formatted string of the execute command
        :type source: str
        :param target: formatted string of the execute command
        :type target: str
        """
        if self.connected and not self.busy:
            self.busy = True
            self.notify_busy.emit(self.busy)
            result = asyncio.run(self.abb_controller.CreateAndExecute(source, target))
        if result:
            self.busy = False
            self.notify_busy.emit(self.busy)
            self.notify_transport.emit(source, target)
            self.eventlog_service.write_event("ABBControlller", f"Moved Item {source}-->{target}")
        else:
            self.busy = False
            self.notify_busy.emit(self.busy)
            self.eventlog_service.write_event("ABBControlller", f"Error moving Item {source}-->{target}, False returned")

if __name__ == "__main__":
    print("create instance")
    ip = "192.168.2.54"
    tester = wrappertester(ip)
    print("setup")
    tester.setup()
    print("setup done")