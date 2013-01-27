#ifndef ENCODER_H_INCLUDED
#define ENCODER_H_INCLUDED

class Encoder
{
public:
    Encoder(std::string keyin);
    Encoder();
    std::string encrypt(std::string plaintext);
    std::string decrypt(std::string plaintext);
    void setKey(std::string keyin);
    const std::vector<int>& getKey() const;
    size_t keySize() const;
private:
    void init(std::string keyin);
    std::map<char,int> invAlphabet;
    std::string alphabet;
    std::vector<int> key;
    int ctr;

};


#endif // ENCODER_H_INCLUDED
