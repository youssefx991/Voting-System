#include "User.h"
#include "VotingSystem.h"
#include "Election.h"
#include "ConsoleUI.h"
#include "UI.h"
#include <iostream>

using namespace std;

/* ---------- Constructor / Destructor ---------- */
User::User(int id, string uname, string mail, string pass, VotingSystem* sys)
    : userId(id),
      username(uname),
      email(mail),
      password(pass),
      isBanned(false),
      system(sys)
{
}

User::~User() {}

/* ---------- Getters ---------- */
bool User::getBanStatus() const
{
    return isBanned;
}

void User::ban()
{
    isBanned = true;
}

int User::getUserId() const
{
    return userId;
}

string User::getPassword() const
{
    return password;
}

string User::getUsername() const
{
    return username;
}

string User::getEmail() const
{
    return email;
}

/* ---------- Logic ---------- */
void User::viewElections()
{
    for (const Election& e : system->getElections())
    {
        // display each election in single line
        cout<<"ID: "<< e.getElectionId()
            <<", Title: " << e.getTitle()
            <<", Description: " << e.getDescription()
            <<", Status: " << (e.isOpen() ? "Open" : "Closed")
            << endl;
        // display candidates in election
        system->viewElectionCandidates(const_cast<Election*>(&e));
        cout << "----------------------------------------\n";
    }
}

void User::login()
{
    bool validInput = false;
    do
    {
        int centerX = 45;
        int startY = 7;

        gotoxy(centerX, startY);
        cout << BOLD << "=========== LOGIN ===========" << RESET;

        gotoxy(centerX, startY + 3);
        cout << "Username:";

        gotoxy(centerX, startY + 5);
        cout << "Password:";

        string username = inputField(centerX + 12, startY + 3, 20, false);
        string password = inputField(centerX + 12, startY + 5, 20, true);


        for (User* user : system->getUsers())
        {
            if (user->getUsername() == username &&
                user->getPassword() == password)
            {
                // check user role in correct menu
                if (user->getRole() != this->getRole()) break;

                userId = user->getUserId();
                username = username;
                password = password;
                gotoxy(55,20);
                cout << "Login successful!" << endl;
                validInput = true;
                break;
            }
        }

        if (!validInput)
        {
            gotoxy(40,20);
            cout << "Invalid username or password. Please try again." << endl;
        }

    } while (!validInput);
}



void User::registerUser()
{
    bool validInput = false;

    do
    {
        //::system("cls");

        int centerX = 45;
        int startY  = 6;

        gotoxy(centerX, startY);
        cout << BOLD << "========= REGISTER =========" << RESET;

        gotoxy(centerX, startY + 3);
        cout << "Username:";

        gotoxy(centerX, startY + 5);
        cout << "Email:";

        gotoxy(centerX, startY + 7);
        cout << "Password:";

        string inputUsername = inputField(centerX + 12, startY + 3, 20, false);
        string inputEmail    = inputField(centerX + 12, startY + 5, 25, false);
        string inputPassword = inputField(centerX + 12, startY + 7, 20, true);

        bool exists = false;

        // check username
        for (User* user : system->getUsers())
        {
            if (user->getUsername() == inputUsername)
            {
                gotoxy(38, startY + 11);
                cout << RED << "Username already exists." << RESET;
                exists = true;
                break;
            }
        }

        if (exists) continue;

        // check email
        for (User* user : system->getUsers())
        {
            if (user->getEmail() == inputEmail)
            {
                gotoxy(38, startY + 11);
                cout << RED << "Email already registered." << RESET;
                exists = true;
                break;
            }
        }

        if (exists) continue;

        // generate userId
        int maxId = 0;
        for (User* user : system->getUsers())
            if (user->getUserId() > maxId)
                maxId = user->getUserId();

        userId   = maxId + 1;
        username = inputUsername;
        email    = inputEmail;
        password = inputPassword;

        system->getUsers().push_back(this);

        gotoxy(45, startY + 11);
        cout << GREEN << "Registration successful!" << RESET;

        validInput = true;

    } while (!validInput);
}

void User::logout()
{
    gotoxy(47,12);
    cout << "Logged out successfully." << endl;
}
