#include <iostream>
#include <fstream>
#include <vector>
using namespace std;



class LoginSystem {
    bool corUsrnm = false; // variable determing if the user is logged in yet - or not 
    bool corPword = false; // variable determining whether the user has inpputed a correct password

    public:
        void createAccount(){
            // adds new usernames to users.txt
            ofstream usrFile("users.txt",fstream::app);
            string newUsr;
            cout << "Enter new username: ";
            getline(cin,newUsr);
            usrFile << newUsr << endl;
            usrFile.close();

            // adds passwords to passwords.txt
            ofstream pWordFile("passwords.txt",fstream::app);
            string newPWord;
            cout << "Enter new password: ";
            getline(cin,newPWord);
            pWordFile << newPWord << endl;
            pWordFile.close();
        }

        int checkCredentials(string fileName,string credential,bool password=false,int lnFound=0){ // enter non .txt part of file name, enter result of g
            int lineNum = 0; // Line number for username in txt file
            int lineNum2 = 0; // Line number for password in txt file
            ifstream infile; // creates ifstream object "infile"
            infile.open(fileName + ".txt");
            bool credFound = false;
            string x;
            if(infile && !password){
                while(infile >> x && !credFound){
                    if(x == credential){ // Loops through the file to check if the username param that has been passed in is equal to any of the lines in the txt file
                        credFound = true;
                        corUsrnm = true;
                    }
                    lineNum++;
                }
                if(!credFound){ // If the username entered is not valid, then call the create account function
                    cout << "Incorrect username! Please create an account" << endl;
                    createAccount();
                }
            } else if (infile) {
                while(infile >> x){
                    if(x == credential){ 
                        corPword = true;
                    }
                    lineNum2++;
                }
            }
            infile.close();

            if(lineNum == lineNum2){
                cout << "Logged in successfully!" << endl;
            } 
            return lineNum;
        }

        /* This functions steps:
            1.First it gets the username and checks if its in the "users.txt" file it also records the line number (that's what the return statement is for)
            2.This function is called for a second time for the password
                - if the line number of the username and password are the same, then the login is successfull
        */

        string getCredentials(string phrase){ // This function simply prompts the user for their username, then returns it
            string username;
            cout << "Enter your " + phrase + ": ";
            getline(cin,username);
            return username;

        }
        void beginLogin(){
            int lineUsrnmFound;
            while(!corUsrnm) { // This loop will continously prompt the user for a username until they are logged in
                string currentUsername = getCredentials("username");
                lineUsrnmFound = checkCredentials("users",currentUsername);
                
            } 
            while(!corPword){
                string pWord = getCredentials("password");
                checkCredentials("passwords",pWord,true,lineUsrnmFound);
            }

        }

        
};

int main(){
    LoginSystem sys;
    sys.beginLogin();
    cout << "Login Successfull!" << endl;
            
    return 0;
}