#include "Definitions.h"
#include "Collision.h"

//sphere to box collision function
boxSide SphereToBox(float sxPos, float szPos, float oldsxPos, float oldszPos, float srad, float bxPos, float bzPos, float bwidth, float bdepth)
{
	float minX = bxPos - bwidth / 2 - srad;
	float maxX = bxPos + bwidth / 2 + srad;
	float minZ = bzPos - bdepth / 2 - srad;
	float maxZ = bzPos + bdepth / 2 + srad;

	boxSide result = noSide;

	if (sxPos > minX && sxPos < maxX && szPos > minZ && szPos < maxZ)
	{
		if (oldsxPos < minX) result = leftSide;
		else if (oldsxPos > maxX) result = rightSide;
		else if (oldszPos < minZ) result = frontSide;
		else                      result = backSide;
	}

	return(result);
}

//Sphere to sphere collision detection
float SphereTosphere(float s1xPos, float s1zPos, float s2xPos, float s2zPos)
{
	float distX = s2xPos - (s1xPos);
	float distZ = s2zPos - (s1zPos);
	float distance = sqrt(distX*distX + distZ * distZ);

	return distance;
}

//Sphere to sphere collision resolution for hovercar and the watertanks
void CollisionDetection(float collisionDist, float collisionDist2, float collisionDist3, IModel* model1, vector <IModel*> model2,
	float oldX, float oldZ, float model2Radius, int &health, float frameTime, vector2D &momentum)
{
	for (int i = 0; i < model2.size(); i++)
	{
		//collision detection for all 3 spheres inside the hovercar
		collisionDist = SphereTosphere(model1->GetX(), model1->GetZ(), model2[i]->GetX(), model2[i]->GetZ());
		collisionDist2 = SphereTosphere(model1->GetX(), model1->GetZ() + kHovercarRadius, model2[i]->GetX(), model2[i]->GetZ());
		collisionDist3 = SphereTosphere(model1->GetX(), model1->GetZ() - kHovercarRadius, model2[i]->GetX(), model2[i]->GetZ());


		if (collisionDist <= kHovercarRadius + model2Radius ||
			collisionDist2 <= kHovercarRadius + model2Radius ||
			collisionDist3 <= kHovercarRadius + model2Radius)

		{
			model1->SetX(oldX);
			model1->SetZ(oldZ);

			//reversing the momentum of the hovercar
			momentum.x = -momentum.x;
			momentum.z = -momentum.z;

			//if there is a collision then the health reduces
			health -= 1;

		}
	}
}



//collision resolution for hovercar and the checkpoint legs
void CollisionDetection(float collisionDist, float collisionDist2, float collisionDist3, float collisionDist4, float collisionDist5, float collisionDist6, IModel* model1, vector <checkpointStruct> model2,
	float oldX, float oldZ, float model2Radius, int &health, float frameTime, vector2D &momentum)
{
	for (int i = 0; i < model2.size(); i++)
	{
		//collision detection for all 3 spheres inside the hovercar with both legs of a checkpoint
		collisionDist = SphereTosphere(model1->GetX(), model1->GetZ(), model2[i].model->GetX() - kCheckpointRadius, model2[i].model->GetZ() - kCheckpointFeetZDiameter);
		collisionDist2 = SphereTosphere(model1->GetX(), model1->GetZ(), model2[i].model->GetX() + kCheckpointRadius, model2[i].model->GetZ() + kCheckpointFeetZDiameter);
		collisionDist3 = SphereTosphere(model1->GetX(), model1->GetZ() + kHovercarRadius, model2[i].model->GetX() - kCheckpointRadius, model2[i].model->GetZ() - kCheckpointFeetZDiameter);
		collisionDist4 = SphereTosphere(model1->GetX(), model1->GetZ() + kHovercarRadius, model2[i].model->GetX() + kCheckpointRadius, model2[i].model->GetZ() + kCheckpointFeetZDiameter);
		collisionDist5 = SphereTosphere(model1->GetX(), model1->GetZ() - kHovercarRadius, model2[i].model->GetX() - kCheckpointRadius, model2[i].model->GetZ() - kCheckpointFeetZDiameter);
		collisionDist6 = SphereTosphere(model1->GetX(), model1->GetZ() - kHovercarRadius, model2[i].model->GetX() + kCheckpointRadius, model2[i].model->GetZ() + kCheckpointFeetZDiameter);


		if (collisionDist <= kHovercarRadius + model2Radius ||
			collisionDist2 <= kHovercarRadius + model2Radius ||
			collisionDist3 <= kHovercarRadius + model2Radius ||
			collisionDist4 <= kHovercarRadius + model2Radius ||
			collisionDist5 <= kHovercarRadius + model2Radius ||
			collisionDist6 <= kHovercarRadius + model2Radius)

		{

			model1->SetX(oldX);
			model1->SetZ(oldZ);

			//reversing the momentum of the hovercar
			momentum.x = -momentum.x;
			momentum.z = -momentum.z;

			//if there is a collision then the health reduces
			health -= 1;

		}
	}
}

//hovercar and nonplayer hovercar collision resolution
void CollisionDetection(float collisionDist, float collisionDist2, float collisionDist3, IModel* model1, IModel* model2,
	float oldX, float oldZ, float model2Radius, int &health, float frameTime, vector2D &momentum, float oldXnonplayer, float oldZnonplayer)
{
	
	    //collision detection for all 3 spheres inside the hovercar
		collisionDist = SphereTosphere(model1->GetX(), model1->GetZ(), model2->GetX(), model2->GetZ());
		collisionDist2 = SphereTosphere(model1->GetX(), model1->GetZ() + kCheckpointFeetRadius, model2->GetX(), model2->GetZ());
		collisionDist3 = SphereTosphere(model1->GetX(), model1->GetZ() - kCheckpointFeetRadius, model2->GetX(), model2->GetZ());


		if (collisionDist <= kHovercarRadius + model2Radius ||
			collisionDist2 <= kHovercarRadius + model2Radius ||
			collisionDist3 <= kHovercarRadius + model2Radius)

		{
			model1->SetX(oldX);
			model1->SetZ(oldZ);

			model2->SetX(oldXnonplayer);
			model2->SetZ(oldZnonplayer);

			//reversing the momentum of the hovercar
			momentum.x = -momentum.x;
			momentum.z = -momentum.z;

			//if there is a collision then the health reduces
			health -= 1;

		}
	
}

//point to box collision for the hovercar and the checkpoint to check if it went through the checkpoint
bool PointToBox(IModel* model, float MinX, float MaxX, float MinZ, float MaxZ)
{
	if (model->GetX() > MinX && model->GetX() < MaxX && model->GetZ() >= MinZ && model->GetZ() <= MaxZ)
	{
		return true;

	}
	else
	{
		return false;
	}
}
