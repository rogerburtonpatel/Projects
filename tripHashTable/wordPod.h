// TODO: header and comments 

struct wordPod {
    std::string filepath;
    size_t index; 
    int linenumber; 
    wordPod(std::string fp, size_t i, int ln) {
        filepath   = fp;
        index = i;
        linenumber = ln;
    }
};



