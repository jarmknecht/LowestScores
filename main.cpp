//
//  main.cpp
//  LeagueLowScores
//
//  Created by Jonathan Armknecht on 8/15/17.
//  Copyright © 2017 Jonathan Armknecht. All rights reserved.
//

#include <iostream>
#include <sstream>
#include <fstream>
#include <chrono>
#include <ctime>

#include "League.h"

using namespace std;

void RunLeagueScores() {
   League myLeague;
   
   istringstream inSS;
   string lineString;
   string holesPlayed;
   string lastName;
   string firstName;
   bool save = false;
   int score = 0;
   int playerNum = 1;
   
   cout << "Welcome to the Eaglewood Men's League Skins Program!" << endl;
   
   cout << "Please indicate if the front 9 or back 9 were played. Type f for front 9 and b for back 9, or press enter for 18 holes." << endl;
   
   cout << "Holes played: ";
   
   getline(cin, holesPlayed);
   
   cout << "Enter first initial then last name and then scores, Example: \"J Armknecht 4 4 5 3 4 4 4 3 5\"" << endl << endl;
   cout << "Enter \"upload\" to upload saved scores from the file \"SavedScores.txt\"" << endl;
   cout << "Enter \"print\" to print all of the golfers entered so far" << endl;
   cout << "Enter \"delete\" to delete the last golfer added" << endl;
   cout << "Enter \"edit\" to edit a golfer entered" << endl;
   cout << "Enter \"save\" to save and quit to finish for later" << endl;
   cout << "Enter \"quit\" when all players have been added" << endl << endl;
   
   while (true) {
      lastName = "";
      firstName = "";
      
      Player* newPlayer = new Player();
      
      cout << "Golfer " << playerNum << " ";
      
      getline(cin, lineString);
      
      inSS.clear();
      inSS.str(lineString);
      
      inSS >> lastName;
      if (lastName == "quit" || lastName == "Quit") {
         break;
      }
      else if (lastName == "upload" || lastName == "Upload") {
         ifstream inFS;
         
         cout << "Uploading file \"SavedScores.txt\"" << endl;
         
         inFS.open("SavedScores.txt");
         if (!inFS.is_open()) {
            cout << "Could not upload file \"SavedScores.txt\"" << endl;
         }
         
         if (inFS.peek() == EOF) {
            //do nothing, There are not scores in the file
            cout << "The file is empty. Cannot upload!" << endl;
         }
         else {
            while (!inFS.eof()) {
               Player* player = new Player();
               inSS.clear();
               getline(inFS, lineString);
               inSS.str(lineString);
               
               inSS >> lastName;
               player->SetLastName(lastName);
               
               inSS >> firstName;
               player->SetFirstName(firstName);
               
               while (!inSS.eof()) {
                  inSS >> score;
                  player->SetScoreByHole(score);
               }
               myLeague.AddPlayer(player);
               playerNum++;
            }
            inFS.close();
         }
      }
      else if (lastName == "save" || lastName == "Save") {
         save = true;
         break;
      }
      else if (lastName == "delete" || lastName == "Delete") {
         if (myLeague.GetAmountOfPlayers() == 0) {
            cout << "No players have been added can't delete" << endl;
         }
         else {
            myLeague.DeletePlayer();
            playerNum--;
         }
      }
      else if (lastName == "print" || lastName == "Print") {
         cout << myLeague.PrintGolfers(holesPlayed);
         cout << endl;
      }
      else if (lastName == "edit" || lastName == "Edit") {
         myLeague.EditGolfer(holesPlayed);
      }
      else {
         newPlayer->SetLastName(lastName);
      
         inSS >> firstName;
         newPlayer->SetFirstName(firstName);
      
         while (!inSS.eof()) {
            inSS >> score;
            while (inSS.fail()) {
               newPlayer->ClearScores();
               
               inSS.clear();
               
               cout << "Adding scores failed. Please type scores again: ";
               getline(cin, lineString);
               inSS.str(lineString);
               
               inSS >> score;
            }
            newPlayer->SetScoreByHole(score);
         }
         myLeague.AddPlayer(newPlayer);
         playerNum++;
      }
   }
   
   if ((myLeague.GetAmountOfPlayers() != 0) && (!save)) {
      stringstream ss;
      ss.clear();
      
      ss << myLeague.toString(holesPlayed);
      cout << ss.str();
      
      cout << "Generating reports..." << endl;
      
      chrono::time_point<chrono::system_clock> time;
      
      time = chrono::system_clock::now();
      
      time_t myTime = chrono::system_clock::to_time_t(time);
      
      ofstream outWinners;
      ofstream outScores;
      
      outWinners.open("Winners.txt");
      if (!outWinners.is_open()) {
         cout << "An error occured while trying to generate \"Winners.txt\"" << endl;
      }
      else {
         outWinners << "Men's League Skins winners for ";
         outWinners << ctime(&myTime) << endl;
         outWinners << ss.str();
         outWinners.close();
      }
      
      outScores.open("Scores.txt");
      if (!outScores.is_open()) {
         cout << "An error occured while trying to generate \"Scores.txt\"" << endl;
      }
      else {
         outScores << "All player's scores for ";
         outScores << ctime(&myTime) << endl;
         outScores << myLeague.PrintGolfers(holesPlayed);
         outScores.close();
      }
   }
   else if (save) {
      cout << "Generating and saving results so far" << endl;
      
      ofstream saveScores;
      
      saveScores.open("SavedScores.txt");
      if (!saveScores.is_open()) {
         cout << "An error occured while trying to generate \"SavedScoreds.txt\"" << endl;
      }
      else {
         saveScores << myLeague.SaveGolfers();
         saveScores.close();
      }
      
   }
   
   cout << "Thank you for using the program!" << endl;
}




int main() {
   RunLeagueScores();
   return 0;
}
