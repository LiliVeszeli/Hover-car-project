//Lili Veszeli G20752773
///file reading in and particle effects are not working, but I included what I did with them.
// Hover car.cpp: A program using the TL-Engine

#include "Collision.h"

////state for reading in
//enum read {name, x, y, z, rotation};
//
////struct for reading in
//struct ModelStruct
//{
//	string name;
//	float x;
//	float y;
//	float z;
//	float rotation;
//};

//structure for particles
struct particle
{
	IModel *model;
	float moveVector[3];
	
};

// Return a random number in the range between rangeMin and rangeMax inclusive
// range_min <= random number <= range_max
float random(int rangeMin, int rangeMax)
{
	float result = (float)rand() / (float)(RAND_MAX + 1);
	result *= (float)(rangeMax - rangeMin);
	result += rangeMin;

	return result;
}

//Reads in text file with models - not working
//void ReadFile(std::ifstream &infile)
//{
//	read fileRead = name;
//
//	if (!infile) //checking if the file exists
//	{
//		cout << "Error";
//	}
//
//	string str;
//
//	vector<ModelStruct> Models;
//	ModelStruct modelStruct;
//
//	infile >> noskipws;


//	while (!infile.eof()) //loops until it reached the end of the file
//	{
//		char ch;
//		infile >> ch; //puts the contents of the file in the character one by one
//
//		if (!infile.eof())
//		{
//			if (ch == ' ' || ch == '\n')
//			{
//				if ( fileRead == name)
//				{
//					fileRead = x;
//					modelStruct.name = str;
//				}
//				else if (fileRead == x)
//				{
//					fileRead = y;
//					modelStruct.x = stof(str);
//				}
//				else if (fileRead == y)
//				{
//					fileRead = z;
//					modelStruct.y = stof(str);
//				}
//				else if (fileRead == z)
//				{
//					fileRead = rotation;
//					modelStruct.z = stof(str);
//				}
//				else if (fileRead == rotation)
//				{
//					fileRead = name;
//					modelStruct.rotation = stof(str);
//					Models.push_back(modelStruct); //puts all the read in information in the vector
//				}
//			}
//			else
//			{
//				str += ch;
//			}
//		}
//	} //end of while loop
//	
//}




void main()
{
	// Create a 3D engine (using TLX engine here) and open a window for it
	I3DEngine* myEngine = New3DEngine(kTLX);
	myEngine->StartWindowed();

	// Add default folder for meshes and other media
	myEngine->AddMediaFolder(".\\Models");
	myEngine->AddMediaFolder("C:\\ProgramData\\TL-Engine\\Media");

	/**** Set up your scene here ****/

    //variables
	float collisionDist = 0.0f;					  //stores the distance for collision check
	float collisionDist2 = 0.0f;				  //stores the distance for collision check
	float collisionDist3 = 0.0f;				  //stores the distance for collision check
	float collisionDist4 = 0.0f;				  //stores the distance for collision check
	float collisionDist5 = 0.0f;				  //stores the distance for collision check
	float collisionDist6 = 0.0f;				  //stores the distance for collision check
	float nonplayerDist = 0.0f;					  //distance calcualtion for nonplayer hovercar and dummy
	float directionX;							  //stores the x direction of vector of the nonplayer hovercar
	float directionZ;							  //stores the z direction of vector of the nonplayer hovercar
	float vectorX;								  //stores the distance in x between the nonplayer hovercar and a waypoint
	float vectorZ;								  //stores the distance in z between the nonplayer hovercar and a waypoint
	float mouseRotationX = 20;					  //stores the mouse movement in x direction
	float mouseRotationY = 0;					  //stores the mouse movement in y direction
	bool spacePressed = false;					  //checks if space is pressed
	float countDown = 4;						  //checks if a second has passed and displays the next text
	stringstream currentText;					  //stores the text that should be displayed
	bool goThroughCheckpoint = false;			  //stores if the hovercar has gone through a checkpoint or not
	int health = 100;						      //stores the health of the hovercar
	float thrustFactor = kBaseThrust;			  //the amount of thrust
	float dragCoefficient = kBaseDragCoefficient; //the amount of drag
	float crossCountDown[5] = { 0, 0, 0, 0, 0 };  //stores the time for how long the crosses appear
	float boostCountDown = 3;				      //the boost can be used for this amount of time
	bool boostDisabled = false;					  //stores if the boost is disabled or not
	float boostDiasbledCountDown = kBoostDisabledUpperLimit; //the amount of time the boost can't be used
	int dummyCount = 0;						      //stores how many waypoints have been passed by the nonplayer car
	int lapCount = 0;							  //stores how many laps have been done by the hovercar
	int nonplayerLapCount = 0;					  //stores how many laps have been done by the nonplayer hovercar
	float rotationX = 0;						  //stores the rotation of the hovercar while turning
	float rotationZ = 0;						  //stores the rotation of the hovercar while accelerating
	float verticalMovement = 3;				      //the Y position the hovercar starts in its floating
	bool goingUp = true;						  //stores if the hovercar is going up or down for the floating effect
	int checkpointCount = 0;					  //counts how many checkpoint has the hovercar passed
	int NPcheckpointCount = 0;					  //counts how many checkpoint has the nonplayer hovercar passed
	float raceTime = 0;                           //measures hovercar's race time
	float NPraceTime = 0;						  //measures nonplayer hovercar's race time
	float endNPRaceTime = 0;					  //the final time of the NP hovercar
	//float particleCount = 0;

	
	

	


	//meshes
	IMesh* checkpointMesh = myEngine->LoadMesh("Checkpoint.x");
	IMesh* islandMesh = myEngine->LoadMesh("IsleStraight.x");
	IMesh* wallMesh = myEngine->LoadMesh("Wall.x");
	IMesh* skyMesh = myEngine->LoadMesh("Skybox 07.x");
	IMesh* groundMesh = myEngine->LoadMesh("ground.x");
	IMesh* hovercarMesh = myEngine->LoadMesh("race2.x");
	IMesh* nonplayerHovercarMesh = myEngine->LoadMesh("race3.x");
	IMesh* watertankMesh = myEngine->LoadMesh("TankSmall2.x");
	IMesh* walkwayMesh = myEngine->LoadMesh("Walkway.x");
	IMesh* crossMesh = myEngine->LoadMesh("Cross.x");
	IMesh* dummyMesh = myEngine->LoadMesh("Dummy.x");
	IMesh* ballMesh = myEngine->LoadMesh("Planet.x");
	IMesh* particleMesh = myEngine->LoadMesh("Sphere.x");
	

	//reading in
	//ifstream infile("Text.txt");

	////opens file + reads in file
 //   ReadFile(infile);

	//infile.close();


	//models
	IModel* sky = skyMesh->CreateModel(kskyPosition.x, kskyPosition.y, kskyPosition.z);
	IModel* ground = groundMesh->CreateModel();
	IModel* hovercar = hovercarMesh->CreateModel(0.0f, 0.0f, 0.0f);
	IModel* nonplayerHovercar = nonplayerHovercarMesh->CreateModel(kNPhovercarStartPosition.x, kNPhovercarStartPosition.y, kNPhovercarStartPosition.z);
	IModel* hovercarDummy = dummyMesh->CreateModel(khovercarStartPosition.x, khovercarStartPosition.y, khovercarStartPosition.z);
	IModel* ball = ballMesh->CreateModel(kBallPosition.x, kBallPosition.y, kBallPosition.z);
	ISprite* backdrop = myEngine->CreateSprite("japan.jfif", kBackdropPosition.x, kBackdropPosition.y);
	IFont* myFont = myEngine->LoadFont("Cooper Black", kFontSize);
	IFont* myBigFont = myEngine->LoadFont("Cooper Black", kBigFontSize);
	
	//scaling and attaching to parent
	hovercar->Scale(kHovercarScale);
	nonplayerHovercar->Scale(kHovercarScale);
	ball->Scale(kBiggestBallScale);
	
	hovercar->AttachToParent(hovercarDummy);

	//setting skins
	ball->SetSkin(kBallTexture);
	
	

	//setting game states
	gameState currentState = ready;
	checkpointState currentCheckpoint = first;
	eNonplayerState nonplayerState = race;


	//vectors
	vector2D momentum{ 0, 0 };
	vector2D thrust{ 0, 0 };
	vector2D drag{ 0, 0 };

	float matrix[4][4];

	//vectors to store models

	vector<checkpointStruct> checkpoints =
	{
		{checkpointMesh->CreateModel(-40.0f, 0.0f, 0.0f), 1}, //1
	    {checkpointMesh->CreateModel(-40.0f, 0.0f, 120.0f), 2}, //2

       
	    {checkpointMesh->CreateModel(45.0f, 0.0f, 160.0f), 3}, //3

		
		{checkpointMesh->CreateModel(45.0f, 0.0f, 56.0f), 4}, //4

		//end race
	    {checkpointMesh->CreateModel(35.0f, 0.0f, 10.0f), 5} //5
	};




	vector<IModel*> islandsWalls =
	{
	 islandMesh->CreateModel(-50.0f, 0.0f, 40.0f),
	 islandMesh->CreateModel(-30.0f, 0.0f, 40.0f),
	 islandMesh->CreateModel(-50.0f, 0.0f, 56.0f),
	 islandMesh->CreateModel(-30.0f, 0.0f, 56.0f),
	 islandMesh->CreateModel(-50.0f, 0.0f, 72.0f),
	 islandMesh->CreateModel(-30.0f, 0.0f, 72.0f),
									  
	 wallMesh->CreateModel(-50.0f, 0.0f, 48.0f),
	 wallMesh->CreateModel(-30.0f, 0.0f, 48.0f),
	 wallMesh->CreateModel(-50.0f, 0.0f, 64.0f),
	 wallMesh->CreateModel(-30.0f, 0.0f, 64.0f),

	 //narrow
	 islandMesh->CreateModel(40.0f, 0.0f, 140.0f),
	 islandMesh->CreateModel(50.0f, 0.0f, 140.0f),
	 islandMesh->CreateModel(40.0f, 0.0f, 124.0f),
	 islandMesh->CreateModel(50.0f, 0.0f, 124.0f),
	 islandMesh->CreateModel(40.0f, 0.0f, 108.0f),
	 islandMesh->CreateModel(50.0f, 0.0f, 108.0f),

	 wallMesh->CreateModel(40.0f, 0.0f, 132.0f),
	 wallMesh->CreateModel(50.0f, 0.0f, 132.0f),
	 wallMesh->CreateModel(40.0f, 0.0f, 116.0f),
	 wallMesh->CreateModel(50.0f, 0.0f, 116.0f)
	};

	vector<IModel*> watertank =
	{
		watertankMesh->CreateModel(-58.0f, 0.0f, 110.0f),
		watertankMesh->CreateModel(55.0f, 0.0f, 180.0f),
		watertankMesh->CreateModel(65.0f, -5.0f, 80.0f),
		watertankMesh->CreateModel(13.0f, -5.0f, 30.0f),
	};

	//rotating watertanks
	watertank[2]->RotateZ(45.0f);
	watertank[1]->RotateY(180.0f);
	watertank[3]->RotateZ(-45.0f);


	vector<IModel*> walkway =
	{
		walkwayMesh->CreateModel(-40.0f, 0.0f, 130.0f),
		walkwayMesh->CreateModel(-38.0f, 0.0f, 145.0f),
		walkwayMesh->CreateModel(-30.0f, 0.0f, 158.0f),
		walkwayMesh->CreateModel(-18.0f, 0.0f, 168.0f),
		walkwayMesh->CreateModel(-4.0f, 0.0f, 173.0f),
		walkwayMesh->CreateModel(10.0f, 0.0f, 175.0f),
		walkwayMesh->CreateModel(24.0f, 0.0f, 175.0f),
		walkwayMesh->CreateModel(38.0f, 0.0f, 168.0f),


		//between start and end checkpoint
		walkwayMesh->CreateModel(-40.0f, 0.0f, -10.0f),
		walkwayMesh->CreateModel(-38.0f, 0.0f, -25.0f),
		walkwayMesh->CreateModel(-30.0f, 0.0f, -38.0f),
		walkwayMesh->CreateModel(-18.0f, 0.0f, -48.0f),
		walkwayMesh->CreateModel(-4.0f, 0.0f, -53.0f),
		walkwayMesh->CreateModel(10.0f, 0.0f, -52.0f),
		walkwayMesh->CreateModel(24.0f, 0.0f, -48.0f), //14
		walkwayMesh->CreateModel(30.0f, 0.0f, -43.0f), //overlapping, very rotated
		walkwayMesh->CreateModel(35.0f, 0.0f, -29.0f),
		walkwayMesh->CreateModel(35.0f, 0.0f, -14.0f),
		walkwayMesh->CreateModel(35.0f, 0.0f, 0.0f), //18


	};

	vector<IModel*> ballsSmall =
	{
		ballMesh->CreateModel(-50.0f,4.0f, 130.0f),
		ballMesh->CreateModel(-48.0f,4.0f, 147.0f),
		ballMesh->CreateModel(-40.0f,4.0f, 165.0f),
		ballMesh->CreateModel(-18.0f,4.0f, 178.0f),
		ballMesh->CreateModel(-4.0f, 4.0f, 183.0f),
		ballMesh->CreateModel(20.0f, 4.0f, 190.0f),
		ballMesh->CreateModel(34.0f, 4.0f, 190.0f),
		ballMesh->CreateModel(58.0f, 4.0f, 168.0f),


	
		ballMesh->CreateModel(-50.0f, 4.0f, -10.0f),
		ballMesh->CreateModel(-48.0f, 4.0f, -25.0f),
		ballMesh->CreateModel(-40.0f, 4.0f, -38.0f),
		ballMesh->CreateModel(-18.0f, 4.0f, -58.0f),
		ballMesh->CreateModel(-4.0f, 4.0f, -63.0f),
		ballMesh->CreateModel(10.0f, 4.0f, -62.0f),
		ballMesh->CreateModel(24.0f, 4.0f, -58.0f), 
		ballMesh->CreateModel(30.0f, 4.0f, -53.0f), 
		ballMesh->CreateModel(45.0f, 4.0f, -32.0f),
		ballMesh->CreateModel(45.0f, 4.0f, -14.0f),
		ballMesh->CreateModel(45.0f, 4.0f, 0.0f),


	};

	vector<IModel*> ballsMedium =
	{
		ballMesh->CreateModel(-55.0f, 8.0f, 130.0f),
		ballMesh->CreateModel(-53.0f, 8.0f, 147.0f),
		ballMesh->CreateModel(-45.0f, 8.0f, 165.0f),
		ballMesh->CreateModel(-18.0f, 8.0f, 183.0f),
		ballMesh->CreateModel(-4.0f, 8.0f, 188.0f),
		ballMesh->CreateModel(20.0f, 8.0f, 192.0f),
		ballMesh->CreateModel(35.0f, 8.0f, 195.0f),
		ballMesh->CreateModel(63.0f, 8.0f, 168.0f),


		
		ballMesh->CreateModel(-55.0f, 8.0f, -10.0f),
		ballMesh->CreateModel(-53.0f, 8.0f, -25.0f),
		ballMesh->CreateModel(-45.0f, 8.0f, -38.0f),
		ballMesh->CreateModel(-18.0f, 8.0f, -63.0f),
		ballMesh->CreateModel(-4.0f,  8.0f, -68.0f),
		ballMesh->CreateModel(10.0f,  8.0f, -67.0f),
		ballMesh->CreateModel(24.0f,  8.0f, -63.0f), 
		ballMesh->CreateModel(30.0f,  8.0f, -58.0f), 
		ballMesh->CreateModel(45.0f,  8.0f, -37.0f),
		ballMesh->CreateModel(50.0f,  8.0f, -14.0f),
		ballMesh->CreateModel(50.0f,  8.0f, 0.0f),
								  

	};

	vector<IModel*> ballsBig =
	{
		ballMesh->CreateModel(-60.0f,20.0f, 130.0f),
		ballMesh->CreateModel(-58.0f,20.0f, 147.0f),
		ballMesh->CreateModel(-50.0f,20.0f, 165.0f),
		ballMesh->CreateModel(-18.0f,20.0f, 188.0f),
		ballMesh->CreateModel(-4.0f, 20.0f, 193.0f),
		ballMesh->CreateModel(20.0f, 20.0f, 195.0f),
		ballMesh->CreateModel(35.0f, 20.0f, 195.0f),
		ballMesh->CreateModel(68.0f, 20.0f, 168.0f),



		ballMesh->CreateModel(-60.0f, 20.0f, -10.0f),
		ballMesh->CreateModel(-58.0f, 20.0f, -25.0f),
		ballMesh->CreateModel(-50.0f, 20.0f, -38.0f),
		ballMesh->CreateModel(-18.0f, 20.0f, -68.0f),
		ballMesh->CreateModel(-4.0f,  20.0f, -73.0f),
		ballMesh->CreateModel(10.0f,  20.0f, -72.0f),
		ballMesh->CreateModel(24.0f,  20.0f, -68.0f),
		ballMesh->CreateModel(30.0f,  20.0f, -63.0f),
		ballMesh->CreateModel(45.0f,  20.0f, -42.0f),
		ballMesh->CreateModel(55.0f,  20.0f, -14.0f),
		ballMesh->CreateModel(55.0f,  20.0f, 0.0f),


	};

	//scaling the hologram balls and setting skin
	for (int i = 0; i < ballsSmall.size(); i++)
	{
		ballsSmall[i]->Scale(kSmallBallScale);
		ballsSmall[i]->SetSkin(kBallTexture);
	}

	for (int i = 0; i < ballsMedium.size(); i++)
	{		
		ballsMedium[i]->SetSkin(kBallTexture);
	}
	
	

	for (int i = 0; i < ballsBig.size(); i++)
	{
		ballsBig[i]->Scale(kBigBallScale);
		ballsBig[i]->SetSkin(kBallTexture);
	}

	//rotating walkways
	walkway[1]->RotateY(20.0f);
	walkway[2]->RotateY(40.0f);
	walkway[3]->RotateY(60.0f);
	walkway[4]->RotateY(80.0f);
	walkway[5]->RotateY(90.0f);
	walkway[6]->RotateY(100.0f);
	walkway[7]->RotateY(130.0f);

	walkway[9]->RotateY(-20.0f);
	walkway[10]->RotateY(-40.0f);
	walkway[11]->RotateY(-60.0f);
	walkway[12]->RotateY(-90.0f);
	walkway[13]->RotateY(-100.0f);
	walkway[14]->RotateY(-110.0f);
	walkway[15]->RotateY(-150.0f);
	walkway[16]->RotateY(10.0f);
	
	//scaling walkways
	for (int i = 0; i < walkway.size(); i++)
	{
		walkway[i]->Scale(kWalkwayScale);
	}

	vector <IModel*> cross =
	{
		crossMesh->CreateModel(checkpoints[0].model->GetX(), kCrossStartYPosition, checkpoints[0].model->GetZ()),
		crossMesh->CreateModel(checkpoints[1].model->GetX(), kCrossStartYPosition, checkpoints[1].model->GetZ()),
		crossMesh->CreateModel(checkpoints[2].model->GetX(), kCrossStartYPosition, checkpoints[2].model->GetZ()),
		crossMesh->CreateModel(checkpoints[3].model->GetX(), kCrossStartYPosition, checkpoints[3].model->GetZ()),
		crossMesh->CreateModel(checkpoints[4].model->GetX(), kCrossStartYPosition, checkpoints[4].model->GetZ()),

	};

	//scaling crosses
	for (int i = 0; i < cross.size(); i++)
	{
		cross[i]->Scale(kCrossScale);
	}
	
	vector <IModel*> dummy =
	{
		dummyMesh->CreateModel(checkpoints[0].model->GetX(), 0.0f, checkpoints[0].model->GetZ()),
		dummyMesh->CreateModel(checkpoints[1].model->GetX(), 0.0f, checkpoints[1].model->GetZ()),
		dummyMesh->CreateModel(-18.0f, 0.0f, 168.0f),
		dummyMesh->CreateModel(10.0f, 0.0f, 175.0f),
		dummyMesh->CreateModel(24.0f, 0.0f, 175.0f),
		dummyMesh->CreateModel(checkpoints[2].model->GetX(), 0.0f, checkpoints[2].model->GetZ()),
		dummyMesh->CreateModel(checkpoints[3].model->GetX(), 0.0f, checkpoints[3].model->GetZ()),
		dummyMesh->CreateModel(checkpoints[4].model->GetX(), 0.0f, checkpoints[4].model->GetZ()),
		dummyMesh->CreateModel(35.0f, 0.0f, -29.0f),
		dummyMesh->CreateModel(10.0f, 0.0f, -52.0f),
		dummyMesh->CreateModel(-30.0f, 0.0f , -38.0f),
	};

	
	

	//camera
	ICamera* myCamera;
	myCamera = myEngine->CreateCamera(kManual, kCameraPosition.x, kCameraPosition.y, kCameraPosition.z);
	myCamera->AttachToParent(hovercarDummy);
	myCamera->RotateX(kCameraRotation);


	myEngine->Timer();
	myEngine->StartMouseCapture();


	// The main game loop, repeat until engine is stopped
	while (myEngine->IsRunning())
	{
		// Draw the scene
		myEngine->DrawScene();

		// Close the scene




		/////////////////////////////////////////////////////////////////////////////////////////////
		//                                      GAME LOOP										   //
		/////////////////////////////////////////////////////////////////////////////////////////////






		/**** Update your scene each frame here ****/

		//timer
		float frameTime = myEngine->Timer();

		//drawing text
		myBigFont->Draw("User Interface",kUserInterfacePosition.x, kUserInterfacePosition.y, kMyMagenta);
		ball->RotateY(kBallRotationSpeed* frameTime);

		for (int i = 0; i < ballsSmall.size(); i++)
		{
			ballsSmall[i]->RotateY(kBallRotationSpeed* frameTime);
			ballsMedium[i]->RotateY(kBallRotationSpeed*frameTime);
			ballsBig[i]->RotateY(kBallRotationSpeed*frameTime);
		}

		

		//setting the coundown for the crosses
		for (int i = 0; i < cross.size(); i++)
		{
			if (crossCountDown[i] > 0)
			{
				crossCountDown[i] -= frameTime;

			}
			else if (crossCountDown[i] <= 0)
			{
				cross[i]->SetY(kCrossStartYPosition);

			}
		}
		
		//countdown for how long is the boost disabled
		if (boostDiasbledCountDown > 0 && boostDiasbledCountDown < kBoostDisabledUpperLimit)
		{
			boostDiasbledCountDown -= frameTime;
		}
		else if (boostDiasbledCountDown <= 0)
		{
			boostDisabled = false;
			boostDiasbledCountDown = kBoostDisabledUpperLimit;

		}

		// game states 
		switch (currentState)
		{
			//state for the count down
			case ready:
			{
				//until space is pressed this is displayed
				if (!spacePressed)
				{
					 currentText << kStartMessage;
				}
				else
				{
					//counts down from 4 
					countDown -= frameTime;

					//goes to the play state after "Go!"
					if (countDown <= 0)
					{
						currentState = play;
						currentCheckpoint = first;

					}

					//count down from 3
					else if (countDown <= 1)
					{
						currentText << "Go!";
					}

					else if (countDown <= 2)
					{
						currentText << "1";
					}

					else if (countDown <= 3)
					{
						currentText << "2";
					}

					else if (countDown <= 4)
					{
						currentText << "3";
					}				
				}

				//checks if space was hit
				if (myEngine->KeyHit(SpaceKey))
				{
					spacePressed = true;
				}
							
				break;
			}



																			//~////////////
																			//PLAY STATE///
																			////////////~//


			//play state, hover car can be controlled
			case play:
			{
				

				//states for if the checkpoints have been crossed
				switch (currentCheckpoint)
				{
					
					//before the first checkpoint was crosse
					case first:
					{			
						//checks if this is the first lap or not
						if (lapCount > 0)
						{
						    currentText << "Stage 5 complete";
						}

						//going throught the checkpoint
						//checks if the hover car went through between the two poles of the checkpoint
						for (int i = 0; i < checkpoints.size(); i++)
						{
							
							goThroughCheckpoint = PointToBox(hovercar, checkpoints[i].model->GetX() - kCheckpointRadius, checkpoints[i].model->GetX() + kCheckpointRadius, checkpoints[i].model->GetZ() -1, checkpoints[i].model->GetZ() +1);

							//if it did go through, then it will go to the next stage
							if (goThroughCheckpoint == true && checkpoints[i].stage == 1)

							{		
								cross[i]->SetY(5); //sets the red cross's position to the crossed checkpoint
								crossCountDown[i] = 1; //makes the cross appear for a ceratin time
								checkpointCount++;
								currentCheckpoint = second; //goes to next state
							}

						}

						nonplayerHovercar->LookAt(dummy[0]);

						break;
					}

					//before the second checkpoint is crossed
					case second:
					{
						
						currentText << "Stage 1 complete";
						
						//checks if the hover car went through between the two poles of the checkpoint and if the previus stage was completed
						for (int i = 0; i < checkpoints.size(); i++)
						{
							goThroughCheckpoint = PointToBox(hovercar, checkpoints[i].model->GetX() - kCheckpointRadius, checkpoints[i].model->GetX() + kCheckpointRadius, checkpoints[i].model->GetZ(), checkpoints[i].model->GetZ() + 1);

							//if it did go through, then it will go to the next stage
							if (goThroughCheckpoint == true && checkpoints[i].stage == 2)
							{
								
								cross[i]->SetY(5); //sets the red cross's position to the crossed checkpoint
								crossCountDown[i] = 1; //makes the cross appear for a ceratin time
								checkpointCount++;
							    currentCheckpoint = third; //goes to next state
							}

						}
						break;
					}

					//before the third checkpoint is crossed
					case third:
					{
						
						
							currentText << "Stage 2 complete";
						

						for (int i = 0; i < checkpoints.size(); i++)
						{
							goThroughCheckpoint = PointToBox(hovercar, checkpoints[i].model->GetX() - kCheckpointRadius, checkpoints[i].model->GetX() + kCheckpointRadius, checkpoints[i].model->GetZ(), checkpoints[i].model->GetZ() + 1);

							//if it did go through, then it will go to the next stage
							if (goThroughCheckpoint == true && checkpoints[i].stage == 3)
							{
								cross[i]->SetY(5); //sets the red cross's position to the crossed checkpoint
								crossCountDown[i] = 1; //makes the cross appear for a ceratin time
								checkpointCount++;
								currentCheckpoint = fourth; //goes to next state
							}

						}
						
						break;
					}


					case fourth:
					{
						
						
							currentText << "Stage 3 complete";
						

						for (int i = 0; i < checkpoints.size(); i++)
						{
							goThroughCheckpoint = PointToBox(hovercar, checkpoints[i].model->GetX() - kCheckpointRadius, checkpoints[i].model->GetX() + kCheckpointRadius, checkpoints[i].model->GetZ(), checkpoints[i].model->GetZ() + 1);

							//if it did go through, then it will go to the next stage
							if (goThroughCheckpoint == true && checkpoints[i].stage == 4)
							{
								cross[i]->SetY(5); //sets the red cross's position to the crossed checkpoint
								crossCountDown[i] = 1; //makes the cross appear for a ceratin time
								checkpointCount++;
								currentCheckpoint = fifth; //goes to next state
							}

						}

						break;
					}

					case fifth:
					{


						currentText << "Stage 4 complete";


						for (int i = 0; i < checkpoints.size(); i++)
						{
							goThroughCheckpoint = PointToBox(hovercar, checkpoints[i].model->GetX() - kCheckpointRadius, checkpoints[i].model->GetX() + kCheckpointRadius, checkpoints[i].model->GetZ(), checkpoints[i].model->GetZ() + 1);

							//if it did go through, then it will go to the next stage
							if (goThroughCheckpoint == true && checkpoints[i].stage == 5)
							{
								cross[i]->SetY(5); //sets the red cross's position to the crossed checkpoint
								crossCountDown[i] = 1; //makes the cross appear for a ceratin time

								
								checkpointCount++;
								checkpointCount = 0;
								lapCount++; //increments the laps
								currentCheckpoint = first; //goes back to the first state
								
							}

						}

						break;
					}

				}



				//storing the race time of the players
				raceTime += frameTime;
				NPraceTime += frameTime;


				//camera control 

				//moves camera up
				if (myEngine->KeyHeld(cameraMoveUpKey))
				{
					myCamera->MoveLocalZ(kSpeed * frameTime);
				}
				//moves camera down
				if (myEngine->KeyHeld(cameraMoveDownKey))
				{
					myCamera->MoveLocalZ(-kSpeed * frameTime);
				}
				//moves camera right
				if (myEngine->KeyHeld(cameraMoveRightKey))
				{
					myCamera->MoveLocalX(kSpeed * frameTime);
				}
				//moves camera left
				if (myEngine->KeyHeld(cameraMoveLeftKey))
				{
					myCamera->MoveLocalX(-kSpeed * frameTime);
				}

				//rotating camera with mouse movement
				//rotates left and right around the Y axis
				mouseRotationX = myEngine->GetMouseMovementX();
				myCamera->RotateY(mouseRotationX);

				//rotates up and down around the X axis
				mouseRotationY = myEngine->GetMouseMovementY();
				myCamera->RotateLocalX(mouseRotationY);


				//resetting position 
				if (myEngine->KeyHit(ChaseViewCameraKey))
				{
					myCamera->SetLocalPosition(kCameraPosition.x, kCameraPosition.y, kCameraPosition.z);
					myCamera->ResetOrientation();
					myCamera->RotateX(kCameraRotation);
				}

				//first person camera view
				if (myEngine->KeyHit(Key_2))
				{
					myCamera->SetLocalPosition(kFPSCameraPosition.x, kFPSCameraPosition.y, kFPSCameraPosition.z);
					myCamera->RotateX(-kCameraRotation);
				}

				//particle system
				//particle p[1000];

				//for (int i = 0; i < 1000; i++)
				//{
				//	particleCount += frameTime;

				//	if (particleCount == 1)
				//	{
				//		p[i].model = particleMesh->CreateModel(0, 0, -4);
				//		particleCount = 0;
				//	p[i].model->AttachToParent(hovercar);
				//	//p[i].model->RotateX(-45);
				//	p[i].model->Scale(0.01);
				//	p[i].model->SetSkin("purpleparticle.png");
				//	}


				//	p[i].moveVector[0] = random(min, max);
				//	p[i].moveVector[1] = random(min, max);
				//	p[i].moveVector[2] = velocity;
				//}

				////particle system
				//for (int i = 0; i < 1000; i++)
				//{

				//	p[i].moveVector[1] = p[i].moveVector[1] + gravity * frameTime;
				//	p[i].model->Move(p[i].moveVector[0] * frameTime, p[i].moveVector[1] * frameTime, p[i].moveVector[2] * frameTime);

				//	// quad->MoveY(velocity * frameTime);


				//	if (p[i].model->GetY() <= 5)
				//	{
				//		p[i].moveVector[2] = 110;
				//		
				//		p[i].moveVector[0] = random(min, max);
				//		p[i].moveVector[1] = random(min, max);
				//	}

				//	

				//}


				//MOVING HOVER CAR

				

				//making the hovercar look like it's floating
				if (verticalMovement < kHovercarVerticalUpperLimit && goingUp == true)
				{
				  hovercar->MoveY(kVerticalMovementSpeed*frameTime);
				  verticalMovement += kVerticalMovementSpeed*frameTime;
				  if (verticalMovement >= kHovercarVerticalUpperLimit)
				  {
					  goingUp = false;
				  }
				}
				else if (verticalMovement > kHovercarVerticalLowerLimit && goingUp == false)
				{
				  hovercar->MoveY(-kVerticalMovementSpeed * frameTime);
				  verticalMovement -= kVerticalMovementSpeed * frameTime;
				  if (verticalMovement <= kHovercarVerticalLowerLimit)
				  {
					  goingUp = true;
				  }
				}

				//storing the x and z positions of the hovercar
				float oldX = hovercarDummy->GetX();
				float oldZ = hovercarDummy->GetZ();

				//storing the x and z positions of the nonplayer hovercar
				float oldXnonplayer = nonplayerHovercar->GetX();
				float oldZnonplayer = nonplayerHovercar->GetZ();

				//get the facing vector (local Z axis)
				hovercarDummy->GetMatrix(&matrix[0][0]);
				vector2D facingVector{ matrix[2][0], matrix[2][2] };




				//calculate thrust (based on keybord input)

				//hover car control

				//turns right
				if (myEngine->KeyHeld(hovercarTurnRight))
				{
					hovercarDummy->RotateY(kSpeed * frameTime);

					//checking if the turning rotation is over the min limit
					if (rotationZ > -kTurnLimit)
					{
					  hovercar->RotateZ(-kHovercarTiltSpeed);
					  rotationZ -= kHovercarTiltSpeed;

					}
				}
				else
				{
					//rotating the hovercar back to the normal position
					if (rotationZ < 0)
					{
					hovercar->RotateZ(kHovercarTiltBackSpeed);
					rotationZ += kHovercarTiltBackSpeed;

					}
				}

				if (myEngine->KeyHeld(hovercarTurnLeft))
				{
					hovercarDummy->RotateY(-kSpeed * frameTime);

					//checking if the turning rotation is below the max limit
					if (rotationZ < kTurnLimit)
					{
						hovercar->RotateZ(kHovercarTiltSpeed);
						rotationZ += kHovercarTiltSpeed;

					}
				}
				else
				{
					//rotating the hovercar back to the normal position
					if (rotationZ > 0)
					{
						hovercar->RotateZ(-kHovercarTiltBackSpeed);
						rotationZ -= kHovercarTiltBackSpeed;

					}
				}

				//goes forward
				if (myEngine->KeyHeld(hovercarForward))
				{
					thrust = scalar(thrustFactor, facingVector);
					
					//makes the hovercar tilt forward
					if (rotationX < kTiltUpperLimit)
					{
					  hovercar->RotateX(kHovercarTiltSpeed);
					  rotationX += kHovercarTiltSpeed;
					}
				}
				//goes backward
				else if (myEngine->KeyHeld(hovercarBackward))
				{
					thrust = scalar(-thrustFactor/2, facingVector);
				}
				else
				{
					thrust = { 0, 0 };

					//makes the hovercar go back to its original non-tilted position
					if (rotationX > 0)
					{
						hovercar->RotateX(-kHovercarTiltSpeed);
						rotationX -= kHovercarTiltSpeed;
					}
				}



				//calculate drag (based on previous momentum)
				drag = scalar(kBaseDragCoefficient, momentum);

				//calculate momentum (based on thrust, drag, and m')
				momentum = sum3(momentum, thrust, drag);

				//move the hover car (according to new momnetum)
				hovercarDummy->Move(momentum.x * frameTime, 0, momentum.z * frameTime);

				//length of momentum vector
				int speed = sqrt((momentum.x * momentum.x)+(momentum.z * momentum.z));
				speed *= kUnitScale;
				speed *= kSpeedConstant;

				//outputs speed of hovercar
				stringstream speedText;
				speedText << "Speed: " << speed << " km/h";
				myFont->Draw(speedText.str(), myEngine->GetWidth() / 2 - kSpeedTextPosition.x, kSpeedTextPosition.y, kGrapefruit);


				
		
				//collision with checkpoint legs
				CollisionDetection(collisionDist, collisionDist2, collisionDist3, collisionDist4 , collisionDist5 , collisionDist6, hovercarDummy, checkpoints, oldX, oldZ, kCheckpointFeetRadius, health, frameTime, momentum);


				//hovercar and watertanks collision 
				CollisionDetection(collisionDist, collisionDist2, collisionDist3, hovercarDummy, watertank, oldX, oldZ, kWatertankRadius, health, frameTime, momentum);

				//hovercar and nonplayer collision
				CollisionDetection(collisionDist, collisionDist2, collisionDist3, hovercarDummy, nonplayerHovercar, oldX, oldZ, kNonplayerRadius, health, frameTime, momentum, oldXnonplayer, oldZnonplayer);

				


				//states for the nonplayer hovercar
				switch (nonplayerState)
				{

					//state for when it moves
					case race:
					{
					//nonplayer hovercar movement
					//making sure that the variable doesn't go out of range
					if (dummyCount == dummy.size())
					{
						dummyCount = 0;
						nonplayerLapCount++; //increments its lap count
						NPcheckpointCount = 0;
					}

				

					//makes the NPhovercar look at the next waypoint
					nonplayerHovercar->LookAt(dummy[dummyCount]);
					nonplayerHovercar->Scale(kHovercarScale);

					//calculating distance between the next dummy and the nonplayer hovercar
					nonplayerDist = SphereTosphere(dummy[dummyCount]->GetX(), dummy[dummyCount]->GetZ(), nonplayerHovercar->GetX(), nonplayerHovercar->GetZ());
					
					
					vectorX = dummy[dummyCount]->GetX() - nonplayerHovercar->GetX();
					vectorZ = dummy[dummyCount]->GetZ() - nonplayerHovercar->GetZ();
					
					directionX = vectorX / nonplayerDist;
					directionZ = vectorZ / nonplayerDist;
					
					//moving the nonplayer hovercar with the vectors calculated
					nonplayerHovercar->Move(directionX*frameTime*kNPHovercarSpeed, 0, directionZ*frameTime*kNPHovercarSpeed);

					//setting the next dummy, checks if the NPhovercar went throught the waypoint
					if (nonplayerDist < kNonplayerRadius)
					{
						dummyCount++;
						//checks if the dummy is a checkpoint
						if (dummyCount == 0 || dummyCount == 1 || dummyCount == 5 || dummyCount == 6 || dummyCount == 7)
						{
							NPcheckpointCount++;
						}
					}

					//if the NPhovercar finished all the laps, it goes to the end state
					if (nonplayerLapCount == 2 && dummyCount == 8)
					{
						nonplayerState = eNonplayerState::end;
					}
						break;
					}

					//it stops moving when it finished the laps
					case eNonplayerState::end:
					{
						endNPRaceTime = NPraceTime;
						nonplayerHovercar->SetPosition(-35, 0, -15.0f);

						break;
					}

				}//end of nonplayer switch






				//hovercar and wall collision
				for (int i = 0; i < islandsWalls.size(); i++)
				{
					boxSide collision = SphereToBox(hovercarDummy->GetX(), hovercarDummy->GetZ(), oldX, oldZ, kHovercarRadius,
						islandsWalls[i]->GetX(), islandsWalls[i]->GetZ(), kWallWidth, kWallDepth);

					boxSide collision2 = SphereToBox(hovercarDummy->GetX(), hovercarDummy->GetZ()- kHovercarDiameter, oldX, oldZ, kHovercarRadius,
						islandsWalls[i]->GetX(), islandsWalls[i]->GetZ(), kWallWidth, kWallDepth);

					boxSide collision3 = SphereToBox(hovercarDummy->GetX(), hovercarDummy->GetZ()+ kHovercarDiameter, oldX, oldZ, kHovercarRadius,
						islandsWalls[i]->GetX(), islandsWalls[i]->GetZ(), kWallWidth, kWallDepth);

					//resolve collision	
					if (collision == frontSide || collision == backSide ||
						collision2 == frontSide || collision2 == backSide ||
						collision3 == frontSide || collision3 == backSide)
					{
						hovercarDummy->SetZ(oldZ);
						momentum.z = -momentum.z;
						health -= 1;
					}
			   else if (collision == leftSide || collision == rightSide ||
						collision2 == leftSide || collision2 == rightSide ||
						collision3 == leftSide || collision3 == rightSide)
					{
				        hovercarDummy->SetX(oldX);
						momentum.x = -momentum.x;
						
						health -= 1;
					}
				
				}

				
				
				//boost
				//if the boost key is hit and the health is above 30, the boost works
				if (myEngine->KeyHeld(SpaceKey) && health >= kLowHealth && boostDisabled == false)
				{
					thrustFactor = kBaseThrust * 1.5f; //makes the thrust bigger
					boostCountDown -= frameTime; //when the boost key is pressed, it measures how long it is pressed, and disables it if it's used for too long
					myFont->Draw("Boost is active", myEngine->GetWidth() / 2 - kBoostActiveTextPosition.x, kBoostActiveTextPosition.y, kLightBlue); //outputs if boost is active
				}
				else
				{
					thrustFactor = kBaseThrust; //if boost is not used, it uses the usual thrust
				}



				//if boost button is pressed for too long it's disabled for a certain time
				if( boostCountDown < 0)
				{
					dragCoefficient *= 2.0f; //the drag becomes double as much - slows down car
					boostDisabled = true; 
					boostDiasbledCountDown = 5; //boost will be disabled for this long
					boostCountDown = 3.0f; //resetting the coundown for the boost
				
				}
				else
				{
					dragCoefficient = kBaseDragCoefficient;//if the boost wasn't overheated, it uses the normal drag
				}

				//displays message for a readable amount of time before it overheats
				if (boostCountDown <= kboostCountDownUpperLimit && boostCountDown >= kboostCountDownLowerLimit)
				{
					myFont->Draw("Warning: Boost will overheat in 1 second", myEngine->GetWidth() / 2 - kBoostOverheatTextPosition.x, myEngine->GetHeight() /2, kDeepPurple);
				}

				
				//checks which hovercar has more checkpoint count
				//if the player hovercar has more than it's at 1st place
				if (checkpointCount > NPcheckpointCount)
				{
					myFont->Draw("You are currently at 1st place", myEngine->GetWidth() / 2 - kRacePositionText.x, kRacePositionText.y, kPink);
				}
				//if the player hovercar has less than it's at 2nd place
				else if (checkpointCount < NPcheckpointCount)
				{ 
					myFont->Draw("You are currently at 2nd place", myEngine->GetWidth() / 2 - kRacePositionText.x, kRacePositionText.y, kPink);
				}
				//if they have the same , it calculates which car is closer to the next checkpoint
				else if(checkpointCount == NPcheckpointCount)
				{
					float distHovercar = SphereTosphere(checkpoints[checkpointCount].model->GetX(), checkpoints[checkpointCount].model->GetZ(), hovercarDummy->GetX(), hovercarDummy->GetZ());
					float distNPHovercar = SphereTosphere(checkpoints[checkpointCount].model->GetX(), checkpoints[checkpointCount].model->GetZ(), nonplayerHovercar->GetX(), nonplayerHovercar->GetZ());

					if (distHovercar > distNPHovercar)
					{
						myFont->Draw("You are currently at 2nd place", myEngine->GetWidth() / 2 - kRacePositionText.x, kRacePositionText.y, kPink);
					
					}
					else if (distHovercar < distNPHovercar)
					{
						myFont->Draw("You are currently at 1st place", myEngine->GetWidth() / 2 - kRacePositionText.x, kRacePositionText.y, kPink);
					}
					else
					{
					myFont->Draw("Draw", myEngine->GetWidth() / 2 - kRacePositionText.x, kRacePositionText.y, kPink);

					}
				}



				//if health is zero the game ends
				if (health <= 0)
				{
					currentState = over;
				}

				
				//if the hovercar did all the required laps, the game ends or can be restarted
				if (lapCount == kLaps)
				{
					currentState = over;
					
				}

				break;
			}//end of play state	


			//state for when health is zero or the race is completed
			case over:
			{
				//checks if all the laps have been done - it means the game didn't end because of zero health
				if (lapCount == kLaps )
				{
				    myFont->Draw("Race Completed", myEngine->GetWidth() / 2 - kEndScreenXPos, myEngine->GetHeight()/2 -kEndMessageYPos, kOrangeish);

					if (checkpointCount > NPcheckpointCount + kLaps)
					{
						myBigFont->Draw("You won!", myEngine->GetWidth() / 2 - kEndScreenXPos, myEngine->GetHeight() / 2 -kYouWonYPos, kReddish);
						
						//draws race time
						stringstream raceTimeText;
						raceTimeText << "Race time: " << raceTime << " s";
						myFont->Draw(raceTimeText.str(), myEngine->GetWidth() / 2 - kEndScreenXPos, myEngine->GetHeight() / 2  -kRaceTimeYPos, kYellowish);
					}
					else 
					{
						myFont->Draw("Nonplayer hovercar has won!", myEngine->GetWidth() / 2 - kEndScreenXPos, myEngine->GetHeight() / 2 - kNPWonYPos, kReddish);

						//draws race time
						stringstream NPraceTimeText;
						NPraceTimeText << "Race time: " << endNPRaceTime << " s";
						myFont->Draw(NPraceTimeText.str(), myEngine->GetWidth() / 2 - kEndScreenXPos, myEngine->GetHeight() / 2 + kRaceTimeYPos, kYellowish);
					}
				}
				else
				{
					myFont->Draw("Game over", myEngine->GetWidth() / 2 - kEndScreenXPos, myEngine->GetHeight() / 2 - kEndMessageYPos, kOrangeish);
				}

				myFont->Draw("Press Enter to restart game", myEngine->GetWidth() / 2 - kEndScreenXPos, myEngine->GetHeight() / 2, kGreenish);
				myFont->Draw("Press Escape to quit", myEngine->GetWidth() / 2 - kEndScreenXPos, myEngine->GetHeight() / 2  + kPressEscYPos, kBlueish);


				//restart game - resetting all the variables and states
				if (myEngine->KeyHit(RestartKey))
				{
					
					collisionDist = 0.0f;					           //stores the distance for collision check
					collisionDist2 = 0.0f;					           //stores the distance for collision check
					collisionDist3 = 0.0f;					           //stores the distance for collision check
					collisionDist4 = 0.0f;					           //stores the distance for collision check
					collisionDist5 = 0.0f;					           //stores the distance for collision check
					collisionDist6 = 0.0f;					           //stores the distance for collision check
					nonplayerDist = 0.0f;					           //distance calcualtion for nonplayer hovercar and dummy
					mouseRotationX = 20;					           //stores the mouse movement in x direction
					mouseRotationY = 0;					               //stores the mouse movement in y direction
					spacePressed = false;					           //checks if space is pressed
					countDown = 4;						               //checks if a second has passed and displays the next text													  
					currentText.str("");					           //stores the text that should be displayed				
					goThroughCheckpoint = false;			           //stores if the hovercar has gone through a checkpoint or not
					health = 100;							           //stores the health of the hovercar
					thrustFactor = kBaseThrust;				           //the amount of thrust
					dragCoefficient = kBaseDragCoefficient;            //the amount of drag

					 for (int i = 0; i < cross.size(); i++)
					 {
						 crossCountDown[i] = 0;

					 }

					boostCountDown = 3;						           //the boost can be used for this amount of time
					boostDisabled = false;					           //stores if the boost is disabled or not
					boostDiasbledCountDown = kBoostDisabledUpperLimit; //the amount of time the boost can't be used
					dummyCount = 0;							           //stores how many waypoints have been passed by the nonplayer car
					lapCount = 0;							           //stores how many laps have been done by the hovercar
					nonplayerLapCount = 0;					           //stores how many laps have been done by the nonplayer hovercar
					rotationX = 0;							           //stores the rotation of the hovercar while turning
					rotationZ = 0;							           //stores the rotation of the hovercar while accelerating
					verticalMovement = 3;					           //the Y position the hovercar starts in its floating
					goingUp = true;							           //stores if the hovercar is going up or down for the floating effect
					checkpointCount = 0;							   //counts how many checkpoint has the hovercar passed
					NPcheckpointCount = 0;							   //counts how many checkpoint has the nonplayer hovercar passed
					float raceTime = 0;								   //measures hovercar's race time
					float NPraceTime = 0;							   //measures nonplayer hovercar's race time
					float endNPRaceTime = 0;						   //the final time of the NP hovercar


					hovercar->AttachToParent(hovercarDummy);
					myCamera->AttachToParent(hovercarDummy);

					hovercarDummy->SetPosition(-45, 3, -15.0f);
					hovercar->SetLocalPosition(0, 0, 0);
					nonplayerHovercar->SetPosition(-35, 0, -15.0f);
					hovercarDummy->ResetOrientation();
					nonplayerHovercar->ResetOrientation();
					myCamera->SetLocalPosition(0, 15.0f, -20.0f);
					myCamera->ResetOrientation();
					myCamera->RotateX(20.0f);
					
					
					currentState = ready;

					currentCheckpoint = first;

					nonplayerState = race;

					matrix[4][4];

				}

				break;
			}

		} //end of switch

			

		
		//draws the text
		myFont->Draw(currentText.str(), myEngine->GetWidth() / 2 - 100, 665, kPurple);
		
		//draws health
		stringstream healthText;
		healthText << "Health: " << health;
		myFont->Draw(healthText.str(), myEngine->GetWidth() / 2 - 100, 690, kPastelYellow);

		//draws the laps
		stringstream lapText;
		lapText << "Lap: " << lapCount << "/3";
		myFont->Draw(lapText.str(), myEngine->GetWidth() / 2 - 370, 620, kOrange);

	
		//clears currentText
		currentText.str("");








		//quits game
		if (myEngine->KeyHit(Key_Escape))
		{
			myEngine->Stop();
		}
	} //end of while loop

	// Delete the 3D engine now we are finished with it
	myEngine->Delete();
}
