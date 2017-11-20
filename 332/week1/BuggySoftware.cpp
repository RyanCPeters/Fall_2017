// Edited by Ryan Peters, student ID: 1775396
// CSS 332 A Au 17
// due Sunday, 10/1/17 by 11:30pm

// for a list of corrections in this assignment, please see the commented list at the
// bottom of this file.


/* BuggySoftware.cpp
   1.  Locate and fix the errors first in this bug ridden software:
       There are MULTIPLE SYNTAX & LOGIC errors.
   2.  Practice proper naming conventions and spacing.
   3.  Make sure your code compiles.
   4.  Test your code to produce the correct output.
   5.  Before you move on, be sure your professor checks your output.
*/

#include <iostream>
#include <string>
using namespace std;

// declaring the functions used in this file
double finalGrade(double testScore, double examScore);
double checkGrade(double theGrade);



/*int main()
 * this function contains all of the logic and functionality for this class file.
 *
 * This function will print a request tot he command line that asks the user for
 * a students midterm and exam scores.
 *
 * It will then confirm that those scores are within acceptable boundaries and either
 * proceed to calculating the weighted average of those scores or it will request that
 * the user enter scores within the required boundaries.
 *
 * @return hard coded to return a value of 0, as per instructors requirements.
 */
int main()
{
	double midtermGrade;
	double examScore;

    // requesting the user to enter the student's midterm grade
	cout<< endl << "Please enter the mid term grade (max 100 points) : ";
	cin >> midtermGrade;
	midtermGrade = checkGrade(midtermGrade);

    // requesting the user to enter the student's exam grade
	cout<<endl<< "Now, enter the final exam score (max 100 points) : ";
	cin >> examScore;
	examScore = checkGrade(examScore);

	cout<<"This student got "<<  finalGrade(midtermGrade, examScore);
	cout<<"% in the course" << endl << endl;
	system("pause");
	return 0;

}

/* double finalGrade(double testScore, double examScore)
 *
 *  This function will accept values representing a student's midterm and exam scores,
 *  then perform the calculations for a weighted averaging of those scores.
 *
 *  This function assumes that all input values have already been sanity checked via the
 *  checkGrade function.
 *
 * @param testScore a double type value that should represent the student's midtermGrade
 * @param examScore
 * @return
 */
double finalGrade(double midtermGrade, double examScore)
{
	double grade = (midtermGrade + 3.5) * examScore / 103;
	return (grade + .5);
}

/* double checkGrade(double gradeToCheck)
 *
 * This function sanity checks the input data from the user.
 *
 * It verifies that the gradeToCheck parameter is a
 *
 * @param gradeToCheck
 * @return
 */
double checkGrade(double gradeToCheck)
{
	/* the loops variable will serve as a sanity checker for the while loop's logic
	 * should the user try to enter bizarre inputs for student grades.
	 *
	 *  Without this check, an input of a non-numeric value will result in an infinite
	 *  loop bellow.
	 */
	double loops = 0, maxGrade = 100.00;

	while((gradeToCheck < 0.0 || gradeToCheck > maxGrade))	{

		loops++;
        if(loops > 20){
            cout << "It appears that you may not have entered a number for this grade." << endl;
            cout << "please enter a NUMERIC grade in this range [0, \" << maxGrade <<\"]:";
            loops = 0;
        }
        else {
            cout << endl << "Great, genius!! That's out of range." << endl;
            cout << "What's the matter with you, enter a grade in this range [0, " << maxGrade << "]:";
        }
		cin>> theGrade;
	}
	return theGrade;
}

/* Note: all line numbers are correct for the state of this file as it is in my JetBrains
 * CLion IDE.
 *
 * 1.) line 42
 *      needed to put the data type in front of examScore
 *
 * 2.) line 46
 *     needed to include a command-line in call to catch user input for the
 *	   value saved to midtermGrade
 *
 * 3.) line 54
 *     Added the midtermGrade variable as an input for the first parameter in the
 *     call to finalGrade
 *
 * 4.) line 57
 *      Had to change the capitalization of the return keyword to be lower-case.
 *
 * 5.) line 75
 *      Had to add the examScore parameter to the expression in order to have
 *      the correct logical output.
 *
 * 6.) line 88
 *      Made a subjective decision to change the parameter named "theGrade" to be
 *      "gradeToCheck". This seemed to make the purpose of that parameter more clear
 *      should a tired brain try to interact with this code later.
 *
 * 7.) line 98
 *      Changed the && operator to be the || operator.
 *
 *      This fixed the logic error that prevented any input less than 0 or greater
 *      than 100 from causing the correction request.
 *
 *
 */
