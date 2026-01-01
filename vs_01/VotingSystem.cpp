#include "VotingSystem.h"

#include "User.h"
#include "Candidate.h"
#include "Voter.h"
#include "Admin.h"
#include "Election.h"
#include "Vote.h"
#include "UI.h"
#include "ConsoleUI.h"

#include <iostream>
#include <limits>
#include <unordered_map>
#include<windows.h>
#include <conio.h>

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


void VotingSystem::run()
{
    int current = 0;
    char input;

    do
    {
       // system("cls");
        drawVotingMenu(current);
        input = _getch();

        // Handle extended keys
        if (input == -32)
            input = _getch();

        switch (input)
        {
        case 72: // UP
            if (current > 0) current--;
            break;

        case 80: // DOWN
            if (current < 4) current++;
            break;

        case 13: // ENTER
            blinkSelection(9 + current * 2,3);
            system("cls");

            switch (current)
            {
            case 0: guestMenu(); break;
            case 1: candidateAuthMenu(); break;
            case 2: adminAuthMenu(); break;
            case 3: voterAuthMenu(); break;
            case 4: return; // Exit
            }
            break;

        case 27: // ESC
            return;
        }

        Sleep(80); // smooth effect, no flashing
    }
    while (true);
}

void VotingSystem::guestMenu()
{
    Guest guest(this);
    int current = 0;
    char input;

    while (true)
    {

        drawGuestMenu(current);
        input = _getch();

        if (input == -32)
            input = _getch();

        switch (input)
        {
        case 72: // UP
            if (current > 0) current--;
            break;

        case 80: // DOWN
            if (current < 3) current++;
            break;

        case 13: // ENTER
            blinkSelection(9 + current * 2,3,1);
            system("cls");

            switch (current)
            {
            case 0:
                guest.viewVotingRules();
                break;
            case 1:
                guest.viewElections();
                break;
            case 2:
                guest.viewAllCandidates();
                break;
            case 3:
                return; // Back to main menu
            }

            cout << "Press any key to continue...";
            _getch();
            system("cls");
            break;

        case 27:
            system("cls");
            return;
        }

        Sleep(80);
    }
}



void VotingSystem::voterMenu(Voter* voter)
{
    int current = 0;
    char input;

    const char* menu[] = { "View Rules", "View All Elections", "Logout" };
    const int menuSize = 3;

    while (true)
    {
        ::system("cls");

        gotoxy(45, 5);
        cout << BOLD << "===== VOTER MENU =====" << RESET;

        // Draw menu with hover effect
        for (int i = 0; i < menuSize; i++)
        {
            gotoxy(50, 8 + i * 2);
            if (i == current)
                cout << "\033[47;30m> " << menu[i] << " <\033[0m"; // highlighted
            else
                cout << "  " << menu[i] << "  ";
        }

        input = _getch();
        if (input == -32)
            input = _getch(); // extended key

        switch (input)
        {
        case 72: // UP
            if (current > 0) current--;
            break;

        case 80: // DOWN
            if (current < menuSize - 1) current++;
            break;

        case 13: // ENTER
            blinkSelection(8 + current * 2, 1, 1); // blink selected option
            switch (current)
            {
            case 0:
                voter->rulesMenu(); // View Rules
                break;
            case 1:
                voter->availableElectionsMenu(); // View Elections
                break;
            case 2:

                voter->logout(); // Logout
                ::system("cls");
                return;
            }
            break;

        case 27: // ESC
            voter->logout();
            return;
        }

        Sleep(80);
    }
}


void VotingSystem::adminMenu(Admin* admin)
{
    int current = 0;
    char input;

    while (true)
    {
        drawAdminMenu(current, admin->getUsername());
        input = _getch();

        if (input == -32)
            input = _getch();

        switch (input)
        {
        case 72: // UP
            if (current > 0) current--;
            break;

        case 80: // DOWN
            if (current < 3) current++;
            break;

        case 13: // ENTER
        {
            blinkSelection(11 + current * 2, 2, 1);
            system("cls");

            switch (current)
            {
            case 0: // Create Election
                admin->createElection();
                break;

            case 1: // View Elections
            {
                admin->viewElections();

                gotoxy(45, 20);
                cout << "Select Election ID:";
                int id = stoi(inputField(65, 20, 5, false));

                for (Election& e : elections)
                {
                    if (e.getElectionId() == id)
                        admin->getElection(e);
                }
                break;
            }

            case 2: // View Voters
            {
                admin->viewVoters();
                gotoxy(45, 20);
                cout << "Enter Voter ID to ban:";
                int id = stoi(inputField(68, 20, 5, false));
                admin->banVoter(id);
                break;
            }

            case 3: // Logout
                admin->logout();
                system("cls");
                return;
            }

            gotoxy(45, 23);
            cout << "Press any key to continue...";
            _getch();
            system("cls");
            break;
        }

        case 27: // ESC
            admin->logout();
            system("cls");
            return;
        }

        Sleep(80);
    }
}

/* -------- Candidate Menus --------*/
void VotingSystem::candidateAuthMenu()
{
    int current = 0;
    char input;

    while (true)
    {
        drawCandidateAuthMenu(current);
        input = _getch();

        if (input == -32)
            input = _getch(); // arrow keys

        switch (input)
        {
        case 72: // UP
            if (current > 0) current--;
            break;

        case 80: // DOWN
            if (current < 2) current++;
            break;

        case 13: // ENTER
        {
            blinkSelection(9 + current * 2, 3, 1);
            system("cls");

            Candidate* candidate = new Candidate(0, "", "", "", "", this);

            switch (current)
            {
            case 0:
                candidate->login();
                ::system("cls");
                gotoxy(47,0);
                loading("Loading candidate menu");
                candidateMenu(candidate);
                break;

            case 1: // Register
                candidate->registerUser();
                loading("Loading candidate menu");
                candidateMenu(candidate);
                break;

            case 2: // Back
                delete candidate;
                system("cls");
                return;
            }

            cout << "\nPress any key to continue...";
            _getch();
            system("cls");
            break;
        }

        case 27: // ESC
            system("cls");
            return;
        }

        Sleep(80);
    }
}
void VotingSystem::candidateMenu(Candidate* candidate)
{
    int current = 0;

    while (true)
    {
        system("cls");

        gotoxy(45, 7);
        cout << "===== CANDIDATE MENU =====";

        const char* menu[] =
        {
            "View My Elections",
            "      Logout     "
        };

        for (int i = 0; i < 2; i++)
        {
            gotoxy(48, 9 + i * 2);

            if (i == current)
                cout << "\033[47;30m> " << menu[i] << " <\033[0m";
            else
                cout << "   " << menu[i] << "  ";
        }

        char key = _getch();

        if (key == -32)
        {
            key = _getch();
            if (key == 72 && current > 0) current--;     // up
            if (key == 80 && current < 1) current++;    // down
        }
        else if (key == 13)
        {
            blinkSelection(9 + current * 2, 2, 2);

            if (current == 0)
                candidateElectionsMenu(candidate);
            else
            {
                candidate->logout();
                return;
            }
        }
    }
}

void VotingSystem::candidateElectionsMenu(Candidate* candidate)
{
    vector<Election*> myElections;

    for (Election& e : elections)
    {
        for (int cid : e.getCandidates())
            if (cid == candidate->getUserId())
                myElections.push_back(&e);
    }

    int current = 0;

    while (true)
    {
        system("cls");

        gotoxy(45, 7);
        cout << "===== MY ELECTIONS =====";

        int y = 9;

        for (int i = 0; i < myElections.size(); i++)
        {
            gotoxy(48, y + i * 2);

            if (i == current)
                cout << "\033[47;30m> "
                     << myElections[i]->getTitle()
                     << " <\033[0m";
            else
                cout << "  " << myElections[i]->getTitle() << "  ";
        }

        // Back
        gotoxy(48, y + myElections.size() * 2);
        if (current == myElections.size())
            cout << "\033[47;30m>      Back      <\033[0m";
        else
            cout << "       Back       ";

        char key = _getch();

        if (key == -32)
        {
            key = _getch();
            if (key == 72 && current > 0) current--;
            if (key == 80 && current < myElections.size()) current++;
        }
        else if (key == 13)
        {
            blinkSelection(y + current * 2, 2, 2);

            if (current == myElections.size())
                return;

            candidateElectionDetailsMenu(
                candidate,
                myElections[current]->getElectionId()
            );
        }
    }
}

void VotingSystem::candidateElectionDetailsMenu(Candidate* candidate, int electionID)
{
    Election* target = nullptr;
    for (Election& e : elections)
        if (e.getElectionId() == electionID)
            target = &e;

    if (!target) return;

    int current = 0;

    while (true)
    {
        system("cls");

        gotoxy(40, 5);
        cout << "===== ELECTION DETAILS =====";

        gotoxy(30, 8);
        cout << "Title: " << target->getTitle();

        gotoxy(30, 10);
        cout << "Description: " << target->getDescription();

        gotoxy(30, 12);
        cout << "Status: ";
        if (target->getStatus() == ElectionStatus::OPENED)
            cout << "OPEN";
        else if (target->getStatus() == ElectionStatus::CREATED)
            cout << "Not Opened";
        else
            cout << "CLOSED";

        gotoxy(30, 14);
        cout << "Candidates: " << target->getCandidates().size();

        int votesCount = 0;
        for (const Vote& v : votes)
            if (v.getElectionId() == electionID)
                votesCount++;

        gotoxy(30, 16);
        cout << "Votes: " << votesCount;

        if (target->getStatus() == ElectionStatus::CLOSED)
        {
            gotoxy(30, 18);
            cout << "Your Votes: "
                 << candidate->viewVoteCount(electionID);
            displayElectionResults(electionID);
        }

        const char* menu[] =
        {
            "View Election Candidates",
            "Back"
        };

        int y = 21;
        for (int i = 0; i < 2; i++)
        {
            gotoxy(48, y + i * 2);

            if (i == current)
                cout << "\033[47;30m> " << menu[i] << " <\033[0m";
            else
                cout << "  " << menu[i] << "  ";
        }

        char key = _getch();
        if (key == -32)
        {
            key = _getch();
            if (key == 72 && current > 0) current--;
            if (key == 80 && current < 1) current++;
        }
        else if (key == 13)
        {
            blinkSelection(y + current * 2, 2, 1);

            if (current == 0)
                viewElectionCandidates(target);
            else
                return;
        }
    }
}

void VotingSystem::viewElectionCandidates(Election* election)
{

    cout << "\n \n === All Candidates in Election: " << election->getTitle() << " ===\n";
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
    _getch();
    return;
}

/* ---------- Authentication Menus ---------- */
void VotingSystem::adminAuthMenu()
{
    int current = 0;
    char input;

    while (true)
    {
        drawAdminAuthMenu(current);
        input = _getch();

        if (input == -32)
            input = _getch(); // arrow keys

        switch (input)
        {
        case 72: // UP
            if (current > 0) current--;
            break;

        case 80: // DOWN
            if (current < 1) current++;
            break;

        case 13: // ENTER
        {
            blinkSelection(11 + current * 2, 2, 1);
            system("cls");

            Admin* admin = new Admin(0, "", "", "", this);

            switch (current)
            {
            case 0: // Login
                admin->login();
                loading("Loading admin menu");
                adminMenu(admin);
                break;

            case 1: // Back
                delete admin;
                system("cls");
                return;
            }

            gotoxy(45, 23);
            cout << "Press any key to continue...";
            _getch();
            system("cls");
            break;
        }

        case 27: // ESC
            system("cls");
            return;
        }

        Sleep(80);
    }
}


void VotingSystem::voterAuthMenu()
{
            ::system("cls");
    int current = 0; // current highlighted option
    char input;

    const char* menu[] = { "Login", "Register", "Back " };
    const int menuSize = 3;

    while (true)
    {


        gotoxy(45, 5);
        cout << BOLD << "===== VOTER AUTH MENU =====" << RESET;

        // Draw menu with hover effect
        for (int i = 0; i < menuSize; i++)
        {
            gotoxy(55, 8 + i * 2);
            if (i == current)
                cout << "\033[47;30m> " << menu[i] << " <\033[0m"; // highlighted
            else
                cout << "  " << menu[i] << "  ";
        }

        input = _getch();
        if (input == -32)
            input = _getch(); // extended key

        switch (input)
        {
        case 72: // UP
            if (current > 0) current--;
            break;

        case 80: // DOWN
            if (current < menuSize - 1) current++;
            break;

        case 13: // ENTER
        {
            blinkSelection(8 + current * 2, 1, 1);

            Voter* voter = new Voter(0, "", "", "", this);

            switch (current)
            {
            case 0: // Login
                ::system("cls");
                voter->login();
                loading("Loading voter menu");
                voterMenu(voter);
                break;

            case 1: // Register
                ::system("cls");
                voter->registerUser();
                loading("Loading voter menu");
                voterMenu(voter);
                break;

            case 2: // Back
                delete voter;
                ::system("cls");
                return; // exit menu
            }
            break;
        }

        case 27: // ESC
            return;
        }

        Sleep(80);
    }
}

/* ---------- Election Result ---------- */
void VotingSystem::displayElectionResults(int electionId)
{
    std::unordered_map<int, int> results; // candidateId -> voteCount

    // Initialize results map with candidates in the election
    for (const Election& election : elections)
    {
        if (election.getElectionId() == electionId)
        {
            for (int candidateId : election.getCandidates())
            {
                results[candidateId] = 0;
            }
            break;
        }
    }

    // Tally votes for the specified election
    for (const Vote& vote : votes)
    {
        if (vote.getElectionId() == electionId)
        {
            results[vote.getCandidateId()]++;
        }
    }

    vector<pair<int, int>> sortedResults(results.begin(), results.end());

    // Sort candidates by vote count in descending order
    sort(sortedResults.begin(), sortedResults.end(),
         [](const pair<int, int>& a, const pair<int, int>& b)
         {
             return b.second < a.second; // descending order
         });
    results.clear();

    cout << "\n=== Election Results for Election ID: " << electionId << " ===\n";
    for (const auto& entry : sortedResults)
    {
        for (User* u : users)
        {
            if (u->getUserId() == entry.first &&
                u->getRole() == "Candidate")
            {
                cout << "- Candidate ID: " << entry.first
                     << ", Username: " << u->getUsername()
                     << ", Votes: " << entry.second << endl;
                break;
            }
        }
    }
}

int VotingSystem::viewAllCandidatesHover()
{
    vector<Candidate*> candidates;

    // Collect candidates from users
    for (User* u : users)
    {
        if (u->getRole() == "Candidate")
        {
            candidates.push_back(static_cast<Candidate*>(u));
        }
    }

    if (candidates.empty())
    {
        gotoxy(40, 20);
        cout << "No candidates available.";
        _getch();
        return -1;
    }

    int current = 0;
    char input;

    while (true)
    {
        system("cls");

        gotoxy(40, 4);
        cout << BOLD << "=========== ALL CANDIDATES ===========" << RESET;

        int startY = 7;

        // Draw candidates
        for (int i = 0; i < candidates.size(); i++)
        {
            int y = startY + i * 2;

            gotoxy(30, y);
            cout << "==============================================";

            gotoxy(32, y + 1);

            if (i == current)
                cout << BOLD << GREEN << "> ";
            else
                cout << "  ";

            cout << "ID: " << candidates[i]->getUserId()
                 << " | " << candidates[i]->getUsername()
                 << " | " << candidates[i]->getEmail();

            cout << RESET;
        }

        // Back option
        int backY = startY + candidates.size() * 2;

        gotoxy(30, backY);
        cout << "==============================================";

        gotoxy(32, backY + 1);
        if (current == candidates.size())
            cout << BOLD << GREEN << "> BACK" << RESET;
        else
            cout << "  BACK";

        // Input
        input = _getch();
        if (input == -32)
            input = _getch();

        switch (input)
        {
        case 72: // UP
            if (current > 0) current--;
            break;

        case 80: // DOWN
            if (current < candidates.size()) current++;
            break;

        case 13: // ENTER
            blinkSelection(startY + current * 2 + 1, 1, 1);

            if (current == candidates.size())
                return -1; // BACK

            return candidates[current]->getUserId();

        case 27: // ESC
            return -1;
        }

        Sleep(80);
    }
}



