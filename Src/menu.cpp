#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <memory>
#include <inttypes.h>
#include <utility>
#include <type_traits>
#include <random>
#include <algorithm>

#include <boost/multiprecision/cpp_int.hpp>
#include <boost/numeric/conversion/cast.hpp>

#include "menu.hpp"

void displayManu(void)
{
    std::cout << "E-MEDIA\n";
    std::cout << "L-> Load .wav file\n";
    std::cout << "S-> Save .wav file\n";
    std::cout << "P-> Print first N samples\n";
    std::cout << "X-> Encrypt file with XOR\n";
    std::cout << "Y-> Decrypt file with XOR\n";
    std::cout << "E-> Encrypt file with RSA\n";
    std::cout << "D-> Decrypt file with RSA\n";
    std::cout << "T-> Test RSA with numeric data\n";
    std::cout << "Q-> Quit\n";
}

void Menu(void)
{
    char option;
    WAVHeader header;
    data_t* WAVData;
    std::string filename_open = "Audio/";
    std::string filename_save = "Audio/";
    std::ifstream file_open(filename_open.c_str(), std::ifstream::binary);
    std::ofstream file_save(filename_save.c_str(), std::ofstream::binary);
    Cryptography::RsaKeys keys(53,59);
    unsigned int nSamples;
    int data_size;

    do
    {
        std::system("clear");
        displayManu();
        std::cin >> option;
        switch(option)
        {
            case 'L':
            {
                std::string input;
                std::cout << "File name: \n";
                std::cin >> input;
                filename_open += input;
                std::ifstream file_open(filename_open.c_str(), std::ifstream::binary);

                if (!file_open)
                    { std::cerr << "ERR: Cannot find the file" << std::endl; }
                
                if(remove("Audio/encryptedfile.wav") != 0) { perror("Error deleting old WAV file"); }
                else { puts( "Old WAV file successfully deleted"); }
                std::cout << "Start reading WAV file... " << std::endl;
                
                readHeader(file_open,header);
                printHeader(header);

                data_size = getSubchunk2Size(header);       
                WAVData = new data_t[data_size]();
                WAVData = readData(file_open,header);

                filename_open.clear();
                filename_open = "Audio/"; 
            }
            break;
            case 'S':
            {
                std::string input;
                std::cout << "File name: \n";
                std::cin >> input;
                filename_save += input;
                std::ofstream file_save(filename_save.c_str(), std::ofstream::binary);
                //Save data to wav file
                if (!file_save)
                    { std::cerr << "ERR: Cannot find the file\n"; }

                if (std::is_empty<WAVHeader>::value)
                    { std::cerr << "ERR: Cannot save file without header\n"; file_save.close(); }
                
                std::cout << "Start saving WAV file... \n";
                writeHeader(file_save,header);
                writeData(file_save,header,WAVData);

                filename_save.clear();
                filename_save = "Audio/";
            }
            break;
            case 'P':
            {
                std::cout << "Number of samples to print:\n";
                std::cin >> nSamples;
                printExampleData(WAVData,nSamples);
            }
            break;
            case 'X':
            {
                std::vector<data_t> vec;
                vec.resize(data_size);
                boost::multiprecision::uint1024_t xor_key;

                for(int i=0; i < data_size; i++)
                    { vec[i] = *(WAVData + i); }

                std::cout << "XOR key:\n";
                std::cin >> xor_key;
                vec = Cryptography::xorEncrypt(vec,xor_key);

                std::ofstream xor_file;
                xor_file.open("Keys/xor_key.txt");
                xor_file << xor_key;
                xor_file.close();

                WAVData = new data_t[data_size](); // make sure memory is allocated
                
                for(int j=0; j < data_size; j++)
                    { *(WAVData + j) = vec[j]; }

                vec.clear(); // clear vector
                vec.shrink_to_fit(); // release memory
            }
            case 'Y':
            {
                
            }
            break;
            break;
            case 'E':
            {
                std::vector<data_t> vec;
                vec.resize(data_size);

                for(int i=0; i < data_size; i++)
                    { vec[i] = *(WAVData + i); }

                vec = Cryptography::rsaEncrypt(vec,keys);

                WAVData = new data_t[data_size](); // make sure memory is allocated
                
                for(int j=0; j < data_size; j++)
                    { *(WAVData + j) = vec[j]; }

                vec.clear(); // clear vector
                vec.shrink_to_fit(); // release memory
            }
            break;
            case 'D':
            {
                std::vector<data_t> vec;
                vec.resize(data_size);

                for(int i=0; i < data_size; i++)
                    { vec[i] = *(WAVData + i); }

                vec = Cryptography::rsaDecrypt(vec,keys);

                WAVData = new data_t[data_size](); // make sure memory is allocated
                
                for(int j=0; j < data_size; j++)
                    { *(WAVData + j) = vec[j]; }

                vec.clear(); // clear vector
                vec.shrink_to_fit(); // release memory
            }
            break;
            case 'T':
            {
                std::vector<data_t> data;
                data.resize(20);
                std::iota(data.begin(),data.end(),1);
    
                keys.generateKeys(131,107);
                keys.PrintKeys();
                auto encrypted = Cryptography::rsaEncrypt(data,keys);
                auto decrypted = Cryptography::rsaDecryptAsync(encrypted,keys);
                std::cout << "Data: \n";
                for(auto x : data) { std::cout << x << " "; }
                std::cout << "\n";
                std::cout << "Encrypted: \n";
                for(auto x : encrypted) { std::cout << x << " "; }
                std::cout << "\n";
                std::cout << "Decrypted: \n";
                for(auto x : decrypted) { std::cout << x << " "; }
                std::cout << "\n";
            }
            break;
            case 'Q':
            break;
            default:
                std::cout << "No such option\n";
            break;
        }
    } while (option != 'Q');
}