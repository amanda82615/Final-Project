#include <string>
#include <cmath>
#include <fstream>
#include <iostream>
using namespace std;

struct place{
    int pcode;
    string pname;
    double plat;
    double plng;
    double d_link1;
    double d_link2;
    place* link1;
    place* link2;
};

int get_numLines(string fname){
    fstream newfile("flights.txt", ios::in);
    int n = 0;
    string tp;
    while (!newfile.eof()){
        getline(newfile, tp);
        n++;
    }
    newfile.close();
    return n;
}

int get_Places(string fname, place myPlaces[], int linkedPlaceCode1[], int linkedPlaceCode2[]){
    fstream newfile(fname, ios::in);
    int n = 0; string tp;
    while(!newfile.eof()){                                  //Reading file into arrays
        getline(newfile, tp);
        myPlaces[n].pcode = stoi(tp);
        getline(newfile, tp);
        myPlaces[n].pname = tp;
        getline(newfile, tp);
        myPlaces[n].plat = stod(tp);
        getline(newfile, tp);
        myPlaces[n].plng = stod(tp);
        getline(newfile, tp);
        linkedPlaceCode1[n] = stoi(tp);
        getline(newfile, tp);
        linkedPlaceCode2[n] = stoi(tp);
        n++;
    }
    newfile.close();
    return n;
}

void display_Places(place* placesPtr[], int numPlaces){
    place* temp1; place* temp2;
    for (int i = 0; i < numPlaces; i++){                        //Printing all city info
        cout << placesPtr[i]->pcode << " " << placesPtr[i]->pname << " (Latitude: " << placesPtr[i]->plat << "   Longitude: " << placesPtr[i]->plng << ")" << endl;
        if (placesPtr[i]->d_link1 != 0){
            temp1 = placesPtr[i]->link1;
            cout << "       Destination " << temp1->pcode << ": " << temp1->pname << " " << placesPtr[i]->d_link1 << " miles" << endl;
        }
        if (placesPtr[i]->d_link2 != 0){
            temp2 = placesPtr[i]->link2;
            cout << "       Destination " << temp2->pcode << ": " << temp2->pname << " " << placesPtr[i]->d_link2 << " miles" << endl;
        }
    }
}

double calculate_Distance(double lng1, double lng2, double lat1, double lat2){
    double distance = 0.0;
    distance = 60 * sqrt(pow(lng1 - lng2, 2) + pow(lat1 - lat2, 2));        //calculating distance
    return distance;
}

void remove_Link(place* placesPtr[], int numPlaces){
    int a; int b; int n;
    cout << "Enter the 3-digit origin code to edit: " << endl;
    cin >> a;
    if ((a < 101) || (a > 108)) {cout << "NOT A VALID CODE" << endl; return;}
    cout << "Enter the 3-digit destination code to remove: " << endl;
    cin >> b;
    if ((b < 101) || (b > 108) || (b == a)) {cout << "NOT A VALID CODE" << endl; return;}
    for (int i = 0; i < numPlaces; i++){
        if (placesPtr[i]->pcode == a){
            if ((placesPtr[i]->d_link1 == 0) || (placesPtr[i]->d_link2 == 0)){
                cout << placesPtr[i]->pname << " only has one destination and it cannot be removed.  Use menu to add or change a destination." << endl;
                return;
            }
            for (int j = 0; j < numPlaces; j++){
                if (placesPtr[j]->pcode == b){
                    if(placesPtr[j] == placesPtr[i]->link1){                //If user chose to remove 1st destination, nulling the first link
                        placesPtr[i]->d_link1 = 0;
                        placesPtr[i]->link1 = NULL;
                        cout << "The destination " << placesPtr[j]->pname << " has been successfully removed from the origin " << placesPtr[i]->pname << ". " << endl;
                        return;
                    }
                    if(placesPtr[j] == placesPtr[i]->link2){                //If user chose to remove 2nd destination, nulling the second link
                        placesPtr[i]->d_link2 = 0;
                        placesPtr[i]->link2 = NULL;
                        cout << "The destination " << placesPtr[j]->pname << " has been successfully removed from the origin " << placesPtr[i]->pname << ". " << endl;
                        return;
                    }
                }
            }
        }
    }
}

void change_Link(place* placesPtr[], int numPlaces){                    //Adding a destination if a link is empty, changing a link if both are full
    int a; int b; int c; int d; int n;
    cout << "Enter the 3-digit origin code to edit: " << endl;
    cin >> a;
    if ((a < 101) || (a > 108)) {cout << "NOT A VALID CODE" << endl; return;}
    for (int i = 0; i < numPlaces; i++){
        place* temp1 = placesPtr[i]->link1; place* temp2 = placesPtr[i]->link2;
        if (placesPtr[i]->pcode == a){
            if (placesPtr[i]->d_link1 == 0){                                            //Adding a destination to link1 if link1 is empty
                cout << "Enter the 3-digit destination code to add: " << endl;
                cin >> c;
                if ((c < 101) || (c > 108) || (c == a) || (c == temp2->pcode)) {cout << "NOT A VALID CODE" << endl; return;}
                for (int j = 0; j < numPlaces; j++){
                    if (placesPtr[j]->pcode == c){
                        placesPtr[i]->d_link1 = calculate_Distance(placesPtr[i]->plng, placesPtr[j]->plng, placesPtr[i]->plat, placesPtr[j]->plat);
                        placesPtr[i]->link1 = placesPtr[j];
                        cout << "The destination " << placesPtr[j]->pname << " has been successfully added to the origin " << placesPtr[i]->pname << "." << endl;
                        return;
                    }
                }
            }
            if (placesPtr[i]->d_link2 == 0){                                            //Adding a destination to link2 if link2 is empty
                cout << "Enter the 3-digit destination code to add: " << endl;
                cin >> c;
                if ((c < 101) || (c > 108) || (c == a) || (c == temp1->pcode)) {cout << "NOT A VALID CODE" << endl; return;}
                for (int j = 0; j < numPlaces; j++){
                    if (placesPtr[j]->pcode == c){
                        placesPtr[i]->d_link2 = calculate_Distance(placesPtr[i]->plng, placesPtr[j]->plng, placesPtr[i]->plat, placesPtr[j]->plat);
                        placesPtr[i]->link2 = placesPtr[j];
                        cout << "The destination " << placesPtr[j]->pname << " has been successfully added to the origin " << placesPtr[i]->pname << "." << endl;
                        return;
                    }
                }
            }
            if ((placesPtr[i]->d_link1 != 0) && (placesPtr[i]->d_link2 != 0)){              //If both links full, user decides which link to overwrite
                cout << "This origin has 2 destinations. Enter the 3-digit code of the destination to overwrite: " << endl;
                cin >> c;
                if ((c != temp1->pcode) && (c != temp2->pcode)) {cout << "NOT A VALID CODE - destination already exists" << endl; return;}
                cout << "Enter the 3-digit of the destination to add: " << endl;
                cin >> b;
                if ((b < 101) || (b > 108) || (b == a)) {cout << "NOT A VALID CODE" << endl; return;}
                if ((b == temp2->pcode) || (b == temp1->pcode)) {cout << "NOT A VALID CODE - destination already exists" << endl; return;}
                
                if (temp1->pcode == c){                                     //Overwrite link1
                    for (int j = 0; j < numPlaces; j++){
                        if (placesPtr[j]->pcode == b){
                            placesPtr[i]->d_link1 = calculate_Distance(placesPtr[i]->plng, placesPtr[j]->plng, placesPtr[i]->plat, placesPtr[j]->plat);
                            placesPtr[i]->link1 = placesPtr[j];
                            cout << "The destination " << placesPtr[j]->pname << " has been successfully added to the origin " << placesPtr[i]->pname << "." << endl;
                            return;
                        }
                    }
                }
                if (temp2->pcode == c){                                     //Overwrite link2
                    for (int j = 0; j < numPlaces; j++){
                        if (placesPtr[j]->pcode == b){
                            placesPtr[i]->d_link2 = calculate_Distance(placesPtr[i]->plng, placesPtr[j]->plng, placesPtr[i]->plat, placesPtr[j]->plat);
                            placesPtr[i]->link2 = placesPtr[j];
                            cout << "The destination " << placesPtr[j]->pname << " has been successfully added to the origin " << placesPtr[i]->pname << "." << endl;
                            return;
                        }
                    }
                }
            }
        }
    }
}

void find_Route(place* placesPtr[], int numPlaces){
    int x; int y; place* origin; place* destination; double distance = 0.0; int hops = 0;
    cout << "Enter the location code of your departure city: " << endl;
    cin >> x;
    if ((x < 101) || (x > 108)) {cout << "NOT A VALID CODE" << endl; return;}
    cout << "Enter the location code of your destination city: " << endl;
    cin >> y;
    if ((y < 101) || (y > 108) || (y == x)) {cout << "NOT A VALID CODE" << endl; return;}
    
    for (int i = 0; i < numPlaces; i++){
        if (placesPtr[i]->pcode == x){
            origin = placesPtr[i];
        }
        if (placesPtr[i]->pcode == y){
            destination = placesPtr[i];
        }
    }

    place* n = destination;
    while(n != origin){
        for (int i = 0; i < numPlaces; i++){
            if (placesPtr[i]->link1 == n){
                n = placesPtr[i];
                hops++;
                distance = distance + placesPtr[i]->d_link1;
                break;
            }
            if (placesPtr[i]->link2 == n){
                n = placesPtr[i];
                hops++;
                distance = distance + placesPtr[i]->d_link2;
                break;
            }
            break;
        }
    }
    
    cout << "Route from " << origin->pname << " to " << destination->pname << ":" << endl;
    cout << "Distance: " << distance << " miles" << endl;
    cout << "Hops: " << hops << endl;
    
}
