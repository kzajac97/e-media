#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <memory>
#include <inttypes.h>
#include <utility>
#include <type_traits>

#include "rsa.hpp"
#include "reader.hpp"

int main(void)
{
//__________________WAV Files________________________________________

//     //std::string fileName_open = "ptak.wav";
//     std::string fileName_open = "timer.wav"; 
//     //std::string fileName_open = "melodia.wav";
// //___________________________________________________________________

//     std::string fileName_save= "encryptedfile.wav";
//     std::ifstream file_open(fileName_open.c_str(), std::ifstream::binary);
//     std::ofstream file_save(fileName_save.c_str(), std::ofstream::binary);
//     WAVHeader header;

//     if (!file_open)
//         { std::cerr << "ERR: Cannot find the file" << std::endl; }
    
//     if(remove("plik_przetworzony.wav") != 0) { perror("Error deleting old WAV file"); }
//     else { puts( "Old WAV file successfully deleted"); }
//     std::cout << "Start reading WAV file... " << std::endl;
    
//     readHeader(file_open,header);
//     printHeader(header);

//     int data_size = getSubchunk2Size(header);       
//     DataType* WAVData = new DataType[data_size]();
//     WAVData = readData(file_open,header);
//     printExampleData(WAVData,150);   // 150 - amount of sampels to print

//     // int data_size2 = getSubchunk2Size(header);       
//     // WAVData = modifyWAVData(WAVData,header ,data_size2);
//     // printExampleData(WAVData,150);
    
//     // Copy from C like pointer array to std::vector
//     std::vector<DataType> wavedata;
//     int i=0;
//     while(*(WAVData+i)) 
//     { 
//         wavedata.push_back(*(WAVData + i)); 
//         i++; 
//     }

//     delete[] WAVData;
    
    // CRYPTOGRAHY 
    std::vector<short int> data = {7};
    auto keys = Cryptography::RsaKeys(7901,7919);
    keys.PrintKeys();
    auto encrypted = Cryptography::rsaEncrypt(data,keys);
    auto decrypted = Cryptography::rsaDecryptAsync(encrypted,keys);
    for(auto x : data) { std::cout << x << " "; }
    std::cout << "\n";
    for(auto x : encrypted) { std::cout << x << " "; }
    std::cout << "\n";
    for(auto x : decrypted) { std::cout << x << " "; }
    std::cout << "\n";

    // END CRYPTOGRAPHY

    // DataType* EncryptedWAVData = new DataType[wavedata.size()]();

    // int j=0;
    // for(const auto data : encrypted)
    // {
    //     *(EncryptedWAVData + j) = data;
    //     j++; 
    // }

    // // free memory
    // wavedata.clear();
    // wavedata.shrink_to_fit();

    // //Save data to wav file
    // if (!file_save)
    //     { std::cerr << "ERR: Cannot find the file\n"; }

    // if (std::is_empty<WAVHeader>::value)
    //     { std::cerr << "ERR: Cannot save file without header\n"; file_save.close(); }
    
    // std::cout << "Start saving WAV file... \n";
    // writeHeader(file_save,header);
    // writeData(file_save,header,EncryptedWAVData);

    // delete[] EncryptedWAVData;

    // return 0;
}

