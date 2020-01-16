/*************************************************
This work is the property of Christopher Lucinski.
**************************************************/

struct name_basics {
    char * nconst;
    char * primaryName;
};

struct name_array_info {
    int numItems;
    struct name_basics * address;
};

struct name_array_info * get_name(const char * dirPath);
