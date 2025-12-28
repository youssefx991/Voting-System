#ifndef VOTE_H
#define VOTE_H

class Vote
{
private:
    int voteId;
    int electionId;
    int voterId;
    int candidateId;

public:
    Vote(int vId, int eId, int vrId, int cId);

    int getVoteId() const;
    int getElectionId() const;
    int getVoterId() const;
    int getCandidateId() const;
};

#endif
