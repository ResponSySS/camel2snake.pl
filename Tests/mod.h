#ifndef JUAM_MOD_HEADERS
#define JUAM_MOD_HEADERS


char mod_TitleT 
    (sfRenderWindow * windowMain, sfEvent * event, sfInput * input);

char mod_GameG 
    (sfRenderWindow * windowMain, sfEvent * event, sfInput * input, 
    double * d_score);

char mod_RetryR 
    (sfRenderWindow * windowMain, sfEvent * event, sfInput * input,
    double d_score);


#endif
