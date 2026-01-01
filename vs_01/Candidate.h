#ifndef CANDIDATE_H
#define CANDIDATE_H

#include "User.h"

/* ---------- Forward Declarations ---------- */
class VotingSystem;

class Candidate : public User
{
private:
    std::string profileInfo;

public:
    Candidate(int id,
              std::string uname,
              std::string mail,
              std::string pass,
              std::string profile,
              VotingSystem* sys);

    std::string getRole() const override;

    void registerUser() override;

    void viewMyElections();
    int viewVoteCount(int electionId);
  static Candidate* getCandidateById(VotingSystem* system, int id);
};

#endif

