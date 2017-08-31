//
//  League.h
//  LeagueLowScores
//
//  Created by Jonathan Armknecht on 8/15/17.
//  Copyright © 2017 Jonathan Armknecht. All rights reserved.
//

#ifndef League_h
#define League_h

#include "Player.h"
#include "Tuple.h"

class League {
public:
   League();
   ~League();
   
   void AddPlayer(Player* player);
   
   int GetAmountOfPlayers() const;
   
   void DeletePlayer();
   
   void GetPersonWithLowestScorePerHole();
   int LowestHoleScore(std::vector<int> scoresByHole);
   
   void EditGolfer(std::string holesPlayed);
   
   std::string PrintGolfers(std::string holesPlayed);
   
   std::string SaveGolfers();
   
   std::string toString(std::string holesPlayed);
   
private:
   std::vector<Player*> players;
   std::vector<Tuple*> lowestScores;
};


#endif /* League_h */
