#include "Voter.h"
#include "VotingSystem.h"
#include "Election.h"
#include "Vote.h"

#include <iostream>

using namespace std;

/* ---------- Constructor ---------- */
Voter::Voter(int id, string uname, string mail, string pass, VotingSystem* sys)
    : User(id, uname, mail, pass, sys) {}

/* ---------- Role ---------- */
string Voter::getRole() const
{
    return "Voter";
}



/* ---------- Voting ---------- */
void Voter::vote(int electionId, int candidateId)
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

    if (!targetElection->isOpen())
    {
        cout << "Election not open.\n";
        return;
    }

    bool candidateFound = false;
    for (int cid : targetElection->getCandidates())
    {
        if (cid == candidateId)
        {
            candidateFound = true;
            break;
        }
    }

    if (!candidateFound)
    {
        cout << "This candidate is not part of this election.\n";
        return;
    }

    if (hasVoted(electionId))
    {
        cout << "You have already voted in this election.\n";
        return;
    }

    int voteId = system->getVotes().size() + 1;
    Vote newVote(voteId, electionId, userId, candidateId);
    system->getVotes().push_back(newVote);

    cout << "Vote submitted successfully.\n";
}

/* ---------- Check if Already Voted ---------- */
bool Voter::hasVoted(int electionId) const
{
    for (const Vote& v : system->getVotes())
    {
        if (v.getVoterId() == userId && v.getElectionId() == electionId)
        {
            return true;
        }
    }
    return false;
}

/* ---------- Voting Status ---------- */
void Voter::viewVotingStatus()
{
    // Implementation can be added later
}




void Voter::rulesMenu()
{
    int choice;
    do {
        cout << "1.Rule number 1\n";
        cout << "2. Rule number 2\n";
        cout << "3. Rule number 3\n";

        cout << "Back: press 0: ";
        cin >> choice;
        if (choice != 0|| cin.fail()) {
            cin.clear(); // clear the fail state
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard invalid input
            cout << RED << "Invalid input! Please enter a number from 0 to 3 .\n" << RESET;
        }
        switch (choice) {
            case 0:
                cout << YELLOW << "Return...\n" << RESET;
                return;
                break;
            default:
                cout << RED << "Invalid choice!\n" << RESET;
        }
    } while (choice != 0);

    return;
}





void Voter::availableElectionsMenu()
{
    int choice;
    do {
            cout<<"welcome"<<endl;
        for ( Election& e : system->getElections())
        {


                cout << "Id: " << e.getElectionId() << endl;
                cout << "title: " << e.getTitle() << endl;
                e.isOpen()? cout<< "open for voting"<<endl : cout<< "closed"<<endl;
                cout<< "------------------------------"<<endl;
        }
        cout << "choose Election ID: ";
        cout << "Back press 0: ";
        cin >> choice;
        if ( cin.fail()) {
            cin.clear(); // clear the fail state
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard invalid input
            cout << RED << "Invalid input! Please enter a number from 0 to 3 .\n" << RESET;
        }
        switch (choice) {
            case 0:
                cout << YELLOW << "Return...\n" << RESET;
                return;
                break;
            default:
                {
                    Election* selectedElection = nullptr;
                    for (Election& e : system->getElections())
                    {
                        if (e.getElectionId() == choice)
                        {
                            selectedElection = &e;
                            break;
                        }
                    }
                    if (!selectedElection)
                    {
                        cout << RED << "Invalid election ID. Please choose from the list.\n" << RESET;
                    }
                    else
                    {
                        ElectionDetails(selectedElection->getElectionId());
                    }
                    break;
                }

        }

    } while (choice != 0);

    return;
}



void Voter::ElectionDetails(int ElectionID){
    Election* targetElection = nullptr;

    // 1️⃣ Find election
    for (Election& e : system->getElections())
    {
        if (e.getElectionId() == ElectionID)
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

    int choice;

    do {
        cout << "\n=== Election Details ===\n";
        cout << "Title: " << targetElection->getTitle() << endl;
        cout << "Description: " << targetElection->getDescription() << endl;
        cout << "------------------------------\n";

        cout << "Candidates:\n";
        for (int cid : targetElection->getCandidates())
        {
            cout << "Candidate ID: " << cid << endl;
        }

        cout << "------------------------------\n";
        cout << "Enter Candidate ID to vote\n";
        cout << "Back: press 0\n";
        cout << "Choice: ";
        cin >> choice;

        // ❌ invalid input
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << RED << "Invalid input. Enter a number.\n" << RESET;
            continue;
        }

        if (choice == 0)
        {
            cout << YELLOW << "Returning...\n" << RESET;
            return;
        }

        // 2️⃣ Try voting
        vote(ElectionID, choice);

    } while (true);

}

