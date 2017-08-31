//
//  League.cpp
//  LeagueLowScores
//
//  Created by Jonathan Armknecht on 8/15/17.
//  Copyright © 2017 Jonathan Armknecht. All rights reserved.
//

#include "League.h"
#include <iostream>
#include <sstream>

League::League() {
   
}

League::~League() {
   for (int i = 0; i < this->players.size(); i++) {
      delete this->players.at(i);
      this->players.at(i) = NULL;
   }
   for (int i = 0; i < this->lowestScores.size(); i++) {
      delete this->lowestScores.at(i);
      this->lowestScores.at(i) = NULL;
   }
}

void League::AddPlayer(Player* player) {
   this->players.push_back(player);
}

void League::GetPersonWithLowestScorePerHole() {
   
   for (int i = 0; i < this->players.at(0)->GetNumOfHoles(); i++) { //i is keeping try of the hole
      std::vector<int> scoresByHole;
      for (int j = 0; j < this->players.size(); j++) { //add each score for each player from each hole
         scoresByHole.push_back(this->players.at(j)->GetScoreByHole(i));
      }
      int index = LowestHoleScore(scoresByHole);
      if (index == -1) {
         Tuple* tup = new Tuple("NOBODY", -1);
         lowestScores.push_back(tup);
      }
      else {
         std::stringstream ss;
         ss << this->players.at(index)->GetLastName() << ". " << this->players.at(index)->GetFirstName();
         Tuple* tup = new Tuple(ss.str(), this->players.at(index)->GetScoreByHole(i));
         lowestScores.push_back(tup);
      }
   }
}

int League::LowestHoleScore(std::vector<int> scoresByHole) {
   int index = -1;
   int lowScore = 0;
   
   for (int i = 0; i < scoresByHole.size(); i++) {
      if (i == 0) {
         lowScore = scoresByHole.at(i);
         index = i;
      }
      else {
         if (scoresByHole.at(i) == lowScore) {
            index = -1;
         }
         if (scoresByHole.at(i) < lowScore) {
            lowScore = scoresByHole.at(i);
            index = i;
         }
      }
   }
   return index;
}

std::string League::toString(std::string holesPlayed) {
   GetPersonWithLowestScorePerHole();
   
   std::stringstream ss;
   
   int numOfHolesNoWinner = 0;
   
   for (int i = 0; i < lowestScores.size(); i++) {
      if (this->lowestScores.at(i)->GetName() == "NOBODY") {
         //don't print out if no winner
         numOfHolesNoWinner++;
      }
      else {
         ss << "Hole ";
         if (holesPlayed == "b") {
            ss << i + 10;
         }
         else if (holesPlayed == "f") {
            ss << i + 1;
         }
         else {
            ss << i + 1; //if f or b wasn't typed just print 1 - 9
         }
         ss << " winner " << this->lowestScores.at(i)->GetName();
         ss << " with a score of " << this->lowestScores.at(i)->GetScore() << std::endl;
      }
   }
   if (numOfHolesNoWinner == this->players.at(0)->GetNumOfHoles()) {
         ss << "No skins awarded." << std::endl;
   }
   
   return ss.str();
}

void League::EditGolfer(std::string holesPlayed) {
   int golferNum = 0;
   int holeToEdit = 0;
   int newScore = 0;
   std::string lineString;
   
   if (GetAmountOfPlayers() == 0) {
      std::cout << "There have been no players added." << std::endl;
   }
   
   else {
      std::cout << "Enter golfer number that you want to edit: ";
      std::cin >> golferNum;
      std::cin.ignore();
      
      while (std::cin.fail()) {
         std::cin.clear();
         std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
         
         std::cout << "Selecting golfer failed. Try again: ";
         std::cin >> golferNum;
         std::cin.ignore();
         
      }
      
      while ((golferNum > GetAmountOfPlayers()) || golferNum < 1) {
         std::cout << "There is no golfer " << golferNum << " that has been entered yet. Try again: ";
         std::cin >> golferNum;
         std::cin.ignore();
         
         while (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            
            std::cout << "Selecting golfer failed. Try again: ";
            std::cin >> golferNum;
            std::cin.ignore();
            
         }
      }
      
      golferNum = golferNum - 1;
      
      while (true) {
         
         for (int i = 0; i < this->players.at(golferNum)->GetNumOfHoles(); i++) {
            if (holesPlayed == "b") {
               std::cout << "Hole " << i + 10 << ": ";
            }
            else if (holesPlayed == "f") {
               std::cout << "Hole " << i + 1 << ": ";
            }
            else {
               std::cout << "Hole " << i + 1 << ": "; //if f or b wasn't typed just print 1 - 9
            }
            std::cout << this->players.at(golferNum)->GetScoreByHole(i) << std::endl;
         }
         std::cout << "Please select which hole you would like to edit for " << this->players.at(golferNum)->GetFullName() << ": ";
         std::cin >> holeToEdit;
         std::cin.ignore();
         
         while (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            
            std::cout << "Selecting hole failed. Try again: ";
            std::cin >> holeToEdit;
            std::cin.ignore();
            
         }
         
         while ((holeToEdit > this->players.at(golferNum)->GetNumOfHoles()) || holeToEdit < 1) {
            std::cout << "There is no hole for " << holeToEdit << ". Try again: ";
            std::cin >> holeToEdit;
            std::cin.ignore();
            
            while (std::cin.fail()) {
               std::cin.clear();
               std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
               
               std::cout << "Selecting hole failed. Try again: ";
               std::cin >> holeToEdit;
               std::cin.ignore();
               
            }
         }
      
         std::cout << "Enter new score for hole " << holeToEdit << ": ";
         std::cin >> newScore;
         std::cin.ignore();
         
         while (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            
            std::cout << "Entering new score failed. Try again: ";
            std::cin >> newScore;
            std::cin.ignore();
            
         }
         
         holeToEdit = holeToEdit - 1;
         this->players.at(golferNum)->SetScoreAt(holeToEdit, newScore);
         
         std::cout << "Enter \"done\" if done editing this golfer. If more holes press enter: ";
         
         getline(std::cin, lineString);
         
         if (lineString == "done") {
            break;
         }
      }
   }
}

std::string League::PrintGolfers(std::string holesPlayed) {
   std::stringstream ss;
   if (GetAmountOfPlayers() == 0) {
      return "There have been no players added.\n";
   }
   else {
      std::cout << std::endl;
      for (int i = 0; i < this->players.size(); i++) {
         ss << "Golfer " << i + 1 << ": ";
         ss << this->players.at(i)->GetLastName() << ". " << this->players.at(i)->GetFirstName();
         ss << "\'s scores: " << this->players.at(i)->PrintScores(holesPlayed) << std::endl;
      }
   }
   
   return ss.str();
}

std::string League::SaveGolfers() {
   std::stringstream ss;
   if (GetAmountOfPlayers() == 0) {
      return "";
   }
   else {
      for (int i = 0; i < this->players.size(); i++) {
         ss << this->players.at(i)->GetLastName() << " " << this->players.at(i)->GetFirstName() << " ";
         ss << this->players.at(i)->SaveScores();
         if (i < this->players.size() - 1) {
            ss << std::endl;
         }
      }
   }
   return ss.str();
}

void League::DeletePlayer() {
   delete this->players.back();
   this->players.pop_back();
}

int League::GetAmountOfPlayers() const {
   return this->players.size();
}

