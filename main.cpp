/******************************************************************************
                Amanda Macrorie         13 DEC 
Final Project
*******************************************************************************/

#include "functions.h"

int main()
{
    int menuOption;
    int numLines = get_numLines("flights.txt");
    int numPlaces = numLines / 6;
    
    place myPlaces[numPlaces];                          //Create array of places
    int linkedPlaceCode1[numPlaces]; int linkedPlaceCode2[numPlaces];   //Create corresponding array of linked codes
    
    int r = get_Places("flights.txt", myPlaces, linkedPlaceCode1, linkedPlaceCode2);    //Reading file into array
    
    place* placesPtr[numPlaces];                //Create corresponding pointer array to places
    for (int i = 0; i < numPlaces; i++){
        placesPtr[i] = &myPlaces[i];
    }
    
    for (int i = 0; i < numPlaces; i++){
        for (int j = 0; j < numPlaces; j++){
            if (linkedPlaceCode1[i] == placesPtr[j]->pcode){        //Creating first link (link1) to other city
                placesPtr[i]->link1 = placesPtr[j];                 //Calculating distance to that linked city
                placesPtr[i]->d_link1 = calculate_Distance(placesPtr[i]->plng, placesPtr[j]->plng, placesPtr[i]->plat, placesPtr[j]->plat); 
            }
            if (linkedPlaceCode2[i] == placesPtr[j]->pcode){        //Creating second link (link2) to other city
                placesPtr[i]->link2 = placesPtr[j];                 //Calculating distance to that linked city
                placesPtr[i]->d_link2 = calculate_Distance(placesPtr[i]->plng, placesPtr[j]->plng, placesPtr[i]->plat, placesPtr[j]->plat);
            }
            if (linkedPlaceCode1[i] == 000){                    //Nulling link1 if not yet established
                placesPtr[i]->d_link1 = 0;
                placesPtr[i]->link1 = NULL;
            }
            if (linkedPlaceCode2[i] == 000){                    //Nulling link2 if not yet established
                placesPtr[i]->d_link2 = 0;
                placesPtr[i]->link2 = NULL;
            }
        }
    }
    
    cout << endl << "ORIGINS IN THE DATABASE 'flights.txt' AND THEIR DESTINATIONS: " << endl;
lup:
    display_Places(placesPtr, numPlaces);                   //Displaying original data, and then displaying data as user edits information
    cout << endl << endl;
    
    cout << "MENU ITEMS:" << endl << "1 - REMOVE DESTINATION" << endl << "2 - ADD OR CHANGE DESTINATION" << endl << "3 - FIND ROUTE" << endl << endl;
    cout << "Enter numbers 1 - 3 to use menu or 9 to EXIT:" << endl;
    cin >> menuOption;
    switch(menuOption){
        case 1:
            remove_Link(placesPtr, numPlaces);                  //Removing a link
            break;
        case 2:
            change_Link(placesPtr, numPlaces);                  //Adding/changing a link
            break;
        case 3:
            find_Route(placesPtr, numPlaces);                             //Finding route
            break;
        case 9: goto ext;                                       //Exiting menu
        default:
            cout << "INVALID MENU OPTION" << endl;
    }
    cout << endl << "Enter any number to continue: ";
    int proceed;
    cin >> proceed;
    cout << endl;
    goto lup;                                           //Looping to allow user to continue making changes until user exits menu
    
ext:                                                    //Exiting menu
    cout << "You have exited the menu." << endl;
    
    
    for (int i = 0; i < numPlaces; i++){
        place* temp1 = placesPtr[i]->link1; place* temp2 = placesPtr[i]->link2;
        if (placesPtr[i]->d_link1 == 0){
            linkedPlaceCode1[i] = 000;
            linkedPlaceCode2[i] = temp2->pcode;
        }
        if (placesPtr[i]->d_link2 == 0){
            linkedPlaceCode2[i] = 000;
            linkedPlaceCode1[i] = temp1->pcode;
        }
        if ((placesPtr[i]->d_link1 != 0) && (placesPtr[i]->d_link2 != 0)){
            linkedPlaceCode1[i] = temp1->pcode;
            linkedPlaceCode2[i] = temp2->pcode;
        }
    }
    
    
    string fname = "flightsUPDATED.txt";
    ofstream updateFile(fname, ios::out);
    for (int i = 0; i < numPlaces; i++){
        place* temp1 = myPlaces[i].link1; place* temp2 = myPlaces[i].link2;
        updateFile << myPlaces[i].pcode << endl;
        updateFile << myPlaces[i].pname << endl;
        updateFile << myPlaces[i].plat << endl;
        updateFile << myPlaces[i].plng << endl;
        updateFile << linkedPlaceCode1[i] << endl;
        updateFile << linkedPlaceCode2[i] << endl;
    }
    
    cout << "Your edits have been written to the new file 'flightsUPDATED.txt'.  Thank you for using this program!" << endl;

    return 0;
}
