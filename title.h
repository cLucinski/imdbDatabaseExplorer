/*************************************************
This work is the property of Christopher Lucinski.
**************************************************/

struct title_basics {
    char *tconst;
    char *primaryTitle;
};

struct title_array_info {
    int numItems;
    struct title_basics * address;
};

struct title_array_info * get_title(const char * dirPath);
