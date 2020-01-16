/*************************************************
This work is the property of Christopher Lucinski.
**************************************************/

struct title_principals {
    char * tconst;
    char * nconst;
    char * characters;
};

struct principals_array_info {
    int numItems;
    struct title_principals * address;
};

struct principals_array_info * get_principals(const char * dirPath);
