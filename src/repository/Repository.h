#if !defined(REPOSITORY_H)
#define REPOSITORY_H

#include <string>
#include <vector>
#include "src/entity/Party.h"
#include "src/entity/Candidate.h"
#include "src/util/Date.h"
#include "src/election/Election.h"
#include "src/util/CSVReader.h"



class Repository{
    Election election;
    CSVReader CandidatesReader;
    CSVReader VotesReader;
    Date *date;
    int polPosition; 
public:
    Repository(string candidatesPath, string votesPath, Date *date, int polPosition);
    Election *getElection();
    void createElection();
    Party *createParty(vector<string> token);
    Candidate *createCandidate(vector<string> token, Party *party);
    void addParty(Party *party);
    void addCandidate(Candidate *candidate);
};

#endif // REPOSITORY_H
