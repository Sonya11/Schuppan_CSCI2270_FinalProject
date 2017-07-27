#include <iostream>
#include "Supplement.hpp"

void header(){
    std::cout<<""<<std::endl;
    std::cout<<"WELCOME TO THE VIRTUAL RUBIX CUBE!"<<std::endl;
    std::cout<<""<<std::endl;
    std::cout<<"Note: "<<std::endl;
    std::cout<<"  R = red, Y = yellow, O = orange, B = blue, G = green, W = white"<<std::endl;
    std::cout<<"  The cube is to be viewed as if it folds along the"<<std::endl;
    std::cout<<"  dotted lines INTO the page"<<std::endl;
    std::cout<<"        (i.e. face 6 is on the top when folded and face 1" <<std::endl;
    std::cout<<"        is on the bottom when folded)"<<std::endl;
    std::cout<<"  The side numbers correlating to cube are shown to the right"<<std::endl;
    std::cout<<""<<std::endl;
    std::cout<<""<<std::endl;
    std::cout<<"Enter a valid number option from the menu below to manipulate the cube:"<<std::endl;
    std::cout<<""<<std::endl;
}

void advancedMenu(){
std::cout<<"-------- Menu --------"<<std::endl;
std::cout<<"1. Turn a Side"<<std::endl; //enter side you want to turn
std::cout<<"2. Undo Turn"<<std::endl;
std::cout<<"3. Scramble Cube"<<std::endl;
std::cout<<"4. Solve Cube"<<std::endl;
std::cout<<"5. View Past Turns"<<std::endl;
std::cout<<"6. Quit Program"<<std::endl;
std::cout<<""<<std::endl;
}

void options(){ //pop_back
std::cout<<""<<std::endl;
std::cout<<"Action completed!"<<std::endl;
std::cout<<"Enter a valid menu number. If you would like to view the menu again, enter 0."<<std::endl;
}
