#ifndef USER_H
#define USER_H

#include <string>

using std::string;

/* ---------- Forward Declarations ---------- */
class VotingSystem;

/* ---------- User ---------- */
class User
{
protected:
    int userId;
    string username;
    string email;
    string password;
    bool isBanned;
    VotingSystem* system;

public:
    User(int id, string uname, string mail, string pass, VotingSystem* sys);
    virtual ~User();

    virtual string getRole() const = 0;

    virtual void login();
    virtual void registerUser();
    virtual void logout();

    bool getBanStatus() const;
    void ban();

    void viewElections();

    int getUserId() const;
    string getPassword() const;
    string getUsername() const;
    string getEmail() const;
};

#endif
