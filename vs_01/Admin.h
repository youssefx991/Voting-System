#ifndef ADMIN_H
#define ADMIN_H

#include "User.h"

/* ---------- Forward Declarations ---------- */
class VotingSystem;
class Election;
class Candidate;

class Admin : public User
{
public:
    Admin(int id,
          std::string uname,
          std::string mail,
          std::string pass,
          VotingSystem* sys);

    std::string getRole() const override;

    int createElection();
    void updateElection(int electionId);
    void getElection(Election &election );

    void openElection(int electionId);
    void closeElection(int electionId);

    void addCandidate(int electionId, int candidateId);
    void removeCandidate(int electionId, int candidateId);

    void viewVoters();
    void banVoter(int voterId);

    void viewResults(int electionId); 
};

#endif

