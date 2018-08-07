%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%% Demo 3 of the Vrep-Matlab multi robot simulation setup for a Quadcopter
%%% and the Strider V1.0 vessel.
%%%
%%% Author: Omar Velasco Anrar
%%% Revision: 17-07-2018
%%%
%%%
%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%% Set Control Type to Cascaded PID

ControlType = 0;

%% Set up waypoints for the Strider V1.0

% Waypoints coordinates (x,y) 
Waypoints = [20 0; 20 20; 10 20; 10 10; 0 10; 0 20];
WaypointsX = Waypoints(:,1)';
WaypointsY = Waypoints(:,2)';

% Set up Strider Speed Command in m/s
StriderSpeedCmd = 1;

% Set up acceptance radius for the waypoint algorithm in m
AccRadius =0.5;

%% Set up Quadcopter commands (Quadcopter will track automatically the Strider V1.0 Position)

Psi_cmd = 0;
Alt_cmd = 2;

% Set up the time when the "land" command is sent to the VTOL controller
% and enable the VTOL controller
LandingSchedule = 5;
EnableVTOL=1;

% Set up approaching altitude and error threshold for the VTOl algorithm
AppAlt =1;
e = 0.000000000000000001;


sim('UAV_USV_Simulator',60)
% set_param(bdroot,'SimulationCommand','update') For uptadting from the
% command line




