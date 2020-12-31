
// Created by support on 20-Dec-20.
//

#include "SHA.h"
#include <bitset>
#include <iostream>
#include <vector>
#include <iomanip>
#include <sstream>
using namespace std;
//----------------------------------------------------------------------- initialising needed operations to hash

unsigned long rot(unsigned long word, int bits) {
    long x = (word >> bits);
    long y = (word << (32 - bits));
    return x | y;
}
unsigned long s0(unsigned long word) {
    long x = rot(word, 7);
    long y = rot(word, 18);
    long z = word >> 3;
    return x ^ y ^ z;
}
unsigned long s1(unsigned long word) {
    long x = rot(word, 17);
    long y = rot(word, 19);
    long z = word >> 10;
    return x ^ y ^ z;
}
unsigned long E0(unsigned long word) {
    long x = rot(word, 2);
    long y = rot(word, 13);
    long z = rot(word, 22);
    return x ^ y ^ z;
}
unsigned long E1(unsigned long word) {
    long x = rot(word, 6);
    long y = rot(word, 11);
    long z = rot(word, 25);
    return x ^ y ^ z;
}
unsigned long ch(long x, long y, long z) {
    long temp1 = x & y;
    //cout << "ch function debug 2 x&y:"<<temp1<<endl;
    long temp2 = ~x & z;
    //cout << "ch function debug 2 ~x&z:"<<temp1<<endl;
    return temp1 ^ temp2;
}
unsigned long ma(long x, long y, long z) {
    long temp1 = x & y;
    long temp2 = x & z;
    long temp3 = y & z;
    return temp1 ^ temp2 ^ temp3;
}


//-------------------------------------------------------------------------

vector <unsigned long> convert_to_binary(string input)
{
    vector<unsigned long> block;
    for (int i = 0; i < input.size(); i++)
    {
        bitset<8> b(input.c_str()[i]);
        block.push_back(b.to_ulong());
    }
    return block;
}

//-------------------------------------------------------------------------

vector<unsigned long> padding(vector <unsigned long> block) {
    //debugging
    if (0) {
        for (int i = 0; i < block.size(); i++) {
           // cout << block[i] << " ";
            if (i % 8 == 0)
                cout << endl;
        }
    }
    //l is the message length in bits
    int l = block.size() * 8;

    //z is the number of zeros that will be appended
    //padding equation: l+1+z=448 mod 512
    //l+1+z=448
    //l+z=447

    int z = 447 - l;

    //appending the one
    int temp1 = 0x80;    //128
    block.push_back(temp1);

    //removing 7 zeros from z
    z = z - 7;

    //appending the remaining zeros
    for (int i = 0; i < z / 8; i++)
        block.push_back(0x00000000);
    //just debugging
    if (0) {
        for (int i = 0; i < block.size(); i++) {
           // cout << block[i] << " ";
            if (i % 8 == 0)
            
               cout << endl;
        }
        cout << endl;
    }

    //now we are 448 bits out of 512 now we need to add the message length in binary 8x8
    bitset<64>bit64(l);
    string str64 = bit64.to_string();

    //the substr(start,length) returns a part of string
    for (int i = 0; i < 64; i = i + 8)
    {
        bitset<8>temp2(str64.substr(i, 8));
        block.push_back(temp2.to_ulong());
    }
    //i hate debugging
    if (0) {
        for (int i = 0; i < block.size(); i++) {
            //cout << block[i] << " ";
            if (i % 8 == 0)
                cout << endl;
        }
        cout << endl << endl;
    }
    int x = block.size();
    //cout<< "size (padding) = "<<x<<endl<<endl;

    return block;
}
//that was hard :)

//-----------------------------------------------------------

vector<unsigned long> resize_block(vector<unsigned long> input)
{
    vector<unsigned long> output(16);
    int x = input.size();
    //cout<< "size (resize) = "<<x<<endl<<endl;
    // Loop through the 64 sections by 4 steps and merge those 4 sections.
    for (int i = 0; i < input.size(); i = i + 4)
    {
        // Lets make a big 32 bit section first.
        unsigned long temp;

        // Shift the blocks to their assigned spots and OR them with the original
        // to combine them.
        temp = input[i];
        temp = temp << 8;
        temp = (input[i + 1]) | temp;
        temp = temp << 8;
        temp = (input[i + 2]) | temp;
        temp = temp << 8;
        temp = (input[i + 3]) | temp;

        // Puts the new 32 bit word into the correct output array location.
        output[i / 4] = temp;
    }
    if (0) {
        //cout << "el gowa el w[] (function): ";
        for (int i = 0; i < output.size(); i++) {
            //cout << output[i] << " ";
        }
        //cout << endl << endl;
    }

    return output;
}
//---------------------------------------------------------------
string hashProcess(vector <unsigned long> block) {
    string hashString = "";

    if (block.size() != 16) {
        cout << "error input size";
    }
    //initialising the initial round constants (k)
    unsigned long k[64] = {
            0x428a2f98,0x71374491,0xb5c0fbcf,0xe9b5dba5,0x3956c25b,0x59f111f1,
            0x923f82a4,0xab1c5ed5,0xd807aa98,0x12835b01,0x243185be,0x550c7dc3,
            0x72be5d74,0x80deb1fe,0x9bdc06a7,0xc19bf174,0xe49b69c1,0xefbe4786,
            0x0fc19dc6,0x240ca1cc,0x2de92c6f,0x4a7484aa,0x5cb0a9dc,0x76f988da,
            0x983e5152,0xa831c66d,0xb00327c8,0xbf597fc7,0xc6e00bf3,0xd5a79147,
            0x06ca6351,0x14292967,0x27b70a85,0x2e1b2138,0x4d2c6dfc,0x53380d13,
            0x650a7354,0x766a0abb,0x81c2c92e,0x92722c85,0xa2bfe8a1,0xa81a664b,
            0xc24b8b70,0xc76c51a3,0xd192e819,0xd6990624,0xf40e3585,0x106aa070,
            0x19a4c116,0x1e376c08,0x2748774c,0x34b0bcb5,0x391c0cb3,0x4ed8aa4a,
            0x5b9cca4f,0x682e6ff3,0x748f82ee,0x78a5636f,0x84c87814,0x8cc70208,
            0x90befffa,0xa4506ceb,0xbef9a3f7,0xc67178f2
    };

    //initialising the hash initial values (h)
    unsigned long static H0 = 0x6a09e667;
    unsigned long static H1 = 0xbb67ae85;
    unsigned long static H2 = 0x3c6ef372;
    unsigned long static H3 = 0xa54ff53a;
    unsigned long static H4 = 0x510e527f;
    unsigned long static H5 = 0x9b05688c;
    unsigned long static H6 = 0x1f83d9ab;
    unsigned long static H7 = 0x5be0cd19;




    unsigned long w[64];

    // first 16 chuck are the same but i have to make sure it is 32 bit
    for (int i = 0; i <= 15; i++)
    {
        w[i] = block[i] & 0xFFFFFFFF;
    }

    // for the next chucks
    for (int i = 16; i <= 63; i++)
    {
        w[i] = w[i - 16] + s0(w[i - 15]) + w[i - 7] + s1(w[i - 2]);
        w[i] = w[i] & 0xFFFFFFFF;
    }
    if (0)
       // cout << "w[1]rotation 7:" << rot(w[1], 18) << endl
       // << "w[1] without rotation: " << w[1] << endl;

    if (0)
       // cout << "sigma is: " << s0(w[1]) << endl
        //<< "w[1]: " << w[2] << endl
        //<< "sigma1 is: " << s1(w[14]) << endl;

    if (0) {
       // cout << "w[19]is: " << w[19] << endl
         //   << "w[20]is: " << w[20] << endl
           // << "w[62]is: " << w[62] << endl;
    }

    unsigned long temp1 = 0;
    unsigned long temp2 = 0;
    unsigned long a = H0;
    unsigned long b = H1;
    unsigned long c = H2;
    unsigned long d = H3;
    unsigned long e = H4;
    unsigned long f = H5;
    unsigned long g = H6;
    unsigned long h = H7;

    if (0)
    {
       // cout << "value of e before compression: " << e << endl
         //   << "SIGMA 1 (e) = " << E1(e) << endl
           // << "value of ch function: " << ch(e, f, g) << endl
            //<< "value of temp1: " << h + E1(e) + ch(e, f, g) + k[0] + w[0] << endl
            //<< "value of temp2: " << E0(a) + ma(a, b, c) << endl;
    }


    //compression function
    for (int i = 0; i < 64; i++)
    {
        temp1 = h + E1(e) + ch(e, f, g) + k[i] + w[i];
        temp2 = E0(a) + ma(a, b, c);
        h = g;
        g = f;
        f = e;
        e = (d + temp1) & 0xFFFFFFFF;
        d = c;
        c = b;
        b = a;
        a = (temp1 + temp2);


        if (1) {
            if (i == 0)
                //   cout << "a0: " << a << " e0: " << e << endl;
                if (i == 1)
                    // cout << "a1: " << a << " e1: " << e << endl
                     //<< "value of temp1: " << temp1 << endl
                     //<< "value of temp2: " << temp2 << endl;
                    cout << endl;
        }

    }

    if (0) {
        ////cout << "a: " << a << endl
        //  //  << "b: " << b << endl
        //   // << "c: " << c << endl
        //    //<< "d: " << d << endl
        //    << "e: " << e << endl
        //    << "f: " << f << endl
        //    << "g: " << g << endl
        //    << "h: " << h << endl;


    }
    H0 = (H0 + a) & 0xFFFFFFFF;
    H1 = (H1 + b) & 0xFFFFFFFF;
    H2 = (H2 + c) & 0xFFFFFFFF;
    H3 = (H3 + d) & 0xFFFFFFFF;
    H4 = (H4 + e) & 0xFFFFFFFF;
    H5 = (H5 + f) & 0xFFFFFFFF;
    H6 = (H6 + g) & 0xFFFFFFFF;
    H7 = (H7 + h) & 0xFFFFFFFF;

    // Append the hash segments together one after the other to get the full
    // 256 bit hash.
    //cout << "hash is : " << hex << H0 << H1 << H2 << H3 << H4 << H5 << H6 << H7 << endl;
    //hashString.insert(hex);
    //hashString.append(to_string(hex)));

    stringstream ss;
    ss << hex << H0;
    hashString.append(ss.str());
    stringstream s1;
    s1 << hex << H1;
    hashString.append(s1.str());
    stringstream s2;
    s2 << hex << H2;
    hashString.append(s2.str());
    stringstream s3;
    s3 << hex << H3;
    hashString.append(s3.str());
    stringstream s4;
    s4 << hex << H4;
    hashString.append(s4.str());
    stringstream s5;
    s5 << hex << H5;
    hashString.append(s5.str());
    stringstream s6;
    s6 << hex << H6;
    hashString.append(s6.str()); 
    stringstream s7;
    s7 << hex << H7;
    hashString.append(s7.str());

    



    //cout << "Hashstring = " <<hashString << endl;
    return hashString;
}

string hash_(string inputToHash) {
    vector <unsigned long> bin;
    bin = convert_to_binary(inputToHash);
    bin = padding(bin);
    bin = resize_block(bin);
    string hashed = hashProcess(bin);
    return hashed;
   // cout << endl;
   // displayHash(bin);
}
void displayHash(string inputToHash) {
    cout << hash_(inputToHash) << endl;
}
//that was cruel
