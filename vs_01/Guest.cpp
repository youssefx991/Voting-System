#include "Guest.h"
#include "VotingSystem.h"
#include "Election.h"
#include "User.h"
#include <iostream>

using namespace std;

/* ---------- Constructor ---------- */
Guest::Guest(VotingSystem* sys) : system(sys) {}

/* ---------- Methods ---------- */
void Guest::viewVotingRules()
{
    int choice = -1;
    do
    {
        cout << "\n===== Voting Rules =====\n";
        cout << "1. Each voter can vote only once per election.\n";
        cout << "2. Voting is allowed only when the election is OPEN.\n";
        cout << "3. Votes cannot be changed after submission.\n";
        cout << "4. Banned users are not allowed to vote.\n";
        cout << "5. Candidates cannot vote in elections they participate in.\n";
        cout << "0. Back to Guest Menu\n";
        cout << "========================\n";
        cout << "Enter 0 to go back: ";
        cin >> choice;

        if (choice != 0)
            cout << "Invalid input. Press 0 to go back.\n";

    } while (choice != 0);
}

void Guest::viewElections()
{
    int choice = -1;

    do
    {
        cout << "\n===== AVAILABLE ELECTIONS =====\n";

        for (const Election &e : system->getElections())
        {
            cout << "ID: " << e.getElectionId()
                 << " | Title: " << e.getTitle()
                 << " | Status: ";

            if (e.getStatus() == ElectionStatus::CREATED)
                cout << "Created";
            else if (e.getStatus() == ElectionStatus::OPENED)
                cout << "Opened";
            else
                cout << "Closed";

            cout << endl;
        }

        cout << "\n===== OPTIONS =====\n";
        cout << "1. View Election Details\n";
        cout << "2. View Election Candidates\n";
        cout << "0. Back\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            int electionId;
            cout << "Enter Election ID: ";
            cin >> electionId;
            viewElectionDetails(electionId);
            break;
        }
        case 2:
        {
            int electionId;
            cout << "Enter Election ID: ";
            cin >> electionId;
            viewCandidates(electionId);
            break;
        }
        case 0:
            cout << "Returning to Guest Menu...\n";
            break;

        default:
            cout << "Invalid choice. Try again.\n";
        }

    } while (choice != 0);
}


void Guest::viewElectionDetails(int electionId)
{
    for (const Election &e : system->getElections())
    {
        if (e.getElectionId() == electionId)
        {
            cout << "\n===== Election Details =====\n";
            cout << "Title: " << e.getTitle() << endl;
            cout << "Description: " << e.getDescription() << endl;
            cout << "Status: ";

            if (e.getStatus() == ElectionStatus::CREATED)
                cout << "Created";
            else if (e.getStatus() == ElectionStatus::OPENED)
                cout << "Opened";
            else
                cout << "Closed";

            cout << endl;
            break;
        }
    }

    cout << "\n0. Back\n";
    cout << "Enter 0 to return: ";
    int back;
    cin >> back;
}


void Guest::viewCandidates(int electionId)
{
    bool electionFound = false;

    for (Election &e : system->getElections())
    {
        if (e.getElectionId() == electionId)
        {
            electionFound = true;
            cout << "\nCandidates for Election: " << e.getTitle() << "\n";

            for (int candidateId : e.getCandidates())
            {
                for (User *u : system->getUsers())
                {
                    if (u->getUserId() == candidateId &&
                        u->getRole() == "Candidate")
                    {
                        cout << "- ID: " << u->getUserId()
                             << " | Username: " << u->getUsername()
                             << " | Email: " << u->getEmail() << endl;
                    }
                }
            }
            break;
        }
    }

    if (!electionFound)
        cout << "Election not found.\n";

    cout << "\n0. Back\n";
    cout << "Enter 0 to return: ";
    int back;
    cin >> back;
}
