#ifndef ELECTION_H
#define ELECTION_H

#include <string>
#include <vector>

using std::string;
using std::vector;

/* ---------- Enums ---------- */
enum class ElectionStatus
{
    CREATED,
    OPENED,
    CLOSED
};

/* ---------- Election ---------- */
class Election
{
private:
    int electionId;
    string title;
    string description;
    ElectionStatus status;
    vector<int> candidateIds;

public:
    Election(int id, string t, string d);

    int getElectionId() const;
    ElectionStatus getStatus() const;

    void open();
    void close();
    bool isOpen() const;

    void addCandidate(int candidateId);
    void removeCandidate(int candidateId);

    //vector<int>& getCandidates();
    const vector<int>& getCandidates() const { return candidateIds; }
    vector<int>& getCandidates() { return candidateIds; }

    string getTitle() const;
    string getDescription() const;

    void setTitle(const string& newTitle);
    void setDescription(const string& newDescription);
};

#endif
