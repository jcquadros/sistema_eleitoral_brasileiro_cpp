#include "Party.h"

Party::Party(string name,int number, bool isInFederation)
{
    this->name = name;
    this->number = number;
    this->isInFederation = isInFederation;
    this->nominalVotes = 0;
    this->captionVotes = 0;
}

int Party::getNumber()
{
    return this->number;
}

string Party::getName()
{
    return this->name;
}

unordered_map<int, Candidate *> Party::getCandidates()
{
    return this->candidates;
}

bool Party::getIsInFederation()
{
    return this->isInFederation;
}

int Party::getNominalVotes()
{
    return this->nominalVotes;
}

int Party::getCaptionVotes()
{
    return this->captionVotes;
}

void Party::addCandidate(Candidate *candidate)
{
    if(this->candidates.find(candidate->getNumber()) != NULL ){
        throw "Candidate already exists";
        return;
    }
    this->candidates.emplace(candidate->getNumber(), candidate);
}

void Party::addNominalVotes(int votes)
{
    this->nominalVotes += votes;
}

void Party::addCaptionVotes(int votes)
{
    this->captionVotes += votes;
}

string Party::toString()
{
    return this->name + " - " + to_string(this->nominalVotes) + " - " + to_string(this->captionVotes);
}
