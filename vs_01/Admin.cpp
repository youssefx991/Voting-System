#include "Admin.h"
#include "VotingSystem.h"
#include "Election.h"
#include "Candidate.h"

#include <iostream>
#include <limits>
#include "UI.h"

using namespace std;

/* ---------- Constructor ---------- */
Admin::Admin(int id,
             string uname,
             string mail,
             string pass,
             VotingSystem* sys)
    : User(id, uname, mail, pass, sys)
{
}

/* ---------- Role ---------- */
string Admin::getRole() const
{
    return "Admin";
}

/* ---------- Create Election ---------- */
int Admin::createElection()
{
    int id;
    cout << "Enter Election ID: ";
    cin >> id;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (const Election& e : system->getElections())
    {
        if (e.getElectionId() == id)
        {
            cout << "Election ID already exists.\n";
            return -1;
        }
    }

    string title, description;

    cout << "Enter Election Title: ";
    getline(cin, title);

    cout << "Enter Election Description: ";
    getline(cin, description);

    system->getElections().emplace_back(id, title, description);
    cout << "Election has been created successfully.\n";

    return id;
}

/* ---------- Update Election ---------- */
void Admin::updateElection(int electionId)
{
    for (Election& e : system->getElections())
    {
        if (e.getElectionId() == electionId)
        {
            string newTitle, newDescription;

            cout << "Current title: " << e.getTitle() << endl;
            cout << "Enter new title (or press Enter to keep current): ";
            getline(cin, newTitle);

            if (!newTitle.empty())
                e.setTitle(newTitle);

            cout << "Current description: " << e.getDescription() << endl;
            cout << "Enter new description (or press Enter to keep current): ";
            getline(cin, newDescription);

            if (!newDescription.empty())
                e.setDescription(newDescription);

            cout << "Election updated successfully.\n";
            return;
        }
    }

    cout << "Election with ID " << electionId << " not found.\n";
}

/* ---------- Open Election ---------- */
void Admin::openElection(int electionId)
{
    for (Election& e : system->getElections())
    {
        if (e.getElectionId() == electionId)
        {
            if (e.getStatus() == ElectionStatus::CREATED)
            {
                e.open();
                cout << "Election opened for voting.\n";
            }
            else
            {
                cout << "Election is already "
                     << (e.getStatus() == ElectionStatus::OPENED ? "open" : "closed")
                     << ".\n";
            }
            return;
        }
    }

    cout << "Election not found.\n";
}

/* ---------- Close Election ---------- */
void Admin::closeElection(int electionId)
{
    for (Election& e : system->getElections())
    {
        if (e.getElectionId() == electionId)
        {
            if (e.getStatus() == ElectionStatus::OPENED)
            {
                e.close();
                cout << "Election closed successfully.\n";
            }
            else
            {
                cout << "Election is already closed or not open yet.\n";
            }
            return;
        }
    }

    cout << "Election not found.\n";
}

/* ---------- View Voters ---------- */
void Admin::viewVoters()
{
    loading("Loading Voters List");
  
    cout << "+-------------------------------------------------------------------+\n";
    cout << "                     VOTER LIST WINDOW                               \n";
    cout << "+-------------------------------------------------------------------+\n";
    for (User* u : system->getUsers())
    {
        if (u->getRole() == "Voter")
        {
            cout << "ID: " << u->getUserId()
                 << ", Username: " <<BOLD << u->getUsername() << RESET
                 << ", Email: " << u->getEmail()
                 << ", Status: ";   
                if (u->getBanStatus())
                    cout << RED << "BANNED";
                else
                    cout << GREEN << "ACTIVE";

                cout << RESET << endl;

            this_thread::sleep_for(chrono::milliseconds(250));
        }
        
    }
    cout << "+-------------------------------------------------------------------+\n";


    
    cout << endl;
}

/* ---------- Ban Voter ---------- */
void Admin::banVoter(int voterId)
{
    for (User* u : system->getUsers())
    {
        if (u->getUserId() == voterId && u->getRole() == "Voter")
        {
            if (u->getBanStatus())
            {
                cout << BOLD << YELLOW
                     << "Voter is already banned.\n"
                     << RESET;
                return;
            }

            u->ban();
            cout << BOLD << GREEN 
                 << "Voter banned successfully.\n"
                 << RESET;
            return;
        }
    }

     cout << BOLD << RED
         << "Voter not found.\n"
         << RESET;
}

/* ---------- Add Candidate ---------- */
void Admin::addCandidate(int electionId, int candidateId)
{
    Election* targetElection = nullptr;
    Candidate* targetCandidate = nullptr;

    for (Election& e : system->getElections())
    {
        if (e.getElectionId() == electionId)
        {
            targetElection = &e;
            break;
        }
    }

    if (!targetElection)
    {
        cout << "Election not found.\n";
        return;
    }

    for (User* u : system->getUsers())
    {
        if (u->getUserId() == candidateId)
        {
            targetCandidate = dynamic_cast<Candidate*>(u);
            break;
        }
    }

    if (!targetCandidate)
    {
        cout << "User is not a candidate.\n";
        return;
    }

    for (int cid : targetElection->getCandidates())
    {
        if (cid == candidateId)
        {
            cout << "Candidate already added.\n";
            return;
        }
    }

    targetElection->addCandidate(candidateId);
    cout << "Candidate added successfully.\n";
}

/* ---------- Remove Candidate ---------- */
void Admin::removeCandidate(int electionId, int candidateId)
{
    Election* targetElection = nullptr;

    for (Election& e : system->getElections())
    {
        if (e.getElectionId() == electionId)
        {
            targetElection = &e;
            break;
        }
    }

    if (!targetElection)
    {
        cout << "Election not found.\n";
        return;
    }

    targetElection->removeCandidate(candidateId);
    cout << "Candidate removed successfully.\n";
}



  void Admin::getElection(Election &election ){
        cout<<"============election details============="<<endl;
       cout << "ID: " << election.getElectionId()<<endl
                 << "  Title: " << election.getTitle()<<endl
                 << "  Status: ";
         switch (election.getStatus())
        {
            case ElectionStatus::CREATED: cout << "Created"; break;
            case ElectionStatus::OPENED:  cout << "Opened"; break;
            case ElectionStatus::CLOSED:  cout << "Closed"; break;
        }
        cout << endl;

        cout << "Enter Election number of operation (or any invalid input to return): "<<endl;
            election.isOpen()?cout<<"1. close ":cout<<"1. open";
            cout<<endl
                <<"2. Update election"<<endl
                <<"3. View Results"<<endl
                <<"4.Add candidate"<<endl
                <<"5.Remove candidate"<<endl;
        int option ;
        cin>>option;
        switch(option){
        case 1:
            (election.isOpen())?election.close():election.open();
            break;
        case 2:
            updateElection(election.getElectionId());
            break;
        case 3:
            //viewResults(election.getElectionId());
            break;
        case 4:{
            int cand;
            /// view all candidate
            int i=1;
            for(int cId: election.getCandidates()){
                cout<< "======================="<<endl;
                cout<<"               candidate num: "<< i<<"#                 "<<endl;

                Candidate *c= c->getCandidateById(Admin::system,cId);

                cout<<" Candidate ID:"<<c->getUserId()<<endl
                <<" Candidate username:"<<c->getUsername()<<endl
                <<" Candidate Email:"<<c->getEmail()<<endl;
                i++;
            }
            cout<< "enter candidate id to add :"<<endl;
            cin>>cand;

            addCandidate(election.getElectionId(), cand);
            break;
        }
        case 5:{
            int candi;
            int i=1;
              for(int cId: election.getCandidates()){
                cout<< "======================="<<endl;
                cout<<"               candidate num: "<< i<<"#                 "<<endl;

                Candidate *c= c->getCandidateById(Admin::system,cId);

                cout<<" Candidate ID:"<<c->getUserId()<<endl
                <<" Candidate username:"<<c->getUsername()<<endl
                <<" Candidate Email:"<<c->getEmail()<<endl;
                i++;
            }
            cout<< "enter candidate id to remove"<<endl;
            cin>>candi;
            removeCandidate(election.getElectionId(), candi);
            break;

        }
        default:
            cout<< "wrong input "<<endl;
        }
    }
