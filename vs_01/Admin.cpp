#include "Admin.h"
#include "VotingSystem.h"
#include "Election.h"
#include "Candidate.h"
#include "UI.h"
#include "ConsoleUI.h"

#include <iostream>
#include <limits>
#include <conio.h>


using namespace std;

/* ---------- Constructor ---------- */
Admin::Admin(int id,
             string uname,
             string mail,
             string pass,
             VotingSystem* sys)
    : User(id, uname, mail, pass, sys)
{
}

/* ---------- Role ---------- */
string Admin::getRole() const
{
    return "Admin";
}

/* ---------- Create Election ---------- */
int Admin::createElection()
{
    //::system("cls");

    int centerX = 40;
    int startY  = 7;

    gotoxy(centerX, startY);
    cout << BOLD << "======== CREATE NEW ELECTION ========" << RESET;

    gotoxy(centerX, startY + 3);
    cout << "Election ID:";

    gotoxy(centerX, startY + 5);
    cout << "Title:";

    gotoxy(centerX, startY + 7);
    cout << "Description:";

    // input fields
    string idStr  = inputField(centerX + 15, startY + 3, 6, false);
    string title  = inputField(centerX + 15, startY + 5, 25, false);
    string desc   = inputField(centerX + 15, startY + 7, 40, false);

    // validate ID numeric
    if (idStr.empty() || !isdigit(idStr[0]))
    {
        gotoxy(centerX, startY + 10);
        cout << RED << "Invalid Election ID!" << RESET;
        Sleep(1200);
        return -1;
    }

    int id = stoi(idStr);

    // check ID uniqueness
    for (const Election& e : system->getElections())
    {
        if (e.getElectionId() == id)
        {
            gotoxy(centerX, startY + 10);
            cout << RED << "Election ID already exists!" << RESET;
            Sleep(1200);
            return -1;
        }
    }

    // create election
    system->getElections().emplace_back(id, title, desc);

    gotoxy(centerX, startY + 10);
    cout << GREEN << "Election created successfully!" << RESET;

    Sleep(1200);
    return id;
}


/* ---------- Update Election ---------- */
void Admin::updateElection(int electionId)
{
    Election* target = nullptr;
    for (Election& e : system->getElections())
    {
        if (e.getElectionId() == electionId)
        {
            target = &e;
            break;
        }
    }

    if (!target)
    {
        gotoxy(40, 20);
        cout << RED << "Election with ID " << electionId << " not found." << RESET;
        _getch();
        return;
    }

    ::system("cls");
    int centerX = 40;
    int startY = 7;

    gotoxy(centerX, startY);
    cout << BOLD << "========== UPDATE ELECTION ==========" << RESET;

    // Title
    gotoxy(centerX, startY + 3);
    cout << "Current title: " << target->getTitle();

    gotoxy(centerX, startY + 5);
    cout << "New title (Enter to keep current): ";

    string newTitle = inputField(centerX + 40, startY + 5, 30, false);
    if (!newTitle.empty())
        target->setTitle(newTitle);

    // Description
    gotoxy(centerX, startY + 7);
    cout << "Current description: " << target->getDescription();

    gotoxy(centerX, startY + 9);
    cout << "New description (Enter to keep current): ";

    string newDesc = inputField(centerX + 40, startY + 9, 30, false);
    if (!newDesc.empty())
        target->setDescription(newDesc);

    gotoxy(centerX, startY + 12);
    cout << GREEN << "Election updated successfully!" << RESET;

    _getch();
}


/* ---------- Open Election ---------- */
void Admin::openElection(int electionId)
{
    for (Election& e : system->getElections())
    {
        if (e.getElectionId() == electionId)
        {
            if (e.getStatus() == ElectionStatus::CREATED)
            {
                e.open();
                cout << "Election opened for voting.\n";
            }
            else
            {
                cout << "Election is already "
                     << (e.getStatus() == ElectionStatus::OPENED ? "open" : "closed")
                     << ".\n";
            }
            return;
        }
    }

    cout << "Election not found.\n";
}

/* ---------- Close Election ---------- */
void Admin::closeElection(int electionId)
{
    for (Election& e : system->getElections())
    {
        if (e.getElectionId() == electionId)
        {
            if (e.getStatus() == ElectionStatus::OPENED)
            {
                e.close();
                cout << "Election closed successfully.\n";
            }
            else
            {
                cout << "Election is already closed or not open yet.\n";
            }
            return;
        }
    }

    cout << "Election not found.\n";
}

/* ---------- View Voters ---------- */
void Admin::viewVoters()
{
    loading("Loading Voters List");

    cout << "+-------------------------------------------------------------------+\n";
    cout << "                     VOTER LIST WINDOW                               \n";
    cout << "+-------------------------------------------------------------------+\n";
    for (User* u : system->getUsers())
    {
        if (u->getRole() == "Voter")
        {
            cout << "ID: " << u->getUserId()
                 << ", Username: " <<BOLD << u->getUsername() << RESET
                 << ", Email: " << u->getEmail()
                 << ", Status: ";
                if (u->getBanStatus())
                    cout << RED << "BANNED";
                else
                    cout << GREEN << "ACTIVE";

                cout << RESET << endl;

            this_thread::sleep_for(chrono::milliseconds(250));
        }

    }
    cout << "+-------------------------------------------------------------------+\n";



    cout << endl;
}

/* ---------- Ban Voter ---------- */
void Admin::banVoter(int voterId)
{
    for (User* u : system->getUsers())
    {
        if (u->getUserId() == voterId && u->getRole() == "Voter")
        {
            if (u->getBanStatus())
            {
                cout << BOLD << YELLOW
                     << "Voter is already banned.\n"
                     << RESET;
                return;
            }

            u->ban();
            cout << BOLD << GREEN
                 << "Voter banned successfully.\n"
                 << RESET;
            return;
        }
    }

     cout << BOLD << RED
         << "Voter not found.\n"
         << RESET;
}

/* ---------- Add Candidate ---------- */
void Admin::addCandidate(int electionId, int candidateId)
{
    Election* targetElection = nullptr;
    Candidate* targetCandidate = nullptr;

    for (Election& e : system->getElections())
    {
        if (e.getElectionId() == electionId)
        {
            targetElection = &e;
            break;
        }
    }

    if (!targetElection)
    {
        cout << "Election not found.\n";
        return;
    }

    for (User* u : system->getUsers())
    {
        if (u->getUserId() == candidateId)
        {
            targetCandidate = dynamic_cast<Candidate*>(u);
            break;
        }
    }

    if (!targetCandidate)
    {
        cout << "User is not a candidate.\n";
        return;
    }

    for (int cid : targetElection->getCandidates())
    {
        if (cid == candidateId)
        {
            cout << "Candidate already added.\n";
            return;
        }
    }

    targetElection->addCandidate(candidateId);
    cout << "Candidate added successfully.\n";
}

/* ---------- Remove Candidate ---------- */
void Admin::removeCandidate(int electionId, int candidateId)
{
    Election* targetElection = nullptr;

    for (Election& e : system->getElections())
    {
        if (e.getElectionId() == electionId)
        {
            targetElection = &e;
            break;
        }
    }

    if (!targetElection)
    {
        cout << "Election not found.\n";
        return;
    }

    targetElection->removeCandidate(candidateId);
    cout << "Candidate removed successfully.\n";
}



  void Admin::getElection(Election& election)
{
    int current = 0;
    char input;

    while (true)
    {
        ::system("cls");

        gotoxy(40, 6);
        cout << BOLD << "============ Election Details =============" << RESET;

        gotoxy(40, 8);
        cout << "ID: " << election.getElectionId();

        gotoxy(40, 9);
        cout << "Title: " << election.getTitle();

        gotoxy(40, 10);
        cout << "Status: ";

        switch (election.getStatus())
        {
        case ElectionStatus::CREATED: cout << "Not Opened"; break;
        case ElectionStatus::OPENED:  cout << "Opened"; break;
        case ElectionStatus::CLOSED:  cout << "Closed"; break;
        }

        drawAdminElectionMenu(current, election.isOpen());

        input = _getch();
        if (input == -32)
            input = _getch();

        switch (input)
        {
        case 72: // UP
            if (current > 0) current--;
            break;

        case 80: // DOWN
            if (current < 5) current++;
            break;

        case 13: // ENTER
            blinkSelection(12 + current * 2, 1, 1);

            switch (current)
            {
            case 0: // Open / Close
                election.isOpen() ? election.close() : election.open();
                break;

            case 1: // Update
                updateElection(election.getElectionId());
                break;

            case 2: // Results
                ::system("cls");
                system->displayElectionResults(election.getElectionId());
                _getch();
                break;

            case 3: // Add candidate
                    {
                        int candId = system->viewAllCandidatesHover();
                        if (candId != -1)
                        {
                            addCandidate(election.getElectionId(), candId);
                        }
                        break;
                    }

            case 4: // Remove candidate
            {
                ::system("cls");
                int candi;
                int i=1;
                 for(int cId: election.getCandidates()){
                        cout<< "======================="<<endl;
                 cout<<" candidate num: "<< i<<"# "<<endl;
                  Candidate* c = Candidate::getCandidateById(Admin::system, cId);
                  cout<<" Candidate ID:"<<c->getUserId()
                  <<endl <<" Candidate username:"<<c->getUsername()
                  <<endl <<" Candidate Email:"<<c->getEmail()
                  <<endl; i++;
                   }
                cout<< "enter candidate id to remove"<<endl;
                 cin>>candi; removeCandidate(election.getElectionId(), candi);
                  break;
            }

            case 5: // Back
                return;
            }
            break;

        case 27: // ESC
            return;
        }

        Sleep(80);
    }
}
