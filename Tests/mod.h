#ifndef JUAM_MOD_HEADERS
#define JUAM_MOD_HEADERS


char mod_TitleT 
    (sf_render_window * window_main, sf_event * event, sf_input * input);

char mod_GameG 
    (sf_render_window * window_main, sf_event * event, sf_input * input, 
    double * d_score);

char mod_RetryR 
    (sf_render_window * window_main, sf_event * event, sf_input * input,
    double d_score);


#endif
