#include "Vote.h"

/* ---------- Constructor ---------- */
Vote::Vote(int vId, int eId, int vrId, int cId)
    : voteId(vId),
      electionId(eId),
      voterId(vrId),
      candidateId(cId)
{
}

/* ---------- Getters ---------- */
int Vote::getVoteId() const
{
    return voteId;
}

int Vote::getElectionId() const
{
    return electionId;
}

int Vote::getVoterId() const
{
    return voterId;
}

int Vote::getCandidateId() const
{
    return candidateId;
}
