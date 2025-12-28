#include "Election.h"

/* ---------- Constructor ---------- */
Election::Election(int id, string t, string d)
    : electionId(id),
      title(t),
      description(d),
      status(ElectionStatus::CREATED)
{
}

/* ---------- Getters ---------- */
int Election::getElectionId() const
{
    return electionId;
}

ElectionStatus Election::getStatus() const
{
    return status;
}

string Election::getTitle() const
{
    return title;
}

string Election::getDescription() const
{
    return description;
}

/* ---------- State Control ---------- */
void Election::open()
{
    status = ElectionStatus::OPENED;
}

void Election::close()
{
    status = ElectionStatus::CLOSED;
}

bool Election::isOpen() const
{
    return status == ElectionStatus::OPENED;
}

/* ---------- Candidate Control ---------- */
void Election::addCandidate(int candidateId)
{
    candidateIds.push_back(candidateId);
}

void Election::removeCandidate(int candidateId)
{
    for (auto it = candidateIds.begin(); it != candidateIds.end(); ++it)
    {
        if (*it == candidateId)
        {
            candidateIds.erase(it);
            return;
        }
    }
}

/* ---------- Setters ---------- */
void Election::setTitle(const string& newTitle)
{
    title = newTitle;
}

void Election::setDescription(const string& newDescription)
{
    description = newDescription;
}
