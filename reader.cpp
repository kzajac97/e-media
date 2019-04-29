#include "reader.hpp"





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

 data_t* readData(std::ifstream& file,WAVHeader& Header)
{

    int data_size=Header.subchunk2Size;
    char* buffer = new char[data_size];
    file.read(buffer,data_size);
    data_t* tmp = reinterpret_cast<data_t*>(buffer);
    file.close();
    return tmp;
}
 /*with some bug
std::vector<data_t> readData(std::ifstream& file,WAVHeader& Header)
{

    int data_size=Header.subchunk2Size;
    char* buffer = new char[data_size];
    file.read(buffer,data_size);
    data_t* tmp = reinterpret_cast<data_t*>(buffer);
    std::vector<data_t> DATA;

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

void writeData(std::ofstream& file,WAVHeader& Header,data_t* WAVData)
{
    int data_size=Header.subchunk2Size;
    char* buffer = reinterpret_cast<char*>(WAVData);
    file.write(buffer, data_size);
}

//function modifi first half part of wav file 
data_t* modifyWAVData(data_t* Data,WAVHeader& wav, int sampels_amount)
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

void printExampleData(data_t* Data, const int sampels_amount)
{
std::cout<<"First "<<sampels_amount<<" sampels :"<<std::endl;
    for(int i=0; i <sampels_amount; i++)
    {
     std::cout<<Data[i]<<" ";   
    } 
}

