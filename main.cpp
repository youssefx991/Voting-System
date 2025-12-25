#include <iostream>
#include <vector>
#include <string>

using namespace std;

/* ---------- Forward Declaration ---------- */
class VotingSystem;

/* ---------- Enums ---------- */
enum class ElectionStatus
{
    CREATED,
    OPEN,
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
    vector<int> candidateIds;   // ✅ candidates inside election

public:
    Election(int id, string t, string d)
        : electionId(id), title(t), description(d),
          status(ElectionStatus::CREATED) {}

    int getElectionId() const { return electionId; }
    ElectionStatus getStatus() const { return status; }

    void open() { status = ElectionStatus::OPEN; }
    void close() { status = ElectionStatus::CLOSED; }

    bool isOpen() const { return status == ElectionStatus::OPEN; }

    void addCandidate(int candidateId)
    {
        candidateIds.push_back(candidateId);
    }

    vector<int>& getCandidates()
    {
        return candidateIds;
    }
};

/* ---------- User ---------- */
class User
{
protected:
    int userId;
    string username;
    string email;
    string password;              // ✅ added
    bool isBanned;
    VotingSystem* system;          // ✅ system reference

public:
    User(int id, string uname, string mail, string pass, VotingSystem* sys)
        : userId(id), username(uname), email(mail),
          password(pass), isBanned(false), system(sys) {}

    virtual ~User() {}

    virtual string getRole() const = 0;

    virtual void login() {}
    virtual void logout() {}

    bool getBanStatus() const { return isBanned; }
    void ban() { isBanned = true; }

    void viewElections();   // implemented after VotingSystem

    int getUserId() const { return userId; }
    string getPassword() const { return password; }
};

/* ---------- Guest ---------- */
class Guest
{
private:
    VotingSystem* system;

public:
    Guest(VotingSystem* sys) : system(sys) {}

    void viewElections() {}
    void viewElectionDetails(int electionId) {}
    void viewCandidates(int electionId) {}
    void viewVotingRules() {}
};

/* ---------- Voter ---------- */
class Voter : public User
{
public:
    Voter(int id, string uname, string mail, string pass, VotingSystem* sys)
        : User(id, uname, mail, pass, sys) {}

    string getRole() const override { return "Voter"; }

    void vote(int electionId, int candidateId) {}
    bool hasVoted(int electionId) const { return false; }
    void viewVotingStatus() {}

    void login() override
    {
        cout << "Enter username: ";
        cin >> username;

        cout << "Enter password: ";
        cin >> password;

        // authentication logic will be added later
    }
};

/* ---------- Candidate ---------- */
class Candidate : public User
{
private:
    string profileInfo;

public:
    Candidate(int id, string uname, string mail,
              string pass, string profile, VotingSystem* sys)
        : User(id, uname, mail, pass, sys),
          profileInfo(profile) {}

    string getRole() const override { return "Candidate"; }

    void viewMyElections() {}
    void viewVoteCount(int electionId) {}
};

/* ---------- Admin ---------- */
class Admin : public User
{
public:
    Admin(int id, string uname, string mail, string pass, VotingSystem* sys)
        : User(id, uname, mail, pass, sys) {}

    string getRole() const override { return "Admin"; }

    void createElection() {}
    void updateElection(int electionId) {}
    void openElection(int electionId) {}
    void closeElection(int electionId) {}

    void addCandidate(int electionId, int candidateId) {}
    void removeCandidate(int electionId, int candidateId) {}

    void viewVoters() {}
    void banVoter(int voterId) {}
    void viewResults(int electionId) {}
};

/* ---------- Vote ---------- */
class Vote
{
private:
    int voteId;
    int electionId;
    int voterId;
    int candidateId;

public:
    Vote(int vId, int eId, int vrId, int cId)
        : voteId(vId), electionId(eId),
          voterId(vrId), candidateId(cId) {}

    int getVoterId() const { return voterId; }
    int getElectionId() const { return electionId; }
};

/* ---------- VotingSystem ---------- */
class VotingSystem
{
private:
    vector<User*> users;
    vector<Election> elections;
    vector<Vote> votes;

public:
    vector<Election>& getElections() { return elections; }
    vector<User*>& getUsers() { return users; }

    void fillDate()
{
    /* ----------- Elections ----------- */
    elections.push_back(
        Election(1, "Student Union Election", "Choose the student union president")
    );

    elections.push_back(
        Election(2, "Club Leader Election", "Choose the club leader")
    );

    /* ----------- Candidates ----------- */
    users.push_back(new Candidate(101, "cand1", "c1@mail.com", "123", "Profile 1", this));
    users.push_back(new Candidate(102, "cand2", "c2@mail.com", "123", "Profile 2", this));
    users.push_back(new Candidate(103, "cand3", "c3@mail.com", "123", "Profile 3", this));
    users.push_back(new Candidate(104, "cand4", "c4@mail.com", "123", "Profile 4", this));
    users.push_back(new Candidate(105, "cand5", "c5@mail.com", "123", "Profile 5", this));

    // Election 1 → 2 candidates
    elections[0].addCandidate(101);
    elections[0].addCandidate(102);

    // Election 2 → 3 candidates
    elections[1].addCandidate(103);
    elections[1].addCandidate(104);
    elections[1].addCandidate(105);

    /* ----------- Voters (10) ----------- */
    users.push_back(new Voter(1, "voter1", "v1@mail.com", "123", this));
    users.push_back(new Voter(2, "voter2", "v2@mail.com", "123", this));
    users.push_back(new Voter(3, "voter3", "v3@mail.com", "123", this));
    users.push_back(new Voter(4, "voter4", "v4@mail.com", "123", this));
    users.push_back(new Voter(5, "voter5", "v5@mail.com", "123", this));
    users.push_back(new Voter(6, "voter6", "v6@mail.com", "123", this));
    users.push_back(new Voter(7, "voter7", "v7@mail.com", "123", this));
    users.push_back(new Voter(8, "voter8", "v8@mail.com", "123", this));
    users.push_back(new Voter(9, "voter9", "v9@mail.com", "123", this));
    users.push_back(new Voter(10,"voter10","v10@mail.com","123", this));

    /* ----------- Votes (5) ----------- */
    votes.push_back(Vote(1, 1, 1, 101));  // voter1 → election1 → candidate101
    votes.push_back(Vote(2, 1, 2, 102));
    votes.push_back(Vote(3, 2, 3, 103));
    votes.push_back(Vote(4, 2, 4, 104));
    votes.push_back(Vote(5, 2, 5, 105));
}
    void run() {}

    void guestMenu() {}
    void voterMenu(Voter* voter) {}
    void adminMenu(Admin* admin) {}
};

/* ---------- User method implementation ---------- */
void User::viewElections()
{
    for (const Election& e : system->getElections())
    {
        cout << "Id: " << e.getElectionId() << endl;
        cout << "Status: " << e.isOpen() << endl;
    }
}

/* ---------- main ---------- */
int main()
{
    VotingSystem system;
    system.run();
    cout<< "test";
    return 0;
}
