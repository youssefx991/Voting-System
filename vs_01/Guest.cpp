#include "Guest.h"
#include "VotingSystem.h"
#include "Election.h"
#include "User.h"
#include "UI.h"
#include "ConsoleUI.h"

#include <iostream>
#include <limits>
#include<windows.h>
#include <conio.h>
#include <string.h>


using namespace std;

/* ---------- Constructor ---------- */
Guest::Guest(VotingSystem* sys) : system(sys) {}

/* ---------- Methods ---------- */
#include <iostream>
#include <conio.h>  // for _getch() on Windows
using namespace std;

void Guest::viewVotingRules() {

    gotoxy(40, 7 + 0 * 2);
    cout << BOLD  << "================ VOTING RULES ================\n" << RESET;

    gotoxy(40, 7 + 1 * 2);
    cout << BOLD << GREEN << "1. Each voter can vote only once per election.\n" << RESET;
    gotoxy(40, 7 + 2 * 2);
    cout << BOLD  << GREEN << "2. Voting is allowed only when the election " << BOLD << "OPEN" << RESET << GREEN << ".\n" << RESET;
    gotoxy(40, 7 + 3 * 2);
    cout << BOLD  << GREEN << "3. Votes cannot be changed after submission.\n" << RESET;
    gotoxy(40, 7 + 4 * 2);
    cout << BOLD  << GREEN << "4. Banned users are not allowed to vote.\n" << RESET;
    gotoxy(40, 7 + 5 * 2);
    cout << BOLD << GREEN << "5. Candidates cannot vote in elections they participate in.\n" << RESET;
    gotoxy(40, 7 + 6 * 2);
    cout << BOLD << YELLOW << "Press ENTER to go back to Guest Menu\n" << RESET;
    gotoxy(40, 7 + 7 * 2);
    cout << BOLD  << "=============================================\n" << RESET;

    _getch();
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
//        cout << "2. View Election Candidates\n";
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
//        case 2:
//        {
//            int electionId;
//            cout << "Enter Election ID: ";
//            cin >> electionId;
//            void viewAllCandidates();
//            break;
//        }
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
    bool found = false;
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

            cout << "Candidates Participating:\n";
            system->viewElectionCandidates(const_cast<Election*>(&e));
            found = true;
            break;
        }
    }

    if (!found)
        cout << "Election not found with ID " << electionId << ".\n";
    cout << "\nEnter anything to go back: ";
    cin.ignore();
    cin.get();
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

    cout << "\nEnter anything to go back: ";
    cin.ignore();
    cin.get();
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
