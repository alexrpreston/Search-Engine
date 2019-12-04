#include "userinterface.h"
using namespace std;
#include "documentparser.h"
#include "iostream"
#include "IndexInterface.h"
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

void userInterface::maintenanceMode(){
    int choice = 0;
    do{
        cout << "1. Add Opinions to the index." << "\n";
        cout << "2. Clear the Index." << "\n";
        cout << "3. Parse the corpus and populate index" << "\n";
        cout << "4. Go back to main menu." << "\n";
        cout << "5. Exit " << "\n";
        cout << "Enter an option: ";
        cin >> choice;
        
        if(choice == 1){
            
                string folderPath;
                cout << "Enter a folder path: ";
                cin >> folderPath;  
                char * formatedFilePath = &folderPath[0];
                documentParser(formatedFilePath, 0);
                cout << "Opinions added to corpus" << endl;
        }
        if(choice == 2){
            //IndexInterface.clear()
        }
        if(choice == 3){
            //IndexInterface.clear()
            documentParser("/home/student/Desktop/scotus-med/", 0);
        }
        if(choice == 4){
            userInterface();
        }
        
        
    }while(choice != 5);
}

void userInterface::interactiveMode()
{

}
