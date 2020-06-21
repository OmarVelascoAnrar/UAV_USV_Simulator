UAV_USV_Simulator

This repository contains the necessary resources for the use of the UAV and USV simulator implented in the paper "A Multi-platform Open Simulation Strategy for Rapid Control Design in Aerial and Maritime Drone Teams".

The simulator uses V-REP as it's physics and environment simulation and Matlab/Simulink as the control system simulation, which provides a flexible approach to testing and developping different control schemes in multirobot situations.

Inside the repository you will find the V-REP Scenes and provided robot models for the UAV (AR. Drone) and a USV model developped by the authors. You can use the provided code in the models and scenes to adapt it to your own simulations.

The Simulink model shows a simple control scheme based on cascaded PID control for both the UAV and USV, which provides an example of how to interface Simulink and the provided V-REP model.


The implementation of the robotic model is generally straightforward but it usually requires some time to simplify and optimize the model for simulation. This involves a series of steps to be followed to obtain the models of the robots in the simulation environment. In the case of the provided examples, these were the steps to generate both robotic models.

1) The models of both robots have to be imported into the V-REP environment. This can be done by importing a pre-existing CAD model of the robot or by building it directly in V-REP. V-REP allows CAD imports from various data formats such as OBJ, STL, Collada, etc that get imported as single meshes. Because of the possible complexity of the meshes, CAD models should not be too heavy as they will significantly reduce simulation speed. Nevertheless, to simplify the imported models, V-REP has several tools for automatic and manual mesh edition. This tools allow the editing of the imported models into simpler meshes and even divide the meshes into the different bodies or shapes that compose the robots. CAD model division into simpler shapes allows for more efficient shape geometries (convex bodies or primitive shapes) for physics simulations and sets up the building blocks of the robot, as the relationships and constrains between shapes, such as joints cannot be set up in single mesh/shape bodies.

2) After the import of the CAD models and their simplification, it is necessary to configure the shape's properties and the hierarchical relationship between them to build an operational robot model for simulation. V-REP shapes (mesh objects that compose the model of the robot) have a set of dynamic properties that control its dynamic behaviour. Shapes can be either respondable or not, meaning that they will interact and produce collisions with other respondable shapes. Shapes can also be dynamically enabled (static or non-static), on which the physics engine will act upon the shape. The respondable dynamically enabled frame of the robot is usually based on primitive shapes (more efficient) and is used for dynamic simulation and collision detection. Thanks to the CAD import features visual appearance of the robotic models can be easily obtained and gets attached to the physically enabled model. An example of this model building structure can be seen in Figure~\ref{fig:V-REP_example}, where the visual appearance of the robot, and the respondable and dynamic shapes are compared side by side.


<img src="https://github.com/OmarVelascoAnrar/UAV_USV_Simulator/blob/master/Figures/CAD_comp2.png" width="500"/>

Robotic models setup in V-REP: a) V-REP hierarchical relationships, b) Quadrotor CAD model c) Strider CAD model and d) Quadrotor mesh objects.



3) The implementation of the robotic models in V-REP, where the communication and behaviour of each of the robot models has to be set. This is achieved by embedded scripts attached to each model. These scripts handle the external API functions in order to receive and send the commands and current states. After that, it applies these received commands as forces and torques in the appropriate locations. These embedded scripts are written in Lua and an example is shown in Figure~\ref{fig:code}.

<img src="https://github.com/OmarVelascoAnrar/UAV_USV_Simulator/blob/master/Figures/code.png" width="500"/>

Code fragment with quadrotor primitives handles.

- Some useful resources:

Vortex physics engine download: https://www.cm-labs.com/blog/2017/03/23/get-copy-vortex-studio-essentials/
You only need to install Vortex Studio Essentials.


- Videos of the produced simulations can be found in the following playlist:

https://www.youtube.com/playlist?list=PL2Ub55STnEPlj0ItbI2156DDFPJcaDuv0

