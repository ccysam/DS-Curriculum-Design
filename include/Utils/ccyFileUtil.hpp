/*
 * @Author: ccysam
 * @E-Mail: ccysam@hotmail.com
 * @Date: 2022-11-26 12:37:04
 * @LastEditTime: 2022-11-27 09:01:49
 * @Description:
 * @Copyright: Copyright (c) 2022 by ccysam, All Rights Reserved.
 */
#pragma once
#ifndef __CCYSAM_FILE_UTILS__
#define __CCYSAM_FILE_UTILS__

// Includes
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

// Marcos

#define cFU_TYPE_FILE 0x0001
#define cFU_TYPE_DIR 0x0002

// Declarations

// namespace
// {

//     // Interface

//     struct FileUtilObject
//     {

//         // Variables

//         std::fstream &file;
//         bool hasContents;

//         // Constructors and Destructors

//         FileUtilObject()
//         {
//             hasContents = false;
//         }

//         FileUtilObject(const char *filename)
//         {
//             file.open(filename, std::ios::in | std::ios::out | std::ios::app);
//             if (!file.is_open())
//             {
//                 throw std::runtime_error("Failed to open file!");
//             }
//             hasContents = true;
//         }

//         ~FileUtilObject()
//         {
//             if (file.is_open())
//                 file.close();
//         }

//         // Virtual functions

//         virtual bool empty() = 0;
//         virtual const char *toString() = 0;
//         virtual const char *getName() = 0;
//         virtual const char *getExtension() = 0;
//         virtual const char *readAllLine() = 0;
//     };
// } // Anonymous namespace

namespace cFU
{
    // typedef struct File : FileUtilObject
    // {
    //     File() : FileUtilObject(){};
    //     File(const char *filename) : FileUtilObject(filename){};
    //     ~File(){};

    //     virtual bool empty() override
    //     {
    //         char c;
    //         file >> c;
    //         if (file.eof())
    //             return true;
    //         else
    //             return false;
    //     }

    //     virtual const char *toString() override
    //     {
    //         return "String";
    //     }

    //     virtual const char *getName() override
    //     {
    //         return "Name";
    //     }

    //     virtual const char *getExtension() override
    //     {
    //         return "Extension";
    //     }

    //     virtual const char *readAllLine() override
    //     {
    //         std::stringstream buffer;
    //         buffer << file.rdbuf();
    //         return buffer.str().c_str();
    //     }
    // } File;
    
    static const char *readAllLine(const char *filename)
    {
        std::ifstream file;
        file.open(filename, std::ios::in);
        if (!file)
        {
            throw std::runtime_error("Failed to open file ");
        }
        std::stringstream buffer;
        buffer << file.rdbuf();
        return buffer.str().c_str();
    }
} // namespace cFU

#endif