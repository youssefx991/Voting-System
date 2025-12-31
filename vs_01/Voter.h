#ifndef VOTER_H
#define VOTER_H

#include "User.h"

/* ---------- Forward Declarations ---------- */
class VotingSystem;
class Election;

class Voter : public User
{
public:
    Voter(int id, std::string uname, std::string mail, std::string pass, VotingSystem* sys);

    std::string getRole() const override;

    void vote(int electionId, int candidateId);
    bool hasVoted(int electionId) const;
    void rulesMenu();
    void availableElectionsMenu();
    void ElectionDetails(int ElectionID);
    void viewVotingStatus();
};

#endif

