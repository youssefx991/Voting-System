#include <iostream>
#include <limits>
#include<windows.h>
#include <conio.h>
#include <string.h>

#include "VotingSystem.h"
#include "Guest.h"
#include "Admin.h"
#include "Candidate.h"
#include "Election.h"
#include "User.h"

using namespace std;

/* ---------- Test Declarations ---------- */
void testGuest(VotingSystem& system);
void testAdmin(VotingSystem& system);
void testCandidate(VotingSystem& system);

/* ---------- main ---------- */
int main()
{
       HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    SetConsoleMode(hOut, dwMode | 0x0004);

    cout<< "===== VOTING SYSTEM TESTS =====\n";
    VotingSystem system;
    system.fillData();
    system.run();

    // testGuest(system);
    // testAdmin(system);
    // testCandidate(system);

    return 0;
}


void testGuest(VotingSystem& system)
{
    cout << "\n===== TEST: GUEST =====\n";

    Guest guest(&system);

    cout << "\n--- Voting Rules ---\n";
    guest.viewVotingRules();

    cout << "\n--- View Elections ---\n";
    guest.viewElections();

    cout << "\n--- Election Details (ID = 1) ---\n";
    guest.viewElectionDetails(1);

    cout << "\n--- Election Details (Invalid) ---\n";
    guest.viewElectionDetails(999);

    cout << "\n--- Candidates (Election ID = 1) ---\n";
    guest.viewCandidates(1);

    cout << "\n--- Candidates (Invalid Election ID) ---\n";
    guest.viewCandidates(999);
}


void testAdmin(VotingSystem& system)
{
    cout << "\n===== TEST: ADMIN =====\n";

    cout << "\n--- Ensure Admins Created ---\n";
    for (User* u : system.getUsers())
    {
        if (u->getRole() == "Admin")
        {
            cout << "Admin ID: " << u->getUserId()
                 << ", Username: " << u->getUsername() << endl;
        }
    }

    Admin* adminUser = nullptr;

    for (User* u : system.getUsers())
    {
        if (u->getRole() == "Admin")
        {
            adminUser = dynamic_cast<Admin*>(u);
            break;
        }
    }

    if (!adminUser)
    {
        cout << "No admin found.\n";
        return;
    }

    cout << "\n--- Create Election ---\n";
    int id = adminUser->createElection();

    for (const Election& e : system.getElections())
    {
        if (e.getElectionId() == id)
        {
            cout << "Created Election: "
                 << e.getElectionId() << " | "
                 << e.getTitle() << endl;
        }
    }

    cout << "\nEnter election id to UPDATE: ";
    cin >> id;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    adminUser->updateElection(id);

    cout << "\nEnter election id to OPEN: ";
    cin >> id;
    adminUser->openElection(id);

    cout << "\nEnter election id to CLOSE: ";
    cin >> id;
    adminUser->closeElection(id);

    cout << "\n--- View Voters ---\n";
    adminUser->viewVoters();
}


void testCandidate(VotingSystem& system)
{
    cout << "\n===== TEST: CANDIDATE =====\n";

    cout << "\n--- All Users ---\n";
    for (User* u : system.getUsers())
    {
        cout << "ID: " << u->getUserId()
             << ", Username: " << u->getUsername()
             << ", Role: " << u->getRole() << endl;
    }

    Candidate* existingCandidate = nullptr;

    for (User* u : system.getUsers())
    {
        if (u->getRole() == "Candidate")
        {
            existingCandidate = dynamic_cast<Candidate*>(u);
            break;
        }
    }

    if (existingCandidate)
    {
        cout << "\n--- Existing Candidate Login ---\n";
        existingCandidate->login();
        existingCandidate->viewMyElections();
        existingCandidate->logout();
    }

    cout << "\n--- Candidate Registration ---\n";
    Candidate* newCandidate =
        new Candidate(999, "", "", "", "", &system);

    newCandidate->registerUser();

    cout << "\n--- Login After Registration ---\n";
    newCandidate->login();
}


