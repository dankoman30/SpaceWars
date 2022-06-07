#pragma once
#include <string>

using namespace std;

class GameStructure { // create root class
public:
    virtual void Help(); // virtual empty method
};

class Character : public GameStructure { // declare Character class, derived from GameStructure
private:
    int Health;
public:
    string Name;
    int getHealth();
    void setHealth(int health);
    virtual void defend(int hitPoints);
    void Talk(string stuffToSay);
    void Talk(string name, string stuffToSay);
    void Help(); // overriding help method
};

class Ninja : public Character { // declare Ninja class, derived from Character
public:
    Ninja(string N, int H); // constructor
    void defend(int hitPoints); // override virtual method in superclass
    void Help();
};

class Pirate : public Character { // declare Pirate class, derived from Character
public:
    Pirate(string N, int H); // constructor
    void defend(int hitPoints); // override virtual method in superclass
    void Help();
};

class Launchable {
private:
	int rocketsLaunched;
public:
	Launchable(); // constructor
	int getRocketsLaunched(); // getter method
	void incrementRocketsLaunched(int newRockets); // setter method (increments by passed integer)
};

class PirateBase : public Launchable {
public:
    void Launch(int rocketsToLaunch);
};

class NinjaBase : public Launchable {
public:
    void Launch(int rocketsToLaunch);
};