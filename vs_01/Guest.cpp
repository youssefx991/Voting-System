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
    auto &elections = system->getElections();
    int totalOptions = elections.size() + 1; // All elections + "Back"
    int current = 0;
    char input;

    while (true)
    {
        ::system("cls");
        gotoxy(45, 7);
        cout << "===== AVAILABLE ELECTIONS =====";

        // Draw elections
        for (int i = 0; i < elections.size(); i++)
        {
            gotoxy(45, 9 + i * 2);
            if (current == i)
                cout << "\033[47;30m> ID: " << elections[i].getElectionId()
                     << " | " << elections[i].getTitle() << " <\033[0m";
            else
                cout << "  ID: " << elections[i].getElectionId()
                     << " | " << elections[i].getTitle();
        }

        // Draw "Back" option
        gotoxy(45, 9 + elections.size() * 2);
        if (current == totalOptions - 1)
            cout << "\033[47;30m>    Back     <\033[0m";
        else
            cout << "   Back   ";

        // Get user input
        input = _getch();
        if (input == -32) input = _getch(); // arrow keys

        switch (input)
        {
        case 72: // UP
            if (current > 0) current--;
            break;
        case 80: // DOWN
            if (current < totalOptions - 1) current++;
            break;
        case 13: // ENTER
            if (current == totalOptions - 1) // Back
            {
                return;
            }
            else // An election selected
            {
                int electionId = elections[current].getElectionId();
                viewElectionDetails(electionId);
                cout <<endl<< "Press any key to continue...";
                _getch();
            }
            break;
        case 27: // ESC
            return;
        }

        Sleep(80); // smooth hover effect
    }
}


void Guest::viewElectionDetails(int electionId)
{
    ::system("cls");
    bool found = false;
    int y = 7; // starting row

    for (const Election &e : system->getElections())
    {
        if (e.getElectionId() == electionId)
        {
            gotoxy(45, y++);
            cout << "===== Election Details =====";

            gotoxy(45, y++);
            cout << "Title: " << e.getTitle();

            gotoxy(45, y++);
            cout << "Description: " << e.getDescription();

            gotoxy(45, y++);
            cout << "Status: ";
            if (e.getStatus() == ElectionStatus::CREATED)
                cout << "Not Opened";
            else if (e.getStatus() == ElectionStatus::OPENED)
                cout << "Opened";
            else
                cout << "Closed";

            system->viewElectionCandidates(const_cast<Election*>(&e));

            if (e.getStatus() == ElectionStatus::CLOSED)
            {
                cout << "Election Results:";
                system->displayElectionResults(electionId);
            }
            found = true;
            break;
        }
    }

    if (!found)
    {
        gotoxy(45, y++);
        cout << "Election not found with ID " << electionId << ".";
    }

    cout << "Press any key to go back...";
    _getch();
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
     ::system("cls");
}


//ss
void Guest::viewAllCandidates()
{

    auto &users = system->getUsers();

    // Filter candidates
    std::vector<User*> candidates;
    for (User* u : users)
        if (u->getRole() == "Candidate")
            candidates.push_back(u);

    int totalOptions = candidates.size() + 1; // all candidates + "Back"
    int current = 0;
    char input;

    while (true)
    {
        //::system("cls");
        int y = 7;
        gotoxy(45, y); y += 2;
        cout << "===== ALL CANDIDATES =====";

        // Display candidates
        for (int i = 0; i < candidates.size(); i++)
        {
            gotoxy(35, y); y += 2;

            if (current == i)
                cout << "\033[47;30m> "
                     << "ID: " << candidates[i]->getUserId()
                     << " | Username: " << candidates[i]->getUsername()
                     << " | Email: " << candidates[i]->getEmail()
                     << " <\033[0m";
            else
                cout << "  ID: " << candidates[i]->getUserId()
                     << " | Username: " << candidates[i]->getUsername()
                     << " | Email: " << candidates[i]->getEmail()<<"  ";

            gotoxy(45, y); y += 2;
            cout << "==============================";
        }

        // Display "Back" option
        gotoxy(55, y); y += 2;
        if (current == totalOptions - 1)
            cout << "\033[47;30m> Back <\033[0m";
        else
            cout << "  Back   ";

        // Get input
        input = _getch();
        if (input == -32) input = _getch(); // arrow keys

        switch (input)
        {
        case 72: // UP
            if (current > 0) current--;
            break;
        case 80: // DOWN
            if (current < totalOptions - 1) current++;
            break;
        case 13: // ENTER
            if (current == totalOptions - 1) // Back
                return;
            else // Candidate selected
                viewCandidateDetails(candidates[current]->getUserId());
            break;
        case 27: // ESC
            return;
        }

        Sleep(80); // smooth highlight effect
    }
}

