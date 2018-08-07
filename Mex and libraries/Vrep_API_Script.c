#define S_FUNCTION_NAME Vrep_API_Script /* Defines and Includes */
#define S_FUNCTION_LEVEL 2

#define NON_MATLAB_PARSING
#define MAX_EXT_API_CONNECTIONS 255

#define MDL_START

#include "simstruc.h"
#include "math.h"

#include "extApi.h"
#include "extApiPlatform.h"
#include "extApi.c"
#include "extApiPlatform.c"

static void mdlInitializeSizes(SimStruct *S)
{
    
    ssSetNumSFcnParams(S, 0);
    if (ssGetNumSFcnParams(S) != ssGetSFcnParamsCount(S)) {
        return; /* Parameter mismatch reported by the Simulink engine*/
    }

    if (!ssSetNumInputPorts(S, 1)) return;
    ssSetInputPortWidth(S, 0, 14);
    ssSetInputPortDirectFeedThrough(S, 0, 0);

    if (!ssSetNumOutputPorts(S,1)) return;
    ssSetOutputPortWidth(S, 0, 22);

    ssSetNumSampleTimes(S, 1);
   
    /* Take care when specifying exception free code - see sfuntmpl.doc */
    //ssSetOptions(S, SS_OPTION_EXCEPTION_FREE_CODE);
    }



static void mdlStart(SimStruct *S)
{
    
    int clientID=simxStart((simxChar*)"127.0.0.1",19997,true,true,5000,0.5);
    if (clientID!=-1){
        printf("CLIENT ID EXISTS :D\n");
        simxSynchronous(clientID,true);
        
        printf("START SIMULATION\n");
        printf("Client ID: %i\n",clientID);
        simxStartSimulation(clientID,simx_opmode_blocking);
    }else{
     
     printf("Simulation could not be started, check if VREP's simulation is started\n");
     ssWarning(S, "Simulation could not be started, check if VREP's simulation is started.\nTerminating the simulation now...");
     ssSetStopRequested(S, 1); 
    }  
}

int u=0; 
float Output[22];



static void mdlInitializeSampleTimes(SimStruct *S)
{
    ssSetSampleTime(S, 0, 0.01);
    ssSetOffsetTime(S, 0, 0.0);
}



static void mdlOutputs(SimStruct *S, int_T tid) // Set the outputs of the S-F block
{
    int_T i;
    real_T *y = ssGetOutputPortRealSignal(S,0);
    int_T widthOut = ssGetOutputPortWidth(S,0);
    
    for (i=0; i<widthOut; i++) {     
        *y++ = Output[i];
    }
    
    
   //   Debugging...
    
// //    printf("test");
// //    for (i=0; i<widthOut; i++) {    
// //        printf("test");
// //         printf("Output %i: %f\n",i,Output[i]);
// //     }
// //    u++;
// //    printf("Passes through Outputs = %i \n",u);
}


#define MDL_UPDATE
static void mdlUpdate(SimStruct *S, int_T tid){ // Executes once per simulation step, it has to be here in order to avoid direct feedthrough (and avoid Algebraic loops)

    // S-Block  info
    int_T i;
    InputRealPtrsType uPtrs = ssGetInputPortRealSignalPtrs(S,0);
    real_T *y = ssGetOutputPortRealSignal(S,0);
    int_T widthOut = ssGetOutputPortWidth(S,0);
    int_T widthIn = ssGetInputPortWidth(S,0);
    
    // Aux variables
    int result;
    int result1;
    float TandT[8]={0,0,0,0,0,0,0,0}; // Thrust and torque vector {Th1,Th2,Th3,Th4,Tq1,Tq2,Tq3,Tq4}
    float StrForces[6]={0,0,0,0,0,0}; // Thrust and torque vector {Propeler force, Rudder X, Rudder Y}
    int retIntCnt;
    float* OutputVR;
    float* OutputStrider;
    int* retInts;
    int OutputNb;
    int OutputNbStrider;
    float test[9]={0,0,0,0,10,0,0,0,0};
    
    // Get the inputs to the vector to be passed to VREP containing Thrust and torques
    for (i=0; i<8; i++) {
        TandT[i] = *uPtrs[i];
        //*y++ = 2.0 *(*uPtrs[i]);
    } 
    
    for (i=8; i<widthIn; i++) {
        StrForces[i-8] = *uPtrs[i];
    }   
    
    

    // VREP comunication...
    result=simxCallScriptFunction(0,"Quadrotor_body",sim_scripttype_childscript,"Com_Func",0,NULL,8,TandT,1,"MyDummyName",0,NULL,NULL,NULL,&OutputNb,&OutputVR,NULL,NULL,NULL,NULL,simx_opmode_oneshot_wait);
    
//Set the received outputs to the Output vector
    for (i=0; i<12; i++) {     
        Output[i] = OutputVR[i];
//         printf("Passes through Outputs %i = %f \n",i,OutputVR[i]);
//         printf("Passes through Output %i = %f \n",i,Output[i]);
    }
    
    result1=simxCallScriptFunction(0,"Strider_V1",sim_scripttype_childscript,"Com_Func_Strider",0,NULL,6,StrForces,1,"MyDummyName",0,NULL,NULL,NULL,&OutputNbStrider,&OutputStrider,NULL,NULL,NULL,NULL,simx_opmode_oneshot_wait);
    
    for (i=12; i<widthOut; i++) {     
        Output[i] = OutputStrider[i-12];
//         printf("Passes through OutputsStr %i = %f \n",i,OutputStrider[i-12]);
//         printf("Passes through Output %i = %f \n",i,Output[i]);
    }

    // Trigger the next simulation step
    simxSynchronousTrigger(0);
    
    //simxGetPingTime(0,&retInts);
    //printf("Ping Time %i \n",retInts);
    // Debugging...
    //u=0;
   
       //   Debugging...
    

}

static void mdlTerminate(SimStruct *S){

    simxPauseSimulation(0,simx_opmode_blocking);
    simxFinish(-1);
    printf("Terminated :D\n");
}


#ifdef MATLAB_MEX_FILE /* Is this file being compiled as a MEX-file? */
#include "simulink.c" /* MEX-file interface mechanism */
#else
#include "cg_sfun.h" /* Code generation registration function */
#endif

/* To compile: mex Vrep_API_Script.c -lws2_32 -lWinmm  */