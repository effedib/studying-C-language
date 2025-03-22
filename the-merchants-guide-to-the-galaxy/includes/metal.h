typedef struct metal
{
    char *metal;
    float cost;
    struct metal *next;
} metal;

metal *createMetal(metal **head, char *met, float cost);
metal *addMetal(metal **head, char *met, float cost);
void releaseMetal(metal *m);