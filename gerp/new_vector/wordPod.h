#ifndef WORDPOD_H
#define WORDPOD_H

#include <functional>
#include "stringProcessing.h"

struct wordPod {
    std::string word;
    size_t fileindex;
    size_t lineindex; 
    size_t linenumber; 

    bool operator==(const wordPod& wp) const {
        return (this->word       == wp.word
           and this->fileindex   == wp.fileindex 
           and this->lineindex   == wp.lineindex
           and this->linenumber  == wp.linenumber);
    }
    size_t operator()(const wordPod& wp) const {
        return (std::hash<std::string>() (wp.word)) ^ 
               (std::hash<size_t>() (wp.fileindex)) ^
               (std::hash<size_t>() (wp.lineindex)) ^
              (std::hash<size_t>() (wp.linenumber));
    }
};

#endif