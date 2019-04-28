#include "reader.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <memory>
#include <inttypes.h>
#include <utility>
#include <type_traits>





int main(void)
{
//__________________WAV Files________________________________________

    //std::string fileName_open = "ptak.wav";
    std::string fileName_open = "timer.wav"; 
    //std::string fileName_open = "melodia.wav";
//___________________________________________________________________

    std::string fileName_save= "plik_przetworzony.wav";
    std::ifstream file_open(fileName_open.c_str(), std::ifstream::binary);
    std::ofstream file_save(fileName_save.c_str(), std::ofstream::binary);
    WAVHeader header;

    /*
    std::vector<DataType> WAVData_vector;
    std::cout<<"Vectro max size : "<<" "<<WAVData_vector.max_size() <<std::endl;
    */

    std::cout<<"Program E-media"<<std::endl;

    int a;
    std::cin>>a;

    if (!file_open)
        {
            std::cerr << "ERR: Cannot find the file" << std::endl;
            return 1;
        }
    if( remove("plik_przetworzony.wav") != 0)
        perror( "Error deleting old WAV file" );
    else
        puts( "Old WAV file successfully deleted" );
    std::cout<<"Start reading WAV file... "<<std::endl;
    readHeader(file_open,header);
    printHeader(header);
    int data_size=getSubchunk2Size(header);       
    DataType* WAVData = new DataType[data_size]();
    WAVData = readData(file_open,header);
    printExampleData(WAVData,150);   // 150 - amount of sampels to print

    int data_size2=getSubchunk2Size(header);       
    WAVData = modifyWAVData(WAVData,header ,data_size2);
    printExampleData(WAVData,150);
    //Save data to wav file
        if (!file_save)
        {
            std::cerr << "ERR: Cannot find the file" << std::endl;
            return 1;
        }

        if (std::is_empty<WAVHeader>::value)
        {
            std::cerr << "ERR: Cannot save file without header" << std::endl;
            file_save.close();
            return 1;
        }
    std::cout<<"Start saving WAV file... "<<std::endl;
    writeHeader(file_save,header);
    writeData(file_save,header,WAVData);

    delete[] WAVData;

    return 0;
}

