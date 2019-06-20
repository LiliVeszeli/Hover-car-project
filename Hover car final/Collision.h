#pragma once
#include "Definitions.h"

boxSide SphereToBox(float sxPos, float szPos, float oldsxPos, float oldszPos, float srad, float bxPos, float bzPos, float bwidth, float bdepth);

float SphereTosphere(float s1xPos, float s1zPos, float s2xPos, float s2zPos);

void CollisionDetection(float collisionDist, float collisionDist2, float collisionDist3, IModel* model1, vector <IModel*> model2,
	float oldX, float oldZ, float model2Radius, int &health, float frameTime, vector2D &momentum);

void CollisionDetection(float collisionDist, float collisionDist2, float collisionDist3, float collisionDist4, float collisionDist5, float collisionDist6, IModel* model1, vector <checkpointStruct> model2,
	float oldX, float oldZ, float model2Radius, int &health, float frameTime, vector2D &momentum);

void CollisionDetection(float collisionDist, float collisionDist2, float collisionDist3, IModel* model1, IModel* model2,
	float oldX, float oldZ, float model2Radius, int &health, float frameTime, vector2D &momentum, float oldXnonplayer, float oldZnonplayer);

bool PointToBox(IModel* model, float MinX, float MaxX, float MinZ, float MaxZ);