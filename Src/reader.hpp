#ifndef READER_HPP
#define READER_HPP

#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <memory>
#include <inttypes.h>
#include <utility>
#include <type_traits>

using data_t = uint16_t;

// more about wave struct : http://soundfile.sapp.org/doc/WaveFormat/
struct WAVHeader 
{
    unsigned char chunkID[4];           //RIFF 
    uint32_t chunkSize;                 //overall size 
    unsigned char format[4];            //WAVE
    unsigned char subchunk1ID[4];       //fmt
    uint32_t subchunk1Size;             //sampel_amount of fmt
    uint16_t audioFormat;               //format_type
    uint16_t numChannels;
    uint32_t sampleRate;                //sampling frequency
    uint32_t byteRate;
    uint16_t block_align;
    uint16_t bits_per_sample;
    unsigned char subchunk2ID[4];       //data
    uint32_t subchunk2Size;             //wav data size - NumSamples * NumChannels * BitsPerSample/8
};

void readHeader(std::ifstream& file,WAVHeader& Header);
int getSubchunk2Size(WAVHeader& Header);
data_t* readData(std::ifstream& file,WAVHeader& Header);
//std::vector<data_t> readData(std::ifstream& file,WAVHeader& Header) //with bugs
void writeHeader(std::ofstream& file,WAVHeader& wav);
void writeData(std::ofstream& file,WAVHeader& Header,data_t* WAVData);
data_t* modifyWAVData(data_t* Data,WAVHeader& wav, int sampels_amount);
void printHeader(const WAVHeader& Header);
void printExampleData(data_t* Data, const int sampels_amount);

#endif