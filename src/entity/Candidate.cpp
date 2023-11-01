#include "Candidate.h"

Candidate::Candidate(string name, int number, Party *party, Date birthDate, bool isElected, bool isApproved, bool isCaptionVote)
{
    this->name = name;
    this->number = number;
    this->numberOfVotes = 0;
    this->party = party;
    this->birthDate = birthDate;
    this->isElected = isElected;
    this->isApproved = isApproved;
    this->isCaptionVote = isCaptionVote;
}

string Candidate::getName()
{
    return this->name;
}

int Candidate::getNumber()
{
    return this->number;
}

int Candidate::getNumberOfVotes()
{
    return this->numberOfVotes;
}

Party* Candidate::getParty()
{
    return this->party;
}

Date Candidate::getBirthDate()
{
    return this->birthDate;
}

bool Candidate::getIsElected()
{
    return this->isElected;
}

bool Candidate::getIsApproved()
{
    return this->isApproved;
}

bool Candidate::getIsCaptionVote()
{
    return this->isCaptionVote;
}

string Candidate::toString()
{
    return this->name + " - " + to_string(this->getNumberOfVotes());
}
