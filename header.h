class fidaki{
    unsigned short int *fidia;
    unsigned short int *skales;
    unsigned short int *Cpos; //Current position of every player
public:
    fidaki(unsigned short int);
    ~fidaki();
    unsigned short int checkFor(unsigned short int,unsigned short int*) const; //Check if player is on skales or fidia block
    void UpPos(unsigned short int, unsigned short int); // Update position of a player
    unsigned short int GetPos(unsigned short int) const; //Get player's position
    unsigned short int RollDice(void) const;    // Dice method for rolling the dices with new seed
};

class userInterface{
    std::string *NaSu; //Names and surenames
    unsigned short int players; // How many players are playing
    unsigned short int *PlayRound; // Round for players [AddBy1,AddBy2]
public:
    userInterface(unsigned short int);
    ~userInterface();
    void NextRound(void); // Next player
    unsigned short int WhoPlays(void) const; //Pllayer's turn
    unsigned short int PlayBy2(void) const; // Two counter
    void GetName(unsigned short int) const; // Cout player name
    void GetNaSus(void); //Fill Nasus array with names and surenames
    void AnnPlayer(void) const; //Announce player turn
};

bool CkSp(std::string); // Check the spaces from a given string
void starting(void);    // Intro draw
unsigned short int sanitizePls(void); // Sanizize number input for players
void theend(void); //The End draw
