#include <iostream>
#include<ctime>
#include<random>

using namespace std;

struct location{
    int height = 0;
    int wid = 0;
};

struct chocolateBar{
    int height = 0;
    int wid = 0;
};

location getMoldLocation(int heightSize, int widSize){
    location moldLoc;
    moldLoc.height = 1 + (rand() % heightSize);
    moldLoc.wid = 1 + (rand() % widSize);

    return moldLoc;
}

int main(){
    srand(time(0));
    
    //Making a chocolate bar of size MxN and determining where to place the moldy piece.
    int height, wid;
    string input;
    chocolateBar chocoBar;

    cout << "Enter the height of the chocolate bar: ";
    cin >> height;
    cout << endl;
    chocoBar.height = height;

    cout << "Enter the width of the chocolate bar: ";
    cin >> wid;
    cout << endl;
    chocoBar.wid = wid;

    location moldLocation = getMoldLocation(height,wid);

    //Game
    int xCoord, yCoord;
    int playersTurn = 0;
    string dir, portion;
    

    while(xCoord != -999 && yCoord != -999 && dir != "quit"){
        playersTurn++;

        if(playersTurn == 3){
            playersTurn = 1;
        }

        int validDir = 0;

        for(int i = 0; i < height; i++){
            for(int j = 0; j < wid; j++){
                if(i == (height - moldLocation.height) && j == (moldLocation.wid-1)){
                    cout << "|X_|";
                } else {
                cout << "|__|";
                }
            }
            cout << endl;
        }

        //Getting valid removal inputs
        cout << endl << "Player " << playersTurn << ": Input an x coordinate for the starting piece to be removed(-999 to quit): ";
        cin >> xCoord;
        if(xCoord == -999){
            break;
        }

        cout << endl  << "Player " << playersTurn << ": Input a y coordinate for the starting piece to be removed(-999 to quit): ";
        cin >> yCoord;
        if(yCoord == -999){
            break;
        }

        while(validDir != 1){
            cout << endl << "Player " << playersTurn << ": Input a direction in which you want the chocolate to be removed from(u, d, l, r)(\"quit\" to quit): ";
            cin >> dir;

            if(dir == "quit"){
                break;
            }

            cout << endl;
            validDir = 1;

            //Picked left edge
            if(xCoord == 1 && yCoord != height && yCoord != 1 && dir != "r" && wid != 1 && height != 1){
                cout << "INVALID DIRECTION";
                validDir = 0;
            }

            //Picked the right edge
            if(xCoord == wid && yCoord != height && yCoord != 1 && dir != "l" && wid != 1 && height != 1){
                cout << "INVALID DIRECTION";
                validDir = 0;
            }

            //Picked the top edge
            if(yCoord == height && xCoord != wid && xCoord != 1 && dir != "d" && wid != 1 && height != 1){
                cout << "INVALID DIRECTION";
                validDir = 0;
            }

            //Picked the bottom edge
            if(yCoord == 1 && xCoord != wid && xCoord != 1 && dir != "u" && wid != 1 && height != 1){
                cout << "INVALID DIRECTION";
                validDir = 0;
            }

            //Picked the top left corner
            if(xCoord == 1 && yCoord == height && dir != "r" && dir != "d" && wid != 1 && height != 1){
                cout << "INVALID DIRECTION";
                validDir = 0;
            }

            //Picked the bottom left corner
            if(xCoord == 1 && yCoord == 1 && dir != "u" && dir != "r" && wid != 1 && height != 1){
                cout << "INVALID DIRECTION";
                validDir = 0;
            }

            //Picked the top right corner
            if(xCoord == wid && yCoord == height && dir != "l" && dir != "d" && wid != 1 && height != 1){
                cout << "INVALID DIRECTION";
                validDir = 0;
            }

            //Picked the bottom right corner
            if(xCoord == wid && yCoord == 1 && dir != "l" && dir != "u" && wid != 1 && height != 1){
                cout << "INVALID DIRECTION";
                validDir = 0;
            }

            //Defaults a win to the opposite player if only two pieces left
            if((wid == 2 && height == 1)||(wid == 1 && height == 2)){
                if(playersTurn == 1){
                    cout << "Player 1 WINS BY DEFAULT!!!!" << endl;
                    dir = "quit";
                    exit;
                } else{
                    cout << "Player 2 WINS BY DEFAULT!!!!" << endl;
                    dir = "quit";
                    exit;
                }
            }

            //Determining whether to remove the left, right, upper, or lower portion
            if(validDir == 1 && (dir == "l" || dir == "r")){
                cout << "Player " << playersTurn << ": Do you want to remove the upper portion or lower portion?(u, l)"; 
                cin >> portion;
                if(portion == "l"){  
                   height -= yCoord; 
                    moldLocation.height -= yCoord;
                }
                if(portion == "u"){  
                    height -= (height - yCoord) + 1; // -1
                    moldLocation.height -= (moldLocation.height -yCoord) -1;
                }
                validDir = 1;

            }
            if(validDir == 1 && (dir == "u" || dir == "d")){
                cout << "Player " << playersTurn << ": Do you want to remove the right portion or left portion?(r, l)"; 
                cin >> portion;
                if(portion == "l"){  
                    wid -= xCoord; 
                    moldLocation.wid -= xCoord;
                }

                if(portion == "r"){  
                    wid -= (wid - xCoord) + 1;
                }
                validDir = 1;
            }

            //Gives a loss if player takes out the moldy piece
            if(moldLocation.height > height || moldLocation.wid > wid || moldLocation.height < 1 || moldLocation.wid < 1){
                if(playersTurn == 1){
                    cout << "Player 2 WINS!!!!" << endl;
                    dir = "quit";
                    exit;
                } else{
                    cout << "Player 1 WINS!!!!" << endl;
                    dir = "quit";
                    exit;
                }
                
            }
        } 
    }
}


