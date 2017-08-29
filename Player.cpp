//
//  Player.cpp
//  LeagueLowScores
//
//  Created by Jonathan Armknecht on 8/15/17.
//  Copyright © 2017 Jonathan Armknecht. All rights reserved.
//

#include "Player.h"
#include <sstream>

Player::Player() {
   this->lastName = "NO NAME";
   this->firstName = "NO NAME";
}

Player::~Player() {
   
}

Player::Player(std::string lastName, std::string firstName, std::vector<int> scores) {
   this->lastName = lastName;
   this->firstName = firstName;
   this->scores = scores;
}

void Player::SetFirstName(std::string fName) {
   this->firstName = fName;
}

std::string Player::GetFirstName() const {
   return this->firstName;
}

void Player::SetLastName(std::string lName) {
   this->lastName = lName;
}

std::string Player::GetLastName() const {
   return this->lastName;
}

void Player::SetScores(std::vector<int> scores) {
   this->scores = scores;
}

void Player::SetScoreByHole(int score) {
   this->scores.push_back(score);
}

void Player::SetScoreAt(int index, int newScore) {
   this->scores.at(index) = newScore;
}

int Player::GetScoreByHole(int i) const {
   if ((i > this->scores.size()) || (this->scores.size() == 0)) {
      return 0;
   }
   return this->scores.at(i);
}

std::vector<int> Player::GetScores() const {
   return this->scores;
}

std::string Player::PrintScores(std::string holesPlayed) {
   std::stringstream ss;
   
   for (int i = 0; i < GetNumOfHoles(); i++) {
      if (holesPlayed == "b") {
         ss << i + 10 << ": ";
      }
      else if (holesPlayed == "f") {
         ss << i + 1 << ": ";
      }
      else {
         ss << i + 1 << ": "; //if f or b wasn't typed just print 1 - 9
      }
      ss << this->scores.at(i) << " ";
   }
   
   return ss.str();
}

std::string Player::GetFullName() {
   std::stringstream ss;
   
   ss << GetLastName() << ". " << GetFirstName();
   
   return ss.str();
}

void Player::ClearScores() {
   this->scores.clear();
}

int Player::GetNumOfHoles() const {
   return this->scores.size();
}
