#include <SFML/Audio.h>
#include <SFML/Graphics.h>
#include <SFML/Graphics/Font.h>
//#include <SFML/System.h>
//#include <SFML/Window.h>

#include "func.h"

inline sf_bool fnGame_IsItTimeToAnimCarlitaSmile 
	(double d_time, double * d_nextAnimTime)
{
	if (d_time > (*d_nextAnimTime))
    {	*(d_nextAnimTime) = d_time + D_ANIM_CARLITA_SMILE_STEP_TIME;
        return sf_true;
    }
	return sf_false;
}

inline sf_bool fnGame_IsItTimeToAnimCarlitaFeet
	(double d_time, double * d_nextAnimTime)
{
	if (d_time > (*d_nextAnimTime))
    {	*(d_nextAnimTime) = d_time + D_ANIM_CARLITA_FEET_STEP_TIME;
        return sf_true;
    }
	return sf_false;
}

inline int fnGame_CarlitaAnimateSmile
    (sf_sprite * spr, sf_int_rect * irect_spr, 
    int * ip_animStep)
{
    (*(ip_animStep))++;
    *(ip_animStep) = *(ip_animStep) % I_CARLITA_SPR_SMILE_ANIM_STEPS_TOTAL;
    
    (*(irect_spr)).Left
        = *(ip_animStep) * I_CARLITA_SPR_WIDTH;
    (*(irect_spr)).Right
        = I_CARLITA_SPR_WIDTH + (*(ip_animStep) * I_CARLITA_SPR_WIDTH);
    
    sfSprite_SetSubRect (spr, *(irect_spr));
    
    return (*(ip_animStep));
}

inline int fnGame_CarlitaAnimateFeet
    (sf_sprite * spr, sf_int_rect * irect_spr, 
    int * ip_animStep)
{
    (*(ip_animStep))++;
    *(ip_animStep) = *(ip_animStep) % I_CARLITA_SPR_FEET_ANIM_STEPS_TOTAL;
    
    (*(irect_spr)).Top
        = *(ip_animStep) * I_CARLITA_SPR_WIDTH;
    (*(irect_spr)).Bottom
        = I_CARLITA_SPR_WIDTH + (*(ip_animStep) * I_CARLITA_SPR_WIDTH);
    
    sfSprite_SetSubRect (spr, *(irect_spr));
    
    return (*(ip_animStep));
}

inline sf_bool fnGame_IsItTimeToAnimJuanDance
	(double d_time, double * d_nextAnimTime)
{
	if (d_time > (*d_nextAnimTime))
    {	*(d_nextAnimTime) = d_time + D_ANIM_JUAN_DANCE_STEP_TIME;
        return sf_true;
    }
	return sf_false;
}

inline int fnGame_JuanAnimateDance
    (sf_sprite * spr, sf_int_rect * irect_spr, 
    int * ip_animStep)
{
    (*(ip_animStep))++;
    *(ip_animStep) = *(ip_animStep) % I_JUAN_SPR_DANCE_ANIM_STEPS_TOTAL;
    
    (*(irect_spr)).Left
        = I_JUAN_SPR_WIDTH + (*(ip_animStep) * I_JUAN_SPR_WIDTH);
    (*(irect_spr)).Right
        = I_JUAN_SPR_WIDTH + I_JUAN_SPR_WIDTH + (*(ip_animStep) * I_JUAN_SPR_WIDTH);
    
    sfSprite_SetSubRect (spr, *(irect_spr));
    
    return (*(ip_animStep));
}

inline void fnGame_JuanDoesNotDance
    (sf_sprite * spr, sf_int_rect * irect_spr)
{
    (*(irect_spr)).Left = 0;
    (*(irect_spr)).Right = I_JUAN_SPR_WIDTH;
    
    sfSprite_SetSubRect (spr, *(irect_spr));
}

inline void fnGame_PeopleLooksDown
    (sf_sprite * spr, sf_int_rect * irect_spr)
{
    (*(irect_spr)).Top      = 0;
    (*(irect_spr)).Bottom   = I_PEOPLE_SPR_WIDTH;
    sfSprite_SetSubRect (spr, *(irect_spr));
}

inline void fnGame_PeopleLooksUp
    (sf_sprite * spr, sf_int_rect * irect_spr)
{
    (*(irect_spr)).Top      = I_PEOPLE_SPR_WIDTH;
    (*(irect_spr)).Bottom   = I_PEOPLE_SPR_WIDTH + I_PEOPLE_SPR_WIDTH;
    sfSprite_SetSubRect (spr, *(irect_spr));
}

#define MAC_UINT8_DEPENDS_ON_F_VAR\
(f)\
    1 + (120 * f)
/* F_JUAN_HEALTH_MAX must 2.f */
inline void fnGame_ArrowPositive 
    (sf_sprite * spr, float f_health)
{
    sfSprite_SetColor
        (spr, sfColor_FromRGB (96, (MAC_UINT8_DEPENDS_ON_F_VAR (f_health)), 63));
    sfSprite_FlipY      (spr, sf_true);
}

/* F_JUAN_HEALTH_MAX must 2.f */
inline void fnGame_ArrowNegative
    (sf_sprite * spr, float f_health)
{
    sfSprite_SetColor
        (spr, sfColor_FromRGB ((MAC_UINT8_DEPENDS_ON_F_VAR (f_health)), 32, 32));
    sfSprite_FlipY      (spr, sf_false);
}
