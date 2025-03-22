typedef struct tokenArray
{
    char **tokens;
    int count;
} tokenArray;

tokenArray *tokenize(char *input);
void releaseTokens(tokenArray *t);
int split(tokenArray *tokens, tokenArray **prefix, tokenArray **suffix);
