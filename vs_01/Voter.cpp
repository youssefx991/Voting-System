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

/* ---------- Login ---------- */
void Voter::login()
{
    cout << "Enter username: ";
    cin >> username;

    cout << "Enter password: ";
    cin >> password;

    // Authentication logic can be added later
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
