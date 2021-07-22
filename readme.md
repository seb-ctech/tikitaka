# The Essence of Tiki Taka

[Tiki-Taka](https://www.youtube.com/watch?v=1o8C8n4XUwU) has been a very polarising football tactic that became a signature style for the Spanish national team and the Barcelona Football club. This tactic focuses on short passes and possession football depending on high team cohesion and a strict positioning system where players arrange in triangles to distribute evenly in the available space. The key is to outnumber areas on the pitch with fast direct passes and, simply put, tear the opponent’s defense apart. This results in controversally very fluid dynamics in space that for many is informally seen as the most beautiful way to play football. I want to extract the resulting dynamic behavior and model this with an agent system. Focus lies on extracting the aesthetics given by the two opposing forces, going for the ball and distance it visually as far from football as possible without losing the characteristic behavior. One group of agents moves fluedly in space to link up and pass around the ball, while the other force pushes towards the agent posessing the ball. This requires a highly advanced agent algorithm that is aware of it’s party, the position on the canvas, the position of the ball and predict the movement of the other agents, resulting in a challenge of software design and architecture as well as simulation, which are core learnings of the 2. semester. 


## System requirements:

* Way of displaying and representing information and parameters on which the decisions are dependent
    
    * Pitch
    * Passing Lanes
    * Ball
    * Formation
    * Space and Space distribution
    * Player arrangement
* Decision making system for the agents
    * **offensive agents:**
        * Keep cohesion
        * Keep triangle formation for passing lanes
        * Distribute evenly in space
    * **defensive agents:**
        * Reduce space
        * Build layered formation
        * Attack player with ball
* Locomotion system:
    * Current position
    * Possible next movement
        * Direction
        * Pace and Distance: *Varying pace of movement (continous slow jogging → sudden sprint)*
    * Possible next pass
