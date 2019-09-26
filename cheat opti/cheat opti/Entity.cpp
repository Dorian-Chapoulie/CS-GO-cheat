#include "Entity.h"

Entity::Entity(int index)
{
	this->index = index;
	position.x = 9999;
	position.y = 9999;
}

Entity::Entity() {

}


Entity::~Entity()
{
}

void Entity::setVisible(bool visible) {
	this->isVisible = visible;
}

void Entity::setHealth(int health) {
	this->health = health;
}

void Entity::setTeam(int team) {
	this->team = team;
}

void Entity::setIndex(int index) {
	this->index = index;
}

int Entity::getHealth() {
	return health;
}

int Entity::getTeam() {
	return team;
}

void Entity::setBoneMatrice(int bM) {
	this->dwBoneMatrice = bM;
}

void Entity::setTaille(float taille) {
	this->taille = taille;
}

void Entity::setClientState(int state) {
	this->clientState = state;
}

void Entity::setClassID(int id) {
	this->classID = id;
}

int Entity::getClassID() {
	return classID;
}
