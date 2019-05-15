//
// Created by jiang on 19-3-21.
//

#include "util.h"
#include <ctime>
using std::string;

std::string Get_Current_Date()
{
    time_t nowtime;
    nowtime = time(NULL); //获取日历时间
    char tmp[64];
    strftime(tmp, sizeof(tmp), "%Y-%m-%d %H:%M:%S", localtime(&nowtime));
    return tmp;
}

std::string Get_File_Md5(std::string filePath)
{
    //Start opening your file
    std::ifstream inBigArrayfile;
    inBigArrayfile.open(filePath, std::ios::binary | std::ios::in);

    //Find length of file
    inBigArrayfile.seekg(0, std::ios::end);
    long Length = inBigArrayfile.tellg();
    inBigArrayfile.seekg(0, std::ios::beg);

    //read in the data from your file
    char * InFileData = new char[Length];
    inBigArrayfile.read(InFileData, Length);

    //Calculate MD5 hash
    std::string Temp = md5(InFileData, Length);

    inBigArrayfile.close();
    //Clean up
    delete[] InFileData;

    return Temp;
}

string&   replace_all(string&   str,const   string&   old_value,const   string&   new_value)
{
    while(true)   {
        string::size_type   pos(0);
        if(   (pos=str.find(old_value))!=string::npos   )
            str.replace(pos,old_value.length(),new_value);
        else   break;
    }
    return   str;
}