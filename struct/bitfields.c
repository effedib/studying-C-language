#include <stdio.h>

typedef struct
{
    unsigned int low_pass_vcf : 1;
    unsigned int filter_coupler : 1;
    unsigned int reverb : 1;
    unsigned int sequential : 1;

} synth;

int main()
{
    synth s = {1, 0, 1, 0};
    printf("%i", s.filter_coupler);
    printf("%i", s.low_pass_vcf);
    printf("%i", s.reverb);
    printf("%i", s.sequential);

    return 0;
}