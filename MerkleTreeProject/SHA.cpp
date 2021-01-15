
// Created by support on 20-Dec-20.
//

#include "SHA.h"
#include <bitset>
#include <iostream>
#include <vector>
#include <iomanip>
#include <string>
#include<sstream>
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

vector <unsigned int> sha256::convert_to_binary(string input)
{
    cout << "in convert to binary" << endl;
    vector<unsigned int> block;
    for (int i = 0; i < input.size(); i++)
    {
        bitset<8> b(input.c_str()[i]);
        block.push_back(b.to_ulong());
    }
    return block;
}

//-------------------------------------------------------------------------

vector<unsigned int> sha256::padding(vector <unsigned int> block) {
    //debugging
    if (0) {
        for (int i = 0; i < block.size(); i++) {
            cout << block[i] << " ";
            if (i % 8 == 0)
                cout << endl;
        }
    }
    //l is the message length in bits
    cout << "in padding" << endl;
    int l = block.size() * 8;

    //z is the number of zeros that will be appended
    //padding equation: l+1+z=448 mod 512
    //l+1+z=448
    //l+z=447

    int z = 447 - l;

    //appending the one
    long temp1 = 0x80;    //128
    block.push_back(temp1);

    //removing 7 zeros from z
    z = z - 7;

    //appending the remaining zeros
    for (int i = 0; i < z / 8; i++)
        block.push_back(0x00000000);
    //just debugging
    if (0) {
        for (int i = 0; i < block.size(); i++) {
            cout << block[i] << " ";
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
    if (1) {
        for (int i = 0; i < block.size(); i++) {
            cout << block[i] << " ";
            if (i % 8 == 0)
                cout << endl;
        }
        cout << endl << endl;
    }
    cout << block.size() << endl;
    return block;
}
//that was hard :)

//-----------------------------------------------------------

vector<unsigned long> sha256::resize_block(vector<unsigned int> input)
{
    cout << "in resize" << endl;
    vector<unsigned long> output(16);
    // Loop through the 64 sections by 4 steps and merge those 4 sections.


    for (int i = 0; i < input.size(); i += 4)
    {
        unsigned long temp;

        // Shift the blocks to their assigned spots and OR them with the original
        // to combine them.
       /* if (i == 12) {
            cout << input[i] << " " << input[i + 1] << " " << input[i + 2] << " " << input[i + 3] << endl;
            temp = input[i];
            temp = temp << 8;
            temp = (input[i + 1]) | temp;
            temp = temp << 8;
            temp = (input[i + 2]) | temp;
            temp = temp << 8;
            temp = (input[i + 3]) | temp;
            output[i / 4] = temp;
            break;
        }*/

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
    if (1) {
        cout << "el gowa el w[] (function): ";
        for (int i = 0; i < output.size(); i++) {
            cout << output[i] << " ";
        }
        cout << endl << endl;
    }

    return output;
}
string to_hex_string(const unsigned long i) {

    stringstream s;
    s << std::hex << i;
    return s.str();
}
//--------------------------------------------------------------
string sha256::extractstr(string input) {
    string res;
    cout << input << endl;
    while ((wordCounter % 55 != 0 && input[wordCounter] != NULL) || isFirst) {
        isFirst = false;
        char x = input[wordCounter];
        res.push_back(x);
        cout << res << endl;
        wordCounter++;
    }
    cout << wordCounter << endl;
    cout << res << endl;
    return res;

}
//---------------------------------------------------------------
string sha256::hashing(string input) {



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


    int l = input.size();

    for (int iterator = l; iterator > 0; iterator = iterator - 55)
    {
        string s = extractstr(input);
        cout << s << endl;
        vector <unsigned long> block = resize_block(padding(convert_to_binary(s)));
        //cout << block.size() << endl;
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
            cout << "w[1]rotation 7:" << rot(w[1], 18) << endl
            << "w[1] without rotation: " << w[1] << endl;

        if (0)
            cout << "sigma is: " << s0(w[1]) << endl
            << "w[1]: " << w[2] << endl
            << "sigma1 is: " << s1(w[14]) << endl;

        if (0) {
            cout << "w[19]is: " << w[19] << endl
                << "w[20]is: " << w[20] << endl
                << "w[62]is: " << w[62] << endl;
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
            cout << "value of e before compression: " << e << endl
                << "SIGMA 1 (e) = " << E1(e) << endl
                << "value of ch function: " << ch(e, f, g) << endl
                << "value of temp1: " << h + E1(e) + ch(e, f, g) + k[0] + w[0] << endl
                << "value of temp2: " << E0(a) + ma(a, b, c) << endl;
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


            if (0) {
                if (i == 0)
                    cout << "a0: " << a << " e0: " << e << endl;
                if (i == 1)
                    cout << "a1: " << a << " e1: " << e << endl
                    << "value of temp1: " << temp1 << endl
                    << "value of temp2: " << temp2 << endl;
            }

        }

        if (0) {
            cout << "a: " << a << endl
                << "b: " << b << endl
                << "c: " << c << endl
                << "d: " << d << endl
                << "e: " << e << endl
                << "f: " << f << endl
                << "g: " << g << endl
                << "h: " << h << endl;


        }
        H0 = (H0 + a) & 0xFFFFFFFF;
        H1 = (H1 + b) & 0xFFFFFFFF;
        H2 = (H2 + c) & 0xFFFFFFFF;
        H3 = (H3 + d) & 0xFFFFFFFF;
        H4 = (H4 + e) & 0xFFFFFFFF;
        H5 = (H5 + f) & 0xFFFFFFFF;
        H6 = (H6 + g) & 0xFFFFFFFF;
        H7 = (H7 + h) & 0xFFFFFFFF;
    }


    string out = to_hex_string(H0);
    out.append(to_hex_string(H1));
    out.append(to_hex_string(H2));
    out.append(to_hex_string(H3));
    out.append(to_hex_string(H4));
    out.append(to_hex_string(H5));
    out.append(to_hex_string(H6));
    out.append(to_hex_string(H7));
    cout << out << endl;
    return out;
}
//that was cruel
//------------------------------------------------------
