#include "Repository.h"
static const int IDX_CANDIDATE_NUMBER = 0;
static const int IDX_CANDIDATE_NAME = 1;
static const int IDX_CANDIDATE_BIRTH_DATE = 2;
static const int IDX_CANDIDATE_IS_ELECTED = 3;
static const int IDX_CANDIDATE_IS_APPROVED = 4;
static const int IDX_CANDIDATE_IS_CAPTION_VOTE = 5;
static const int IDX_PARTY_NUMBER = 6;
static const int IDX_PARTY_NAME = 7;
static const int IDX_FEDERATION = 8;
static const int IDX_POL_POSITION = 9;


Repository::Repository(string candidatesPath, string votesPath, Date *date, int polPosition)
{
    this->date = date;
    this->polPosition = polPosition;
    this->CandidatesReader.setPath(candidatesPath);
    this->VotesReader.setPath(votesPath);
}

void Repository::createElection()
{
    while(this->CandidatesReader.hasNext()){
        vector<string> tokens = this->CandidatesReader.nextAsVector();
        Party *p = NULL;

        int polPosition = stoi(tokens[IDX_POL_POSITION].substr(0, tokens[IDX_POL_POSITION].length() - 1));
        if(!this->partyKeyExists(tokens[IDX_PARTY_NUMBER].substr(0, tokens[IDX_PARTY_NUMBER].length() - 1))){
            p = this->createParty(tokens);
            this->addParty(p);
        }        
        Candidate *c = this->createCandidate(tokens, p);
        if(c != NULL){
            this->addCandidate(c);
        }
    }
    this->CandidatesReader.close();
}

Party *Repository::createParty(vector<string> token)
{
    int numParty = stoi(token[IDX_PARTY_NUMBER].substr(0, token[IDX_PARTY_NUMBER].length() - 1));
    string name = token[IDX_PARTY_NAME].substr(0, token[IDX_PARTY_NAME].length() - 1);
    bool isInFederation = token[IDX_FEDERATION].substr(0, token[IDX_FEDERATION].length() - 1) != "-1";
    return new Party(name, numParty, isInFederation);
}

Candidate *Repository::createCandidate(vector<string> token, Party *party)
{
    int numCandidate = stoi(token[IDX_CANDIDATE_NUMBER].substr(0, token[IDX_CANDIDATE_NUMBER].length() - 1));
    string name = token[IDX_CANDIDATE_NAME].substr(0, token[IDX_CANDIDATE_NAME].length() - 1);
    Date birthDate; //= Date(token[IDX_CANDIDATE_BIRTH_DATE].substr(0, token[IDX_CANDIDATE_BIRTH_DATE].length() - 1));
    bool isElected = token[IDX_CANDIDATE_IS_ELECTED].substr(0, token[IDX_CANDIDATE_IS_ELECTED].length() - 1) == "ELEITO";
    bool isApproved = token[IDX_CANDIDATE_IS_APPROVED].substr(0, token[IDX_CANDIDATE_IS_APPROVED].length() - 1) == "2" || token[IDX_CANDIDATE_IS_APPROVED].substr(0, token[IDX_CANDIDATE_IS_APPROVED].length() - 1) == "16";
    bool isCaptionVote = token[IDX_CANDIDATE_IS_CAPTION_VOTE].substr(0, token[IDX_CANDIDATE_IS_CAPTION_VOTE].length() - 1) == "VALIDO (LEGENDA)";

    if(!isApproved && !isCaptionVote){
        return NULL;
    }

    return new Candidate(name, numCandidate, party, birthDate, isElected, isApproved, isCaptionVote);
}



