#if !defined(ELECTION_H)
#define ELECTION_H
#include <string>
#include <unordered_map>
#include "src/entity/Party.h"
#include "src/entity/Candidate.h"


class Election{
    unordered_map<int, Party*> parties = unordered_map<int, Party*>();
    unordered_map<int, Candidate*> candidates = unordered_map<int, Candidate*>();
public:
    Election();
    unordered_map<int, Party*> getParties();
    unordered_map<int, Candidate*> getCandidates();
    void addParty(Party *party);
    void addCandidate(Candidate *candidate);

};

#endif // ELECTION_H
