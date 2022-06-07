#include "classes.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <thread>
#include <mutex>
#include <memory>

void GameStructure::Help() {} // virtual empty method


// CHARACTER STUFF
int Character::getHealth() { // health getter method
    return Health;
}
void Character::setHealth(int health) { // health setter method
    Health = health;
    if (Health <= 0) { // character is dead if health is less than or equal to zero
        Health = 0; // in case health is less than zero, reset it to zero
        cout << Name << " has Expired..." << endl;
    }
}
void Character::defend(int hitPoints) {
    int newHealth = getHealth() - hitPoints; // what will the health be after attack?
    setHealth(newHealth); // set the new health
}
void Character::Talk(string stuffToSay) { // method for character to speak
    cout << endl << stuffToSay << endl << endl;
}
void Character::Talk(string name, string stuffToSay) { // another method for character to speak, but allows name to be passed in as well
    cout << endl << "I'm " << name << ", and " << stuffToSay << endl << endl;
}
void Character::Help() {} // overriding help method


// NINJA STUFF:
Ninja::Ninja(string N, int H) { // constructor
    Name = N; // define name
    setHealth(H); // initialize starting health
}
void Ninja::defend(int hitPoints) {
    Character::defend(hitPoints); // call super method first
    // ninja specific stuff here!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
}
void Ninja::Help() {
    cout << endl << "Ninjas are quiet and swift; you can use them to launch rockets filled with shooting stars!" << endl << endl;
}


// PIRATE STUFF:
Pirate::Pirate(string N, int H) { // constructor
    Name = N; // define name
    setHealth(H); // initialize starting health

}
void Pirate::defend(int hitPoints) {
    Character::defend(hitPoints); // call super method first
    // pirate specific stuff here!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
}
void Pirate::Help() {
    cout << endl << "Pirates are loud and forceful; you can use them to shoot cannonballs!" << endl << endl;
}



mutex locker; // instantiate mutex object
void launch(string origin, int rocketsToLaunch) {
    cout << "\n\nNOW TRANSFERRING LAUNCH CONTROL TO " << origin << "!!!\n\n"; // inform user of control transfer to new station
    cout << "PRESS ENTER TO CONTINUE.....\n";
    cout << "\n\nLAUNCHING " << rocketsToLaunch << " new projectiles!\n\n"; // inform user of number of new rockets being launched
    system("pause>0");

    int rocketNumber;
    locker.lock(); // protect the following code to ensure it finishes executing:
    thread::id threadNumber = this_thread::get_id(); // store thread ID once (no need to get it on each loop iteration)
    for (int i = 0; i < rocketsToLaunch; i++) { // set max loop iterations to rocketsToLaunch
        rocketNumber = i + 1; // this lets iteration 0 equal rocket #1, and so on
        cout << "\nPreparing rocket #" << rocketNumber << " of " << rocketsToLaunch; // inform user of rocket number and new rocket total
        cout << " new rockets to be launched from " << origin; // inform user of origin
        cout << " on the following thread: " << threadNumber << endl; // inform user of current thread id
        for (int i = 3; i >= 0; i--) { // countdown from 3, delaying 1 second on each loop iteration
            printf("countdown: T minus %d seconds\n", i);
            if (i > 0) { // delay for 1 second on each loop iteration except 0
                this_thread::sleep_for(chrono::seconds(1)); // sleep for 1 second
            }
            else { // when we get to 0 (last iteration of the loop), fire the rocket!
                printf("\nROCKET #%d HAS BEEN FIRED!!!\n", rocketNumber); // inform user that rocket has been fired
            }
        }
    }
    locker.unlock(); // unlock the mutex
}





// BASE STUFF:
Launchable::Launchable() { // constructor
	rocketsLaunched = 0; // initialize to 0
};
int Launchable::getRocketsLaunched() { // getter method
	return rocketsLaunched;
}
void Launchable::incrementRocketsLaunched(int newRockets) { // setter method (increments by passed integer)
	rocketsLaunched += newRockets;
}

void PirateBase::Launch(int rocketsToLaunch) {
	cout << "\n Rockets launched thus far from PIRATE BASE: " << getRocketsLaunched() << endl; // inform user of rockets launched so far
	thread t1(launch, "PIRATE BASE", rocketsToLaunch); // pass "PIRATE BASE" as a string parameter to launch function so rocket launches from main base
	t1.join(); // wait for thread to finish executing code
	incrementRocketsLaunched(rocketsToLaunch); // increment running total
	cout << "\n TOTAL ROCKETS LAUNCHED FROM PIRATE BASE: " << getRocketsLaunched() << endl; // inform user of new total
}

void NinjaBase::Launch(int rocketsToLaunch) {
	cout << "\n Rockets launched thus far from NINJA BASE: " << getRocketsLaunched() << endl; // inform user of rockets launched so far
	thread t1(launch, "NINJA BASE", rocketsToLaunch); // pass "NINJA BASE" as a string parameter to launch function so rocket launches from main base
	t1.join(); // wait for thread to finish executing code
	incrementRocketsLaunched(rocketsToLaunch); // increment running total
	cout << "\n TOTAL ROCKETS LAUNCHED FROM NINJA BASE: " << getRocketsLaunched() << endl; // inform user of new total
}