#include "ofMain.h"
#include "system_units.h"

class OffensivePlayer;

/* This is a Ball class.
It attaches to a player and moves with the ball carry.
When a player passes the ball, it moves by interpolating towards the new target 
and reattaches to the new player */

class Ball {

  public:

  Ball();
  
  void PassTo(OffensivePlayer* target);
  void AttachToPlayer(OffensivePlayer* target);
  void Update();
  void Display(SystemUnits* su);
  glm::vec2 getPos(){ return position; };
  OffensivePlayer* getOwner(){ return owner; };

  private:

  void MoveToNextOwner();
  
  float attachTolerance = 3.0;
  float passPower = 0.7;
  glm::vec2 position;
  OffensivePlayer* owner;
  bool attached;
  float size = 1.2;
};