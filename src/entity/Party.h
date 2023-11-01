#if !defined(PARTY_H)
#define PARTY_H
#include <string>
#include <unordered_map>
#include "Candidate.h"
using namespace std;

class Party{
    string name;
    unordered_map<int, Candidate*> candidates = unordered_map<int, Candidate*>();
    bool isInFederation;
    int nominalVotes;
    int captionVotes;
    int number;

public:
    Party(string name,int number, bool isInFederation);
    int getNumber();
    string getName();
    unordered_map<int, Candidate*> getCandidates();
    bool getIsInFederation();
    int getNominalVotes();
    int getCaptionVotes();
    void addCandidate(Candidate *candidate);
    void addNominalVotes(int votes);
    void addCaptionVotes(int votes);
    string toString();
};


#endif // PARTY_H