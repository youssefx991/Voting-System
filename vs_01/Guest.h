#ifndef GUEST_H
#define GUEST_H

#include <string>

using std::string;

/* ---------- Forward Declarations ---------- */
class VotingSystem;
class Election;

class Guest
{
private:
    VotingSystem* system;

public:
    Guest(VotingSystem* sys);

    void viewElections();
    void viewElectionDetails(int electionId);
    void viewCandidates(int electionId);

    void viewVotingRules();
};

#endif
