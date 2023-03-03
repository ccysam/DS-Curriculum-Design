/*
 * @Author: ccysam
 * @E-Mail: ccysam@hotmail.com
 * @Date: 2022-12-14 17:09:45
 * @LastEditTime: 2022-12-18 14:20:15
 * @Description:
 * @Copyright: Copyright (c) ${now_year} by ccysam, All Rights Reserved.
 */
#pragma once
#ifndef __CSV_READER_H_
#define __CSV_READER_H_

#include <fstream>
#include <vector>
#include <string>
#include <sstream>

#define __CSV__DATA_ std::vector<std::vector<std::string>>

namespace CSVReader
{
    typedef __CSV__DATA_ Table;

    inline Table Read(const char *filename)
    {
        Table data;
        std::ifstream file(filename);
        std::string line;
        while (getline(file, line))
        {
            std::vector<std::string> data_line;
            std::istringstream stream(line);
            std::string unity_str;
            while (getline(stream, unity_str, ','))
            {
                data_line.push_back(unity_str);
            }
            data.push_back(data_line);
        }
        file.close();
        return data;
    }

    inline void Write(const char *filename, Table &data)
    {
        std::ofstream file;
        file.open(filename, std::ios::out);
        for (std::vector<std::string> data_line : data)
        {
            for (std::string unity_str : data_line)
            {
                file << unity_str << ',';
            }
            file << std::endl;
        }
        file.close();
    }
}

#endif
