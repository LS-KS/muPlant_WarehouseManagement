from PySide6.QtCore import QObject, Signal, Slot, QThread, QMutex, QMutexLocker
from PySide6.QtWidgets import QApplication
from src.model.CommissionModel import CommissionState, Locations
import socket
import select
import sys


class abbservice(QObject):

    start_worker = Signal() 
    stop_worker = Signal()
    transmit_data = Signal(str)

    def __init__(self, ip:str, port:int, parent=None):
        super().__init__(parent)
        self.ip = ip
        self.port = port
        self.worker = None

    @Slot()
    def start(self):
        """
        Creates a abbsocketworker which inherits from QThread. Uses QMutex to lock data_to_transmit and start_transmit. 
        Connects various signals to abbsocketworker slots. Starts worker by emitting start_worker signal. 
        """
        self.worker = abbsocketworker(ip=self.ip, port=self.port)
        self.transmit_data.connect(self.worker.handle_transmit)
        self.start_worker.connect(self.worker.start)
        self.stop_worker.connect(self.worker.stop)
        self.worker.started.connect(self.handle_started)
        self.worker.stopped.connect(self.handle_stopped)
        self.worker.connection.connect(self.handle_connection)
        self.worker.data.connect(self.handle_data)
        self.worker.notconnected.connect(self.handle_notconnected)
        self.worker.loop.connect(self.handle_loop)
        self.start_worker.emit()

    @Slot()
    def stop(self):
        """
        Stops worker by emitting stop_worker signal. This will delete the worker object.
        Must be called to stop abbservice.
        If it is not called, the worker will continue to run in the background which blocks the port for new sockets.
        """
        self.stop_worker.emit()

    @Slot(str, str)
    def handle_commission(self, source:str, target:str):
        """
        creates execute string from submitted source and target strings.
        These must correspond to the names of the Locations enum object in the commission.
        Emits transmit_data signal with execute string as argument.
        This will be received by the abbsocketworker and transmitted via socket connection to the IRC5 controller.
        """
        execute = self._create_execute_strings(source, target)
        self.transmit_data.emit(execute)
    
    @Slot(bool, str)
    def handle_started(self, result, exception):
        """
        This method is connected to the abbsocketworker.started signal and thus is called when the worker is started.
        """
        print("Service started") if result else print(f"Error while starting: {exception}")
    
    @Slot()
    def handle_stopped(self):
        """
        This method is connected to the abbsocketworker.stopped signal and thus is called when the worker is stopped.
        """
        print("Service stopped")

    @Slot(str, str)
    def handle_connection(self, client:str, client_address:str):
        """
        This method is connected to the abbsocketworker.connection signal and thus is called when a client connects to the socket.
        """
        print(f"Connection from {client},{client_address[0]}:{client_address[1]}")

    @Slot(str)
    def handle_data(self, data:str):
        """
        This method is connected to the abbsocketworker.data signal and thus is called when data is received from the socket.
        """
        print(f"Received data: {data}")
    
    @Slot()
    def handle_loop(self):
        """
        This method is for debug purposes only. It is connected to the abbsocketworker.loop signal and thus is called in every while loop iteration.
        """
        print("Looping")
    
    @Slot(str)
    def handle_notconnected(self, message:str):
        """
        This method is connected to the abbsocketworker.notconnected signal and thus is called when no client is connected to the socket.
        """
        print(message)

    def _create_execute_strings(self, source:str, target:str)->str:
        """
        Create execute strings for IRC5 controller. These are submitted by socket connection.
        string cannot be calculated by formulas, so a dictionary is used to map the locations to string numbers.



        param source: source string from commission, can be created by Locations[idx].name
        type source: str
        param target: target string from commission, , can be created by Locations[idx].name
        type target: str
        return: execute string for IRC5 controller
        rtype: str
        raises ValueError: if errors occur while decoding Locations. These should only be the casein development
        """
        st_map = {
        "L1": (3, 1), "L2": (3, 2), "L3": (3, 3),
        "L4": (3, 4), "L5": (3, 5), "L6": (3, 6),
        "L7": (2, 1), "L8": (2, 2), "L9": (2, 3),
        "L10": (2, 4), "L11": (2, 5), "L12": (2, 6),
        "L13": (2, 7), "L14": (2, 8), "L15": (2, 9),
        "L16": (2, 10), "L17": (2, 11), "L18": (2, 12)
        }
        wb_map = {
            "K1": (1, 1), "K2": (1, 2),
        }
        r_map = {"R": (0, 1, 1)}

        loc_source = Locations[source]
        loc_target = Locations[target]
        cup = True if loc_source.name[-1] in ["A", "B", "T"] else False
        pallet = True if int(loc_source.name[-1]) in range(19) else False
        src_workbench = loc_source.name[0] == "K"
        trg_workbench = loc_target.name[0] == "K"
        src_inventory = loc_source.name[0] == "L"
        trg_inventory = loc_target.name[0] == "L"
        src_robot = loc_source.name[0] == "R"
        trg_robot = loc_target.name[0] == "R"
        if cup == pallet:
            raise ValueError("Error while decoding object to transport")
        # Cup from ROBOT to WORKBENCH
        if all[cup, src_robot, trg_workbench]:
            idx = loc_target.name[0:1]
            slot = 1 if loc_target.name[-1] == "A" else 2
            col = loc_target.name[1]
            return f"Becher_{r_map('R')[0]}_{r_map('R')[1]}_{r_map('R')[2]}_{wb_map(idx)[0]}_{wb_map(idx)[1]}_{slot}"
        # Cup from WORKBENCH to ROBOT
        elif all[cup, src_workbench, trg_robot]:
            idx = loc_source.name[0:1]
            slot = 1 if loc_source.name[-1] == "A" else 2
            col = loc_source.name[1]
            return f"Becher_{wb_map(idx)[0]}_{wb_map(idx)[1]}_{slot}_{r_map('R')[0]}_{r_map('R')[1]}_{r_map('R')[2]}"
        # Cup from WORKBENCH to WORKBENCH
        elif all[cup, src_workbench, trg_workbench]:
            src_slot = 1 if loc_source.name[-1] == "A" else 2
            src_col = loc_source.name[1]
            src_idx = loc_source.name[0:1]
            trg_slot = 1 if loc_target.name[-1] == "A" else 2
            trg_col = loc_target.name[1]
            trg_idx = loc_target.name[0:1]
            return f"Becher_{wb_map(src_idx)[0]}_{wb_map(src_idx)[1]}_{src_slot}_{wb_map(trg_idx)[0]}_{wb_map(trg_idx)[1]}_{trg_slot}"
        # Pallet from WORKBENCH to INVENTORY       
        elif all[pallet, src_workbench, trg_inventory]:
            src = wb_map(loc_source.name) # If pallet, source is "K1" or "K2"
            trg = st_map(loc_target.name) # If pallet, target is "L1" to "L18"
            return f"Palette_{src[0]}_{src[1]}_{trg[0]}_{trg[1]}"
        # Pallet from INVENTORY to WORKBENCH
        elif all[pallet, src_inventory, trg_workbench]:
            src = st_map(loc_source.name) # If pallet, source is "L1" to "L18"
            trg = wb_map(loc_target.name) # If pallet, target is "K1" or "K2"
            return f"Palette_{src[0]}_{src[1]}_{trg[0]}_{trg[1]}"
        raise ValueError("Error while encoding execute string")	


class abbsocketworker(QThread):
    started = Signal(bool, str)
    stopped = Signal(bool)
    connection = Signal(str, str)
    notconnected = Signal(str)
    data = Signal(str)
    loop = Signal()

    def __init__(self, ip:str, port:int, parent = None):
        super().__init__(parent)
        self.ip = ip
        self.port = port
        self.mutex = QMutex()
        self.server = None
        self.is_running = False
        self.data_to_transmit = None
        self.start_transmit = False
        self.transmitting = False


    def start(self):
        """
        Overwrites QThread.start() method. Creates socket server and starts thread.
        """
        try:
            super().start()
            self.server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            self.server.bind((self.ip, self.port))
            self.buffersize = 1024
            self.server.listen(1)
            self.is_running = True
            self.started.emit(True, "")
        except Exception as e:
            self.started.emit(False, str(e))
        

    @Slot()
    def stop(self):
        """
        Overwrites QThread.stop() method. Stops thread and closes socket server.
        Deletes thread object.
        """
        self.is_running = False
        self.server.close()
        super().quit()
        super().wait()
        super().deleteLater()

    @Slot(str)
    def handle_transmit(self, data:str):
        """
        Sets data_to_transmit and start_transmit variables. 
        These are used in the run() method to transmit data via socket connection.
        Uses QMutex to lock data_to_transmit and start_transmit.
        """
        data_set = False
        with QMutexLocker(self.mutex):
            while not data_set:
                if not self.transmitting:
                    self.data_to_transmit = data
                    self.start_transmit = True
                    data_set = True


    def run(self):
        """
        Overwrites QThread.run() method. This method is called when thread is started.
        Creates socket server and listens for incoming connections using select.select().
        If a connection is received, the client is accepted and a new thread is created for the client.
        Also in this case the connection signal is emitted.
        A while loop is used to send and receive data from the client using a QMutex to lock the thread.
        Uses UTF-8 encoding for data transmission.
        """
        while self.is_running:
            # self.loop.emit()
            readables, _, _ = select.select([self.server], [], [], 0.1)
            if self.server in readables:
                client, client_addr = self.server.accept()
                self.connection.emit(str(client), client_addr)
                while True:
                    with QMutexLocker(self.mutex):
                        if self.start_transmit:
                            self.transmitting = True
                            client.send(self.data_to_transmit.encode("utf-8"))
                            self.data_to_transmit = None
                            self.start_transmit = False
                            self.transmitting = False
    
                    response = "accepted".encode("utf-8")
                    client.send(response)
                    request = client.recv(self.buffersize)
                    request = request.decode("utf-8")
                    if request.lower() == "close":
                        client.send("closed".encode("utf-8"))
                        break
                    elif request:
                        self.data.emit(request)
            elif self.start_transmit:
                self.notconnected.emit("No client connected")


if __name__ == "__main__":
    import time
    app = QApplication(sys.argv)
    service = abbservice(ip="192.168.180.23" , port=5000)
    service.start()
    service.transmit_data.emit("test")
    time.sleep(2)
    service.stop()
    sys.exit(app.exec())