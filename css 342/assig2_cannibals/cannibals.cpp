#include <iostream>
#include <sstream>
#include "cannibals.h"

using namespace std;

/** cannibals::cannibals() : initState({3, 3, 1}), failState({-1, -1, -1}), baseCase({0, 0, 0}),
 *                       options({{1, 1, 1}, {0, 2, 1}, {2, 0, 1}, {0, 1, 1}, {1, 0, 1}})
 *
 * The constructor provides the definitions for the class's constant global members as well as starts the recursive
 * process towards finding a solution for the assigned problem.
 *
 * The assignment says that the initial state is as follows:
 *          On the left bank of the river:
 *              3 explorers
 *              3 cannibals
 *              1 boat containing two seats, this boat requires at least one occupant in order to traverse the river.
 *
 *          On the right bank of the river:
 *              0 explorers
 *              0 cannibals
 *              0 boat
 *
 * The assignment also says that the problem is solved when we reach the following state:
 *          n the left bank of the river:
 *              0 explorers
 *              0 cannibals
 *              0 boat
 *
 *          On the right bank of the river:
 *              3 explorers
 *              3 cannibals
 *              1 boat
 */
cannibals::cannibals() : initState({3, 3, 1}), failState({-1, -1, -1}), baseCase({0, 0, 0}),
                         options({{1, 1, 1}, {0, 2, 1}, {2, 0, 1}, {0, 1, 1}, {1, 0, 1}})
{

    vector<vector<int>> path;
    path = recurseSolve(initState, options[0]);

    cout << "\na solution has been found!! path.size() = " << path.size() << endl << endl;
    for (const vector<int> &cur: path) {
        cout << makeString(cur);
        cout << endl;
    }
}


/** vector<vector<int>> recurseSolve(vector<int> curState, int idxPos, bool goingRight)
 *
 * This function checks the validity of curstate after modifying it with modVals.
 *
 * @param curState  This vector<int> container object represents the state of the left bank at the time of this
 *                  recursion's call.
 *
 * @param custOpts a constant reference to a vector<int> object that represents the predetermined list of acceptable
 *                  options for how to modify the curState vector in this round of recursion, none of the options in
 *                  custOpts should cuase for an invalid state on the next round's curState.
 *
 * @return          returns a vector<vector<int>> object that is built from the subsequent recursive calls by this function.
 */
vector<vector<int>> cannibals::recurseSolve(const vector<int> &curState, const vector<int> &custOpts)
{
    bool validity = checkValid(curState);
    vector<vector<int>> ret;
    vector<int> nextState = curState;
    nextState[2] = (nextState[2] == 0) ? 1 : 0;

    ret.push_back((validity)?curState:failState);
    if (!validity || curState == baseCase)return ret;

    nextState = applyStep(curState,custOpts);
    validity = checkValidity(curState, nextState);// sanity checking that our updated nextState is good
    vector<vector<int>> nextOpts = buildOpts(nextState);

    if (validity) {
        vector<vector<int>> recursed;
        vector<int> vec;
        for (int i = 0; i < nextOpts.size(); ++i) {
            vec.clear();
            recursed.clear();
            vec = nextOpts[i];
            if(checkValidity(nextState,applyStep(nextState,vec)))recursed = recurseSolve(nextState, vec);
            if(recursed.back() == baseCase){
                if(ret.back() == failState)ret.pop_back();
                for(const vector<int> &vect : recursed)ret.push_back(vect);
                return ret;
            }
        }// end of for(int i = 0; i < nextOpts.size(); ++i)
    }// end of if(validity) block

    return ret;
}// end of recurseSolve(const vector<int> &curState, const vector<int> &custOpts) function deffinition

/** vector<int> cannibals::applyStep(const vector<int> &curState, const vector<int> &step)
 *
 *  the applyStep(vector, vector) function is used to apply a chosen path option, call it "step" here, to the current
 *  state of the left bank. This function does not have any issue in deeling with multiple levels of recursion so long as
 *  the reference to curState
 *
 * @param curState      a constant reference to a vector<int> of three elements portraying the state of the left side
 *                      bank at the time this function was called.
 *
 * @param step          the three integer array portraying the chosen path option that we want applied to the current state
 *                      of the left bank.
 * @return
 */
vector<int> cannibals::applyStep(const vector<int> &curState, const vector<int> &step)
{
    vector<int> ret = curState;
    if(curState[2] == 1) {
        ret[0] -= step[0];
        ret[1] -= step[1];
        ret[2] -= step[2];
    } else{
        ret[0] += step[0];
        ret[1] += step[1];
        ret[2] += step[2];
    }
    return ret;
}

/** vector<vector<int>> cannibals::buildOpts(const vector<int> &nextState)
 *
 *  This function is used to reduce the amount of backtracking required of the function by eliminating path options that
 *  will fail in the next level of recursion.
 *
 *  Because we've found a valid updated state for the next level of recursion, we have the two pieces of information needed
 *  for making some simple decisions on how we can reduce future steps.
 *
 *      1)  We know we have 5 possible path optoins.
 *
 *      2)  We have the current state of the left bank, from which we can easily infer the state of the right bank.
 *
 *          we can now determine which of the 5 possible path options may be applied to nextState on our next round of
 *          recursion.
 *
 *
 * @param nextState         an updated state from the given curState in a given level of recursion. That is to say,
 *                          nextState represents the vector<int> that will be passed into the next level of recursion as
 *                          we seek the solution path.
 * @return
 */
vector<vector<int>> cannibals::buildOpts(const vector<int> &nextState)
{
    vector<int> test;
    vector<vector<int>> ret;
    bool opts[5] = {true, true, true, true, true};
    if(nextState[0] == 3) {
        if (nextState[1] == 2) {
            opts[0] = opts[2] = opts[3] = opts[4] = false;
        } else if (nextState[1] == 0) {
            if (nextState[2] == 1) opts[0] = opts[1] = opts[3] = opts[4] = false;
            else opts[0] = opts[1] = opts[2] = opts[4] = false;
        }
    }else if(nextState[0] == nextState[1]){
        if(nextState[0] == 1) {
           opts[1] = opts[2] = opts[3] = opts[4] = false;
        }else if(nextState[2] == 1){
            opts[0] = opts[1] = opts[3] = opts[4] = false;
        }
    }else if(nextState[0] == 0 && nextState[1] >0){
        if(nextState[2] == 0)opts[1] = false;
        opts[0] = opts[2] = opts[4] = false;
    }

    for (int i = 0; i < 5; ++i) {
        if(opts[i]) {
            test = applyStep(nextState, options[i]);
            opts[i] = checkValidity(nextState, test);
        }
    }
    for(int i = 0; i < 5; ++i){
        if(opts[i]){
            ret.push_back(options[i]);
        }
    }
    return ret;
}

/**
 *
 * @param curState
 * @param nextState
 * @return
 */
bool cannibals::checkValidity(const vector<int> &curState, const vector<int> &nextState) const
{
    if(!(checkValid(curState) && checkValid(nextState))) return false;
    if(nextState[0] <3 && nextState[1] <= nextState[0]-1)return false;// because we'll be out of ratio on right bank
    if(nextState == initState) return false;
    if(curState[0] == nextState[0] && curState[1] == nextState[1]) return false;

    return true;
}

/** bool cannibals::checkValid(const vector<int> &aState) const
 *
 * As the name implies, this function checks if the given parameter, aState, satisfies the criteria to be a valid state.
 *
 * Note that while aState only contains the explicit data for the left bank, we can use that information to easily infer
 * the state of the right bank.
 *
 *      Using the fact that there can only ever be 3 explorers and 3 cannibals between left and right banks means we can
 *      easily infer that any members of those 6 entities that are not on the left bank, must then be on the right.
 *
 * Those criteria are:
 *
 *          if
 *
 * @param aState
 * @return
 */
bool cannibals::checkValid(const vector<int> &aState) const
{
    return    ( aState[0] <  1 || aState[0] >= aState[1] )
           && ( aState[1] >= 0 && aState[0] >= 0 )
           && ( aState[0] <  4 && aState[1] <  4 )
           && ( aState != failState );
}


/** string cannibals::makeString(vector<int> curr)
 *
 *      Used in both generating the specified outputs for this program, as well as in debugging where a means to generate
 *      an output representing the immediate change in state under some test condition.
 *
 * @param stateToBeRepresented      As its name implies, this vector<int> of 3 only values represents the state for
 *                                  which we need a printed representation. While its elements are only explicitly
 *                                  describing the left bank. The fact that there can only ever be 3 explorers and 3
 *                                  cannibals means we can easily deduce the state of the right bank.
 * @return the string representation of the given vector<int> parameter, stateToBeRepresented
 */
string cannibals::makeString(vector<int> stateToBeRepresented)
{
    int explo = stateToBeRepresented[0], canns = stateToBeRepresented[1], boatSide = stateToBeRepresented[2];
    stringstream scene;
    for (int j = 0; j < (6 - explo - canns); ++j) scene << "-";
    for (int i = 0; i < explo; ++i) scene << "E";
    for (int k = 0; k < canns; ++k) scene << "C";
    scene << " \\ ";
    switch (boatSide) {
        case 0:
            scene << " _ " << "_ ";
            scene << "<..>";
            break;
        case 1:
            scene << "<..>";
            scene << " _ " << "_ ";
            break;
    }
    scene << " / ";
    for (int i = 0; i < 3 - explo; ++i)scene << "E";
    for (int i = 0; i < 3 - canns; ++i)scene << "C";
    for (int i = 0; i < 6 - ((3 - explo) + (3 - canns)); ++i)scene << "-";

    return scene.str();


}
