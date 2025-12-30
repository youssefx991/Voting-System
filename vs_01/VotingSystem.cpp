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

    int choice = 0;
    do
    {
        cout << "\n===== VOTING SYSTEM MAIN MENU =====\n";
        cout << "1. Guest\n";
        cout << "2. Candidate\n";
        cout << "3. Admin\n";
        cout << "4. Voter\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
             guestMenu();
            break;
        case 2:
            candidateAuthMenu();
            break;
        case 3:
        {
            // // adminAuthMenu(); to be implemented
            // Admin* admin = new Admin(1001, "votingsysAdmin", "admin1@mail.com", "123", this);
            // // For testing, we directly call adminMenu with a dummy admin
            // loading("Loading admin menu");
            // adminMenu(admin);
            adminAuthMenu();
            break;
        }
        case 4:
            //voterAuthMenu(); to be implemented
            voterAuthMenu();
            break;
        case 5:
            cout << "Exiting the system. Goodbye!\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 5);
}
void VotingSystem::guestMenu()
{
    int choice = 0;
    Guest guest(this);
    do
    {
        cout << "\n===== GUEST MENU =====\n";
        cout << "1. View Voting Rules\n";
        cout << "2. View Elections\n";
        cout << "3. View All Candidates\n";
        cout << "4. Back to Main Menu\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            guest.viewVotingRules();
            break;
        case 2:
            guest.viewElections();
            break;
        case 3:
            guest.viewAllCandidates();
            break;
        case 4:
            cout << "Returning to Main Menu...\n";
            break;
        default:
            cout << "Invalid choice. Try again.\n";
        }

    } while (choice != 4);
}


void VotingSystem::voterMenu(Voter* voter){
    int choice = 0;
    do
    {
        cout << "\n=== Voter Menu ===\n";
        cout << "1. Logout\n";
        cout << "Choice: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            voter->logout();
            return;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    } while (true);
}

void VotingSystem::adminMenu(Admin *admin)
{
    string adminName = admin->getUsername();
    cout << BOLD << "WELCOME " << adminName << "!" << RESET << endl;

    int choice = -1;

    while (true)
    {
        // Display main menu
        cout << "\n"
             << BOLD << "============================ Admin Menu ============================" << RESET << endl;
        cout << "1. Create Election\n";
        cout << "2. View All Elections\n";
        cout << "3. View All Voters\n";
        cout << "0. Logout\n";
        cout << "Choose: ";

        cin >> choice;

        // Input validation
        if (cin.fail() || choice < 0 || choice > 3)
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << RED << "Invalid input! Please enter a number from 0 to 3.\n"
                 << RESET;
            continue; // back to menu
        }

        switch (choice)
        {
        case 1:
            admin->createElection();
            break;

        case 2:
            admin->viewElections();
            break;

        case 3:
        {
            admin->viewVoters();

            int voterId = -1;
            cout << "Enter Voter ID to ban (or any invalid input to return): ";
            cin >> voterId;

            if (cin.fail() || voterId < 0)
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                loading("Returning to menu"); // optional animation
                break;
            }

            admin->banVoter(voterId);
            break;
        }

        case 0:
            cout << YELLOW << "Logging out...\n"
                 << RESET;
            admin->logout();
            return; // exit menu

        default:
            cout << RED << "Invalid choice!\n"
                 << RESET;
            break;
        }
    }
}


/* -------- Candidate Menus --------*/
void VotingSystem::candidateAuthMenu()
{
    int choice = 0;
    do
    {
        cout << "\n===== CANDIDATE AUTH MENU =====\n";
        cout << "1. Login\n";
        cout << "2. Register\n";
        cout << "3. Back to Main Menu\n";
        cout << "Enter your choice: ";
        cin >> choice;

        Candidate *candidate = nullptr;
        switch (choice)
        {
        case 1:
        {
            candidate = new Candidate(0, "", "", "", "", this);
            candidate->login();
            loading("Loading candidate menu");
            candidateMenu(candidate);
            break;
        }
        case 2:
        {
            candidate = new Candidate(0, "", "", "", "", this);
            candidate->registerUser();
            loading("Loading candidate menu");
            candidateMenu(candidate);
            break;
        }
        case 3:
            cout << "Returning to Main Menu.\n";
            // function to return to main menu will be added later
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 3);
}
void VotingSystem::candidateMenu(Candidate *candidate)
{
    int choice = 0;
    do
    {
        cout << "\n=== Candidate Menu ===\n";
        cout << "1. View My Elections\n";
        cout << "2. Logout\n";
        cout << "Choice: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            candidateElectionsMenu(candidate);
            break;
        case 2:
            candidate->logout();
            return;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    } while (true);
}
void VotingSystem::candidateElectionsMenu(Candidate* candidate)
{
    cout << "\n=== My Elections ===\n";
    candidate->viewMyElections();

    int electionID;
    do
    {
        cout << "Enter Election ID to view details (or 0 to go back): ";
        cin >> electionID;
        if (electionID == 0)
            return;
        else
            candidateElectionDetailsMenu(candidate, electionID);
    } while (true);
}
void VotingSystem::candidateElectionDetailsMenu(Candidate* candidate, int electionID)
{
    Election* target = nullptr;

    for (Election& e : elections)
    {
        if (e.getElectionId() == electionID)
        {
            for (int cid : e.getCandidates())
            {
                if (cid == candidate->getUserId())
                {
                    target = &e;
                    break;
                }
            }
            if (target != nullptr)
                break;
        }
    }

    if (!target)
    {
        cout << "Election not found.\n";
        return;
    }

    int choice = 0;
    do
    {
        cout << "\n=== Election Details ===\n";
        cout << "Title: " << target->getTitle() << endl;
        cout << "Description: " << target->getDescription() << endl;
        cout<< "Status: " << (target->isOpen() ? "OPENED" : "NOT OPENED") << endl;
        // total number of votes in this election, for all candidates
        int voteCount = 0;
        for (const Vote &v : votes)
        {
            if (v.getElectionId() == electionID)
            {
                voteCount++;
            }
        }
        // number of voters all candidates
        cout << "Number of Candidates: " << target->getCandidates().size() << endl;
        cout <<"Number of Votes: " << voteCount << endl;

        if (target->getStatus() == ElectionStatus::CLOSED)
        {
            int myVotes = candidate->viewVoteCount(electionID);
            cout << "Your Votes: " << myVotes << endl;
        }

        cout << "1. View Election Candidates\n";
        cout << "2. Back to My Elections\n";
        cout << "Choice: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            viewElectionCandidates(target);
            break;
        case 2:
            return;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    } while (true);
}
void VotingSystem::viewElectionCandidates(Election* election)
{
    cout << "\n=== All Candidates in Election: " << election->getTitle() << " ===\n";
    for (int candidateId : election->getCandidates())
    {
        for (User* u : users)
        {
            if (u->getUserId() == candidateId &&
                u->getRole() == "Candidate")
            {
                cout << "- Candidate ID: " << u->getUserId()
                     << ", Username: " << u->getUsername()
                     << ", Email: " << u->getEmail() << endl;
            }
        }
    }

    cout << "Press anything to go back: ";
    cin.ignore();
    cin.get();
    return;
}

/* ---------- Authentication Menus ---------- */
void VotingSystem::adminAuthMenu()
{
    // Implementation for admin authentication menu
    int choice = 0;
    do
    {
        cout << "\n===== Admin AUTH MENU =====\n";
        cout << "1. Login\n";
        cout << "2. Register\n";
        cout << "3. Back to Main Menu\n";
        cout << "Enter your choice: ";
        cin >> choice;

        Admin *admin = nullptr;
        switch (choice)
        {
        case 1:
        {
            admin = new Admin(0, "", "", "", this);
            admin->login();
            loading("Loading admin menu");
            adminMenu(admin);
            break;
        }
        case 2:
        {
            admin = new Admin(0, "", "", "", this);
            admin->registerUser();
            loading("Loading admin menu");
            adminMenu(admin);
            break;
        }
        case 3:
            cout << "Returning to Main Menu.\n";
            // function to return to main menu will be added later
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 3);
}

void VotingSystem::voterAuthMenu()
{
    // Implementation for voter authentication menu
    // Implementation for admin authentication menu
    int choice = 0;
    do
    {
        cout << "\n===== Voter AUTH MENU =====\n";
        cout << "1. Login\n";
        cout << "2. Register\n";
        cout << "3. Back to Main Menu\n";
        cout << "Enter your choice: ";
        cin >> choice;

        Voter *voter = nullptr;
        switch (choice)
        {
        case 1:
        {
            voter = new Voter(0, "", "", "", this);
            voter->login();
            loading("Loading voter menu");
            voterMenu(voter);
            break;
        }
        case 2:
        {
            voter = new Voter(0, "", "", "", this);
            voter->registerUser();
            loading("Loading voter menu");
            voterMenu(voter);
            break;
        }
        case 3:
            cout << "Returning to Main Menu.\n";
            // function to return to main menu will be added later
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 3);
}
