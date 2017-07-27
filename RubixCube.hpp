#include <iostream>
#include <vector>

#ifndef RUBIXCUBE_HPP_INCLUDED
#define RUBIXCUBE_HPP_INCLUDED

class rubixStack{
private:
    int top;//to define the index of where the next element in the stack would be placed
    std::vector<std::string>entries; //initializing vector to store all entries in stack
public:
    rubixStack(int _top = 0):top(_top){}
    ~rubixStack();
    bool isEmpty(); //to check if stack is empty
    void push(std::string entry); //to push a value to stack
    std::string pop(); //to pop a value from stack
    void printStack(); //to print the stack from first to last

};
struct adjacent;
struct vertex{
    std::string squareName; // to store unique name for each of the 24 squares in cube (ex: TL1 = Top Left (side)1, TR1 = Top Right side(1), etc)
    std::vector<adjacent>adj; //to store the adjacent vertices
    std::string color; //to store the color associated with each square of the rubix cube
    //to fully identify "fingerprint" of each square:
    int sideNum; //to identify side number of square
    bool isRight; //to identify if square is to the right in programmer-defined (me) oreintation of cube
    bool isTop; //to identify if square is on the top in programmer-defined (me) oreintation of cube
    vertex(std::string _squareName = " ", std::string _color = " ", int _sideNum = -1,
           bool _isRight = false, bool _isTop = false):squareName(_squareName),color(_color),
           sideNum(_sideNum), isRight(_isRight),isTop(_isTop){}
};
struct adjacent{
    int isFaceShared; //"weight" of edge between two vertices is defined by whether the two squares are on the same face or are touching across a corner
    vertex* ptr2v; //points to vertex it shares and edge with
    int isLeftInPair; //to keep track of whether a corner square is on the right side or left side of the face square it shares an edge with
    adjacent(int _isFaceShared = -1, vertex* _ptr2v = nullptr, int _isLeftInPair = -1):
            isFaceShared(_isFaceShared), ptr2v(_ptr2v),isLeftInPair(_isLeftInPair){}
};

class rubixGraph{
private:
    rubixStack stackObj; //stack object to be used for storing rotations
    void insertVertex(std::string name, std::string color, int side, bool isRight, bool isTop);//inserts a vertex into vertices vector
    void insertEdge(std::string name1, std::string name2, int relationship, int leftInPair); //adds edge between two vertices and assigns a binary relationship value for whether or not name1 and name2 are on same cube face
    vertex* searchVertex(std::string name); //searches for a name inside vertices vector
    void cornerEdgeFill(int side, int isFaceShared); //fills the edges or the corner cases
    std::vector<vertex>vertices; //initializes the vector in which all the vertices are stored
public:
    rubixGraph();
    ~rubixGraph();
    void buildCube(); //builds the cube with pre-set names, colors, and side numbers
    void solveCube(); //restarts cube with original color locations when cube was built
    void turnRight(int sideNumber); //turns a face of the cube (defined by sideNumber) to the right
    void turnLeft(int sideNumber); //turns a face of the cube (defined by sideNumber) to the left
    void printCube(); //prints the cube
    void print(); //shows proper layout for printing cube
    void scrambleCube(); //uses randomization to turn sides of the cube left and right (does so in a way that the cube can still be solved)
    bool reverseLastTurn(); //pops 1 element off stack each time it is called and does necessary actions to cube
    void retrieveAction(int side, std::string direction); //pushes actions to stack
    void displayPastActions(); //prints the stack vector that was filled in retrieve past actions
};


#endif // RUBIXCUBE_HPP_INCLUDED
