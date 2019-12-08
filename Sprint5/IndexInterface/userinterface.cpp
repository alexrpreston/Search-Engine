#include "userinterface.h"
using namespace std;
#include "documentparser.h"
#include "iostream"
#include "IndexInterface.h"
#include "queryprocessor.h"
#include "AVLTree.h"
#include "HashMap.h"
#include "stdlib.h"
userInterface::userInterface(){
    documentParser parser("/home/student/Desktop/scotus-small/", II);
    queryProcessor processor(II);

    mainMenu(parser, processor);
}

void userInterface::mainMenu(documentParser &parser, queryProcessor &processor){
    int choice = 0;
    do{
        cout << "1. Maintence mode" << "\n";
        cout << "2. Interactive mode" << "\n";
        cout << "3. Exit " << "\n" ;
        cout << "Enter an option: ";
        cin >> choice;
        system("clear");
        //Implement try catch to test if the choice is not a number
        switch(choice){
            case 1:
                maintenanceMode(parser, processor);
                break;
            case 2:
                interactiveMode(parser, processor);
                break;
            case 3:
                break;
        default:
                cout << "Not a valid option" << "\n\n\n\n";
        }
    }while(choice != 3);
}

void userInterface::maintenanceMode(documentParser &parser, queryProcessor &processor){
    int choice = 0;
    do{
        cout << "1. Add Opinions to the index." << "\n";
        cout << "2. Clear the Index." << "\n";
        cout << "3. Parse the corpus and populate index" << "\n";
        cout << "4. Go back to main menu." << "\n";
        cout << "5. Exit " << "\n";
        cout << "Enter an option: ";
        cin >> choice;
        system("clear");
        if(choice == 1){
                string folderPath;
                cout << "Enter a folder path: ";
                cin >> folderPath;
                char * formatedFilePath = &folderPath[0];
                parser.addOpinions(formatedFilePath);

                cout << "Opinions added to corpus" << endl;
        }
        if(choice == 2){

        }
        if(choice == 3){
            //IndexInterface.clear()
            //documentParser("/home/student/Desktop/scotus-med/", 0);
        }
        if(choice == 4){
            mainMenu(parser, processor);
        }
        
        
    }while(choice != 5);
}

void userInterface::interactiveMode(documentParser &parser, queryProcessor &processor){
    int choice = 0;
    do{
        cout << "1. Choose Data Structure Type." << "\n";
        cout << "2. Enter a Query." << "\n";
        cout << "3. Print Basic Statistics" << "\n";
        cout << "4. Go back to main menu." << "\n";
        cout << "5. Exit " << "\n";
        cout << "Enter an option: ";
        cin >> choice;
        system("clear");
        if(choice == 1){
            //if we don't have a persistent index, print out an error message
            int dataStrChoice = 0;
            cout << "1. Load Persistent Index into AVL Tree." << "\n";
            cout << "2. Load Persistent Index into Hash Table." << "\n";
            cout << "Enter an option: ";
            cin >> dataStrChoice;
            //Chooses Data type
            mainMenu(parser, processor);
        }
        if(choice == 2){
            string query = "";
            cout << "=== Search the Corpus ===" << "\n\n";
            cout << "Enter Query: ";
            cin.ignore();
            getline(cin, query);
            processor.querySearch(query);
        }
        if(choice == 3){
            cout << "Total number of opinions indexed: " << "\n";
            cout << "Average number of words indexed per opinion: " << "\n";
            cout << "Average time to parse each opinion: " << " nanoseconds.";
            cout << "Top 50 most frequent word: " << "\n";


        }
        if(choice == 4){
            mainMenu(parser, processor);
        }


    }while(choice != 5);
}


