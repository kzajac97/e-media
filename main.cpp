#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <memory>
#include <inttypes.h>
#include <utility>
#include <type_traits>
#include <cmath>


using DataType = int16_t;

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
    uint32_t subchunk2Size;             //wav data size -
                            // NumSamples * NumChannels * BitsPerSample/8
};

void readHeader(std::ifstream& file,WAVHeader& Header)
{
    int sampel_amount = sizeof(WAVHeader);
    char* buffer = new char[sampel_amount];
    file.read(buffer, sampel_amount);
    WAVHeader* wav = reinterpret_cast<WAVHeader*>(buffer);
    Header=*wav;     
}

int getSubchunk2Size(WAVHeader& Header)
{
    return Header.subchunk2Size;
}

 DataType* readData(std::ifstream& file,WAVHeader& Header)
{

    int data_size=Header.subchunk2Size;
    char* buffer = new char[data_size];
    file.read(buffer,data_size);
    DataType* tmp = reinterpret_cast<DataType*>(buffer);
    file.close();
    return tmp;
}
 /*with some bug
std::vector<DataType> readData(std::ifstream& file,WAVHeader& Header)
{

    int data_size=Header.subchunk2Size;
    char* buffer = new char[data_size];
    file.read(buffer,data_size);
    DataType* tmp = reinterpret_cast<DataType*>(buffer);
    std::vector<DataType> DATA;

    for(int i=0; i < data_size; i++)
    {
        DATA.push_back(tmp[i]);
    }

    return DATA;
}
*/
void writeHeader(std::ofstream& file,WAVHeader& wav)
{
    WAVHeader header = wav;
    char* buffer = reinterpret_cast<char*>(&header);
    file.write(buffer, sizeof(WAVHeader));
}

void writeData(std::ofstream& file,WAVHeader& Header,DataType* WAVData)
{
    int data_size=Header.subchunk2Size;
    char* buffer = reinterpret_cast<char*>(WAVData);
    file.write(buffer, data_size);
}

//function modifi first half part of wav file 
DataType* modifyWAVData(DataType* Data,WAVHeader& wav, int sampels_amount)
{
    if(wav.numChannels==2)
    {
        for (int i = 0; i<(sampels_amount/4); i++)
        {
            if(i%2==0)
                Data[i]=200+(i%103)*2;
            else
                Data[i]=-330+((i+50)%111)*1.4;
        } 
    }
    else
    {
        for (int i = 0; i<sampels_amount/4; i++)
        {
            Data[i]=1000;
        }
    }
return Data;
}

void printHeader(const WAVHeader& Header)
{
    using namespace std;
    cout<<"Header of *.wav file :"<<endl;
    cout<<"\t\t\tChunkID           "<<Header.chunkID[0]<<
    Header.chunkID[1]<<Header.chunkID[2]<<Header.chunkID[3]<<endl;
    cout<<"\t\t\tChunkSize         "<<Header.chunkSize<<endl;
    cout<<"\t\t\tFormat            "<<Header.format[0]<<
    Header.format[1]<<Header.format[2]<<Header.format[3]<<endl;
    cout<<"\t\t\tSubchunk1ID       "<<Header.subchunk1ID[0]<<
    Header.subchunk1ID[1]<<Header.subchunk1ID[2]<<Header.subchunk1ID[3]<<endl;
    cout<<"\t\t\tSubchunk1Size     "<<Header.subchunk1Size<<endl;  
    cout<<"\t\t\tAudioFormat       "<<Header.audioFormat<<endl;
    cout<<"\t\t\tNumChannels       "<<Header.numChannels<<endl;
    cout<<"\t\t\tSampleRate        "<<Header.sampleRate<<endl;
    cout<<"\t\t\tByteRate          "<<Header.byteRate<<endl;
    cout<<"\t\t\tBlock_align       "<<Header.block_align<<endl;
    cout<<"\t\t\tBits_per_sample   "<<Header.bits_per_sample<<endl;
    cout<<"\t\t\tSubchunk2ID       "<<Header.subchunk2ID[0]<<
    Header.subchunk2ID[1]<<Header.subchunk2ID[2]<<Header.subchunk2ID[3]<<endl; 
    cout<<"\t\t\tSubchunk2Size     "<<Header.subchunk2Size<<endl;   
}

void printExampleData(DataType* Data, const int sampels_amount)
{
std::cout<<"First "<<sampels_amount<<" sampels :"<<std::endl;
    for(int i=0; i <sampels_amount; i++)
    {
     std::cout<<Data[i]<<" ";   
    } 
}



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

