//
// Created by R.Peters on 10/17/2017.
//

//struct Actor{
//    char symb;
//    Actor(const char &c){
//        symb = c;
//    }
//    Actor(){
//        symb = ' ';
//    }
//    Actor operator=(const char c) {
//        symb = c;
//        return *this;
//    }
//
//    Actor operator=(const Actor a){
//        symb = a.symb;
//        return *this;
//    }
//
//    bool operator!=(const Actor &a) const{
//        return a.symb != symb;
//    }
//
//    bool operator!=(const char &c) const{
//        return c != symb;
//    }
//
//    bool operator==(const Actor &a) const{
//        return a.symb == symb;
//    }
//
//    bool operator==(const char &c) const{
//        return c == symb;
//    }
//
//};
//
//struct Boat {
//
//    bool goingRight = true;
//    string outString;
//    const char emptSeat = '.';
//    Actor left = Actor('<');
//    Actor right = Actor('>');
//    Actor tail = Actor('|');
//    Actor seat1 = Actor(emptSeat);
//    Actor seat2 = Actor(emptSeat);
//    vector<Actor> myboat;
//
//    Boat(){
//        myboat[0] = tail;
//        myboat[1] = seat1;
//        myboat[2] = seat2;
//        myboat[3] = right;
//        makeString();
//    }
//
//    Actor setSeat(Actor &a, const int seatNum){
//        Actor returnable;
//        switch (seatNum) {
//            case 1:
//                returnable = seat1;
//                seat1 = a;
//                break;
//            case 2:
//                returnable = seat2;
//                seat2 = a;
//                break;
//        }
//        makeString();
//        return returnable;
//    }
//
//    Actor clearSeat(const int seatNum){
//        Actor returnable;
//        switch (seatNum) {
//            case 1:
//                returnable = seat1;
//                seat1 = emptSeat;
//                break;
//            case 2:
//                returnable = seat2;
//                seat2 = emptSeat;
//                break;
//        }
//        makeString();
//        return returnable;
//    }
//
//    bool goRight(){
//        return goingRight;
//    }
//
//    bool goRight(const bool trueForRight){
//        goingRight = trueForRight;
//        turn();
//        makeString();
//        return goingRight;
//    }
//
//    void turn(){
//        if(goingRight){
//            myboat[0] = tail;
//            myboat[3] = right;
//        }else{
//            myboat[0] = left;
//            myboat[3] = tail;
//        }
//    }
//
//    string makeString(){
//        outString = "";
//        for(unsigned int i = 0; i < 4; i++ ){
//            outString[i] = myboat[i].symb;
//        }
//        return outString;
//    }
//
//    friend std::ostream& operator<<(std::ostream &out, const Boat &printMe){
//        out << printMe.outString;
//        return out;
//    }
//};
//
//struct Shore{
//    string outString;
//    vector<Actor> myShore;
//    Shore(const bool left){
//        if(left){
//            for (int i = 0; i < 6; ++i) {
//                if(i < 3) myShore[i] = Actor(_canni);
//                else myShore[i] = Actor(_exp);
//            }
//        }else{
//            myShore.assign(6,Actor(_dirt));
//        }
//        makeString();
//    }
//
//    Actor xfrAt(int &pos, Actor &a){
//        Actor ret = myShore[pos];
//        myShore[pos] = a;
//        makeString();
//        return ret;
//    }
//
//    string makeString(){
//        for (int i = 0; i < myShore.size() ; ++i) {
//            outString[i] = myShore[i].symb;
//        }
//        return outString;
//    }
//
//    friend std::ostream& operator<<(std::ostream &out, const Shore &printMe){
//        out << printMe.outString;
//        return out;
//    }
//
//};
//
//struct River{
//    const int riverWidth = 8;
//    vector<Actor> myRiver;
//    string outString;
//    int boatPos = 1; // note that 0 will always be _lbnk
//    Boat rivBoat = Boat();
//    River(){
//        myRiver[0] = _lbnk;
//        myRiver[1] = _dirt; // _dirt will be used as a sanity check later when we need to validate boat moves.
//        myRiver[2] = _water;
//        myRiver[3] = _water;
//        myRiver[4] = _rbnk;
//    }
//
//    // returns the index position in river's array that the boat should be inserted.
//    int moveBoat(){
//        switch (boatPos){
//            case 1:
//                myRiver[boatPos++] = _water;
//                myRiver[boatPos] = _dirt;
//                rivBoat.goRight(true);
//                break;
//            case 2:
//                myRiver[boatPos] = _water;
//                boatPos = rivBoat.goRight()? 3:1;
//                myRiver[boatPos] = _dirt;
//                break;
//            case 3:
//                myRiver[boatPos--] = _water;
//                myRiver[boatPos] = _dirt;
//                rivBoat.goRight(false);
//                break;
//            default:
//                cerr << "Something funky happened, as the boat is not where it should be!!"<< endl << endl;
//                break;
//        }
//        return boatPos;
//    }
//    string makeString(){
//        outString = "";
//        string boatString = rivBoat.makeString();
//        bool preDirt = true;
//        for(int i = 0; i < riverWidth && preDirt; i++) {
//            preDirt = myRiver[i] != _dirt;
//            if(preDirt) outString[i] = myRiver[i].symb;
//            else
//                for (int j = 0; j < 4 && j+i < riverWidth ; ++j) outString[i+j] = boatString.at(j);
//        }
//        return outString;
//    }
//
//    friend std::ostream& operator<<(std::ostream &out, const River &printMe){
//        out << printMe.outString;
//        return out;
//    }
//
//};
//
//struct Scene{
//    Shore lShore = Shore(true);
//    Shore rShore = Shore(false);
//    River riv = River();
//    int boatPos;
//    vector<vector<Actor>> myScene;
//    Scene(){
//        myScene[0] = lShore.myShore;
//        myScene[1] = riv.myRiver;
//        myScene[2] = rShore.myShore;
//        boatPos  = riv.boatPos + lShore.myShore.size();
//    }
//
//    friend std::ostream& operator<<(std::ostream &out, const Scene &printMe){
//
//        out << printMe.lShore << printMe.riv << printMe.rShore;
//
//        return out;
//    }
//};