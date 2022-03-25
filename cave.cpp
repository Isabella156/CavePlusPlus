#include <stdexcept>
#include <string>
#include <iostream>
#include <vector>
#include <string>

#include "cave.h"
#include "rock.h"
#include "thing.h"
#include "location.h"
#include "move.h"
#include "place.h"

using namespace std;

Cave::Cave(int w, int h) : width(w), height(h) { // width and height of the cave

    if ( width < 5 || height < 5)
        throw new logic_error("cave too small for tom.");

    map = new Location**[h];

    for (int x = 0; x < h; x++) {
        Location** column = new Location*[w];
        map[x] = column;
        for (int y = 0; y < w; y++)
            column[y] = new Location();
    }

    // create some rocks
    for (int x = 0; x < h; x++) {
        for (int y = 0; y < w; y++)
            if (
                    (x == 0 || y == 0 || x == h - 1 || y == w - 1) )
                 map[x][y] -> add( new Rock() );
    }

    tom = new Tom();

    // add tom to the middle of the map
    tom -> setLocation( this, width/2,height/2);
}

Cave::~Cave() {

}

void Cave::command (string userCommand) {

    if (Move().triggersOn(userCommand))
        Move().fire(*this, userCommand);
    else if (Place().triggersOn(userCommand))
        Place().fire(*this, userCommand);
    else
        cerr << "tom doesn't know how to "+userCommand << endl;;
}

void Cave::show() {

    vector<Thing*>* thingsWithTom = map[tom -> getX()][tom -> getY()] -> getThings();

    for (int y = 0; y < height; y++) { // for all rows
        for (int x = 0; x < width; x++) // for all columns
            cout << map[y][x] -> show(); // output whatever we find there

        cout << "  "; // list the things at this location
        if (y <  (int) thingsWithTom -> size())
            cout << (*thingsWithTom)[y] -> getName();

        cout << endl;
    }

    cout << endl;
}
