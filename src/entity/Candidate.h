#if !defined(CANDIDATES_H)
#define CANDIDATES_H
#include "src/util/Date.h"
#include "Party.h"
#include <string>

using namespace std;

class Candidate{
    string name;
    int number;
    int numberOfVotes;
    Party *party;
    Date birthDate;
    bool isElected;
    bool isApproved;
    bool isCaptionVote;
    
public:
    Candidate(string name, int number, Party *party, Date birthDate, bool isElected, bool isApproved, bool isCaptionVote);
    string getName();
    int getNumber();
    int getNumberOfVotes();
    Party *getParty();
    Date getBirthDate();
    bool getIsElected();
    bool getIsApproved();
    bool getIsCaptionVote();
    string toString();
};


#endif // CANDIDATES_H
