#pragma once
#include <TL-Engine.h>	// TL-Engine include file and namespace
#include <vector>
#include <string>
#include <sstream>
#include <math.h>
#include <fstream>
#include <iostream>
#include <cstdlib>
using namespace tle;
using namespace std;

//enums
//states for the sides of the wall
enum boxSide { leftSide, rightSide, frontSide, backSide, bottomSide, noSide };

//states for the gameplay
enum gameState { ready, play, over };

//states for which checkpoints have been crossed
enum checkpointState { none, first, second, third, fourth, fifth };

//states for the nonplayer hovercar
enum eNonplayerState {race, end};

//constants
const int kLaps = 3;							//the number of laps the players have to complete
const int kLowHealth = 30;						//the amount of health under what the boost is not working
const int kFontSize = 32;                       //the size of font used
const int kBigFontSize = 40;                    //the size of the bigger font used
const float kUnitScale = 1.0f;                  //the scale factor for TL Engine units to metres
const float kBoostDisabledUpperLimit = 50.0f;   //the boostDisabledCountdown is set to this when the boost is not disabled
const float kHovercarVerticalUpperLimit = 4.0f; //the upper limit of the vertical movement of the hovercar
const float kHovercarVerticalLowerLimit = 2.0f; //the lower limit of the vertical movement of the hovercar
const float kWalkwayScale = 3.0f;				//the amount the walkways are scaled up
const float kCrossScale = 0.5f;					//the amount the crosses are scaled down
const float kBaseThrust = 0.1f;                 //the amount of thrust applied to the hovercar if nothing else is affecting it (eg. boost)
const float kBaseDragCoefficient = -0.001f;     //amount of drag if nothing else is affecting it
const float kHovercarRadius = 1.4f;             //radius of the collider sphere in the hover car
const float kHovercarDiameter = 2.8f;		    //diameter of the collider sphere in the hovercar
const float kCheckpointRadius = 8.86f;          //radius of checkpoint
const float kCheckpointFeetRadius = 0.3f;       //radius of checkpoint feet
const float kCheckpointFeetZDiameter = 1.28f;   //diameter of the Z side of the collision box for checking if the hovercar went through the checkpoint
const float kWallDepth = 3.42f;                 //radius of isle in z direction
const float kWallWidth = 2.97f;                 //radius of isle in x dierection
const float kWatertankRadius = 3.50f;           //radius of watertanks
const float kNonplayerRadius = 3.87f;           //radius of nonplayer hovercar
const float kTiltUpperLimit = 10.0f;            //the upper limit of how much the hovercar can tilt forwards
const float kTurnLimit = 20.0f;                 //the upper limit of how much the hovercar can tilt while turning
const float kVelocity = -110.0f;			    //velocity of particles
const float kGravity = 50.0f;				    //gravity on particles
const float kMax = 1.0f;					    //max position of particles
const float kMin = -1.0f;					    //min position of particles
const float kBallRotationSpeed = 20.0f;		    //speed the hologram balls are rotating with
const float kCrossStartYPosition = -100.0f;     //the Y position where all the crosses are placed at the start
const float kSpeed = 50.0f;                     //the speed used in several movements 
const float kCameraRotation = 15.0f;            //the amount of camera rotation
const float kVerticalMovementSpeed = 0.8f;      //the speed with which the hovercar moves up and down
const float kHovercarTiltSpeed = 0.01f;         //the speed with whoch the hovercar tilts
const float kHovercarTiltBackSpeed = 0.07f;     //the spped with which the hovercar is returning to original position from tilted
const float kSpeedConstant = 3.6f;              //the constant used to convert m/s to km/h     
const float kHovercarScale = 0.6f;              //the amount the hovercars are scaled down
const float kSmallBallScale = 0.4f;			    //the amount the balls are scaled down
const float kBigBallScale = 2.0f;			    //the amount the balls are scaled up
const float kBiggestBallScale = 10.0f;			//the amount the ball is scaled up
const float kNPHovercarSpeed = 20.0f;           //the amount the frametime is timesed by for the speed of the hovercars
const float kboostCountDownUpperLimit = 1.5f;   //the upper time limit for displaying the boost warning message
const float kboostCountDownLowerLimit = 0.5f;   //the lower time limit for displaying the boost warning message
const float kEndScreenXPos = 100.0f;			//Y position of text at the end screen
const float kPressEscYPos = 20.0f;				//Y position of Press Ecs text
const float kEndMessageYPos = 70.0f;			//Y position of the end message
const float kNPWonYPos = 100.0f;				//Y position of NP car Won message
const float kYouWonYPos = 200.0f;				//Y position of You won message
const float kRaceTimeYPos = 50.0f;				//Y position of of race time text


//custom colours
const unsigned int kOrange = 0xffff6464;
const unsigned int kPurple = 0xff7c35e0;
const unsigned int kPastelYellow = 0xffffef62;
const unsigned int kLightBlue = 0xff63E9FC;
const unsigned int kDeepPurple = 0xff88023D;
const unsigned int kPink = 0xffF684FC;
const unsigned int kGrapefruit = 0xffffac76;
const unsigned int kReddish = 0xffE51091;
const unsigned int kOrangeish = 0xffFA7344;
const unsigned int kYellowish = 0xffFBE752;
const unsigned int kGreenish = 0xff86FC00;
const unsigned int kBlueish = 0xff48DEFC;
const unsigned int kMyMagenta = 0xffff27ff;


const string kStartMessage = "Hit Space to Start";  //displayed before the game starts
const string kBallTexture = "ball.png";             //the hologram balls' texture

const EKeyCode SpaceKey = Key_Space;            //used at the start of the game and used for boost
const EKeyCode cameraMoveUpKey = Key_Up;        //moves camera further away and up
const EKeyCode cameraMoveDownKey = Key_Down;    //moves camera closer and down
const EKeyCode cameraMoveRightKey = Key_Right;  //moves camera right
const EKeyCode cameraMoveLeftKey = Key_Left;    //moves camera left
const EKeyCode ChaseViewCameraKey = Key_1;      //changes to the chase camera
const EKeyCode FPSCameraKey = Key_2;            //changes to the FPS camera view
const EKeyCode hovercarForward = Key_W;         //moves hovercar forward
const EKeyCode hovercarBackward = Key_S;        //moves hovercar backwards
const EKeyCode hovercarTurnRight = Key_D;       //rotates hovercar right
const EKeyCode hovercarTurnLeft = Key_A;        //rotates hovercar left
const EKeyCode RestartKey = Key_Return;         //at the end of the race it restarts the game

//stores x , y and z values
struct vector3
{
	float x;
	float y;
	float z;
};

const vector3 kCameraPosition = { 0.0f, 12.0f, -20.0f };	       //position of camera
const vector3 kFPSCameraPosition = { 0.0f, 6.0f, 0.0f };	       //position of FPS camera
const vector3 kskyPosition = { 0.0f, -800.0f, 0.0f };			   //position of skybox
const vector3 khovercarStartPosition = { -45.0f, 3.0f, -15.0f };   //starting position of hovercar
const vector3 kNPhovercarStartPosition = { -35.0f, 3.0f, -15.0f }; //starting position of nonplayer hovercar
const vector3 kBallPosition = { 0.0f, 10.0f, 50.0f };			   //position of main ball hologram

//struct for storing the checkpoint models and their order
struct checkpointStruct
{
	IModel* model;
	int stage;
};



//stores x and z values
struct vector2D
{
	float x;
	float z;
};

//stores x and y values
struct vector2
{
	float x;
	float y;
};

const vector2 kBackdropPosition = { 150.0f, 600.0f }; //position of ui backdrop
const vector2 kUserInterfacePosition = { 520.0f, 595.0f }; //position of User interface text
const vector2 kSpeedTextPosition = { 370.0f, 690.0f }; //position of speed text
const vector2 kBoostActiveTextPosition = { 370.0f, 665.0f }; //position of Boost is active text
const vector2 kBoostOverheatTextPosition = { 370.0f, 0.0f }; //position of Boost will overheat text
const vector2 kRacePositionText = { 100.0f, 640.0f }; //position of race position text


//calculates the scalar of a certain number
vector2D scalar(float s, vector2D v);


//calucates the sum of 3 numbers
vector2D sum3(vector2D v1, vector2D v2, vector2D v3);

