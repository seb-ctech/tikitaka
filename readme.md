## Tikitaka
# A Dance of Spaces

![cover image](./preview.gif)

This project was about simulating the behavior of the tikitaka football tactic and extract it with a visualization that only expresses the intersection and positioning of the two sides resulting in a dance of spaces. The final product is an openframeworks program where the user can switch between a shader and a system view and influence parameters that have an impact on the whole relationship of positions and spaces.

[Binary Download](https://github.com/seb-ctech/tikitaka/releases/tag/v.1.0.0-win64)

### Usage

**Binary**: Download and open "tikitaka.exe". Switch between the two views with **Spacebar** and in the two views change the Parameters with **Up-Down Arrow** and **Left-Right Arrow**.

**Source Code**: Use the [OpenFrameworks project generator](https://openframeworks.cc/learning/01_basics/create_a_new_project/) to create a source folder. Paste in the repository's code and update (with the project generator) the source folder to the template and platform you are using.

## Concept

As a football fan my fascination for systems drew me to playstyles where the entire team moves and coordinates as a unit using teamwork instead of individual class, to outplay it's opponents, resulting in dynamic, coordinated attacks. When one looks at the spaces between the players, one can see the sum of those interactions, almost looking like a dance, a ryhtmical exchange in continuos development. This particular aesthetic behavior found it's apex with the iconic [Tikitaka tactic](https://en.wikipedia.org/wiki/Tiki-taka), which became a signature style of the FC Barcelona Club and was later adapted to the [Spanish National Team](https://www.youtube.com/watch?v=t8xSnPoOyuE), which using this concept won three consecutive international competitions.  

I wanted to express this exchange of spaces and coordinated movements of players while they pass the ball around and tear the opponent's defense apart. The ball in this case represents a point of focus for the players in their challenge for possession and for the viewer that follows it as a reference to comprehend the state of a match. Tikitaka focuses on many quick passes to keep the ball as long as possible while the defending players out of position and creating spaces to attack. This were all elements I wanted to capture with a simulation.
The simulation's goal was not the realistic reproduction of the rules of football and real football match. It was merely a model that in it's entirety simulates the behavior. One side passing around the ball, while organizing in cohesive triangles to improve their position and supporting the player with ball, and the other side covering areas of the pitch as cohesive unit and pressuring the player in possession of the ball. This simulation would then produce a set of points in space which can be used as inputs for a fragment shader. Especially SDFs and cellular visualizations provided a fitting visual translation of player positions transforming to spaces moving and intertwining like a fluid with that of the opposing side, while the ball's position serves as a visual focal point.

In the end the viewer can switch between the aesthetic essence in form of the shader and a simple graphical visualization of the system, showing the offensive team as a network, passing around the ball and the defensive team pressuring the ball owner. When in the graphical system mode the user can adjust six parameters which affect the overall positioning of the system: 

*Pass Range*: This affects the distance that the ball is passed and affects the positioning of the supporting players around the player in possession 

*Pass Rate*: Players pass the ball to the best positioned team mate when under pressure from a defender. When not under pressure this parameter determines the frequency of passing

*Pressure Range*: This defines the distance under which the player with possession of the ball feels pressure and passes the ball to his team mate

*Pressure Amount*: Is the only parameter that controls the defensive team. It determines the amount of aggression the defensive team has towards the player in possession result in more or less pressure

*Triangles*: Since Tikitaka is executed in a network of triangles this parameter determines how much the team adheres to form triangles resulting in more structure vs more freedom in positioning

*Responsiveness*: Every player follows a movement system based on a targeting system. The responsiveness determines how frequently an offensive players adjust or changes his target position, resulting in a more rigid or more chaotic behavior.

When the viewer is in the shader mode he can affect two parameters which affect the relation of one side to another radically transforming the overall representation of space allowing the viewer to experiment and reinterpret the dance of spaces.

Visit the [Wiki](https://github.com/seb-ctech/tikitaka/wiki) for a detailed progress report and results.