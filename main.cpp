/*
    Vigenere: a simple Vigenere cipher implementaton in C++.
    Copyright (C) 2013 Deus Kane

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <iterator>

#include "encoder.h"

void encryptInit(std::string& pfile, std::string& cfile);
void decryptInit(std::string& pfile, std::string& cfile);

int main()
{
    std::string ifile;
    std::string ofile;
    std::string key;
    std::string flg;
    Encoder testing;
    std::string (Encoder::*currentFunc)(std::string);

    do{
        std::cout << "Encrypt or decrypt? ";
        std::getline(std::cin, flg);
    }while(flg.size()==0 || (flg[0]!='d' && flg[0]!='D' && flg[0]!='e' && flg[0]!='E'));

    if(flg[0]=='d'||flg[0]=='D'){
        decryptInit(ifile,ofile);
        currentFunc=&Encoder::decrypt;
    }else{
        encryptInit(ifile,ofile);
        currentFunc=&Encoder::encrypt;}

    do{
        std::cout << "Enter key (leave blank for CorrectHorseBatteryStaple): ";
        std::getline(std::cin, key);
        if(key == ""){key="CorrectHorseBatteryStaple";}
        testing.setKey(key);
    }while(testing.keySize()<=0);

    std::ifstream infile (ifile);
    std::ofstream outfile (ofile);

    std::string buffer;
    std::string ebuffer;

    if (infile.is_open()){
        while ( infile.good() ){
            getline (infile,buffer);
            ebuffer=(testing.*currentFunc)(buffer);
            std::cout << ebuffer << std::endl;
            outfile << ebuffer;
            if(infile.good()){ outfile << "\n";}}
        infile.close();
        outfile.close();
    }else{
        std::cout << "File not found!" << std::endl;}

    return 0;
}

void genInit(const std::string& label, std::string& file){
    std::cout << "Enter " << label << " file name (leave blank for default): ";
    std::getline(std::cin, file);
    if(file == ""){file=label+".txt";}
    if(file.substr(file.length()-4,4)!=".txt"){
        file+=".txt";}}

void encryptInit(std::string& pfile, std::string& cfile){
    genInit("plaintext",pfile);
    genInit("ciphertext",cfile);
}

void decryptInit(std::string& cfile, std::string& pfile){
    genInit("ciphertext",cfile);
    genInit("plaintext",pfile);
}
