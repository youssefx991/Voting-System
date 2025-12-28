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
    cout << "\n===== Voting Rules =====\n";
    cout << "1. Each voter can vote only once per election.\n";
    cout << "2. Voting is allowed only when the election is OPEN.\n";
    cout << "3. Votes cannot be changed after submission.\n";
    cout << "4. Banned users are not allowed to vote.\n";
    cout << "5. Candidates cannot vote in elections they participate in.\n";
    cout << "========================\n";
}

void Guest::viewElections()
{
    cout << "===== Available Elections =====\n";
    for (const Election& e : system->getElections())
    {
        cout << "ID: " << e.getElectionId()
             << "  Title: " << e.getTitle()
             << "  Status: ";
        switch (e.getStatus())
        {
            case ElectionStatus::CREATED: cout << "Created"; break;
            case ElectionStatus::OPENED:  cout << "Opened"; break;
            case ElectionStatus::CLOSED:  cout << "Closed"; break;
        }
        cout << endl;
    }
}

void Guest::viewElectionDetails(int electionId)
{
    for (const Election& e : system->getElections())
    {
        if (e.getElectionId() == electionId)
        {
            cout << "===== Election Details =====\n";
            cout << "Title: " << e.getTitle() << endl;
            cout << "Description: " << e.getDescription() << endl;
            cout << "Status: ";
            switch (e.getStatus())
            {
                case ElectionStatus::CREATED: cout << "Created"; break;
                case ElectionStatus::OPENED:  cout << "Opened"; break;
                case ElectionStatus::CLOSED:  cout << "Closed"; break;
            }
            cout << endl;
            return;
        }
    }
    cout << "Election not found.\n";
}

void Guest::viewCandidates(int electionId)
{
    bool electionFound = false;

    for (Election& e : system->getElections())
    {
        if (e.getElectionId() == electionId)
        {
            electionFound = true;
            cout << "Candidates for Election: " << e.getTitle() << "\n";

            for (int candidateId : e.getCandidates())
            {
                for (User* u : system->getUsers())
                {
                    if (u->getUserId() == candidateId && u->getRole() == "Candidate")
                    {
                        cout << "- Candidate ID: " << u->getUserId()
                             << ", Username: " << u->getUsername()
                             << ", Email: " << u->getEmail() << endl;
                    }
                }
            }
            return;
        }
    }

    if (!electionFound)
    {
        cout << "Election with ID " << electionId << " not found.\n";
    }
}
