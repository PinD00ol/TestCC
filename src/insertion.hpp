#include <queue>
#include <fstream>
#include "event.hpp"

std::queue<Event> inputEvents(std::ifstream& file,unsigned int& tablesCount, unsigned int& rate, std::string& timeStart, std::string& timeEnd);
//проверка данных из текстового файла