#ifndef WORDPOD_H
#define WORDPOD_H

#include <functional>

struct wordPod {
    std::string word;
    std::string filepath;
    size_t v_index; 
    int linenumber; 

    bool operator==(const wordPod& wp) const {
        return (this->word       == wp.word
           and this->filepath    == wp.filepath 
           and this->v_index     == wp.v_index
           and this->linenumber  == wp.linenumber);
    }
    size_t operator()(const wordPod& wp) const {
        return (std::hash<std::string>() (wp.word));
    }
};

#endif