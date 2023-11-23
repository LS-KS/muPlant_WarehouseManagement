using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Diagnostics;
using System.Net;
using System.Threading;
using ABB.Robotics.Controllers;
using ABB.Robotics.Controllers.Discovery;
using ABB.Robotics.Controllers.RapidDomain;
using System.Reflection;
using System.ComponentModel;
using System.Collections.ObjectModel;
using Task = System.Threading.Tasks.Task;
using System.Security.Cryptography;

namespace ABBControllerWrapper
{
    public class ABBControllerWrapper
    {
        private RobotController robotController;
        private IPAddress IPAddressRequested;
        private string ipstring;
        private Task? controllerTask;
        public ABBControllerWrapper() {
            robotController = new RobotController();
           
        }
        ~ABBControllerWrapper() { 
            if (this.robotController != null)
            {
                this.robotController.Disconnect();
            }
        }
        public bool Setup(string ip)
        {
            this.ipstring = ip;
            if (IPAddress.TryParse(ipstring, out IPAddress iPAddress))
            {
                this.IPAddressRequested = iPAddress;
            }
            else
            {
                throw new ArgumentException("submitted ip address could not be parsed: ", nameof(iPAddress));
            }
            this.controllerTask = this.robotController.TryConnectAsync(this.IPAddressRequested);
            return this.robotController.IsConnected;
        }
        /// <summary>
        /// creates a command object and executes it using the ABBRobotics dlls.
        /// this method takes a source string and a target string. 
        /// </summary>
        /// <param name="source">source string: 'm' for mobile robot, 'k1a' for commissiontable, 'l1a' to 'l18b' for storage. If no suffix letter is submitted, a pallet is meant.</param>
        /// <param name="target">target string: 'm' for mobile robot, 'k1a' for commissiontable, 'l1a' to 'l18b' for storage. If no suffix letter is submitted, a pallet is meant</param>
        /// <returns></returns>
        public bool CreateAndExecute(string source, string target) {
            // This way of programming my lead to deadlock in this specific thread. 
            // maybe it is better to return the Task and await the Task in python.
            // If this works, it is definitely the more easy way!

            ControllerCommand? command = null;
            // parse source
            if (source.Equals('m'))
            {
                // source is mobile robot. Thus only 'RobotToWorkbench' can be called
                if (target[0].Equals('k'))
                {
                    int w_col = (int)target[1];
                    int w_pos = target[2].Equals('a') ? 0 : 1;
                    command = ControllerCommand.RobotToWorkbench(w_col: w_col, w_pos: w_pos, executable: true);
                }
            }
            else if (source[0].Equals('l'))
            {
                // source is storage, so storage->workbench (Pallet)
                int storage = (source.Length == 3) ? (int)source[1] : (int.Parse(source.Substring(1, 1)));
                // calculate row/col from string
                int s_row = (storage - 1) / 6;
                int s_col = (storage - 1) % 6;
                int w_col = (int)target[1];
                command = ControllerCommand.StorageToWorkbench(s_row: s_row, s_col: s_col, w_col: w_col, executable: true);
            }
            else if (source[0].Equals('k'))
            {
                // source is workbench,so workbench->workbench, workbench->robot, workbench->storage
                if (target[0].Equals('k'))
                {
                    // workbench->workbench (Cup)
                    int from_col = (int)source[1];
                    int from_pos = (source[2].Equals('a')) ? 0 : 1;
                    int to_col = (int)target[1];
                    int to_pos = (target[2].Equals('a')) ? 0 : 1;
                    command = ControllerCommand.WorkbenchToWorkbench(from_col: from_col, from_pos: from_pos, to_col: to_col, to_pos: to_pos, executable: true);
                }else if (target[0].Equals('l'))
                {
                    // workbench->storage (Pallet)
                    int w_col = (int)source[1];
                    int storage = (target.Length == 3) ? (int)target[1] : (int.Parse(target.Substring(1, 1)));
                    int s_row = (storage - 1) / 6;
                    int s_col = (storage - 1) % 6;
                    command = ControllerCommand.WorkbenchToStorage(w_col: w_col, s_row: s_row, s_col: s_col, executable: true);
                }else if (target[0].Equals('m'))
                {
                    // workbench->robot (Cup)
                    int w_col = (int)source[1];
                    int w_pos = (source[2].Equals('a')) ? 0 : 1;

                    command = ControllerCommand.WorkbenchToRobot(w_col: w_col, w_pos: w_pos, executable: true);
                }
            }
            if(command != null)
            {
                Task<bool> task = this.robotController.ExecuteCommand(command);
                task.Wait();
                return task.Result;
            }else
            {
                return false;
            }
        }
    }
    public class ControllerCommand : INotifyPropertyChanged
    {
        #region Property Changed Event
        public event PropertyChangedEventHandler? PropertyChanged;
        public void NotifyPropertyChanged(string propName)
        {
            if (PropertyChanged != null)
                PropertyChanged(this, new PropertyChangedEventArgs(propName));
        }
        #endregion

        #region Properties
        private bool isExecuting = false;
        private bool executable = false;
        private string command = string.Empty;
        private string description = string.Empty;
        #endregion

        #region Properties Handlers:
        public bool IsExecuting
        {
            get { return isExecuting; }
            set
            {
                if (isExecuting != value)
                {
                    isExecuting = value;
                    NotifyPropertyChanged("IsExecuting");
                }
            }
        }
        public bool Executable
        {
            get { return executable; }
            set
            {
                if (executable != value)
                {
                    executable = value;
                    NotifyPropertyChanged("Executable");
                }
            }
        }
        public string Command
        {
            get { return command; }
            set
            {
                if (command != value)
                {
                    command = value;
                    NotifyPropertyChanged("Command");
                }
            }
        }
        public string Description
        {
            get { return description; }
            set
            {
                if (description != value)
                {
                    description = value;
                    NotifyPropertyChanged("Description");
                }
            }
        }
        #endregion

        #region Variables
        public ushort cupID;
        public ushort prodID;
        public bool requireMobileRobot;
        public bool shouldCheckID;
        #endregion


        #region Static Methods
        /// <summary>
        /// StorageToWorkbench transportiert eine Palette vom Lager zum Kommissioniertisch. 
        /// </summary>
        /// <param name="s_row"> Regalreihe </param>
        /// <param name="s_col"> Regalspalte </param>
        /// <param name="w_col"> Kommisioniertischplatz K1 / K2 </param>
        /// <param name="cupId"> ID eines Bechers </param>
        /// <param name="prodId"> ID eines Produkts</param>
        /// <param name="executable"> ?? Ob Command ausführbar ist? </param>
        /// <param name="storage"> Palettenobjekt im Lager</param>
        /// <param name="workbench"> Palettenobject auf dem Kommissioniertisch ?</param>
        /// <returns> Ein ControllerCommand Objekt.</returns>
        static public ControllerCommand StorageToWorkbench(int s_row, int s_col, int w_col, bool executable)
        {
            ControllerCommand cmd = new ControllerCommand();

            int station = 3;
            if (s_row > 0) station = 2;

            int position = s_col + 1;
            if (s_row == 2) position += 6;

            cmd.command = string.Format("Palette_{0}_{1}_1_{2}", station, position, w_col + 1);
            cmd.IsExecuting = false;
            cmd.Executable = executable;
            cmd.requireMobileRobot = false;
            cmd.shouldCheckID = false;
            return cmd;
        }
        /// <summary>
        /// WorkbenchToStorage transportiert eine Palette vom KOmmissioniertisch zum Lagerregal.
        /// </summary>
        /// <param name="s_row"> Regalreihe </param>
        /// <param name="s_col"> Regalspalte </param>
        /// <param name="w_col"> Kommissioniertisch</param>
        /// <param name="cupId"> ID eines Bechers</param>
        /// <param name="prodId"> ID eines Produkts</param>
        /// <param name="executable"> ??? ob command ausführbar ist?</param>
        /// <param name="storage"> Palettenobjekt im Lager?</param>
        /// <param name="workbench"> Palettenobjekt auf dem Kommissioniertisch ?</param>
        /// <returns></returns>
        static public ControllerCommand WorkbenchToStorage(int s_row, int s_col, int w_col, bool executable)
        {
            ControllerCommand cmd = new ControllerCommand();
            int station = 3;
            if (s_row > 0) station = 2;
            int position = s_col + 1;
            if (s_row == 2) position += 6;
            cmd.command = string.Format("Palette_1_{2}_{0}_{1}", station, position, w_col + 1);
            cmd.IsExecuting = false;
            cmd.Executable = executable;
            cmd.requireMobileRobot = false;
            cmd.shouldCheckID = false;
            return cmd;
        }
        /// <summary>
        /// WorkbenchToRobot transportiert einen Becher vom Kommissioniertisch zum mobilen Roboter.
        /// </summary>
        /// <param name="w_col">Palettenplatz auf dem Kommissioniertisch</param>
        /// <param name="w_pos">Becherposition auf der Palette im Kommissioniertisch</param>
        /// <param name="cupId">ID eines Bechers</param>
        /// <param name="prodId">ID eines Produkts</param>
        /// <param name="executable">??? ob Command ausführbar ist???</param>
        /// <param name="workbenchPallet">Palette auf dem Kommissioniertisch</param>
        /// <param name="mobileRobotCup">Becher im Roboter (Ziel)</param>
        /// <returns></returns>
        static public ControllerCommand WorkbenchToRobot(int w_col, int w_pos, bool executable)
        {
            ControllerCommand cmd = new ControllerCommand();

            cmd.command = string.Format("Becher_1_{0}_{1}_0_1_1", w_col + 1, w_pos + 1);
            cmd.IsExecuting = false;
            cmd.Executable = executable;
            return cmd;
        }
        /// <summary>
        /// RobotToWorkbench transportiert einen Becher von dem mobilen Roboter in eine Palette auf dem Kommissioniertisch.
        /// </summary>
        /// <param name="w_col"> Palettenplatz auf dem Kommissioniertisch K1/K2</param>
        /// <param name="w_pos"> Becherposition Position in der Palette auf dem Kommissioniertisch</param>
        /// <param name="cupId"> ID eines Bechers </param>
        /// <param name="prodId"> ID eines Produkts </param>
        /// <param name="executable"> ??? ob command ausführabr ist?</param>
        /// <param name="workbenchPallet"> Palette die auf dem Kommissioniertisch steht </param>
        /// <param name="mobileRobotCup"> Becher, der auf dem mobilen Roboter steht </param>
        /// <returns></returns>
        static public ControllerCommand RobotToWorkbench(int w_col, int w_pos, bool executable)
        {
            ControllerCommand cmd = new ControllerCommand();
            cmd.command = string.Format("Becher_0_1_1_1_{0}_{1}", w_col + 1, w_pos + 1);
            cmd.IsExecuting = false;
            cmd.Executable = executable;
            return cmd;
        }
        /// <summary>
        /// WorkbenchToWorkbench transportiert einen Becher auf dem Kommissioniertisch von Palette zu Palette.
        /// </summary>
        /// <param name="from_col"> Palettenplatz des Kommissioniertischs (Start) </param>
        /// <param name="from_pos"> Becherposition des Palettenplatzes auf dem Kommissioniertischs (Start)</param>
        /// <param name="to_col"> Palettenplatz des Kommissioniertischs (Ziel) </param>
        /// <param name="to_pos"> Becherposition des Palettenplatzes auf dem Kommissioniertisches (Ziel)</param>
        /// <param name="executable"> ??? ob command ausführbar ist???</param>
        /// <param name="palletFrom"> Palettenobjekt (Start)</param>
        /// <param name="palletTo"> Palettenobjekt(Ziel)</param>
        /// <returns></returns>
        static public ControllerCommand WorkbenchToWorkbench(int from_col, int from_pos, int to_col, int to_pos, bool executable)
        {
            ControllerCommand cmd = new ControllerCommand();

            cmd.command = string.Format("Becher_1_{0}_{1}_1_{2}_{3}", from_col + 1, from_pos + 1, to_col + 1, to_pos + 1);
            cmd.cupID = 0;
            cmd.prodID = 0;
            cmd.IsExecuting = false;
            cmd.Executable = executable;
            return cmd;
        }
        #endregion
    }
    public class RobotControllerBase : INotifyPropertyChanged
    {
        #region Property Changed Event
        public event PropertyChangedEventHandler? PropertyChanged;
        public void NotifyPropertyChanged(string propName)
        {
            if (PropertyChanged != null)
                PropertyChanged(this, new PropertyChangedEventArgs(propName));
        }
        #endregion

        #region Properties
        protected int status = -1;    // -1: offline, 0: Sending Order, 1: executing order, 2: standby.
        protected bool isMobileRobotDocked = false;
        protected bool isMobileRobotReadyToLeave = false;
        protected bool hasNonTransparentCup = false;
        #endregion

        #region Properties Handlers
        public virtual int Status
        {
            get { return status; }
            protected set
            {
                if (status != value)
                {
                    status = value;
                    NotifyPropertyChanged("Status");
                }
            }
        }
        public virtual bool IsMobileRobotDocked
        {
            get { return isMobileRobotDocked; }
            set
            {
                if (isMobileRobotDocked != value)
                {
                    isMobileRobotDocked = value;
                    NotifyPropertyChanged("IsMobileRobotDocked");
                    if (!isMobileRobotDocked)
                        IsMobileRobotReadyToLeave = false;
                }
            }
        }
        public virtual bool IsMobileRobotReadyToLeave
        {
            get { return isMobileRobotReadyToLeave; }
            set
            {
                if (isMobileRobotReadyToLeave != value)
                {
                    isMobileRobotReadyToLeave = value;
                    NotifyPropertyChanged("IsMobileRobotReadyToLeave");
                }
            }
        }
        public virtual bool HasNonTransparentCup
        {
            get { return hasNonTransparentCup; }
            set
            {
                if (hasNonTransparentCup != value)
                {
                    hasNonTransparentCup = value;
                    NotifyPropertyChanged("HasNonTransparentCup");
                }
            }
        }
        #endregion

        #region Variables
        public bool IsBusy = false;
        #endregion

        #region Virtual Async Methods
        public virtual async Task<bool> ExecuteCommand(ControllerCommand cmd)
        {
            await Task.Delay(2000);
            return false;
        }
        #endregion
    }
    public class RobotController : RobotControllerBase
        {
            public enum ConnectResult : int { Error = -2, NotFound, Success, UsingFirstOccurrence };

            public bool IsConnected { get; private set; }
            public bool IsWorking { get; private set; }

            private NetworkScanner scanner = new NetworkScanner();
            private Controller? controller = null;
            private Mastership? mastership = null;
            private const string TaskName = "T_ROB1";
            private const string ModuleName = "Module1";

            private ABB.Robotics.Controllers.RapidDomain.Task task;
            private ABB.Robotics.Controllers.RapidDomain.Module module;

            protected RapidData proximitySensorA; // Mobile Robot
            protected RapidData proximitySensorB; // Mobile Robot
            protected RapidData presenseSensor;   // Cup in Mobile Robot
            protected RapidData robotStatus;
            protected RapidData robotCommand;

            public RobotController()
            {
                IsConnected = false;
                IsWorking = false;
            }

            ~RobotController()
            {
                DisposeController();
            }

            public Task<int> TryConnectAsync(string serialNumberRequested)
            {
                return TryConnectAsyncInternal(serialNumberRequested, null);
            }

            public Task<int> TryConnectAsync(IPAddress IPAddressRequested)
            {
                return TryConnectAsyncInternal(null, IPAddressRequested);
            }

            private Task<int> TryConnectAsyncInternal(string serialNumberRequested, IPAddress IPAddressRequested)
            {
                ConnectResult rslt = ConnectResult.NotFound;

                IsWorking = true;
                try
                {
                    scanner.Scan();
                    ControllerInfo[] collection = scanner.GetControllers(NetworkScannerSearchCriterias.Real);
                    int minIx = collection.Length + 1;  /// Use invalid index value.
                    int occurrencesCount = 0;
                    for (int ix = 0; ix < collection.Length; ix++)
                    {
                        if (IsControllerRequested(collection[ix], serialNumberRequested, IPAddressRequested))
                        {
                            occurrencesCount++;
                            if (ix < minIx)
                            {
                                minIx = ix;
                            }
                        }
                    }

                    if (minIx < collection.Length)
                    {
                        DisposeController();
                        Trace.WriteLine("Connecting to " + collection[minIx].IPAddress.ToString() + ", Id: " + collection[minIx].Id);
                        controller = ControllerFactory.CreateFrom(collection[minIx]);
                        controller.Logon(UserInfo.DefaultUser);
                        AssociateVariables();
                        IsConnected = true;
                        rslt = ConnectResult.Success;

                        if (occurrencesCount > 1)
                        {
                            rslt = ConnectResult.UsingFirstOccurrence;
                        }
                    }
                }
                catch (Exception ex)
                {
                    Trace.WriteLine("Trying to Connect Error: " + ex.ToString());
                    rslt = ConnectResult.Error;
                }


                var returnValue = new TaskCompletionSource<int>();
                returnValue.SetResult((int)rslt);
                IsWorking = false;

                return returnValue.Task;
            }

            public void Disconnect()
            {
                DisposeController();
            }

            private bool IsControllerRequested(ControllerInfo controllerInfo, string serialNumberRequested, IPAddress IPAddressRequested)
            {
                bool rslt = false;

                if (serialNumberRequested != null)
                    if (controllerInfo.Id == serialNumberRequested)
                        rslt = true;

                if (IPAddressRequested != null)
                    if (controllerInfo.IPAddress.ToString() == IPAddressRequested.ToString())
                        rslt = true;

                return rslt;
            }

            public Task<bool> IsMobileRobotInStation()
            {
                IsWorking = true;
                bool rslt = false;

                Num sensorA = (Num)proximitySensorA.Value;
                Num sensorB = (Num)proximitySensorB.Value;
                rslt = (sensorA == 1) || (sensorB == 1);

                var returnValue = new TaskCompletionSource<bool>();
                returnValue.SetResult((bool)rslt);
                IsWorking = false;

                return returnValue.Task;
            }
            public Task<bool> DoesMobileRobotHasACup()
            {
                IsWorking = true;
                bool rslt = false;

                Num sensor = (Num)presenseSensor.Value;
                rslt = (sensor == 1);

                var returnValue = new TaskCompletionSource<bool>();
                returnValue.SetResult(rslt);
                IsWorking = false;

                return returnValue.Task;
            }
            public Task<bool> MovePallet()
            {
                IsWorking = true;
                bool rslt = false;

                ABB.Robotics.Controllers.RapidDomain.String cmd = (ABB.Robotics.Controllers.RapidDomain.String)robotCommand.Value;
                Trace.WriteLine("About to move Robot. " + cmd.Value);

                string command = "Palette_1_2_2_6";
                cmd.Value = command;
                robotCommand.Value = cmd;

                Num status = (Num)robotStatus.Value;
                status.Value = 0;
                robotStatus.Value = status;
                while (status.Value < 2)
                {
                    status = (Num)robotStatus.Value;
                }

                var returnValue = new TaskCompletionSource<bool>();
                returnValue.SetResult((bool)rslt);
                IsWorking = false;

                return returnValue.Task;
            }
            public Task<int> ReadRobotStatus()
            {
                IsWorking = true;
                int rslt = -1;

                Num sensor = (Num)robotStatus.Value;
                rslt = (int)sensor;

                var returnValue = new TaskCompletionSource<int>();
                returnValue.SetResult((int)rslt);
                IsWorking = false;

                return returnValue.Task;
            }
            private void DisposeController()
            {
                if (controller != null)
                {
                    mastership.Dispose();
                    controller.Logoff();
                    controller.Dispose();
                    controller = null;
                    mastership = null;
                    IsConnected = false;
                }
            }
            private void AssociateVariables()
            {
                mastership = Mastership.Request(controller.Rapid);
                task = controller.Rapid.GetTask(TaskName);
                module = task.GetModule(ModuleName);

                proximitySensorA = module.GetRapidData("Naeherungsschalter_A");
                proximitySensorB = module.GetRapidData("Naeherungsschalter_B");
                presenseSensor = module.GetRapidData("Sensor_Becher");
                robotStatus = module.GetRapidData("Zustand");
                robotCommand = module.GetRapidData("Befehl");
            }

            #region Properties Handlers
            public override int Status
            {
                get
                {
                    Num sensor = (Num)robotStatus.Value;
                    return (int)sensor;
                }
                protected set
                {
                    if (Status != value)
                    {
                        Num newStatus = (Num)robotStatus.Value;
                        newStatus.Value = value;
                        robotStatus.Value = newStatus;
                        NotifyPropertyChanged("Status");
                    }
                }
            }
            public override bool IsMobileRobotDocked
            {
                get
                {
                    Num sensorA = (Num)proximitySensorA.Value;
                    Num sensorB = (Num)proximitySensorB.Value;
                    bool rslt = (sensorA == 1) || (sensorB == 1);
                    if (!rslt)
                        IsMobileRobotReadyToLeave = false;
                    return rslt;
                }
                set
                {
                    if (isMobileRobotDocked != value)
                    {
                        isMobileRobotDocked = value;
                        NotifyPropertyChanged("IsMobileRobotDocked");
                        if (!isMobileRobotDocked)
                            IsMobileRobotReadyToLeave = false;
                    }
                }
            }
            public override bool HasNonTransparentCup
            {
                get
                {
                    Num sensor = (Num)presenseSensor.Value;
                    return (sensor == 1);
                }
                set
                {
                    if (hasNonTransparentCup != value)
                    {
                        hasNonTransparentCup = value;
                        NotifyPropertyChanged("HasNonTransparentCup");
                    }
                }
            }
            #endregion

            #region Virtual class implementations
            public override async Task<bool> ExecuteCommand(ControllerCommand cmd)
            {
                IsBusy = true;
                bool rslt = false;
                if (Status == 2 && cmd.Executable)
                {
                    cmd.IsExecuting = true;
                    status = 1;

                    ABB.Robotics.Controllers.RapidDomain.String command = (ABB.Robotics.Controllers.RapidDomain.String)robotCommand.Value;
                    command.Value = cmd.Command;
                    robotCommand.Value = command;

                    Status = 0;
                    while (Status < 2)
                    {
                        await System.Threading.Tasks.Task.Delay(500);
                    }
                    rslt = true;

                    cmd.IsExecuting = false;
                }

                IsBusy = false;
                return rslt;
            }
            #endregion
        }

}