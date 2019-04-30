#ifndef MENU_HPP
#define MENU_HPP

#pragma once

#include "rsa.hpp"
#include "reader.hpp"

void displayManu(void);
void Menu(void);
data_t* vec2arr(std::vector<data_t> & data);
std::vector<data_t> arr2vec(data_t* data);
void loadfile(std::ifstream file_open,WAVHeader & header, data_t* WAVData);
void savefile(std::ofstream file_save, WAVHeader header, data_t* WAVData);

#endif