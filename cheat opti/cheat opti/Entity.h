#pragma once
#include "Vector2D.h"
#include "Vector3D.h"

/*Classe représentant une entité*/
class Entity
{
public:
	Entity(int index);
	Entity();
	~Entity();

	void setHealth(int vie);
	void setTeam(int team);
	void setIndex(int index);
	void setBoneMatrice(int bM);
	void setTaille(float taille);
	void setClientState(int state);
	void setClassID(int classID);
	void setVisible(bool visible);

	__forceinline int getIndex() {
		return this->index;
	}
	__forceinline int getBoneMatrice() {
		return this->dwBoneMatrice;
	}
	__forceinline float getTaille() {
		return this->taille;
	}
	__forceinline int getClientState() {
		return this->clientState;
	}

	__forceinline bool getIsVisible() {
		return this->isVisible;
	}

	int getHealth();
	int getTeam();
	int getClassID();

	Vector2D viewAngles;
	Vector2D screenPosition;
	Vector3D position;

private:
	int index = 0;
	int health = 0;
	int team = 0;
	int dwBoneMatrice = 0;
	int clientState = 0;
	int classID = 0;
	bool isVisible = false;
	float taille = 0;

};

