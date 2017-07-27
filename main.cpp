#include <iostream>
#include <stdlib.h>
#include "RubixCube.hpp"
#include "Supplement.hpp"

int main()
{
    //displaying information for user:
    header();
    advancedMenu();
    //creating an instance of the rubix cube graph object:
    rubixGraph graphObj;
    //building and displaying the cube:
    graphObj.buildCube();
    graphObj.printCube();

    int option;
    while(option != 6){
        //recieving menu number input from user:
        std::cin>>option;
        std::cin.clear();
        std::cin.ignore();
        switch(option){
            case 7:{ //display menu
                advancedMenu();
                break;
            }
            case 1:{ //turn a side
                int side;
                std::string direction;
                //used to check if the user entered a valid response:
                int validSideNumbers[6] = {1,2,3,4,5,6};
                //flags for whether or not the user entered a valid response:
                bool isValidSide = false;
                bool isValidDirection = false;

                std::cout<<"Enter the side you would like to turn: ";
                while(isValidSide == false){
                    //receiving side input from user
                    std::cin>>side;
                    std::cin.clear();
                    std::cin.ignore();
                    //checking that side is a valid number (1-6)
                    for(int i = 0; i < 6; i++){
                        if(side == validSideNumbers[i]){
                            isValidSide = true;
                            break;
                        }
                    }
                    //if side is not a valid number, the user is prompted for another side value
                    if(isValidSide == false){
                        std::cout<<"Invalid side - choose again: ";
                    }
                }
                std::cout<<"Enter 'R' to turn side "<<side<<" right, or 'L' to turn side "<<side<<" left: ";
                while(isValidDirection == false){
                    //receiving input form user for direction he/she would like the side to be turned
                    std::cin>>direction;
                    std::cin.clear();
                    std::cin.ignore();

                    if(direction == "L"){
                        isValidDirection = true;
                        graphObj.retrieveAction(side, direction); //pushing the side and the direction of rotation to the stack
                        std::cout<<""<<std::endl; //(formatting)
                        std::cout<<""<<std::endl; //(formatting)
                        std::cout<<"Turning side "<<side<<" to the left:"<<std::endl; //printing information on processes to user
                        //if the input direction is L (aka left) the side is tuned left and is printed:
                        graphObj.turnLeft(side);
                        graphObj.printCube();
                    }else if(direction == "R"){
                        isValidDirection = true;
                        graphObj.retrieveAction(side, direction); //pushing the side and the direction of rotation to the stack
                        std::cout<<""<<std::endl; //(formatting)
                        std::cout<<""<<std::endl; //(formatting)
                        std::cout<<"Turning side "<<side<<" to the right:"<<std::endl; //printing information on processes to user
                        //if the input direction is R (aka right) the side is tuned left and is printed:
                        graphObj.turnRight(side);
                        graphObj.printCube();
                    }else{
                        std::cout<<"Invalid direction - choose again: "; //if input direction is not R or L then it is invalid input and the user is prompted for another input
                    }
                }
                options(); //displays next action options to user
                break;
            }
            case 2:{
                //undo turns
                if(graphObj.reverseLastTurn()){ //checks if stack is empty and reverses last turn
                    graphObj.printCube(); //if stack not empty, the cube is printed
                }
                options(); //displays  next action options to user
                break;
            }
            case 3:{ //scramble cube
                std::string toContinue;
                bool isValidInput = false;
                std::cout<<"If you scramble the cube, all of your past turns will be erased."<<std::endl;
                std::cout<<"Would you like to continue? (Y/N) ";
                while (isValidInput == false){ //checking if the user entered valid input
                  std::cin>>toContinue; //revieving input from user
                  std::cin.clear();
                  std::cin.ignore();
                  if(toContinue.compare("Y") == 0){ //if the user enters Y, then the cube will be scrambled
                    isValidInput = true; //Y is a valid input
                    std::cout<<""<<std::endl; //(formatting)
                    std::cout<<"Scrambled cube: "<<std::endl;
                    //scrambles the cube and prints it:
                    graphObj.scrambleCube(); //(scramble algorithm implemented in a way that the cube is still solvable - view function for more info)
                    graphObj.printCube();
                    options(); //displays next action options to user
                  }else if(toContinue.compare("N") == 0){ //if user enters N, the scramble function will not be called
                    isValidInput = true; //N is a vlaid input
                    std::cout<<""<<std::endl; //(formatting)
                    std::cout<<"Cancelling cube scramble"<<std::endl;
                    options(); //displays next action options to user
                  }
                  if(isValidInput == false){ //if the inout is not N or Y, it is inavlid input
                    std::cout<<"Invalid input - enter Y or N: "; //prompts user for a valid input
                  }
                }
                break;
            }
            case 4:{ //solve cube
                std::string toContinue;
                bool isValidInput = false;
                std::cout<<"If you solve the cube, all of your past turns will be erased."<<std::endl;
                std::cout<<"Would you like to continue? (Y/N) ";
                while (isValidInput == false){ //checking if the user entered valid input
                  std::cin>>toContinue; //revieving input from user
                  std::cin.clear();
                  std::cin.ignore();
                  if(toContinue.compare("Y") == 0){ //if the user enters Y, then the cube will be solved
                    isValidInput = true; //Y is a valid input
                    std::cout<<""<<std::endl; //(formatting)
                    std::cout<<"Solved cube: "<<std::endl;
                    //solves the cube and prints it:
                    graphObj.solveCube();
                    graphObj.printCube();
                  }else if(toContinue.compare("N") == 0){ //if user enters N, the solve function is not called
                    isValidInput = true; //N is a vlaid input
                    std::cout<<""<<std::endl; //(formatting)
                    std::cout<<"Cancelling cube solve"<<std::endl;
                  }
                  if(isValidInput == false){ //if the inout is not N or Y, it is inavlid input
                    std::cout<<"Invalid input - enter Y or N: "; //prompts user for a valid input
                  }
                }
                options(); //displays next action options to user
                break;
            }
            case 5:{ //view past actions
                graphObj.displayPastActions();
                options(); //displays next action options to user
                break;
            }
            case 6:{ //quits the program by exiting the while loop
                std::cout<<"Goodbye!"<<std::endl;
                break;
            }
            default:{ //invalid input checker
                std::cout<<"Invalid input - choose again"<<std::endl;
            }
        }
    }
return 0;
}
