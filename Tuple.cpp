//
//  Tuple.cpp
//  LeagueLowScores
//
//  Created by Jonathan Armknecht on 8/15/17.
//  Copyright © 2017 Jonathan Armknecht. All rights reserved.
//

#include "Tuple.h"

Tuple::Tuple() {
   
}

Tuple::~Tuple() {
   
}

Tuple::Tuple(std::string name, int score) {
   this->name = name;
   this->score = score;
}

void Tuple::SetName(std::string name) {
   this->name = name;
}

std::string Tuple::GetName() const {
   return this->name;
}

void Tuple::SetScore(int score) {
   this->score = score;
}

int Tuple::GetScore() const {
   return this->score;
}
