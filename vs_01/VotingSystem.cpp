#include "VotingSystem.h"

#include "User.h"
#include "Candidate.h"
#include "Voter.h"
#include "Admin.h"
#include "Election.h"
#include "Vote.h"
#include "UI.h"

#include <iostream>
#include <limits>

using namespace std;

/* ---------- Destructor ---------- */
VotingSystem::~VotingSystem()
{
    for (User* u : users)
    {
        delete u;
    }
}

/* ---------- Getters ---------- */
vector<Election>& VotingSystem::getElections()
{
    return elections;
}

vector<User*>& VotingSystem::getUsers()
{
    return users;
}

vector<Vote>& VotingSystem::getVotes()
{
    return votes;
}

/* ---------- Fill Dummy Data ---------- */
void VotingSystem::fillData()
{
    /* ----------- Elections ----------- */
    elections.emplace_back(1, "Student Union Election",
                            "Choose the student union president");

    elections.emplace_back(2, "Club Leader Election",
                            "Choose the club leader");

    /* ----------- Candidates ----------- */
    users.push_back(new Candidate(101, "cand1", "c1@mail.com", "123", "Profile 1", this));
    users.push_back(new Candidate(102, "cand2", "c2@mail.com", "123", "Profile 2", this));
    users.push_back(new Candidate(103, "cand3", "c3@mail.com", "123", "Profile 3", this));
    users.push_back(new Candidate(104, "cand4", "c4@mail.com", "123", "Profile 4", this));
    users.push_back(new Candidate(105, "cand5", "c5@mail.com", "123", "Profile 5", this));

    elections[0].addCandidate(101);
    elections[0].addCandidate(102);

    elections[1].addCandidate(103);
    elections[1].addCandidate(104);
    elections[1].addCandidate(105);

    /* ----------- Voters ----------- */
    for (int i = 1; i <= 10; ++i)
    {
        users.push_back(
            new Voter(i,
                      "voter" + to_string(i),
                      "v" + to_string(i) + "@mail.com",
                      "123",
                      this));
    }

    /* ----------- Admins ----------- */
    for (int i = 1; i <= 10; ++i)
    {
        users.push_back(
            new Admin(1000 + i,
                      "admin" + to_string(i),
                      "admin" + to_string(i) + "@mail.com",
                      "123",
                      this));
    }

    /* ----------- Votes ----------- */
    votes.emplace_back(1, 1, 1, 101);
    votes.emplace_back(2, 1, 2, 102);
    votes.emplace_back(3, 2, 3, 103);
    votes.emplace_back(4, 2, 4, 104);
    votes.emplace_back(5, 2, 5, 105);
}


void VotingSystem::run() {
    Admin* admin = new Admin(1001, "votingsysAdmin", "admin1@mail.com", "123", this);
    // For testing, we directly call adminMenu with a dummy admin
    loading("Loading admin menu");
    adminMenu(admin);
}
void VotingSystem::guestMenu() {}
void VotingSystem::voterMenu(Voter* voter) {}
void VotingSystem::adminMenu(Admin* admin) {
    int choice;
    string adminName = admin->getUsername();
    cout << BOLD <<"WELCOME " << adminName << "!" << RESET << endl  ;
    do {
    
        cout << "1. Create Election\n";
        cout << "2. View All Elections\n";
        cout << "3. View All Voters\n";
        cout << "0. Logout\n";
        cout << "Choose: ";
        cin >> choice;
        if (choice < 0 || choice > 3 || cin.fail()) {
            cin.clear(); // clear the fail state
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard invalid input
            cout << RED << "Invalid input! Please enter a number from 0 to 3 .\n" << RESET;
        }   
        switch (choice) {
            case 1: admin->createElection(); break;
            case 2: admin->viewElections(); break;
            case 3: admin->viewVoters(); break;
            case 0:
                cout << YELLOW << "Logging out...\n" << RESET;
                admin->logout();
                break;
            default:
                cout << RED << "Invalid choice!\n" << RESET;
        }
    } while (choice != 0);
}
