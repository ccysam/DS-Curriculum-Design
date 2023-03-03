/*
 * @Author: ccysam
 * @E-Mail: ccysam@hotmail.com
 * @Date: 2022-11-27 09:10:46
 * @LastEditTime: 2022-11-27 09:23:23
 * @Description:
 * @Copyright: Copyright (c) ${now_year} by ccysam, All Rights Reserved.
 */
#include <iostream>
#include <fstream>
#include <streambuf>
#include <string>

using namespace std;

const char *readAllLine(const char *filename)
{
    ifstream file;
    file.open(filename, ios::in);
    if (!file)
    {
        cout << "Error" << endl;
    }
    else
    {
        cout << "Success" << endl;
    }
    return string((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>()).c_str();
}

int main(int argc, char **argv)
{
    cout << readAllLine("res\\1.vsh") << endl;
    return 0;
}