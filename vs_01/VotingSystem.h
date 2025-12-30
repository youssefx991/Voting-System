#ifndef VOTING_SYSTEM_H
#define VOTING_SYSTEM_H

#include <vector>
#include <unordered_map>

#include "Vote.h"
#include "User.h"
#include "Guest.h"
#include "Admin.h"
#include "Candidate.h"
#include "Election.h"
/* ---------- Forward Declarations ---------- */
class User;
class Election;
class Vote;
class Voter;
class Admin;

class VotingSystem
{
private:
    std::vector<User*> users;
    std::vector<Election> elections;
    std::vector<Vote> votes;

public:
    VotingSystem() = default;
    ~VotingSystem();

    std::vector<Election>& getElections();
    std::vector<User*>& getUsers();
    std::vector<Vote>& getVotes();

    void fillData();   // (fixed name)
    void run();

    void guestMenu();
    void voterMenu(Voter* voter);
    void adminMenu(Admin* admin);

    /* ---------- Candidate Menus ---------- */
    void candidateAuthMenu();
    void candidateMenu(Candidate* candidate);
    void candidateElectionsMenu(Candidate* candidate);
    void candidateElectionDetailsMenu(Candidate* candidate, int electionID);
    void viewElectionCandidates(Election* election);

    /* ---------- Authentication Menus ---------- */
    void adminAuthMenu();
    void voterAuthMenu();

    /* ---------- Election Result ---------- */
    std::unordered_map<int, int> displayElectionResults(int electionId);

};

#endif
