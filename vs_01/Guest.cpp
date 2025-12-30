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
            void viewAllCandidates();
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
void Guest::viewCandidateDetails(int candidateId)
{
    bool found = false;
    for (User* u : system->getUsers())
    {
        if (u->getUserId() == candidateId && u->getRole() == "Candidate")
        {
            found = true;
            cout << "\n===== Candidate Details =====\n";
            cout << "ID: " << u->getUserId() << endl;
            cout << "Username: " << u->getUsername() << endl;
            cout << "Email: " << u->getEmail() << endl;
            cout << "Role: " << u->getRole() << endl;


            cout << "Participating in Elections:\n";
            bool participates = false;
            for (const Election &e : system->getElections())
            {
                for (int id : e.getCandidates())
                {
                    if (id == candidateId)
                    {
                        participates = true;
                        cout << "- " << e.getTitle() << " (ID: " << e.getElectionId() << ")\n";
                    }
                }
            }
            if (!participates)
                cout << "This candidate is not participating in any election.\n";

            break;
        }
    }
    if (!found)
        cout << "Candidate not found.\n";

    cout << "\n0. Back\n";
    cout << "Enter 0 to return: ";
    int back;
    cin >> back;
}

void Guest::viewAllCandidates()
{
    cout << "\n===== ALL CANDIDATES =====\n";


    for (User* u : system->getUsers())
    {
        if (u->getRole() == "Candidate")
        {
            cout << "- ID: " << u->getUserId()
                 << " | Username: " << u->getUsername()
                 << " | Email: " << u->getEmail() << endl;
        }
    }


    int choice = -1;
    do
    {
        cout << "\nEnter Candidate ID to view details (0 to go back): ";
        cin >> choice;
        if (choice != 0)
            viewCandidateDetails(choice);
    } while (choice != 0);
}
