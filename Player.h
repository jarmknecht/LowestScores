//
//  Player.h
//  LeagueLowScores
//
//  Created by Jonathan Armknecht on 8/15/17.
//  Copyright © 2017 Jonathan Armknecht. All rights reserved.
//

#ifndef Player_h
#define Player_h

#include <string>
#include <vector>

class Player {
public:
   Player();
   Player(std::string lastName, std::string firstName, std::vector<int> scores);
   ~Player();
   
   void SetFirstName(std::string fName);
   std::string GetFirstName() const;
   
   void SetLastName(std::string lName);
   std::string GetLastName() const;
   
   void SetScores(std::vector<int> scores);
   void SetScoreByHole(int score);
   int GetScoreByHole(int i) const; //returns one score, this will be called to get the lowest score back
   std::vector<int> GetScores() const; //returns all of the scores for one player
   std::string PrintScores(std::string holesPlayed);
   std::string SaveScores();
   void SetScoreAt(int index, int newScore);
   void ClearScores();
   
   std::string GetFullName();
   
   int GetNumOfHoles() const;
   
private:
   std::string lastName;
   std::string firstName;
   std::vector<int> scores;
};

#endif /* Player_h */
