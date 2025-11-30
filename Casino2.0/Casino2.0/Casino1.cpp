#include <iostream>
#include <cstdlib>
#include <fstream>
#include <ctime>
#include <vector>
#include <string>
#include <unistd.h>
void drawLine(int n, char symbol);
using namespace std;

struct UserData {
    string name;
    int age;
    string password;
};
    long cash;
    bool executed = false, jump=false;
    UserData loggedInUser;
    vector<UserData> users;

    //deposit
void deposit();

bool isUserNew() {
    char choice;
    executed = true;
    do{
        system("cls");
        cout << "Are you a new user? (Y/N): ";
    cin >> choice;
    if(choice!='y'&& choice!='Y' && choice!='N' && choice!='n'){
        cout<<"Invalid";
        sleep(1);
    }

    }while(choice!='y'&& choice!='Y' && choice!='N' && choice!='n');
    return (choice == 'Y' || choice == 'y');
}

bool loginUser(const vector<UserData>& users, UserData& loggedInUser) {
    string name, password;
    cout << "Enter your name: ";
    cin >> name;
    cout << "Enter your password: ";
    cin >> password;

    for (const UserData& user : users) {
        if (user.name == name && user.password == password) {
            loggedInUser = user; // Store the logged-in user's data
            return true; // User is logged in successfully
        }
    }

    cout << "Invalid name or password. Please try again.\n";

    return false; // Login failed
}

void saveUserData(const vector<UserData>& users) {
    ofstream outFile("userdata.txt");

    if (!outFile) {
        cerr << "Error opening file for writing.\n";
        exit(1);
    }

    for (const UserData& user : users) {
        outFile << user.name << " " << user.age << " " << user.password << " " <<endl;
    }

    outFile.close();
}

void registerUser() {
    UserData newUser;
    jump = true;
    cout << "Enter your name: ";
    cin >> newUser.name;
    cout << "Enter your age: ";
    while (true)
  {
    cin >> newUser.age;
    if (!cin)
    {
      cout << "Wrong Input. Enter again " << endl;
      cin.clear();
      cin.ignore();

      continue;
    }
    else break;
  }
    while(newUser.age<18){
              cout << "Sorry, you are too young to play the games." << endl;
              exit(1);
    }
    while(newUser.age>100){
        cout << "Enter valid age(18 to 100): ";
        cin >> newUser.age;
    }
    while(newUser.age<18){
              cout << "Sorry, you are too young to play the games." << endl;
              exit(1);
    }


    cout << "Create a password: ";
    cin >> newUser.password;
    cash = 0; // Initialize cash to 0 for a new user
    users.push_back(newUser);
    saveUserData(users);
    deposit();
    cout << "Registration successful. You can now log in.\n";
}

void loadUserData() {
    ifstream inFile("userdata.txt");

    if (!inFile) {
        cerr << "User data file not found. Creating a new one.\n";
        return;
    }

    while (!inFile.eof()) {
        UserData user;
        inFile >> user.name >> user.age >> user.password;
        if (!user.name.empty()) {
            users.push_back(user);
        }
    }

    inFile.close();


}
void saveValue() {
    ofstream outFile("cash.txt");

    if (!outFile) {
         cerr << "Error opening file for writing.\n";
        return;
    }

    outFile << cash;
    outFile.close();
}

//load
void loadValue() {
    ifstream inFile("cash.txt");

    if (!inFile) {
         cerr << "Error opening file for reading.\n";
        return;
    }

    inFile >> cash;
    inFile.close();
}
// General functions
void bankrupt();

// Function to generate a random number between min and max (inclusive)
int generateRandomNumber(int min, int max) {
    return rand() % (max - min + 1) + min;
}

// Function to spin a single reel
char spinReel(const std::vector<char>& symbols) {
    int index = generateRandomNumber(0, symbols.size() - 1);
    return symbols[index];
}
void casinodrawLine(int n, char symbol);
void casinorules();
void casinorule();

//blackjack function
void blackjack();

//guessing function
void guessing();
// Roulette functions
void roulette01();
void roulette02();
void roulette03();
void rouletteWin();
void rouletteLoss();

// Slots functions
void slot();

//blackjack function
//void blackjack();

//cointoss fuctions
void coinToss();
void coinTossWin();
void coinTossLoss();
// General variables
int invalid = 1;
char input;
int dollars = 50;

// Roulette variables
int bet = 0;
char cColour;
int iColour;
int actualColour;

//replay or not
void replayOrNot(){
    int replay;
    cout<<"Out of balance.\nDo you want to deposit?"<<endl;
    cout<<"1. deposit\n2. quit"<<endl;
    cout<<"> ";
    cin>>replay;
    if(replay==1){
        deposit();
        return;
    }
    else if(replay==2){
            system("cls");
        cout<<"Thanks for playing."<<endl;
        cout<<"Hope we meet again one day"<<endl;
        cout<<"Sayonara!";
        saveUserData(users);
        saveValue();
        exit(1);
    }
    else cout<<"Enter 1 and 2 only."<<endl;
}

void homeScreen() {
    system("cls");
    cout << "\n===============================================================================================";
    cout << "\n       CCCCC      A          SSSSSSS   IIIIIIIII  NN     NN    OOOOOOOO              ";
    cout << "\n     CC          A  A      SS             III     NN N   NN   OO      OO             ";
    cout << "\n    CC          A    A     SSSSSSSSS      III     NN  N  NN   OO      OO             ";
    cout << "\n     CC        AAAAAAAA           SS      III     NN   N NN   OO      OO             ";
    cout << "\n       CCCCC  A        A   SSSSSSS     IIIIIIIII  NN     NN    OOOOOOOO              ";
    cout << "\n===============================================================================================\n";
    cout << "\n Welcome to the Casino, " << loggedInUser.name << "! What would you like to play?" << endl;
    cout << "\n 1. Number Guessing" << endl;
    cout << "\n 2. Slots" << endl;
    cout << "\n 3. Roulette" << endl;
    cout << "\n 4. CoinToss" << endl;
    cout << "\n 5. Exit" << endl;
    cout << "\n Your balance: $" << cash << endl;
    if(cash==0){
        char oob;
        cout<<"Unfortunately, you are out of balance\nDo you want to deposit?(y or n)";
        cin>>oob;
        if(oob=='y'){
            deposit();
        }
        else{
              system("cls");
        cout<<"Thanks for playing."<<endl;
        cout<<"Hope we meet again one day"<<endl;
        cout<<"Sayonara!";
        saveUserData(users);
        saveValue();
        exit(1);
        }
    }
    cout << "\n> ";
    cin >> input;
    cin.clear();
    cin.ignore(1000,'\n');
    do{
            switch (input) {

                case '1':
                    guessing();
                case '2':
                    slot();
                case '3':
                    roulette01();
                case '4':
                    coinToss();
                case '5':
                    system("cls");
                    cout<<"Thanks for playing."<<endl;
                    cout<<"Hope we meet again one day"<<endl;
                    cout<<"Sayonara!";
                    saveUserData(users);
                    saveValue();
                    exit(1);

                default:
                    cout << "\n That was invalid input!" << endl;
                    cout << "\n ";
                    while(!(input == '1' || input == '2' || input == '3' || input == '4' || input == '5'))
                    {    //cin.clear();
                         cout << "Please enter valid input(1 to 5): ";
                         cin >> input;
                         cin.clear();
    cin.ignore(1000,'\n');
                        if(input == '1' || input == '2' || input == '3' || input == '4' || input == '5')
                        break;
                    }
             }
             cout << endl;
           }while(input);
}

//save


int main() {
    bool a = true;
    char tuna;
    string playerName;
    int amount; // hold player's balance amount
    int bettingAmount;
    int guess;
    int dice; // hold computer generated number
    char choice;
    srand (time(NULL));
    loadUserData();
    if (!executed) {
        bool isNewUser = isUserNew();

        if (isNewUser) {
            registerUser();
        } else {
            while (!loginUser(users, loggedInUser)) {
                while(true){
                    cout<<"Return? (y or n)";
                cin>>tuna;
                cin.clear();
    cin.ignore(1000,'\n');

                if(tuna=='y' || tuna=='Y'){
                       isNewUser = isUserNew();
                     if (isNewUser) {
                        registerUser();
                        }
                }
                if(tuna=='n' || tuna=='N')
                    loginUser(users, loggedInUser);
                else{
                    cout<<"Invalid."<<endl;
                }
                }

            }
        }
    }
    if(!jump){

        loadValue();
    }
    homeScreen();
    saveUserData(users);
    saveValue();
    return 0;
}

void roulette01() {
    char rolled;
    if (cash <= 0) {
        replayOrNot();
        return;
    }
    system("cls");
    cout << "Welcome from Roulette";
    cout << "\n You have $ " << cash << "!" << endl;
    cout << "\n Enter 1 to place a bet. Enter 2 to exit to the main menu." << endl;
    cout << "\n> ";
    cin >> rolled;
    switch (rolled) {

        case '1':
            roulette02();
            break;

        case '2':
            saveValue();
            main();
            break;

        default :
            roulette03();
    }
}

void roulette03 () {
    cout<<"Invalid Input"<<endl;
    cout << "\n Enter 1 to place a bet. Enter 2 to exit to the main menu." << endl;
    cout << "\n> ";
    char rolled;
    cin >> rolled;
    switch (rolled) {

        case '1':
            roulette02();
            break;

        case '2':
            saveValue();
            main();
            break;

        default :
        roulette03();
    }

}

void roulette02() {

    cout << "\n Enter how much you would like to bet." << endl;
    cout << "\n> ";
    cin >> bet;
    cin.clear();
    cin.ignore(1000,'\n');
    while(bet <= 0)
    {
        cout << "\n Enter bet amount which is greater than zero: $";
        cin >> bet;
        cin.clear();
    cin.ignore(1000,'\n');
    }

    if (bet > cash) {
        cout << "\n You don't have enough money for that bet!" << endl;
        cout << "\n ";
        system("pause");
        roulette02();
    }

    cout << "\n Would you like to bet on red or black?" << endl;
    cout << "\n Enter r for red. Enter b for black." << endl;
    cout << "\n> ";
    cin >> cColour;
    while( !((cColour == 'r') || (cColour == 'b')))
    {
        cout << "\nEnter valid color (r or b): ";
        cin >> cColour;
    }

    if (cColour == 'r') {
        iColour = 1;
    }

    else {
        iColour = 2;
    }

    actualColour = rand() % 2;

    if (actualColour == iColour) {
        rouletteWin();
    }

    else {
        rouletteLoss();
    }

}

void rouletteWin() {
    cash = cash + bet;
    saveValue();
    cout<<"Congratulations!";
    cout << "\n You won $ " << bet << "!" << endl;
    cout << "\n ";
    system("pause");
    roulette01();

}

void rouletteLoss() {
    cash = cash - bet;
    saveValue();
    cout << "\n You lost $ " << bet << "!" << endl;
    cout << "\n ";
    system("pause");
    roulette01();

}
void deposit(){
    bool realCash=true;
    system("cls");
    do{
        cout << "\n===============================================================================================";
        cout << "\n       CCCCC      A          SSSSSSS   IIIIIIIII  NN     NN    OOOOOOOO              ";
        cout << "\n     CC          A  A      SS             III     NN N   NN   OO      OO             ";
        cout << "\n    CC          A    A     SSSSSSSSS      III     NN  N  NN   OO      OO             ";
        cout << "\n     CC        AAAAAAAA           SS      III     NN   N NN   OO      OO             ";
        cout << "\n       CCCCC  A        A   SSSSSSS     IIIIIIIII  NN     NN    OOOOOOOO              ";
        cout << "\n===============================================================================================\n";
            cout<<"Deposit your cash first: ";
            cin>>cash;
            cin.clear();
            cin.ignore(1000,'\n');
            saveValue();
            if(cash<=0){
                cout<<"Please enter valid amount. Try again!"<<endl;
                realCash = false;
            }
            else realCash=true;
        }while(realCash==false);
               main();

}
//------------------------------------slot---------------------------------------------------------/
void slot()
{
     bool a = true;
    // Set up the symbols for each reel
    vector<char> reel1Symbols = {'7', '*', '?'};
    vector<char> reel2Symbols = {'7', '*', '?'};
    vector<char> reel3Symbols = {'7', '*', '?'};

    // Initialize the random number generator
    srand(static_cast<unsigned int>(time(0)));

    // Variables to hold player credits and bet amount
    int rows;
    int betAmount = 0;
    system("cls");
    cout << "\nWelcome from Slot game";
    cout << "\nEnter spin rows('1' for 1 row of spin or '3' for 3 rows of spin): ";
    cin >> rows;
    cin.clear();
    cin.ignore(1000,'\n');
do{
    if(rows == 3)
    {
        a=false;
        system("cls");
        casinorules();
     while (cash > 0) {
        // Get the bet amount from the player
        cout << "Your balance $: " << cash << endl << endl;
        a=false;

        cout << "Enter your bet (0 or any other character to quit): $";
        cin >> betAmount;
        cin.clear();
    cin.ignore();
        while(betAmount < 0 ){
            cout << "Enter bet amount which is greater than zero: $";
            cin >> betAmount;
            cin.clear();
    cin.ignore(1000,'\n');
        }
        if (betAmount == 0) {
            cout << "Thank you for playing. Goodbye!";
            saveValue();
            main();

        }

        if (betAmount > cash) {
            cout << "Insufficient balance. Please place a valid bet." << std::endl;
            continue;
        }

        // Spin the reels
        char symbol1 = spinReel(reel1Symbols);
        char symbol2 = spinReel(reel2Symbols);
        char symbol3 = spinReel(reel3Symbols);
        char symbol4 = spinReel(reel1Symbols);
        char symbol5 = spinReel(reel2Symbols);
        char symbol6 = spinReel(reel3Symbols);
        char symbol7 = spinReel(reel1Symbols);
        char symbol8 = spinReel(reel2Symbols);
        char symbol9 = spinReel(reel3Symbols);


        // Display the result
        cout << "\t " << symbol1 << " " << symbol2 << " " << symbol3 << endl;
        cout << "\t " << symbol4 << " " << symbol5 << " " << symbol6 << endl;
        cout << "\t " << symbol7 << " " << symbol8 << " " << symbol9 << endl;

        // Check for win
        if(symbol1 == '*' && symbol2 == '*' && symbol3 == '*') {
            int winnings = betAmount * 3; // Payout 3x the bet amount for a win
            cash += winnings;
            cout << "Congratulations! You won $ " << winnings << " !" << endl;
        }
        else if(symbol4 == '*' && symbol5 == '*' && symbol6 == '*') {
            int winnings = betAmount * 3; // Payout 3x the bet amount for a win
            cash += winnings;
            cout << "Congratulations! You won $ " << winnings << " !" << endl;
        }
        else if(symbol7 == '*' && symbol8 == '*' && symbol9 == '*') {
            int winnings = betAmount * 3; // Payout 3x the bet amount for a win
            cash += winnings;
            cout << "Congratulations! You won $ " << winnings << " !" << endl;
        }
        else if(symbol1 == '*' && symbol4 == '*' && symbol7 == '*') {
            int winnings = betAmount * 3; // Payout 3x the bet amount for a win
            cash += winnings;
            cout << "Congratulations! You won $ " << winnings << " !" << endl;
        }
        else if(symbol2 == '*' && symbol5 == '*' && symbol8 == '*') {
            int winnings = betAmount * 3; // Payout 3x the bet amount for a win
            cash += winnings;
            cout << "Congratulations! You won $ " << winnings << " !" << endl;
        }
        else if(symbol3 == '*' && symbol6 == '*' && symbol9 == '*') {
            int winnings = betAmount * 3; // Payout 3x the bet amount for a win
            cash += winnings;
            cout << "Congratulations! You won $ " << winnings << " !" << endl;
        }





        else if(symbol1 == '7' && symbol2 == '7' && symbol3 == '7') {
            int winnings = betAmount * 10; // Payout 3x the bet amount for a win
            cash += winnings;
            cout << "Congratulations! You won $ " << winnings << " ! \nYou won Jackpot" << endl;
        }
        else if(symbol4 == '7' && symbol5 == '7' && symbol6 == '7') {
            int winnings = betAmount * 10; // Payout 3x the bet amount for a win
            cash += winnings;
            cout << "Congratulations! You won $ " << winnings << " ! \nYou won Jackpot" << endl;
        }
        else if(symbol7 == '7' && symbol8 == '7' && symbol9 == '7') {
            int winnings = betAmount * 10; // Payout 3x the bet amount for a win
            cash += winnings;
            cout << "Congratulations! You won $ " << winnings << " ! \nYou won Jackpot" << endl;
        }
        else if(symbol1 == '7' && symbol4 == '7' && symbol7 == '7') {
            int winnings = betAmount * 10; // Payout 3x the bet amount for a win
            cash += winnings;
            cout << "Congratulations! You won $ " << winnings << " ! \nYou won Jackpot" << endl;
        }
        else if(symbol2 == '7' && symbol5 == '7' && symbol8 == '7') {
            int winnings = betAmount * 10; // Payout 3x the bet amount for a win
            cash += winnings;
            cout << "Congratulations! You won $ " << winnings << " ! \nYou won Jackpot" << endl;
        }
        else if(symbol3 == '7' && symbol6 == '7' && symbol9 == '7') {
            int winnings = betAmount * 10; // Payout 3x the bet amount for a win
            cash += winnings;
            cout << "Congratulations! You won $ " << winnings << " ! \nYou won Jackpot" << endl;
        }







        else if(symbol1 == '?' && symbol2 == '?' && symbol3 == '?') {
            int winnings = betAmount * 5; // Payout 3x the bet amount for a win
            cash += winnings;
            cout << "Congratulations! You won $ " << winnings << " !" << endl;
        }
        else if(symbol4 == '?' && symbol5 == '?' && symbol6 == '?') {
            int winnings = betAmount * 5; // Payout 3x the bet amount for a win
            cash += winnings;
            cout << "Congratulations! You won $ " << winnings << "  !" << endl;
        }
        else if(symbol7 == '?' && symbol8 == '?' && symbol9 == '?') {
            int winnings = betAmount * 5; // Payout 3x the bet amount for a win
            cash += winnings;
            cout << "Congratulations! You won $ " << winnings << " !" << endl;
        }
        else if(symbol1 == '?' && symbol4 == '?' && symbol7 == '?') {
            int winnings = betAmount * 5; // Payout 3x the bet amount for a win
            cash += winnings;
            cout << "Congratulations! You won $ " << winnings << "  !" << endl;
        }
        else if(symbol2 == '?' && symbol5 == '?' && symbol8 == '?') {
            int winnings = betAmount * 5; // Payout 3x the bet amount for a win
            cash += winnings;
            cout << "Congratulations! You won $ " << winnings << " !" << endl;
        }
        else if(symbol3 == '?' && symbol6 == '?' && symbol9 == '?') {
            int winnings = betAmount * 5; // Payout 3x the bet amount for a win
            cash += winnings;
            cout << "Congratulations! You won $ " << winnings << " !" << endl;
        }
        else{

            cout << "Sorry, you did not win this time." << endl;
             cash -= betAmount;

             if (cash <= 0) {
                    saveValue();
                replayOrNot();

                }
        }
    }

}





/* ------------------------------one row--------------------------------------*/


    if(rows == 1)
    {
        a=false;
        system("cls");
        casinorule();
       a=false;
    while (cash > 0) {
        // Get the bet amount from the player
         cout << "Your balance: $ " << cash << endl << endl;
         a=false;
         cout << "Enter your bet (0 to quit): $";

         cin >> betAmount;
         cin.clear();
    cin.ignore();

        while(betAmount < 0){
            cout << "Enter bet amount which is greater than zero: $ ";
            cin >> betAmount;
            cin.clear();
    cin.ignore(1000,'\n');
        }
        if (betAmount == 0) {

             cout << "Thank you for playing. Goodbye!";
             main();
        }

        if (betAmount > cash) {
            cout << "Insufficient credits. Please place a valid bet." << endl;
            continue;
        }

        // Spin the reels
        char symbol1 = spinReel(reel1Symbols);
        char symbol2 = spinReel(reel2Symbols);
        char symbol3 = spinReel(reel3Symbols);

        // Display the result
        cout << "Result: " << symbol1 << " " << symbol2 << " " << symbol3 << std::endl;

        // Check for win
        if(symbol1 == '*' && symbol2 == '*' && symbol3 == '*') {
            int winnings = betAmount * 3; // Payout 3x the bet amount for a win
            cash += winnings;
            cout << "Congratulations! You won $ " << winnings << " !" << std::endl;
        }
        else if(symbol1 == '7' && symbol2 == '7' && symbol3 == '7') {
            int winnings = betAmount * 10; // Payout 3x the bet amount for a win
            cash += winnings;
            cout << "Congratulations! You won $" << winnings << " ! \nYou won Jackpot" << std::endl;
        }
        else if(symbol1 == '?' && symbol2 == '?' && symbol3 == '?') {
            int winnings = betAmount * 5; // Payout 3x the bet amount for a win
            cash += winnings;
            cout << "Congratulations! You won $" << winnings << " !" << std::endl;
        }
        else{

            cout << "Sorry, you did not win this time." << endl;
            a=false;
            cash -= betAmount;
            if (cash <= 0) {
                    saveValue();
                replayOrNot();
                return;
                }
        }
    }

  }
  else{
    do{
      cout << "Invalid rows." << endl;
      cout << "\nEnter spin rows('1' for 1 row of spin or '3' for 3 rows of spin): ";
      cin >> rows;
      cin.clear();
    cin.ignore(1000,'\n');
    }while(!(rows==1 || rows==3));
}
}while(!(a==false));
saveValue();
main();
}

/////////////////////////////////////////////
void guessing()
{
    int bettingAmount;
    int guess;
    int dice; // hold computer generated number
    char choice;
    system("cls");
    cout << "\nWelcome from number guessing game";

    do
    {
        system("cls");
    cout << "\n\n";
    drawLine(80,'-');
    cout << "\t\tRULES OF THE GAME\n";
    drawLine(80,'-');
    cout << "\t1. Choose any number between 1 to 10\n";
    cout << "\t2. If you win you will get 10 times of money you bet\n";
    cout << "\t3. If you bet on wrong number you will lose your betting amount\n\n";
    drawLine(80,'-');
        cout << "\n\nYour current balance is $ " << cash << "\n";
		// Get player's betting amount
        do
        {
            cout << "Enter money to bet: $ ";
            cin >> bettingAmount;
            cin.clear();
    cin.ignore(1000,'\n');
            while(bettingAmount <= 0)
            {
                cout << "Enter money which is greater than zero: $ ";
                cin >> bettingAmount;
                cin.clear();
    cin.ignore(1000,'\n');
            }
            if(bettingAmount > cash)
                cout << "Your betting amount is more than your current balance\n"
                     << "\nRe-enter data\n ";
        }while(bettingAmount > cash);

		// Get player's numbers
        do
        {
            cout << "Guess your number to bet between 1 to 10 :";
            cin >> guess;
            cin.clear();
    cin.ignore(1000,'\n');
            if(guess <= 0 || guess > 10)
                cout << "Please check the number!! should be between 1 to 10\n"
                    <<"\nRe-enter data\n ";
        }while(guess <= 0 || guess > 10);

        dice = rand()%10 + 1; // Will hold the randomly generated integer between 1 and 10

        if(dice == guess)
        {
            cout << "\n\nGood Luck!! You won Rs." << bettingAmount * 10;
            cash = cash + bettingAmount * 10;
        }
        else
        {
            cout << "\nBad Luck this time !! You lost $ "<< bettingAmount <<"\n";
            cash = cash - bettingAmount;
        }

        cout << "\nThe winning number was : " << dice <<"\n";
        cout << "\nYou have $ " << cash << "\n";
        if( cash == 0)
        {
            replayOrNot();
            return;
        }
        cout << "\n\n--->Do you want to play again (y/n)? ";
        cin >> choice;
    }while(choice =='Y'|| choice=='y');
    saveValue();
    main();
}

void drawLine(int n, char symbol)
{
    for(int i=0; i<n; i++)
        cout << symbol;
    cout << "\n" ;
}
void casinodrawLine(int n, char symbol)
{
    for(int i=0; i<n; i++)
       std:: cout << symbol;
       std::cout << "\n" ;
}

void casinorules()
{
    system("cls");
    cout << "\n\n";
    casinodrawLine(115,'-');
    cout << "\t\t\t\tRULES OF THE GAME\n";
    casinodrawLine(115,'-');
    cout << "\t1. If you get 3 '*' in row or column at max in one row or column, you will get 3 times of money you bet\n";
    cout << "\t2. If you get 3 '?' in row or column at max in one row or column, you will get 5 times of money you bet\n";
    cout << "\t3. If you get 3 '7' in row or column at max in one row or column, you will get 10 times of money you bet\n";
    cout << "\t   The more you bet , the more you get money\n\n";
    casinodrawLine(115,'-');
}
void casinorule()
{
    system("cls");
    cout << "\n\n";
    casinodrawLine(80,'-');
    cout << "\t\t\t\tRULES OF THE GAME\n";
    casinodrawLine(80,'-');
    cout << "\t1. If you get 3 '*', you will get 3 times of money you bet\n";
    cout << "\t2. If you get 3 '?', you will get 5 times of money you bet\n";
    cout << "\t3. If you get 3 '7', you will get 10 times of money you bet\n";
    cout << "\t   The more you bet, the more you get money\n\n";
    casinodrawLine(80,'-');
}
/*void bankrupt() {

    dollars = 50;
    cout << "\n You have gone bankrupt! Time to start over." << endl;
    cout << "\n ";
    system("pause");
}*/



void coinToss() {
    if (cash <= 0) {
        replayOrNot();
        return;
    }
    system("cls");
     char playAgain;
    cout << "Welcome to Our Coin Toss Game!" <<endl;
    cout<<"\nYour balance: $"<<cash<<endl;
    do{
    cout << "\nEnter bet amount:$ ";
    int betAmount;
  cin >> betAmount;
  cin.clear();
    cin.ignore(1000,'\n');

 while(betAmount > cash)
 {
     cout << "\nInsufficient amount.Please enter bet amount again: ";
     cin >> betAmount;
     cin.clear();
    cin.ignore(1000,'\n');
 }
  while(betAmount<=0){
    cout<< "\nInvalid amount.Please enter your bet greater than zero:$ ";
    cin>>betAmount;
    cin.clear();
    cin.ignore(1000,'\n');
  }
    int playerChoice;
   cout << "\nChoose your bet:\n";
   cout << "1. Heads\n";
    cout << "2. Tails\n" << endl;
   cout << "> ";
   cin >> playerChoice;
   cin.clear();
    cin.ignore(1000,'\n');

    while(!(playerChoice == 1 || playerChoice ==2))
    {
        cout << "\nEnter valid choice(1 for 'Head' or 2 for 'Tail': ";
        cin >> playerChoice;
        cin.clear();
    cin.ignore(1000,'\n');
    }

    int coinSide = rand() % 2 + 1;

    cout << "\nFlipping the coin..." << endl;
    if (coinSide == 1) {
        cout << "The coin landed on: Heads" << endl;
    } else {
        cout << "The coin landed on: Tails" << endl;
    }

    if (coinSide == playerChoice) {
        int winnings = betAmount * 2;
        cash += winnings;
        cout << "Congratulations! You won $ " << winnings << "!" <<endl;
    } else {
        cash -= betAmount;
        cout << "Sorry, you lost $ " << betAmount << "." <<endl;
    }
    cout << "\nYour current balance:$ " << cash<<endl;
    if (cash <= 0) {
        replayOrNot();
    }
    else{
       cout << "\nDo you want to play again? (y/n): ";
       cin >> playAgain;
    }
    }while(playAgain == 'y' || playAgain == 'Y');
    saveValue();
    main();
}
