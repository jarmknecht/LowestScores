//
//  Tuple.h
//  LeagueLowScores
//
//  Created by Jonathan Armknecht on 8/15/17.
//  Copyright © 2017 Jonathan Armknecht. All rights reserved.
//

#ifndef Tuple_h
#define Tuple_h

#include <vector>
#include <string>

class Tuple {
public:
   Tuple();
   ~Tuple();
   Tuple(std::string name, int score);
   
   void SetName(std::string name);
   std::string GetName() const;
   
   void SetScore(int score);
   int GetScore() const;
   
private:
   std::string name;
   int score;
};


#endif /* Tuple_h */
