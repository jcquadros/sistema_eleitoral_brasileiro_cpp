#include "Election.h"

Election::Election()
{
}

unordered_map<int, Party *> Election::getParties()
{
    return this->parties;
}

unordered_map<int, Candidate *> Election::getCandidates()
{
    return this->candidates;
}

void Election::addParty(Party *party)
{
    if(this->parties.find(party->getNumber()) != NULL ){
        throw "Party already exists";
        return;
    }
    this->parties.emplace(party->getName(), party);
}

void Election::addCandidate(Candidate *candidate)
{
    if(this->candidates.find(candidate->getNumber()) != NULL ){
        throw "Candidate already exists";
        return;
    }
    this->candidates.emplace(candidate->getNumber(), candidate);
}
