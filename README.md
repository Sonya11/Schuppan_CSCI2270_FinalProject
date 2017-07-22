# Schuppan_CSCI2270_FinalProject
   Last semster in my freshman projects class, my team and I created a fully-fucntional 2ft by 2ft by 2ft Rubix Cube as a toy to support physical activity in children. Instead of building this cube to physically rotate, I implemented an Arduino program in which LEDs in each square change color based on RPG knob input. This, in turn, simulates the physical rotations of a Rubix Cube. Since I did not have any formal knowledge of data strctures at the time that I created this, I implemented this program primarily with crude array manipulations. Since then, I have been attentive to finding a better method to do this. 
   For my final project, I will recreate this algorithm by instead using a graph data structure. In this structure, the 24 squares of the cube will represent the vertices of the graph, and relationships between the squares of the cube will be determined by whether or not they share the same cube face. Additionally, I will use a queue to store information in a bredth first traversal of the vertices, as well as to store and manipulate the 6 colors of the rubix cube. I will implement a print-out of an "unfolded cube" with capital letters to represent colors that will be used to show the various actions being done to the cube, such as left and right face rotations, color changes, scrambling, and solving.
