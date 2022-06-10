// PiratesAndNinjas.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <thread>
#include <mutex>
#include <memory>
#include <vector>
#include <fstream>
#include "classes.h"

using namespace std; // save us some typing

const string filename = "spacewars_data.txt"; // this will be the name of the save file

void intro() {
    // intro stuff here
    cout << "Hi, welcome to SPACE WARS!!!" << endl << "In this game, a space pirate and a space ninja fight the ultimate battle to the death!" << endl;
}

int RandomRoll() { // function for retrieving a random integer between 0 and 11
    srand((unsigned)time(0));
    int randomNumber;
    randomNumber = (rand() % 10) + 1; // use modulus operator to set maximum number to 10
    return randomNumber;
}

string CharacterName(string charType) { // method for retrieving string from user for character name
    string enteredName;
    while (enteredName.length() == 0) { // keep looping until we have a valid entry
        cout << endl << "enter a name for player: " << charType << endl;
        try {
            getline(cin, enteredName);
            if (enteredName == "\n") { // check for blank entry
                throw("*****NOTHING ENTERED*****"); // nothing entered
            }
        }
        catch (string myExc) {
            cout << endl << myExc << endl << endl << "PLEASE TRY AGAIN!!!\n\n"; // complain to user
        }
    }

    return enteredName;
}

void outtro(unique_ptr<PirateBase> piratebase, unique_ptr<NinjaBase> ninjabase) { // outtro function to display totals at end of game
    cout << "\n\nTOTAL ROCKETS FIRED FROM PIRATE BASE: " << piratebase->getRocketsLaunched(); // output piratebase rockets total
    cout << "\nTOTAL ROCKETS FIRED FROM NINJA BASE: " << ninjabase->getRocketsLaunched() << endl; // output ninjabase rockets total
}

void saveGame(string pirateName, int pirateRockets, int pirateHP, string ninjaName, int ninjaRockets, int ninjaHP) { // this will overwrite existing save file every time
    fstream myfile; // instantiate file object
    myfile.open(filename, ios::out); // initial write
    if (myfile.is_open()) { // check if file is open
        myfile << pirateName << endl << pirateRockets << endl << pirateHP << endl << ninjaName << endl << ninjaRockets << endl << ninjaHP; // output values to file
        myfile.close(); // close file
        cout << endl << endl << "*****GAME HAS BEEN SUCCESSFULLY SAVED TO " << filename << " IN SOURCE DIRECTORY!!!*****" << endl << endl; // notify user of game save
    }
}

bool loadGame(vector<string> &saveData) { // pass pointer to save data vector into this function
    ifstream in(filename);
    if (!in) { // CHECK IF FILE OBJECT IS VALID
        cout << endl << "**********CANNOT OPEN FILE**********" << endl << endl;
        return false;
    }
    string str;
    while (getline(in, str)) { // read next line from file until end is reached
        saveData.push_back(str); // writes line to the vector<string>
    }

    in.close(); // close file
    return true; // return true if file was successfully read
}

int main()
{
    intro(); // call intro method

    vector<string> saveData;

    int choice; // declare choice, for use later
    int startingHealth = 100; // what should the starting health of each player be?

    Pirate pirate(CharacterName("SPACE PIRATE"), startingHealth); // instantiate pirate object with name and starting health, using CharacterName function to retrieve character name from user
    Ninja ninja(CharacterName("SPACE NINJA"), startingHealth); // instantiate ninja object with name and starting health, using CharacterName function to retrieve character name from user

    unique_ptr<PirateBase> pPirateBase(new PirateBase); // instantiate PirateBase object as new pointer
    unique_ptr<NinjaBase> pNinjaBase(new NinjaBase); // instantiate NinjaBase object as new pointer

    for (;;) { // main loop
        int attackHP; // declare attackHP for use later
        cout << "1. Save game" << endl << "2. Load game" << endl << "3. Display character health" << endl << "4. Reset character health to full" << endl; // display menu options
        cout << "5. Space Ninja Attacks!" << endl << "6. Space Pirate Attacks!" << endl << "8. Help" << endl << "9. EXIT" << endl; // display more menu options
        cout << "enter a choice: "; // instruct user to make a choice
        cin >> choice; // take user input

        switch (choice) { // use a switch
        case 1: // save game
            saveGame(pirate.Name, pPirateBase->getRocketsLaunched(), pirate.getHealth(), ninja.Name, pNinjaBase->getRocketsLaunched(), ninja.getHealth()); // pass data to save function
            continue; // repeat loop from beginning
        case 2: // load game
            if (loadGame(saveData)) {
                pirate.Name = saveData[0]; // set pirate name to first array element
                pPirateBase->setRocketsLaunched(stoi(saveData[1])); // set rockets launched to second array element, cast as an integer
                pirate.setHealth(stoi(saveData[2])); // set health to third array element, cast as an integer
                ninja.Name = saveData[3]; // set ninja name to fourth array element
                pNinjaBase->setRocketsLaunched(stoi(saveData[4])); // set rockets launched to fifth array element, cast as an integer
                ninja.setHealth(stoi(saveData[5])); // set health to sixth array element, cast as an integer
                cout << endl << endl << "*****GAME HAS BEEN SUCCESSFULLY LOADED FROM " << filename << "!!!*****" << endl << endl; // notify user of game load
            }
            else {
                cout << endl << "**********FAILED TO LOAD SAVE DATA**********";
            }
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
            pirate.Talk(pirate.Name, "Yarrr! Cannonballs rockets be comin yer way, SCALLYWAG!!!");
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
        default:
            cout << "\n******************************\nNOT A VALID OPTION! TRY AGAIN!\n******************************\n"; // complain to user if invalid option selected, continue the loop
            continue;
        }
        break;
    }
}