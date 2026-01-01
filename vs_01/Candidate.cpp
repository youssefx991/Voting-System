#include "Candidate.h"
#include "VotingSystem.h"
#include "Election.h"
#include "Vote.h"

#include <iostream>

using namespace std;

/* ---------- Constructor ---------- */
Candidate::Candidate(int id,
                     string uname,
                     string mail,
                     string pass,
                     string profile,
                     VotingSystem* sys)
    : User(id, uname, mail, pass, sys),
      profileInfo(profile)
{
}



/* ---------- Role ---------- */
string Candidate::getRole() const
{
    return "Candidate";
}

/* ---------- Register ---------- */
void Candidate::registerUser()
{
    User::registerUser(); // call base registration first

    cout << "Enter profile info: ";
    cin.ignore(); // clear leftover newline
    getline(cin, profileInfo);
}

/* ---------- View My Elections ---------- */
void Candidate::viewMyElections()
{
    cout << "Elections for Candidate " << username << ":\n";

    for (const Election& e : system->getElections())
    {
        for (int cid : e.getCandidates())
        {
            if (cid == userId)
            {
                cout << "Election ID: " << e.getElectionId()
                     << ", Title: " << e.getTitle() << endl;
            }
        }
    }
}

/* ---------- View Vote Count ---------- */
int Candidate::viewVoteCount(int electionId)
{
    int count = 0;

    for (const Vote &v : system->getVotes())
    {
        if (v.getElectionId() == electionId &&
            v.getCandidateId() == userId) // FIX
        {
            count++;
        }
    }

    return count;
}

