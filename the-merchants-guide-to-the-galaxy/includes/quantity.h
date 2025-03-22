typedef struct quantity
{
    char *quantity;
    char *roman;
    struct quantity *next;
} quantity;

quantity *createQuantity(quantity **head, char *qu, char *value);
quantity *addQuantity(quantity **head, char *qu, char *unit);
void releaseQuantity(quantity *q);