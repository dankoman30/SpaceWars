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

int main()
{
    intro(); // call intro method
    int choice; // declare choice, for use later
    int startingHealth = 100; // what should the starting health of each player be?

    string pirateName = CharacterName("SPACE PIRATE"); // get pirate name from user
    string ninjaName = CharacterName("SPACE NINJA"); // get ninja name from user

    Pirate pirate(pirateName, startingHealth); // instantiate pirate object with name and starting health
    Ninja ninja(ninjaName, startingHealth); // instantiate ninja object with name and starting health

    for (;;) { // main loop
        int attackHP; // declare attackHP for use later
        cout << "1. xxxxx" << endl << "2. xxxxx" << endl << "3. Display character health" << endl << "4. Reset character health to full" << endl; // display menu options
        cout << "5. Ninja attacks Pirate with random HP" << endl << "6. Pirate attacks Ninja with random HP" << endl << "8. Help" << endl << "9. EXIT" << endl; // display more menu options
        cout << "enter a choice: "; // instruct user to make a choice
        cin >> choice; // take user input

        switch (choice) { // use a switch
        case 1: // ninja attacks
            continue; // repeat loop from beginning
        case 2: // pirate attacks
            continue; // repeat loop from beginning
        case 3: // display character health
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
        case 5: // ninja attacks pirate random
            attackHP = RandomRoll(); // define attackHP
            pirate.defend(attackHP); // subtract ninja's attack from pirate's health
            ninja.Talk(ninja.Name, "Eat my rockets full of ninja stars, PIRATE SWINE!!!");
            cout << endl << ninja.Name << " ATTACKS " << pirate.Name << " FOR " << attackHP << " hitpoints!" << endl << endl;
            continue;
        case 6: // pirate attacks ninja random
            attackHP = RandomRoll(); // define attackHP
            ninja.defend(attackHP); // subtract pirate's attack from ninja's health
            pirate.Talk(pirate.Name, "Yarrr! Cannonballs comin yer way, SCALLYWAG!!!");
            cout << endl << pirate.Name << " ATTACKS " << ninja.Name << " FOR " << attackHP << " hitpoints!" << endl << endl;
            continue;
        case 8: // help
            pirate.Help();
            ninja.Help();
            continue;
        case 9: // end game sequence
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