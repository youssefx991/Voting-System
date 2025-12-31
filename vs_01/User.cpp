#include "User.h"
#include "VotingSystem.h"
#include "Election.h"

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
    string inputUsername, inputPassword;

    do
    {
        cout << "Enter username: ";
        cin >> inputUsername;

        cout << "Enter password: ";
        cin >> inputPassword;

        for (User* user : system->getUsers())
        {
            if (user->getUsername() == inputUsername &&
                user->getPassword() == inputPassword)
            {
                userId = user->getUserId();
                username = inputUsername;
                password = inputPassword;
                cout << "Login successful!" << endl;
                validInput = true;
                break;
            }
        }

        if (!validInput)
        {
            cout << "Invalid username or password. Please try again." << endl;
        }

    } while (!validInput);
}

void User::registerUser()
{
    bool exists;
    string inputUsername, inputEmail, inputPassword;

    do
    {
        exists = false;

        cout << "Enter username: ";
        cin >> inputUsername;

        for (User* user : system->getUsers())
        {
            if (user->getUsername() == inputUsername)
            {
                cout << "Username already exists." << endl;
                exists = true;
                break;
            }
        }

        if (exists) continue;

        cout << "Enter email: ";
        cin >> inputEmail;

        for (User* user : system->getUsers())
        {
            if (user->getEmail() == inputEmail)
            {
                cout << "Email already registered." << endl;
                exists = true;
                break;
            }
        }

        if (exists) continue;

        cout << "Enter password: ";
        cin >> inputPassword;

        break;

    } while (true);

    cout << "Registration successful!" << endl;

    username = inputUsername;
    email = inputEmail;
    password = inputPassword;
    
    // generate userId -- must be unique
    int maxId = 0;
    for (User *user : system->getUsers())
    {
        if (user->getUserId() > maxId)
        {
            maxId = user->getUserId();
        }
    }
    userId = maxId + 1;

    system->getUsers().push_back(this);
}

void User::logout()
{
    cout << "Logged out successfully." << endl;
}
