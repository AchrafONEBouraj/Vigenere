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
void genInit(const std::string& label, std::string& file);
void doTheseAwfulThings(const std::string ifile, const std::string ofile, Encoder process, std::string (Encoder::*currentFunc)(std::string));

int main(int argc, char* argv[])
{
    std::cout << "Vigenere v0.5, copyright 2013 Deus Kane" << std::endl << "Distributed under the terms of the GNU GPL V3 (or later)" << std::endl;
    #ifdef _DEBUG
    std::cout << "argc=" << argc << std::endl;
    for(int i=0;i<argc;++i){
    std::cout << "argv[" << i << "]=" << argv[i] << std::endl;}
    #endif

//begin processing command line arguments
    std::string flg="";
    std::string arg;
    std::string ifile="";
    std::string ofile="";
    std::string key="";
    for(int i=0;i<argc;++i){
        arg=argv[i];
        if(arg[0]=='-'){
            if(arg=="-e"){flg="e";}
            if(arg=="-d"){flg="d";}
            if(i<argc-1){
                if(arg=="-if"){ifile=argv[i+1];++i;}
                if(arg=="-of"){ofile=argv[i+1];++i;}
                if(arg=="-key"){key=argv[i+1];++i;}}}}
//end processing command line arguments

    Encoder testing;
    std::string (Encoder::*currentFunc)(std::string);

    if(flg==""){
        do{
            std::cout << "Encrypt or decrypt? ";
            std::getline(std::cin, flg);
            if(flg=="x"){return 0;}
        }while(flg.size()==0 || (flg[0]!='d' && flg[0]!='D' && flg[0]!='e' && flg[0]!='E'));}

    if(flg[0]=='d'||flg[0]=='D'){
        decryptInit(ifile,ofile);
        currentFunc=&Encoder::decrypt;
    }else{
        encryptInit(ifile,ofile);
        currentFunc=&Encoder::encrypt;}

    if(key==""){
        do{
            std::cout << "Enter key (leave blank for CorrectHorseBatteryStaple): ";
            std::getline(std::cin, key);
            if(key == ""){key="CorrectHorseBatteryStaple";}
            testing.setKey(key);
        }while(testing.keySize()<=0);
        }else{
            testing.setKey(key);}

    doTheseAwfulThings(ifile, ofile, testing, currentFunc);

    return 0;
}

void encryptInit(std::string& pfile, std::string& cfile){
    genInit("plaintext",pfile);
    genInit("ciphertext",cfile);
}

void decryptInit(std::string& cfile, std::string& pfile){
    genInit("ciphertext",cfile);
    genInit("plaintext",pfile);
}

void genInit(const std::string& label, std::string& file){
    if(file==""){
        std::cout << "Enter " << label << " file name (leave blank for default): ";
        std::getline(std::cin, file);
        if(file == ""){file=label+".txt";}}
    if(file.substr(file.length()-4,4)!=".txt"){
        file+=".txt";}}

void doTheseAwfulThings(const std::string ifile, const std::string ofile, Encoder process, std::string (Encoder::*currentFunc)(std::string)){
    std::ifstream infile (ifile);
    std::ofstream outfile (ofile);
    std::string buffer;

    if (infile.is_open() && outfile.is_open()){
        while ( infile.good() ){
            getline (infile,buffer);
            buffer=(process.*currentFunc)(buffer);
            #ifdef _DEBUG
            std::cout << buffer << std::endl;
            #endif
            outfile << buffer;
            if(infile.good()){ outfile << "\n";}}
        infile.close();
        outfile.close();
        #ifdef _DEBUG
        std::cout << std::endl;
        #endif
        std::cout << "Process completed successfully." << std::endl;
    }else{
        std::cout << "File not found!" << std::endl;}}
