%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%% Demo 2 of the Vrep-Matlab multi robot simulation setup for a Quadcopter
%%% and the Strider V1.0 vessel.
%%% 
%%% This demo commands a box-like path for the Strider V1.0 
%%% 
%%% Author: Omar Velasco Anrar
%%% Revision: 17-07-2018
%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%% Set Control Type to Cascaded PID
ControlType = 0;

%% Set up waypoints for the Strider V1.0

% Waypoints coordinates (x,y) 
Waypoints = [10 10; 10 -10; -10 -10; -10 10; 0 0 ];
WaypointsX = Waypoints(:,1)'/3;
WaypointsY = Waypoints(:,2)'/3;

% Set up Strider Speed Command in m/s
StriderSpeedCmd = 1;

% Set up acceptance radius for the waypoint algorithm in m
AccRadius =0.5;

%% Set up Quadcopter commands (Quadcopter will track automatically the Strider V1.0 Position)
Psi_cmd = 0;
Alt_cmd = 2;

% Set up approaching altitude and error threshold for the VTOl algorithm
AppAlt =1;
e = 0.1;

% Set up the time when the "land" command is sent to the VTOL controller
% and enable the VTOL controller
LandingSchedule = 5;
EnableVTOL=1;


%% Launch the simulation
model = 'UAV_USV_Simulator';

t = timer; t.Period = 2; t.ExecutionMode = 'fixedRate';
t.TimerFcn = @(myTimerObj,thisEvent)disp(['The current simulation time is '...
     num2str(get_param(model,'SimulationTime'))]);
start(t)

out = sim(model,'StopTime', '40','SimulationMode',...
                    'accelerator','SimCompilerOptimization', 'on');
stop(t); delete (t);
                

% set_param(bdroot,'SimulationCommand','update') For uptadting from the
% command line when the simulation is launched from Simulink.









