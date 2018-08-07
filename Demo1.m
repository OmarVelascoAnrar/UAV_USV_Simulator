%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%% Demo of the Vrep-Matlab multi robot simulation setup for a Quadcopter
%%% and the Strider V1.0 vessel.
%%%
%%% Author: Omar Velasco Anrar
%%% Revision: 17-07-2018
%%%
%%% This demo runs a test of the inverse kinematic s controller.
%%%
%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%% Set Control Type to Inverse Kinematics

ControlType = 1;

%% Set up waypoints for the Strider V1.0

% Waypoints coordinates (x,y) 
Waypoints = [0 100];
WaypointsX = Waypoints(:,1)'/3;
WaypointsY = Waypoints(:,2)'/3;

% Set up Strider Speed Command (Strider is nor relevant in this test so we will try and get it to not move)

StriderSpeedCmd = 0;

%% Set up Quadcopter commands

Psi_cmd = -90;
Alt_cmd = 2;

% Load the ax and ay desired profiles and set them to the appropiate
% variables. The division is just for scaling purposes.

load('a_cmds.mat')
ax = ComeBack/2;
ay = Go_Hover/4;

sim('UAV_USV_Simulator',20)
% set_param(bdroot,'SimulationCommand','update') For uptadting from the
% command line





