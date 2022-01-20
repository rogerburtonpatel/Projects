#ifndef WORDPOD_H
#define WORDPOD_H

#include <functional>

struct wordPod {
    std::string word;
    std::string filepath;
    size_t index; 
    int linenumber; 
    wordPod(std::string w, std::string fp, size_t i, int ln) {
        word       = w;
        filepath   = fp;
        index      = i;
        linenumber = ln;
    }
    bool operator==(const wordPod& wp) const {
        return (this->word       == wp.word
           and this->filepath    == wp.filepath 
           and this->index       == wp.index
           and this->linenumber  == wp.linenumber);
    }
    size_t operator()(const wordPod& wp) const {
        return (std::hash<std::string>() (wp.word)     ^ 
                std::hash<std::string>() (wp.filepath) ^ 
                std::hash<size_t>() (wp.index)         ^ 
                std::hash<int>() (wp.linenumber));
    }
};

#endif