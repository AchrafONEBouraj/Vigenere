#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <iterator>

#include "encoder.h"

Encoder::Encoder(std::string keyin){
    init(keyin);}

Encoder::Encoder(){
    init("default");}

std::string Encoder::encrypt(std::string plaintext){
    std::string out;
    for(unsigned int i=0;i<plaintext.length();++i){
        if(invAlphabet.count(plaintext[i]) > 0){
                int k=invAlphabet[plaintext[i]];
                int j=(k>25)?26:0;
            out.push_back(alphabet[(k+key[ctr])%26 + j]);
        }else{
            out.push_back(plaintext[i]);
            --ctr;}
    ctr=(ctr+1)%key.size();}
    return out;};

std::string Encoder::decrypt(std::string plaintext){
    std::string out;
    for(unsigned int i=0;i<plaintext.length();++i){
        if(invAlphabet.count(plaintext[i]) > 0){
                int k=invAlphabet[plaintext[i]];
                int j=(k>25)?26:0;
                if(k-key[ctr]<0){k+=26;};
            out.push_back(alphabet[(k-key[ctr])%26 + j]);
        }else{
            out.push_back(plaintext[i]);
            --ctr;}
    ctr=(ctr+1)%key.size();}
    return out;};

void Encoder::setKey(std::string keyin){
    key.clear();
    for(unsigned int i=0;i<keyin.length();++i){
        if(invAlphabet.count(keyin[i])>0)
            key.push_back(invAlphabet[keyin[i]]%26);}
    ctr=0;}

const std::vector<int>& Encoder::getKey() const {return key;}

size_t Encoder::keySize() const {return key.size();}

void Encoder::init(std::string keyin){
    alphabet ="ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    for(int i=0;i<alphabet.length();++i){
        invAlphabet[alphabet[i]]=i;}
    setKey(keyin);}
