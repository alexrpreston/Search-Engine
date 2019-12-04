#include "userinterface.h"
using namespace std;
#include "iostream"
userInterface::userInterface(){
    int choice = 0;
    do{
        cout << "1. Maintence mode" << "\n";
        cout << "2. Interactive mode" << "\n";
        cout << "3. Exit " << "\n";
        cout << "Enter an option: ";
        cin >> choice;
        //Implement try catch to test if the choice is not a number
        switch(choice){
            case 1:
                maintenanceMode();
                break;
            case 2:
                interactiveMode();
                break;
            case 3:
                break;
        default:
                cout << "Not a valid option" << "\n\n\n\n";
        }
    }while(choice != 3);
}

void userInterface::maintenanceMode()
{

}

void userInterface::interactiveMode()
{

}
