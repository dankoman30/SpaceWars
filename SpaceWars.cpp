// PiratesAndNinjas.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <thread>
#include <mutex>
#include <memory>
#include "classes.h"

using namespace std; // save us some typing

void intro() {
    // intro stuff here
    cout << "Hi, welcome to PIRATES & NINJAS!!!" << endl << "In this game, a pirate and a ninja fight the ultimate battle to the death!" << endl;
}

int RandomRoll() { // function for retrieving a random integer between 0 and 11
    srand((unsigned)time(0));
    int randomNumber;
    randomNumber = (rand() % 10) + 1; // use modulus operator to set maximum number to 10
    return randomNumber;
}

string CharacterName(string charType) { // method for retrieving string from user for character name
    string enteredName;
    cout << endl << "enter a name for player:" << charType << endl;
    cin >> enteredName; // get text from user
    return enteredName;
}

void outtro(unique_ptr<PirateBase> piratebase, unique_ptr<NinjaBase> ninjabase) { // outtro function to display totals at end of game
    cout << "\n\nTOTAL ROCKETS FIRED FROM PIRATE BASE: " << piratebase->getRocketsLaunched(); // output piratebase rockets total
    cout << "\nTOTAL ROCKETS FIRED FROM NINJA BASE: " << ninjabase->getRocketsLaunched() << endl; // output ninjabase rockets total
}

int main()
{
    intro(); // call intro method
    int choice; // declare choice, for use later
    int startingHealth = 100; // what should the starting health of each player be?

    string pirateName = CharacterName("SPACE PIRATE"); // get pirate name from user
    string ninjaName = CharacterName("SPACE NINJA"); // get ninja name from user

    Pirate pirate(pirateName, startingHealth); // instantiate pirate object with name and starting health
    Ninja ninja(ninjaName, startingHealth); // instantiate ninja object with name and starting health
    unique_ptr<PirateBase> pPirateBase(new PirateBase); // instantiate PirateBase object as new pointer
    unique_ptr<NinjaBase> pNinjaBase(new NinjaBase); // instantiate NinjaBase object as new pointer

    for (;;) { // main loop
        int attackHP; // declare attackHP for use later
        cout << "1. xxxxx" << endl << "2. xxxxx" << endl << "3. Display character health" << endl << "4. Reset character health to full" << endl; // display menu options
        cout << "5. Ninja attacks Pirate with random HP" << endl << "6. Pirate attacks Ninja with random HP" << endl << "8. Help" << endl << "9. EXIT" << endl; // display more menu options
        cout << "enter a choice: "; // instruct user to make a choice
        cin >> choice; // take user input

        switch (choice) { // use a switch
        case 1: // 
            continue; // repeat loop from beginning
        case 2: // 
            continue; // repeat loop from beginning
        case 3: // display character health and launch stats
            cout << "\n\nTOTAL ROCKETS FIRED FROM PIRATE BASE: " << pPirateBase->getRocketsLaunched(); // output base rockets total
            cout << "\nTOTAL ROCKETS FIRED FROM NINJA BASE: " << pNinjaBase->getRocketsLaunched() << endl; // output pad rockets total
            cout << endl << "CURRENT HEALTH:" << endl << "===============" << endl; // display health
            cout << pirate.Name << ": " << pirate.getHealth() << endl;
            cout << ninja.Name << ": " << ninja.getHealth() << endl;
            cout << "===============" << endl << endl;
            continue;
        case 4: // reset everyone's health to full
            pirate.setHealth(100);
            ninja.setHealth(100);
            cout << "FULL HEALTH FOR ALL!" << endl << endl;
            continue;
        case 5: // ninja attacks
            attackHP = RandomRoll(); // define attackHP
            ninja.Talk(ninja.Name, "Eat my rockets full of ninja stars, PIRATE SWINE!!!");
            pNinjaBase->Launch(attackHP); // launch attackHP rockets from ninja base
            pirate.defend(attackHP); // subtract ninja's attack from pirate's health
            cout << endl << ninja.Name << " ATTACKS " << pirate.Name << " FOR " << attackHP << " hitpoints!" << endl << endl;
            continue;
        case 6: // pirate attacks
            attackHP = RandomRoll(); // define attackHP
            pirate.Talk(pirate.Name, "Yarrr! Cannonballs comin yer way, SCALLYWAG!!!");
            pPirateBase->Launch(attackHP); // launch attackHP rockets from pirate base
            ninja.defend(attackHP); // subtract pirate's attack from ninja's health
            cout << endl << pirate.Name << " ATTACKS " << ninja.Name << " FOR " << attackHP << " hitpoints!" << endl << endl;
            continue;
        case 8: // help
            pirate.Help();
            ninja.Help();
            continue;
        case 9: // end game sequence
            cout << endl << endl;
            outtro(move(pPirateBase), move(pNinjaBase)); // pass pointers to outtro function
            cout << endl << endl;
            if (pirate.getHealth() > ninja.getHealth()) { // pirate wins
                cout << pirate.Name << " the pirate has won the game!";
            }
            else if (ninja.getHealth() > pirate.getHealth()) { // ninja wins
                cout << ninja.Name << " the ninja has won the game!";
            }
            else { // tie game
                cout << pirate.Name << " and " << ninja.Name << " have tied.  There is no clear winner.";
            }
            cout << endl << "BYE! THANKS FOR PLAYING!" << endl;
            break; // exit switch
        }
        break;
    }
}