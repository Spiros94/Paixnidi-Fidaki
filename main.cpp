#include <iostream>
#include <string>
#include <cstdlib> //random
#include <ctime> // Time for random seed
#include "header.h"


userInterface::userInterface(const unsigned short int pls){
    players = pls;
    try{
        NaSu = new std::string [2*players];
        PlayRound = new unsigned short int[2];
    } catch (std::bad_alloc& ba){
        std::cerr << "bad_alloc caught: " << ba.what() << std::endl;
    }
    PlayRound[0] = 1; PlayRound[1] = 0;
}


userInterface::~userInterface(){
    delete [] NaSu;
    delete [] PlayRound;
}

void userInterface::NextRound(void){
    if(PlayRound[0]==players){ // If last player just played return to first
        PlayRound[0] = 1;
        PlayRound[1] = 0;
    } else {
    PlayRound[0] += 1;
    PlayRound[1] += 2;
    }
    std::cout << "Patise enter gia ton epomeno paikti..\n\n" << std::endl;
    std::cin.get();
}

unsigned short int userInterface::WhoPlays(void) const{
    return PlayRound[0];
}

unsigned short int userInterface::PlayBy2(void) const{
    return PlayRound[1];
}

void userInterface::GetName(unsigned short int pl) const{
    pl-=1;
    std::cout << NaSu[pl*2] << " ";
    std::cout << NaSu[pl*2+1];
}

void userInterface::GetNaSus(void){
    unsigned short int counter = 1;
    std::cout << "Kathe paiktis prepei na dinei prwta to onoma kai meta to epwnimo tou." << std::endl;
    for(unsigned short int i=0; i<(2*players); i+=2){
            std::cout << "\nPaikti " << counter << " dwse to onoma sou: ";
            std::cin >> NaSu[i];
            std::cout << "Twra dwse to epwnimo sou: ";
            std::cin >> NaSu[i+1];
            while(CkSp(NaSu[i]) || CkSp(NaSu[i+1])){ // Check for spaces on input
                std::cout << "\nKapoio lathos egine. Prospathise ksana to onoma: ";
                std::cin >> NaSu[i];
                std::cout << "\nTwra dwse to epinomo: ";
                std::cin >> NaSu[i+1];
            }
            counter++;
    }
    std::cout << "\n";
}

void userInterface::AnnPlayer(void) const{
    std::cout << "Einai h seira toy paikti " << NaSu[PlayRound[1]] << " " << NaSu[PlayRound[1]+1] << std::endl;

}

fidaki::fidaki(unsigned short int pls){
    //Try to create dynamic array and ccatch exceptions
    try{
        fidia = new  unsigned short int[18];
        skales = new  unsigned short int[18];
        Cpos = new unsigned short int[pls];
    } catch (std::bad_alloc& ba){
        std::cerr << "bad_alloc caught: " << ba.what() << std::endl;
    }
    //Fill arrays
    skales[0] = 3; skales[1] = 25; skales[2] = 8; skales[3] = 34; skales[4] = 23; skales[5] = 41; skales[6] = 33; skales[7] = 49; skales[8] = 37; skales[9] = 67; skales[10] = 56; skales[11] = 78; skales[12] = 69; skales[13] = 87; skales[14] = 71; skales[15] = 91; skales[16] = 80 ; skales[17] = 99;
    fidia[0] = 18; fidia[1] = 6; fidia[2] = 36; fidia[3] = 14; fidia[4] = 44; fidia[5] = 20; fidia[6] = 52; fidia[7] = 30; fidia[8] = 61; fidia[9] = 42; fidia[10] = 72; fidia[11] = 24; fidia[12] = 92; fidia[13] = 48; fidia[14] = 94; fidia[15] = 63; fidia[16] = 98; fidia[17] = 57;
    for(int i=0;i<pls;i++){
        Cpos[i] = 0;
    }
}


fidaki::~fidaki(){
    delete [] skales;
    delete [] fidia;
    delete [] Cpos;
}

unsigned short int fidaki::checkFor(unsigned short int blk,unsigned short int* dice) const{
    std::cout << "Isoun sto block " << blk << std::endl;
    if((blk+*dice) > 100){
        blk = 100 - (*dice -(100-blk));
        std::cout << "Perases to 100. Pigaineis pisw sto " << blk << ". ";
    } else {
        blk += *dice;
    }

    for(unsigned short int i=0; i<17; i+=2){
        if(skales[i] == blk){
            blk = skales[i+1];
            std::cout << "Epeses panw se skala. Pigaineis sto " << skales[i+1] << std::endl;
        }
        if(fidia[i] == blk){
            blk = fidia[i+1];
            std::cout << "Epeses panw se fidi. Kateveneis sto " << fidia[i+1] << std::endl;
        }
    }
    std::cout << "Eisai sto block " << blk << " ." << std::endl;
    return blk;
}

void fidaki::UpPos(unsigned short int blk, unsigned short int pl){
    Cpos[pl-1] = blk;
}

unsigned short int fidaki::GetPos(unsigned short int pl) const{
    return Cpos[pl-1];
}

unsigned short int fidaki::RollDice(void) const{
    srand(static_cast<unsigned int>(time(0)));
    unsigned short int j = ((rand() % 11) + 2);
    std::cout << "Ta zaria eferan " << j << std::endl;
    return j;
}

int main()
{
    starting();
    unsigned short int players = sanitizePls();
    fidaki engine(players);
    userInterface user(players);
    user.GetNaSus();
    bool wined = false;
    unsigned short int dice = 0;

    while(!wined){
        user.AnnPlayer();
        dice = engine.RollDice();

        engine.UpPos(engine.checkFor(engine.GetPos(user.WhoPlays()),&dice),user.WhoPlays());

        if(engine.GetPos(user.WhoPlays()) == 100){
            std::cout << "\n\nO paixtis "; user.GetName(user.WhoPlays()); std::cout << " nikise!" << std::endl;
            wined = true;
        }
        if(!wined) user.NextRound();
        dice = 0;
    }
    theend();
    return 0;
}

unsigned short int sanitizePls(void){
    unsigned short int pls = 0;
    std::cout << "Posoi paixtes tha paiksoun(2-6): ";
    std::cin >> pls;
    while(pls<2 || pls>6){
        std::cout << "\n" << "Dwsate lathos arithmo. Prospathiste ksana: ";
        std::cin >> pls;
    }
    return pls;
}
bool CkSp(std::string str){
    if(str == "") return true;
    if(str == " ") return true;
    if(str == "  ") return true;
    if(str == "   ") return true;
    return false;
}

void theend(void){
std::cout << std::endl;
std::cout << "+-+-+-+-+ +-+-+-+-+" << std::endl;
std::cout << "|G|a|m|e| |O|v|e|r|" << std::endl;
std::cout << "+-+-+-+-+ +-+-+-+-+" << std::endl;
std::cin.get();
}

void starting(void){
std::cout << "****************************" << std::endl;
std::cout << " _____ _     _       _    _ " << std::endl;
std::cout << "|  ___(_) __| | __ _| | _(_)" << std::endl;
std::cout << "| |_  | |/ _` |/ _` | |/ / |" << std::endl;
std::cout << "|  _| | | (_| | (_| |   <| |" << std::endl;
std::cout << "|_|   |_|\\__,_|\\__,_|_|\\_\\_|" << std::endl;
std::cout << "                            " << std::endl;
std::cout << "****************************" << std::endl;
std::cout << "Made by Mitropoylos Spiros 2013" << std::endl;
std::cout << " www.eyrhka.gr - cont@eyrhka.gr " << std::endl << std::endl;
}
