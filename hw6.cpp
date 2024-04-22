#include <vector>
#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>
#include <bitset>
#include <locale>
#include <codecvt>
#include <cstdlib> 
#include "card.hpp"


//i would love to know how many other students actually render the cards. 
//cards are objects
//decks are vectors of card objects
//hands are just really small decks
double bal=0;
double wager=0;


void updatePlayerBalance(double change){
bal +=change;
}


void DisplayOutCome(int status){
if (status){
cout<<"Balance update: +$"<<wager<<endl;
}
else{
cout<<"Balance update: -$"<<wager<<endl;
}
cout<<"Your new balance is $";
if (status){
cout<<bal + wager;
}
else{
cout<<bal - wager;
}

cout<<endl;
}


void displayGameSummary(int win, int loss, int tie, int initbal, int wb, int lb){
cout<<"=== Game Summary === "<<endl;
cout<<"Total Rounds Played: "<<win+loss+tie+wb+lb<<endl; 
cout<<"Total Wins (Regular): " <<  win<<endl;
cout<<"Total Wins (Blackjack): " <<  wb<<endl;
cout<<"Total Losses (Regular): " << loss<<endl;
cout<<"Total Losses (Blackjack): " << lb<<endl;
cout<<"Total Ties (Regular): " << tie<<endl;
cout<<"Final Balance: $"<<fixed<<setprecision(2)<<bal<<endl;
cout<<"Net Gain: $"<<fixed<<setprecision(2)<<bal - initbal<<endl;



}

using namespace std;
int findCard(vector<card> inpt, card src){
int rtn;
for (unsigned int i=0; i<inpt.size();i++){
if(inpt.at(i).fullname == src.fullname){
rtn=i;
}
}
return rtn;
}



int getHandSum(vector<card> inpt){
int sum=0;
for (unsigned int i=0; i<inpt.size();i++){
sum+=inpt.at(i).worth;
}
return sum;
}


int isBlackJack(vector<card> inpt){//check to see if we got a blackjack. requirement of assignment.
int sum=0;
for (unsigned int i=0; i<inpt.size();i++){
sum+=inpt.at(i).worth;
}
if(sum - 21){return 0;}
else{return 1;}
return 0;
}


void printHand(vector<card> inpt){


/*for (unsigned int i=0; i < inpt.size();i++){
cout<<inpt.at(i).render << " "<< inpt.at(i).fullname<<endl;
}*/
//for the upgrade to hw6, we are told to display in the order of: Diamonds,Hearts,Clubs, then Spades. 

for (unsigned int i=0; i < inpt.size();i++){
if(inpt.at(i).suit=="Diamonds"){
cout<<inpt.at(i).render << " "<< inpt.at(i).fullname<<endl;}
}
for (unsigned int i=0; i < inpt.size();i++){
if(inpt.at(i).suit=="Hearts"){
cout<<inpt.at(i).render << " "<< inpt.at(i).fullname<<endl;}
}
for (unsigned int i=0; i < inpt.size();i++){
if(inpt.at(i).suit=="Clubs"){
cout<<inpt.at(i).render << " "<< inpt.at(i).fullname<<endl;}
}
for (unsigned int i=0; i < inpt.size();i++){
if(inpt.at(i).suit=="Spades"){
cout<<inpt.at(i).render << " "<< inpt.at(i).fullname<<endl;}
}
for (unsigned int i=0; i < inpt.size();i++){
if(inpt.at(i).suit=="Mysteries"){
cout<<inpt.at(i).render << " "<< inpt.at(i).fullname<<endl;}
}
}



unsigned int GetCardNum(string inptcard){//this function turns our renderable utf8 card into a mathable utf-32 integer of its unicode point code.
unsigned int fist,secnt,therd,phorf;
stringstream e;
e.clear();
fist= inptcard[0] - 0xffffff00;
secnt= inptcard[1] - 0xffffff00;
therd=inptcard[2] - 0xffffff00;
phorf=inptcard[3] - 0xffffff00;
e <<bitset<3>(fist) <<""<<bitset<6>(secnt) <<""<< bitset<6>(therd) <<""<<bitset<6>(phorf);
string outpt=e.str();
return stoll(outpt, nullptr, 2);
}
string GetCardName(string inpt){ //this function gets us the name of a card
unsigned int crd=GetCardNum(inpt);
string nme="error";
stringstream hexcvtr;
switch (crd % 0x10){
case 0x0:
if(crd == 0x1F0A0){
nme="Hidden Card";}
break;
case 0x1:
nme="Ace";
break;
case 0xB:
nme="Jack";break;
case 0xC:
nme="Knight";break;
case 0xD:
nme="Queen";break;
case 0xE:
nme="King";break;
case 0xF:
nme="Joker";break;
default:
hexcvtr<<dec<<(crd % 0x10);
nme=hexcvtr.str();
break;
};
//nme=to_string(crd);
return nme;
}
int IsCardValid(string inpt){ //do we use this card in blackjack?
int chkr=0;
unsigned int crd=GetCardNum(inpt);
switch (crd % 0x10){
case 0x0:
if(crd == 0x1F0A0){ //card back
chkr=1;break;}
chkr=0;//no "zero" cards
break;
case 0xF:
chkr=0;break;//no jokers
case 0xC:
chkr=0;break;//no knights
default:
chkr=1;break;
};

return chkr;
}
string GetCardSuit(string inpt){//this gets us the suit of any given card
string nme;
unsigned int crd=GetCardNum(inpt);
switch ((crd % 0x100) / 0x10 ){
case 0x1:
nme="Ace";
break;
case 0xA:
if(crd == 0x1F0A0){
nme="Mysteries";break;}
nme="Spades";break;
case 0xB:
nme="Hearts";break;
case 0xC:
nme="Diamonds";break;
case 0xD:
nme="Clubs";break;
default:
nme="error";
break;
};
return nme;
}
int GetCardWorth(string inpt){//how much is this card worth in blackjack?
int nme=0;
unsigned int crd=GetCardNum(inpt);
stringstream hexcvtr;
switch (crd % 0x10){
case 0x0:
if(crd == 0x1F0A0){
nme=0;}
break;
case 0x1:
nme=1;
break;
case 0xB:
nme=10;break;
case 0xC:
nme=10;break;
case 0xD:
nme=10;break;
case 0xE:
nme=10;break;
case 0xF:
nme=0;break;
default:
hexcvtr<<dec<<(crd % 0x10);
nme=stoi(hexcvtr.str());
break;
};
return nme;
}
card generateRandomCard(vector<card> inpt){ //generate a random card from a given deck. requirement of the assignment
return inpt.at(rand() % inpt.size());
}
card generateRandomCard(vector<card> inpt, const int probability){//generate a random card from a given deck, with chance of guarenteeing a 10-score card. requirement of the assignment
wstring_convert<codecvt_utf8<char32_t>, char32_t> utf32_to_utf8;
if ( (rand() % 99) <= probability){
//lets generate a vector of only 10 cards. 
vector<card>genvcdeck;
string blankcard="\U0001f0a0";
card genrat;
stringstream genss;
for (int i=0; i<=63;i++){
if(IsCardValid(utf32_to_utf8.to_bytes(GetCardNum(blankcard) + i))) { 
genrat.render=utf32_to_utf8.to_bytes(GetCardNum(blankcard) + i);
genrat.name=GetCardName(utf32_to_utf8.to_bytes(GetCardNum(blankcard) + i));
genrat.suit=GetCardSuit(utf32_to_utf8.to_bytes(GetCardNum(blankcard) + i));
genss.str("");
genss<<GetCardName(utf32_to_utf8.to_bytes(GetCardNum(blankcard) + i))<<" of "<<GetCardSuit(utf32_to_utf8.to_bytes(GetCardNum(blankcard) + i));
genrat.fullname=genss.str();
genrat.worth=GetCardWorth(utf32_to_utf8.to_bytes(GetCardNum(blankcard) + i));
if(genrat.worth == 10){
genvcdeck.push_back(genrat);}
} 
}

return genvcdeck.at(rand() % genvcdeck.size());
}
return inpt.at(rand() % inpt.size());
}
int PlayBlackJack(){

wstring_convert<codecvt_utf8<char32_t>, char32_t> utf32_to_utf8; //make an object "utf32_to_utf8 to convert my integers into renderable characters
string blankcard="\U0001f0a0";



//okay, now that we have ways to get data about cards, lets create our card objects. 
//we're gonna steal the setup of our rendering test to make our table's deck. 

vector<card> tabledeck;
card genrat;
stringstream genss;
for (int i=0; i<=63;i++){
if(IsCardValid(utf32_to_utf8.to_bytes(GetCardNum(blankcard) + i))) { 
genrat.render=utf32_to_utf8.to_bytes(GetCardNum(blankcard) + i);
genrat.name=GetCardName(utf32_to_utf8.to_bytes(GetCardNum(blankcard) + i));
genrat.suit=GetCardSuit(utf32_to_utf8.to_bytes(GetCardNum(blankcard) + i));
genss.str("");
genss<<GetCardName(utf32_to_utf8.to_bytes(GetCardNum(blankcard) + i))<<" of "<<GetCardSuit(utf32_to_utf8.to_bytes(GetCardNum(blankcard) + i));
genrat.fullname=genss.str();
genrat.worth=GetCardWorth(utf32_to_utf8.to_bytes(GetCardNum(blankcard) + i));
tabledeck.push_back(genrat);
} 
}
//now that our table's deck is made, we can just interract with cards by interracting with the vector. 

//time to play blackjack!
vector<card> playerhand;
vector<card> dealerhand;
card flipcard;
flipcard=tabledeck.at(0);
tabledeck.erase(tabledeck.begin());
card holdcard;
int choice=5;

cout<<dec<<fixed<<setprecision(2)<<"Current balance: $"<<bal<<endl;;
cout<<"How much money would you like to wager? ";
cin>>fixed>>setprecision(2)>>wager;
while ((bal - wager) <= 0){
cout<<"no, try again. ";
cin>>wager;}

//time to deal!
cout<<endl;
dealerhand.push_back(generateRandomCard(tabledeck));
tabledeck.erase(tabledeck.begin() + findCard(tabledeck,dealerhand.back()));
dealerhand.push_back(generateRandomCard(tabledeck));
tabledeck.erase(tabledeck.begin() + findCard(tabledeck,dealerhand.back()));
holdcard=dealerhand.back();
dealerhand.back()=flipcard;
//now the dealer has 2 cards.

playerhand.push_back(generateRandomCard(tabledeck,15));
tabledeck.erase(tabledeck.begin() + findCard(tabledeck,playerhand.back()));
playerhand.push_back(generateRandomCard(tabledeck,15));
tabledeck.erase(tabledeck.begin() + findCard(tabledeck,playerhand.back()));
//now the player has 2 cards.



choice=0;
system("clear");
cout<<dec<<fixed<<setprecision(2)<<"Current balance: $"<<bal<<endl;
cout<<"Player's hand: "<<endl;
printHand(playerhand);
cout<<endl;
cout<<"Dealer's hand: "<<endl;
printHand(dealerhand);
cout<<endl;
//check for blackjack
dealerhand.back()=holdcard;
if(isBlackJack(playerhand) && !(isBlackJack(dealerhand))){
cout<<"Congratulations! You hit Blackjack!"<<endl;
return 2;
}
if(isBlackJack(dealerhand) && !(isBlackJack(playerhand))){
cout<<"Too bad, Dealer has Blackjack!"<<endl;
return -2;
}
if(isBlackJack(playerhand) && (isBlackJack(dealerhand))){
cout<<"Its a tie!"<<endl;
return 69420;
}
dealerhand.back()=flipcard;
//checked for blackjacks
cout<<endl;
//player's turn
while (!(choice)){
cout<<endl;
cout<<"make a choice:"<<endl<<"0: hit"<<endl<<"1: double down"<<endl<<"3: stand"<<endl<<"*: exit program."<<endl;

if(!(cin>>choice)){
return(30);
cin.clear();
cout<<endl;
cout<<"error";
cout<<endl;
cin.ignore();
}
if(!(choice)){
playerhand.push_back(generateRandomCard(tabledeck));
cout <<"you received a: "<<playerhand.back().render<<" "<<playerhand.back().fullname<<endl;
tabledeck.erase(tabledeck.begin() + findCard(tabledeck,playerhand.back()));
//cout<<"Player's hand: "<<endl;
//printHand(playerhand);
if(isBlackJack(playerhand) && !(isBlackJack(dealerhand))){
cout<<endl;
cout<<"player's final hand:"<<endl;
printHand(playerhand);
cout<<endl<<"dealers final hand:"<<endl;
printHand(dealerhand);
cout<<"Congratulations! You hit Blackjack!"<<endl;
return 2;
}
if(getHandSum(playerhand) > 21){
cout<<endl;
cout<<"player's final hand:"<<endl;
printHand(playerhand);
cout<<endl<<"dealers final hand:"<<endl;
printHand(dealerhand);
cout<<"you are bust. you lose!"<<endl;
return -1;
}
}
if(choice ==1){
wager *=2;
playerhand.push_back(generateRandomCard(tabledeck));
tabledeck.erase(tabledeck.begin() + findCard(tabledeck,playerhand.back()));
cout <<"you received a: "<<playerhand.back().render<<" "<<playerhand.back().fullname<<endl;
choice=6;
if(isBlackJack(playerhand) && !(isBlackJack(dealerhand))){
cout<<endl;
cout<<"player's final hand:"<<endl;
printHand(playerhand);
cout<<endl<<"dealers final hand:"<<endl;
printHand(dealerhand);
cout<<"Congratulations! You hit Blackjack!"<<endl;
return 2;
}
if(getHandSum(playerhand) > 21){
cout<<endl;
cout<<"player's final hand:"<<endl;
printHand(playerhand);
cout<<endl<<"dealers final hand:"<<endl;
printHand(dealerhand);
cout<<"you are bust. you lose!"<<endl;
return -1;
}
break;
}
}//end of player turn



//begin dealer's turn
dealerhand.back()=holdcard;
cout<<"Dealer's hole card was a "<<dealerhand.back().render<<" "<<dealerhand.back().fullname<<endl;
//check for blackjack
if(isBlackJack(playerhand) && !(isBlackJack(dealerhand))){
cout<<"Congratulations! You hit Blackjack!"<<endl;
return 2;
}
if(isBlackJack(dealerhand) && !(isBlackJack(playerhand))){
cout<<"Too bad, Dealer has Blackjack!"<<endl;
return -2;
}
if(isBlackJack(playerhand) && (isBlackJack(dealerhand))){
cout<<"Its a tie!"<<endl;
return 69420;
}
//dealerhand.back()=flipcard;
//checked for blackjacks

if(getHandSum(dealerhand) <=16){
dealerhand.push_back(generateRandomCard(tabledeck));
cout <<"dealer received a: "<<dealerhand.back().render<<" "<<dealerhand.back().fullname<<endl;
tabledeck.erase(tabledeck.begin() + findCard(tabledeck,dealerhand.back()));
}
if(getHandSum(dealerhand) > 21){
cout<<endl;
cout<<"player's final hand:"<<endl;
printHand(playerhand);
cout<<endl<<"dealers final hand:"<<endl;
printHand(dealerhand);
cout<<"dealer is bust. you win!"<<endl;
return 1;
}
if(isBlackJack(dealerhand) && !(isBlackJack(playerhand))){
cout<<endl;
cout<<"player's final hand:"<<endl;
printHand(playerhand);
cout<<endl<<"dealers final hand:"<<endl;
printHand(dealerhand);
cout<<"Too bad, Dealer has Blackjack!"<<endl;
return -2;
}//end of dealers turn

//cout<<"\U0001f0a0"<<endl;

if(getHandSum(playerhand) > getHandSum(dealerhand)){
cout<<endl;
cout<<"player's final hand:"<<endl;
printHand(playerhand);
cout<<endl<<"dealers final hand:"<<endl;
printHand(dealerhand);
cout<<"you beat the dealer!"<<endl;
return 1;
}
if(getHandSum(playerhand) < getHandSum(dealerhand)){
cout<<endl;
cout<<"player's final hand:"<<endl;
printHand(playerhand);
cout<<endl<<"dealers final hand:"<<endl;
printHand(dealerhand);
cout<<"the dealer beat you!"<<endl;
return -1;
}
if(isBlackJack(playerhand) && (isBlackJack(dealerhand))){
cout<<"Its a tie!"<<endl;
return 69420;
}
/*cout<<endl;
cout<<"player's final hand:"<<endl;
printHand(playerhand);
cout<<endl<<"dealers final hand:"<<endl;
printHand(dealerhand);*/
return 0;
}




int main(){

//wstring_convert<codecvt_utf8<char32_t>, char32_t> utf32_to_utf8; //make an object "utf32_to_utf8 to convert my integers into renderable characters
//string blankcard="\U0001f0a0";
//just testing our ability to render cards, and get their utf32 code as a hex integer, blackjack does math, i refuse to make a lookup table of cards and their values
//for (int i=0; i<=63;i++){
//if(IsCardValid(utf32_to_utf8.to_bytes(GetCardNum(blankcard) + i))) {//dont try to render cards with value of zero, for each suit. because they dont exist, there is no card below on ace.  
//cout<<" "<<utf32_to_utf8.to_bytes(GetCardNum(blankcard) + i);
//cout<<" "<< GetCardName(utf32_to_utf8.to_bytes(GetCardNum(blankcard) + i));
//cout<<" of "<<GetCardSuit(utf32_to_utf8.to_bytes(GetCardNum(blankcard) + i));
//cout<<". score: "<< dec<<GetCardWorth(utf32_to_utf8.to_bytes(GetCardNum(blankcard) + i));
//cout<<endl;
//}// //use the to_bytes method of our wstring_convert instance to convert our integers into renderable utf-8 character
//}
//return 0;
//testing complete
srand(1570);
bal= rand() %(900) + 100;
double initbal=bal;
int wins=0;
int loss=0;
int lb=0;
int wb=0;
int ties=0;
while (bal >0){
cout<<endl;
switch (PlayBlackJack()){
case 1:
DisplayOutCome(1);
wins++;
updatePlayerBalance(wager);

break;
case 2:
DisplayOutCome(1);
wb++;
updatePlayerBalance(wager);
break;
case 69420:
ties++;
break;
case -1:
DisplayOutCome(0);
loss++;
updatePlayerBalance( wager * -1);
break;
case -2:
DisplayOutCome(0);
updatePlayerBalance(wager * -1);
;break;
case 30:
displayGameSummary(wins, loss, ties, initbal, wb, lb);
exit(1);
break;
};
}
displayGameSummary(wins, loss, ties, initbal, wb, lb);
return 0;
}
