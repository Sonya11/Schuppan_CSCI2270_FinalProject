# The Virtual Rubix Cube 
## Sonya Schuppan
      Last semster in my freshman projects class, my team and I created a fully-fucntional 2ft by 2ft by 2ft Rubix Cube as a toy to support physical activity in children. Instead of building this cube to physically rotate, I implemented an Arduino program in which LEDs in each square change color based on RPG knob input. This then simulates the physical rotations of a Rubix Cube. Since I did not have any formal knowledge of data strctures at the time that I created this, I implemented this program primarily with crude array manipulations. Since then, I have been attentive to finding a better method to do this. 
      For my final project, I created a 2 x 2 Rubix Cube algorithm by instead using a graph data structure. In this structure, the 24 squares of the cube represent the vertices of the graph, and relationships between the squares of the cube are determined by whether or not they share the same cube face. Additionally, I used a stack to store information on the user's actions and implement a "reverse turn" feature that allows the user to reverse his or her actions. The cube is displayed as an "unfolded cube" with capital letters to represent the colors of each of the 24 squares. This display is used to demonstrate the various actions applied to the cube including left and right face rotations, scrambling, and solving. Note that the cube displayed in the program is to be veiwed as if it folds into the page as is described at the top of the running program. If it is not vewied in this way, some sides could appear to roatate incorrectly.

### How to Run the Program
	To run this program, clone the repository onto your local machine using the URL: https://github.com/Sonya11/Schuppan_CSCI2270_FinalProject.git. Locate the cloned files inside the Schuppan_CSCI2270_FinalProject directory. Compile the code in the command line with C++11 using the command:g++ -std=c++11 RubixCube.hpp RubixCube.cpp Supplement.hpp Supplement.cpp main.cpp -o Schuppan_CSCI2270_FinalProject and to run the program enter ./Schuppan_CSCI2270_FinalProject.
### System Requirements 
	There are no known system requirements. The program has been tested to run on both Windows and Linux operating systems.
### Dependancies 
	There are no third-party dependancies for this program.
### Open Issues/Bugs
	There are no open issues or bugs in this program. 
