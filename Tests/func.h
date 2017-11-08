#ifndef JUAN_FUNC_HEADERS
#define JUAN_FUNC_HEADERS


#define     D_ANIM_CARLITA_FEET_STEP_TIME           0.5
#define     D_ANIM_CARLITA_SMILE_STEP_TIME          0.2
#define     D_ANIM_JUAN_DANCE_STEP_TIME             0.3

#define     I_CARLITA_SPR_WIDTH                     300
#define     I_JUAN_SPR_WIDTH                        300
#define     I_PEOPLE_SPR_WIDTH                      300

#define     I_CARLITA_SPR_SMILE_ANIM_STEPS_TOTAL    7
#define     I_CARLITA_SPR_FEET_ANIM_STEPS_TOTAL     2
#define     I_JUAN_SPR_DANCE_ANIM_STEPS_TOTAL       2


inline sf_bool fnGame_IsItTimeToAnimCarlitaFeet
    (double d_time, double * d_nextAnimTime);

inline sf_bool fnGame_IsItTimeToAnimCarlitaSmile
    (double d_time, double * d_nextAnimTime);

inline int fnGame_CarlitaAnimateSmile
    (sf_sprite * spr, sf_int_rect * irect_spr, 
    int * ip_animStep);

inline int fnGame_CarlitaAnimateFeet
    (sf_sprite * spr, sf_int_rect * irect_spr, 
    int * ip_animStep);

inline sf_bool fnGame_IsItTimeToAnimJuanDance
    (double d_time, double * d_nextAnimTime);

inline int fnGame_JuanAnimateDance
    (sf_sprite * spr, sf_int_rect * irect_spr, 
    int * ip_animStep);

inline void fnGame_JuanDoesNotDance
    (sf_sprite * spr, sf_int_rect * irect_spr);

inline void fnGame_PeopleLooksDown
    (sf_sprite * spr, sf_int_rect * irect_spr);

inline void fnGame_PeopleLooksUp
    (sf_sprite * spr, sf_int_rect * irect_spr);

inline void fnGame_ArrowPositive 
    (sf_sprite * spr, float f_health);
    
inline void fnGame_ArrowNegative
    (sf_sprite * spr, float f_health);


#endif
