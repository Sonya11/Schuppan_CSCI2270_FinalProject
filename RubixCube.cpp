#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <sstream>
#include "RubixCube.hpp"

//graph implementation
rubixGraph::rubixGraph(){}
rubixGraph::~rubixGraph(){}
rubixStack::~rubixStack(){}

vertex* rubixGraph::searchVertex(std::string name){
    for(uint8_t i = 0; i < vertices.size(); i++){
        if(vertices[i].squareName == name){
            return &vertices[i];
        }
    }
    //if gone through all verticies and still not found:
    return nullptr;
}

void rubixGraph::insertVertex(std::string name, std::string color, int side, bool isRight, bool isTop){ //inserting vertex into vertices vector
    bool found = false;
     for(uint8_t i = 0; i < vertices.size(); i++){
        if(name.compare(vertices[i].squareName) == 0){
            found = true;
            break;
        }
     }
     if (found == false){ //only insert a new vertex if key was not found
        vertex newVertex(name, color, side, isRight, isTop); //create new vertex
        vertices.push_back(newVertex);
     }
}

void rubixGraph::insertEdge(std::string name1, std::string name2, int relationship, int leftInPair){
    //NOTE: name1 is not necessarily before name2
    bool edgeExists = false;
    for(uint8_t i = 0; i < vertices.size(); i++){
        if(name1.compare(vertices[i].squareName) == 0){ //if == 0 then they are equal
            for(uint8_t j = 0; j < vertices.size(); j++){
                if((name2.compare(vertices[j].squareName) == 0) && (i != j)){
                    //to check if the edge already exists:
                    for(uint8_t k = 0; k < vertices[i].adj.size(); k++){
                        if(vertices[i].adj[k].ptr2v == &vertices[j]){ //aka if the edge ALREADY exists
                            if(leftInPair != -1){
                                //access the adjacent and set equal to right of pair or left of pair
                                vertices[i].adj[k].isLeftInPair = leftInPair;
                            }
                            edgeExists = true;
                        }
                    }
                    if(!edgeExists){
                        adjacent adjV1;
                        adjV1.ptr2v = &vertices[j];
                        adjV1.isFaceShared = relationship;
                        adjV1.isLeftInPair = leftInPair;
                        vertices[i].adj.push_back(adjV1);
                        //now vertices[i] is linked to vertices[j], but now need to do vice versa
                        adjacent adjV2;
                        adjV2.ptr2v = &vertices[i];
                        adjV2.isFaceShared = relationship;
                        adjV2.isLeftInPair = leftInPair;
                        vertices[j].adj.push_back(adjV2);
                    }
                }
            }
        }
    }
}

 void rubixGraph::scrambleCube(){
     //scramble algorithm implemented in a way that the cube is still solvable - uses the turn functions instead of simply randomly moving around all the colors
    int randNum2, randNum3;
    int randNum1 = rand()%14+7;//for how many times to do the entire process below (7 to 20 times)
    for(int i = 0; i < randNum1; i++){
        randNum2 = rand()%4; //for number of times to turn the same side (0 to 3 times)
        randNum3 = rand()%6+1; //for which side to turn (side 1 - 6)
        for(int i = 0; i < randNum2; i++){
            turnRight(randNum3);
        }
        randNum2 = rand()%4; //for number of times to turn the same side (0 to 3 times)
        randNum3 = rand()%6+1; //for which side to turn (side 1 - 6)
        for(int i = 0; i < randNum2; i++){
            turnLeft(randNum3);
        }
    }
 }

 void rubixGraph::solveCube(){
    vertices.clear();//clears vertices to start from beginning again
    buildCube(); //rebuilds cube
 }

void rubixGraph::turnRight(int sideNumber){
    //declaring pointer for all adjacent face vertices
    vertex* topLeftV; vertex* topRightV; vertex* bottomLeftV; vertex* bottomRightV;
    //find vertices that have same side number as sideNum(aka find the face vertices):
    for(uint8_t i = 0; i < vertices.size(); i++){
        if(vertices[i].sideNum == sideNumber){
            if(!vertices[i].isRight && vertices[i].isTop){ //if top left square of face
                topLeftV = &vertices[i];
            }else if(vertices[i].isRight && vertices[i].isTop){ //if top right square of face
                topRightV = &vertices[i];
            }else if(!vertices[i].isRight && !vertices[i].isTop){ //if bottom left square of face
                bottomLeftV = &vertices[i];
            }else if(vertices[i].isRight && !vertices[i].isTop){ //if bottom right square of face
                bottomRightV = &vertices[i];
            }
        }
    }
    //declaring pointer for all adjacent corner vertices
    adjacent* firstAdjTL; adjacent* secondAdjTL; adjacent* firstAdjTR; adjacent* secondAdjTR;
    adjacent* firstAdjBL; adjacent* secondAdjBL; adjacent* firstAdjBR; adjacent* secondAdjBR;
    for(uint8_t i = 0; i < topLeftV->adj.size(); i++){
        //find corner vertices and order the adjacent corner vertices based on their right or left orientation with respect to the face vertex they are linked to
        if(topLeftV->adj[i].isFaceShared == 0){
            if(topLeftV->adj[i].isLeftInPair == 0){
                firstAdjTL = &topLeftV->adj[i];
            }else{
                secondAdjTL = &topLeftV->adj[i];
            }
        }
        if(topRightV->adj[i].isFaceShared == 0){
            if(topRightV->adj[i].isLeftInPair == 0){
                firstAdjTR = &topRightV->adj[i];
            }else{
                secondAdjTR = &topRightV->adj[i];
            }
        }
        if(bottomRightV->adj[i].isFaceShared == 0){
            if(bottomRightV->adj[i].isLeftInPair == 0){
                firstAdjBR = &bottomRightV->adj[i];
            }else{
                secondAdjBR = &bottomRightV->adj[i];
            }
        }
        if(bottomLeftV->adj[i].isFaceShared == 0){
            if(bottomLeftV->adj[i].isLeftInPair == 0){
                firstAdjBL = &bottomLeftV->adj[i];
            }else{
                secondAdjBL = &bottomLeftV->adj[i];
            }
        }
    }
    //everything that has an edge with the face is turned:
    std::string colorSaver;
    //swapping colors for face squares
    colorSaver = topRightV->color;
    topRightV->color = topLeftV->color;
    topLeftV->color = bottomLeftV->color;
    bottomLeftV->color = bottomRightV->color;
    bottomRightV->color = colorSaver;

    //swapping colors for corner squares:
    colorSaver = firstAdjTR->ptr2v->color;
    firstAdjTR->ptr2v->color = firstAdjTL->ptr2v->color;
    firstAdjTL->ptr2v->color = firstAdjBL->ptr2v->color;
    firstAdjBL->ptr2v->color = firstAdjBR->ptr2v->color;
    firstAdjBR->ptr2v->color = colorSaver;

    colorSaver = secondAdjTR->ptr2v->color;
    secondAdjTR->ptr2v->color = secondAdjTL->ptr2v->color;
    secondAdjTL->ptr2v->color = secondAdjBL->ptr2v->color;
    secondAdjBL->ptr2v->color = secondAdjBR->ptr2v->color;
    secondAdjBR->ptr2v->color = colorSaver;
 }

 void rubixGraph::turnLeft(int sideNumber){
    //declaring pointer for all adjacent face vertices
    vertex* topLeftV; vertex* topRightV; vertex* bottomLeftV; vertex* bottomRightV;
    //find vertices that have same side number as sideNum(aka find the face vertices):
    for(uint8_t i = 0; i < vertices.size(); i++){
        if(vertices[i].sideNum == sideNumber){
            if(!vertices[i].isRight && vertices[i].isTop){ //if top left square of face
                topLeftV = &vertices[i];
            }else if(vertices[i].isRight && vertices[i].isTop){ //if top right square of face
                topRightV = &vertices[i];
            }else if(!vertices[i].isRight && !vertices[i].isTop){ //if bottom left square of face
                bottomLeftV = &vertices[i];
            }else if(vertices[i].isRight && !vertices[i].isTop){ //if bottom right square of face
                bottomRightV = &vertices[i];
            }
        }
    }
    //declaring pointer for all adjacent corner vertices
    adjacent* firstAdjTL; adjacent* secondAdjTL; adjacent* firstAdjTR; adjacent* secondAdjTR;
    adjacent* firstAdjBL; adjacent* secondAdjBL; adjacent* firstAdjBR; adjacent* secondAdjBR;
    for(uint8_t i = 0; i < topLeftV->adj.size(); i++){
        if(topLeftV->adj[i].isFaceShared == 0){
            //find corner vertices and order the adjacent corner vertices based on their right or left orientation with respect to the face vertex they are linked to
            if(topLeftV->adj[i].isLeftInPair == 0){
                firstAdjTL = &topLeftV->adj[i];
            }else{
                secondAdjTL = &topLeftV->adj[i];
            }
        }
        if(topRightV->adj[i].isFaceShared == 0){
            if(topRightV->adj[i].isLeftInPair == 0){
                firstAdjTR = &topRightV->adj[i];
            }else{
                secondAdjTR = &topRightV->adj[i];
            }
        }
        if(bottomRightV->adj[i].isFaceShared == 0){
            if(bottomRightV->adj[i].isLeftInPair == 0){
                firstAdjBR = &bottomRightV->adj[i];
            }else{
                secondAdjBR = &bottomRightV->adj[i];
            }
        }
        if(bottomLeftV->adj[i].isFaceShared == 0){
            if(bottomLeftV->adj[i].isLeftInPair == 0){
                firstAdjBL = &bottomLeftV->adj[i];
            }else{
                secondAdjBL = &bottomLeftV->adj[i];
            }
        }
    }
    //everything that has an edge with the face is turned:
    std::string colorSaver;
    //swapping colors for face squares
    colorSaver = bottomRightV->color;
    bottomRightV->color = bottomLeftV->color;
    bottomLeftV->color = topLeftV->color;
    topLeftV->color = topRightV->color;
    topRightV->color = colorSaver;

    //swapping colors for corner squares:
    colorSaver = firstAdjBR->ptr2v->color;
    firstAdjBR->ptr2v->color = firstAdjBL->ptr2v->color;
    firstAdjBL->ptr2v->color = firstAdjTL->ptr2v->color;
    firstAdjTL->ptr2v->color = firstAdjTR->ptr2v->color;
    firstAdjTR->ptr2v->color = colorSaver;

    colorSaver = secondAdjBR->ptr2v->color;
    secondAdjBR->ptr2v->color = secondAdjBL->ptr2v->color;
    secondAdjBL->ptr2v->color = secondAdjTL->ptr2v->color;
    secondAdjTL->ptr2v->color = secondAdjTR->ptr2v->color;
    secondAdjTR->ptr2v->color = colorSaver;
 }

void rubixGraph::buildCube(){
    //R = red, G = green, B = blue, Y = yellow, W = white, O = orange
    //1 = lowest square, 2 = square up one from lowest, 3 = right square, 4 = highest square, 5 = left square, 6 = middle square
    //squareNameList notation ex: TL1 = "Top Left (side)1"

    //initializing name, color, and side number lists
    const int numberOfSides = 6;
    const int numberOfSquares = 24;
    std::string colorArray[numberOfSides] = {"R","G","B","Y","W","O"};
    std::string squareNameList[numberOfSquares] = {"TL1","TL2","TL3","TL4","TL5","TL6","TR1","TR2","TR3","TR4","TR5","TR6",
                                                    "BL1","BL2","BL3","BL4","BL5","BL6","BR1","BR2","BR3","BR4","BR5","BR6"};
    int sideNumList[numberOfSides] = {1,2,3,4,5,6};

    //loading in the name, color, and side number to the graph
    for (int i = 0; i < numberOfSquares; i++){
        //matching vertex values with correct name:
        std::string currentName = squareNameList[i];
        if(currentName.find("R") != std::string::npos){ //if "R" is found in name
            if(currentName.find("T") != std::string::npos){ //if "T" is found in name
                insertVertex(currentName, colorArray[i%numberOfSides], sideNumList[i%numberOfSides], true, true);
            }else{ //if "T" is NOT found in name (if B)
                insertVertex(currentName, colorArray[i%numberOfSides], sideNumList[i%numberOfSides], true, false);
            }
        }else{ //if "R" is NOT found in name (if L)
            if(currentName.find("T") != std::string::npos){ //if "T" is found in name
                insertVertex(currentName, colorArray[i%numberOfSides], sideNumList[i%numberOfSides], false, true);
            }else{ //if "T" is NOT found in name (if B)
                insertVertex(currentName, colorArray[i%numberOfSides], sideNumList[i%numberOfSides], false, false);
            }
        }
    }
    //adding edges
    int shareFace;
    //if both vertices are on the SAME FACE
    for(int i = 0; i < numberOfSquares; i++){
        for(int j = 0; j < numberOfSquares; j++){
            if(vertices[i].sideNum == vertices[j].sideNum){
                shareFace = 1;
                insertEdge(vertices[i].squareName, vertices[j].squareName, shareFace, -1);
            }
        }
    }

    //if both vertices are NOT on SAME FACE, but are touching corners
    shareFace = 0;
    for(int j = 1; j <= numberOfSides; j++){
        cornerEdgeFill(j, shareFace);
    }
}

 void rubixGraph::cornerEdgeFill(int side, int isFaceShared){
    int edgeNum = 8;
    int squaresNum = 4;
    int leftInPair[edgeNum] = {1,1,1,1,0,0,0,0};
    //defining which names are associated with which side of the cube
    std::string side6Filling[edgeNum] = {"TL5", "TL4", "TL3", "TL2", "TR4", "TR3", "TR2", "TR5"};
    std::string vertex6Name[squaresNum] = {"TL6", "TR6", "BR6", "BL6"};
    std::string side5Filling[edgeNum] = {"TR4", "BL6", "BL2", "BL1", "TL6", "TL2", "TL1", "BR4"};
    std::string vertex5Name[squaresNum] = {"TL5", "TR5", "BR5", "BL5"};
    std::string side4Filling[edgeNum] = {"TR3", "TL6", "BL5", "BR1", "TR6", "TL5", "BL1", "BR3"};
    std::string vertex4Name[squaresNum] = {"TL4", "TR4", "BR4", "BL4"};
    std::string side3Filling[edgeNum] = {"TR2", "TR6", "BL4", "TR1", "BR6", "TL4", "BR1", "BR2"};
    std::string vertex3Name[squaresNum] = {"TL3", "TR3", "BR3", "BL3"};
    std::string side2Filling[edgeNum] = {"TR5", "BR6", "BL3", "TL1", "BL6", "TL3", "TR1", "BR5"};
    std::string vertex2Name[squaresNum] = {"TL2", "TR2", "BR2", "BL2"};
    std::string side1Filling[edgeNum] = {"BR5", "BR2", "BR3", "BR4", "BL2", "BL3", "BL4", "BL5"};
    std::string vertex1Name[squaresNum] = {"TL1", "TR1", "BR1", "BL1"};

    //inserting edges based on side values and unique names associated with each side
    switch(side){
    case 1:
        for(int i = 0; i < edgeNum; i++){
            insertEdge(vertex1Name[i%4], side1Filling[i], isFaceShared, leftInPair[i]);
        }
        break;
    case 2:
        for(int i = 0; i < edgeNum; i++){
            insertEdge(vertex2Name[i%4], side2Filling[i], isFaceShared, leftInPair[i]);
        }
        break;
    case 3:
        for(int i = 0; i < edgeNum; i++){
            insertEdge(vertex3Name[i%4], side3Filling[i], isFaceShared, leftInPair[i]);
        }
        break;
    case 4:
        for(int i = 0; i < edgeNum; i++){
            insertEdge(vertex4Name[i%4], side4Filling[i], isFaceShared, leftInPair[i]);
        }
        break;
    case 5:
        for(int i = 0; i < edgeNum; i++){
            insertEdge(vertex5Name[i%4], side5Filling[i], isFaceShared, leftInPair[i]);
        }
        break;
    case 6:
        for(int i = 0; i < edgeNum; i++){
            insertEdge(vertex6Name[i%4], side6Filling[i], isFaceShared, leftInPair[i]);
        }
        break;
    }
 }

void rubixGraph::printCube(){
    //to be viewed as if it folds along the dotted lines INTO the page (i.e. the middle face is on the top when folded and the lowest face is on the bottom when folded)
    //keep in mind that it is important to view the folding pattern in this way, or some sides might appear to rotate in the wrong direction
    std::cout<<""<<std::endl;
    std::cout<<"          "<<vertices[21].color<<" "<<vertices[15].color<<"            Side Numbers:             "<<std::endl; //10 spaces L/R
    std::cout<<"          "<<vertices[9].color<<" "<<vertices[3].color<<"                   4  "<<std::endl; //10 spaces L/R
    std::cout<<"          ---                 5 6 3  "<<std::endl; //10 spaces L/R
    std::cout<<"    "<<vertices[16].color<<" "<<vertices[4].color<<" | "<<vertices[5].color<<" "<<vertices[11].color<<" | "<<vertices[8].color<<" "<<vertices[20].color<<"             2  "<<std::endl; //4 spaces L/R
    std::cout<<"    "<<vertices[22].color<<" "<<vertices[10].color<<" | "<<vertices[17].color<<" "<<vertices[23].color<<" | "<<vertices[2].color<<" "<<vertices[14].color<<"             1     "<<std::endl; //4 spaces L/R
    std::cout<<"          ---                   "<<std::endl; //10 spaces L/R
    std::cout<<"          "<<vertices[1].color<<" "<<vertices[7].color<<"                    "<<std::endl; //||
    std::cout<<"          "<<vertices[13].color<<" "<<vertices[19].color<<"                     "<<std::endl; //||
    std::cout<<"          ---                    "<<std::endl; //||
    std::cout<<"          "<<vertices[0].color<<" "<<vertices[6].color<<"                    "<<std::endl; //||
    std::cout<<"          "<<vertices[12].color<<" "<<vertices[18].color<<"                     "<<std::endl; //||
    std::cout<<""<<std::endl;
    std::cout<<""<<std::endl;
}

 void rubixGraph::retrieveAction(int side, std::string direction){
    //convert integer to string
    std::stringstream s;
    s << side;
    std::string sideStr = s.str();
    //concatenate direction and side, and push to stack
    std::string completeAction = direction + sideStr;
    stackObj.push(completeAction);
 }

 void rubixGraph::displayPastActions(){
     if(!stackObj.isEmpty()){
         std::cout<<""<<std::endl;
         std::cout<<"Your Past Actions:"<<std::endl;
         std::cout<<"First -> ";
         stackObj.printStack();
         std::cout<<"<- Last"<<std::endl;
     }else{
        std::cout<<"You have no past turns."<<std::endl;
     }
 }

 bool rubixGraph::reverseLastTurn(){ //ex: L1
    std::string popped = stackObj.pop();
    if(popped != ""){ //if not empty
        std::string sideStr;
        std::string direction;
        //retrieve side and direction info
        sideStr = popped[1];
        direction = popped[0];
        std::stringstream s(sideStr);
        int side;
        s >> side;
        if(direction == "R"){ //if the user turned a side right, it must be turned left to undo it
            std::cout<<"Turning side "<<side<<" back to the left:"<<std::endl;
            turnLeft(side);
        }else{ //direction == L
            std::cout<<"Turning side "<<side<<" back to the right:"<<std::endl;
            turnRight(side);
        }
        return true;
    }else{
        std::cout<<"You have no past turns."<<std::endl;
        return false;
    }
 }

//stack ADT implementation:
bool rubixStack::isEmpty(){
    return(top == 0);
}

void rubixStack::push(std::string entry){
    entries.push_back(entry);
    top++;
}

std::string rubixStack::pop(){
    if(!isEmpty()){
        top--;
        std::string popped = entries[top];
        entries[top].erase();
        return popped;
    }else{
        return "";
    }
}

void rubixStack::printStack(){
    for(uint8_t i = 0; i < entries.size(); i++){
        std::cout<<entries[i]<<" ";
    }
}
