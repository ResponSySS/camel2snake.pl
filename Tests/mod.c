#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "libcsfml-sys.h"

#include "func.h"


char mod_TitleT 
    (sfRenderWindow * windowMain, sfEvent * event, sfInput * input)
{
    puts ("Title module, Juan!");
    
    /* Usual variables */
    char c_running = sfTrue;
    const unsigned int      cui_renderWindowWidth     = sfRenderWindow_GetWidth (windowMain),
                            cui_renderWindowHeight    = sfRenderWindow_GetHeight (windowMain);
    
    /* MUSICA AMIGO!!! */
    sfMusic * musica
        = sfMusic_CreateFromFile ("data/Dance of the Gypsy.oga");
    sfMusic_SetLoop (musica, sfTrue);
    sfMusic_Play (musica);
    
    
    /* Intro text */
    sfFont * font = NULL;
    sfString * str_intro 
        = sfSyS_sfStringDeclare
            (font, "data/Isabella.ttf", 63,
            NULL, "Juan impression\nJuan girl\nJuan Carlos",
            sfColor_FromRGBA (255,255,255,255), 
            sfTrue, 0.8f, 0.8f);
    sfString_SetPosition (str_intro, 
        cui_renderWindowWidth / 2.f, cui_renderWindowHeight / 2.f);
    
    /* Title text */
    sfString * str_title 
        = sfSyS_sfStringDeclare
            (font, "data/Isabella.ttf", 255,
            NULL, "Juan",
            sfColor_FromRGBA (255,255,255,255), 
            sfTrue, 0.f, 0.f);
    sfString_SetPosition (str_title, 
        cui_renderWindowWidth / 2.f, cui_renderWindowHeight / 2.f);
    char c_titleDisplay = sfFalse;
    
    /* Noise layer */
    sfImage * img = NULL;
    sfSprite * spr_noise 
        = sfSyS_sfSpriteDeclare 
            (img, "data/noise.png", sfTrue, 
            sfColor_FromRGBA (255,255,255, 196), sfFalse, 
            cui_renderWindowWidth, cui_renderWindowHeight);
    sfSprite_SetBlendMode (spr_noise, sfBlendAdd);
    
    while (c_running)
    {
        while (sfRenderWindow_GetEvent (windowMain, event)
            && c_titleDisplay)
        {   if ((*event).Type == sfEvtKeyReleased)
                c_running = sfFalse;
        }
        
        
        sfString_Scale (str_intro, 1.001f, 1.001f);
        
        if (sfString_GetScaleX (str_intro) > 1.1f)
        {   c_titleDisplay = sfTrue;
        }
        
        
        ///* Drawing *///
        
        if (c_titleDisplay == sfTrue)
        {   sfRenderWindow_Clear (windowMain, sfColor_FromRGBA (164,32,32, 255));
            sfRenderWindow_DrawSprite (windowMain, spr_noise);
            sfRenderWindow_DrawString (windowMain, str_title);
        }
        else
        {   sfRenderWindow_Clear (windowMain, sfColor_FromRGBA (163,98,33, 255));
            sfRenderWindow_DrawSprite (windowMain, spr_noise);
            sfRenderWindow_DrawString (windowMain, str_intro);
        }
        sfRenderWindow_Display (windowMain);
    }
    
    // Empty sfEvent buffer before next module
    while (sfRenderWindow_GetEvent (windowMain, event))     {}
    
    sfMusic_Stop (musica);
    
    /* Cleanup resources */
    sfFont_Destroy      (font);
    sfImage_Destroy     (img);
    sfMusic_Destroy     (musica);
    sfFont_Destroy      (sfString_GetFont (str_intro));
    sfString_Destroy    (str_intro);
    sfFont_Destroy      (sfString_GetFont (str_title));
    sfString_Destroy    (str_title);
    sfImage_Destroy     (sfSprite_GetImage (spr_noise));
    sfSprite_Destroy    (spr_noise);
    
    return 'G';
}


#define     I_FRAMERATE                         50

#define     F_SIGHT_HEIGHT                      300.f
#define     F_SIGHT_WIDTH                       1900.f

#undef      I_CARLITA_SPR_WIDTH                 
#undef      I_JUAN_SPR_WIDTH
#undef      I_PEOPLE_SPR_WIDTH                 

#define     I_CARLITA_SPR_WIDTH                 300
#define     I_JUAN_SPR_WIDTH                    300
#define     I_PEOPLE_SPR_WIDTH                  300

#define     F_JUAN_HEALTH_MAX                   2.f

#define     F_CARLITA_SIGHT_LIM_MIN             70.f
#define     F_CARLITA_SIGHT_LIM_MAX             110.f
#define     F_CARLITA_SIGHT_ROTAT_OFFSET_MIN    0.05f
#define     F_CARLITA_SIGHT_ROTAT_OFFSET_MAX    0.5f
#define     F_PEOPLE_SIGHT_ROTAT_OFFSET_MIN     0.03f
#define     F_PEOPLE_SIGHT_ROTAT_OFFSET_MAX     0.6f

#define     I_NB_PEOPLE                         7

#define     I_NB_MUSIC_LAYERS                   2

char mod_GameG 
    (sfRenderWindow * windowMain, sfEvent * event, sfInput * input, double * d_score)
{
    puts ("Let's play, Juan!");
    
    /* Usual variables */
    char c_running  = sfTrue;
    char c_nextMod  = 'R';
    const unsigned int      cui_renderWindowWidth     = sfRenderWindow_GetWidth (windowMain),
                            cui_renderWindowHeight    = sfRenderWindow_GetHeight (windowMain);
    int i;
    
    sfImage * img = NULL;
    
    /* Playground */
    sfSprite * spr_playground 
        = sfSyS_sfSpriteDeclare 
            (img, "data/playground.jpg", sfTrue, 
            sfWhite, sfFalse,
            cui_renderWindowWidth, cui_renderWindowHeight);
    sfSprite * spr_playgroundMask 
        = sfSyS_sfSpriteDeclare 
            (img, "data/playground.mask.png", sfTrue, 
            sfWhite, sfFalse, 
            cui_renderWindowWidth, cui_renderWindowHeight);
    
    /* Juan */
    sfSprite * spr_JuanCarlos
        = sfSyS_sfSpriteDeclare 
            (img, "data/Juan.png", sfTrue, 
            sfWhite, sfFalse, 0.f, 0.f);
    sfSprite_SetPosition (spr_JuanCarlos, 
        cui_renderWindowWidth / 2.f, cui_renderWindowHeight / 2.f);
    float f_JuanPositionXY [2] 
        = {sfSprite_GetX (spr_JuanCarlos), 
        sfSprite_GetY (spr_JuanCarlos)};
    char c_JuanDancesNot    = sfFalse;
    char c_JuanIsSoShameful = sfFalse;
    float f_JuanHealth      = 2.f;
    sfIntRect irect_JuanCarlos;
    irect_JuanCarlos.Top    = 0;
    irect_JuanCarlos.Left   = 0;
    irect_JuanCarlos.Bottom = I_JUAN_SPR_WIDTH;
    irect_JuanCarlos.Right  = I_JUAN_SPR_WIDTH;
    sfSprite_SetCenter (spr_JuanCarlos, 
        I_JUAN_SPR_WIDTH / 2.f, I_JUAN_SPR_WIDTH / 2.f);
    sfSprite_SetSubRect (spr_JuanCarlos, irect_JuanCarlos);
    // Anim vars
    int     i_JuanDanceAnimStep             = 0;
    double  d_JuanDanceAnimStep             = 0.0;
    
    //* Carlita *//
    sfSprite * spr_Carlita
        = sfSyS_sfSpriteDeclare 
            (img, "data/Carlita.png", sfTrue, 
            sfWhite, sfFalse, 0.f, 0.f);
    sfSprite_SetPosition (spr_Carlita, 
        cui_renderWindowWidth / 2.f, cui_renderWindowHeight * .12f);
    sfIntRect irect_CarlitaSpr;
    irect_CarlitaSpr.Top 		= 0;
    irect_CarlitaSpr.Left 	    = 0;
    irect_CarlitaSpr.Bottom 	= I_CARLITA_SPR_WIDTH;
    irect_CarlitaSpr.Right 	    = I_CARLITA_SPR_WIDTH;
    sfSprite_SetCenter (spr_Carlita, 
        I_CARLITA_SPR_WIDTH / 2.f, I_CARLITA_SPR_WIDTH / 2.f);
    sfSprite_SetSubRect (spr_Carlita, irect_CarlitaSpr);
    // Anim vars
    int     i_CarlitaSmileAnimStep          = 0;
    int     i_CarlitaFeetAnimStep           = 0;
    double  d_CarlitaAnimFeetStepTime       = 0.0;
    double  d_CarlitaAnimSmileStepTime      = 0.0;
    
    /* People */
    sfSprite * * sprpX_people
        = malloc (I_NB_PEOPLE *  sizeof (sfSprite *));
    for (i = 0; i < I_NB_PEOPLE; i++)
    {   *(sprpX_people + i)
            = sfSyS_sfSpriteDeclare 
                (img, "data/people.png", sfTrue, 
                sfWhite, sfFalse, 0.f, 0.f);
        sfSprite_SetCenter (*(sprpX_people + i),
            I_PEOPLE_SPR_WIDTH / 2.f, I_PEOPLE_SPR_WIDTH * .15f);
        sfSprite_SetX (*(sprpX_people + i), 
            sfRandom_Float (cui_renderWindowWidth * .1f, cui_renderWindowWidth * .4f));
        if (sfRandom_Int (0,1))
        {   sfSprite_SetX (*(sprpX_people + i), 
                sfRandom_Float (cui_renderWindowWidth * .6f, cui_renderWindowWidth * .9f));
        }
        sfSprite_SetY (*(sprpX_people + i), 
            sfRandom_Float (cui_renderWindowHeight * .1f, cui_renderWindowHeight * .4f));
        if (sfRandom_Int (0,1))
        {   sfSprite_SetY (*(sprpX_people + i), 
                sfRandom_Float (cui_renderWindowHeight * .6f, cui_renderWindowHeight * .9f));
        }
        printf ("Debug: People %d position: %.0f %.0f\n", i,
            sfSprite_GetX (*(sprpX_people + i)), sfSprite_GetY (*(sprpX_people + i)));
    }
    sfIntRect irect_people [I_NB_PEOPLE];
    for (i = 0; i < I_NB_PEOPLE; i++)
    {   irect_people [i] . Top     = 0;
        irect_people [i] . Left    = 0;
        irect_people [i] . Bottom  = I_PEOPLE_SPR_WIDTH;
        irect_people [i] . Right   = I_PEOPLE_SPR_WIDTH;
        sfSprite_SetSubRect (*(sprpX_people + i), irect_people [i]);
    }
    
    
    //* Sights *//
    /* Carlita */
    img = sfImage_CreateFromFile ("data/sight1600.png");
    sfSprite * spr_CarlitaSight 
        = sfSyS_sfSpriteDeclare 
            (img, NULL, sfTrue, 
            sfColor_FromRGBA (163,33,98, 64), 
            sfTrue, 0.f, 0.f);
    sfSprite_SetCenter (spr_CarlitaSight, 
        F_SIGHT_WIDTH, F_SIGHT_HEIGHT / 2.f);
    sfSprite_SetPosition (spr_CarlitaSight, 
        sfSprite_GetX (spr_Carlita), cui_renderWindowHeight * .05f);
    float f_CarlitaSightRotatOffset     = sfRandom_Float (F_CARLITA_SIGHT_ROTAT_OFFSET_MIN, F_CARLITA_SIGHT_ROTAT_OFFSET_MAX);
    if (sfRandom_Int (0, 1))            f_CarlitaSightRotatOffset *= -1;
    char c_CarlitaLooksElsewhere        = sfTrue;
    char c_CarlitaLooksAtJuan           = sfFalse;
    float f_CarlitaSightRotat           = sfRandom_Float (F_CARLITA_SIGHT_LIM_MIN, F_CARLITA_SIGHT_LIM_MAX);
    while ((f_CarlitaSightRotat > 80.f)   &&  (f_CarlitaSightRotat < 100.f))
    {   f_CarlitaSightRotat             = sfRandom_Float (F_CARLITA_SIGHT_LIM_MIN, F_CARLITA_SIGHT_LIM_MAX);
    }
    sfSprite_SetRotation (spr_CarlitaSight, f_CarlitaSightRotat);
    /* People */
    sfSprite * * sprpX_peopleSight
        = malloc (I_NB_PEOPLE *  sizeof (sfSprite *));
    for (i = 0; i < I_NB_PEOPLE; i++)
    {   *(sprpX_peopleSight + i)
            = sfSyS_sfSpriteDeclare 
                (img, NULL, sfTrue, 
                sfColor_FromRGBA (255,255,255, 64), 
                sfTrue, 0.f, 0.f);
        sfSprite_SetCenter (*(sprpX_peopleSight + i), 
            F_SIGHT_WIDTH, F_SIGHT_HEIGHT / 2.f);
        sfSprite_SetPosition ( *(sprpX_peopleSight + i), 
            sfSprite_GetX (*(sprpX_people + i)), sfSprite_GetY (*(sprpX_people + i)) );
        sfSprite_SetRotation 
            (*(sprpX_peopleSight + i), sfRandom_Float (1.f, 359.f));
    }
    char    ca_peopleLooksElsewhere         [I_NB_PEOPLE];
    float   fa_peopleSightRotatOffset       [I_NB_PEOPLE];
    for (i = 0; i < I_NB_PEOPLE; i++)
    {   ca_peopleLooksElsewhere     [i] =         sfFalse;
        fa_peopleSightRotatOffset   [i] =         0.f;
    }
    
    /* Rose */
    sfSprite * spr_rose
        = sfSyS_sfSpriteDeclare
            (img, "data/rose.png", sfTrue,
            sfWhite, 
            sfTrue, 0.f, 0.f);
    sfSprite_SetPosition (spr_rose,
        sfRandom_Float (.333f * cui_renderWindowWidth, cui_renderWindowWidth * .666f), 
        - ((float) cui_renderWindowHeight));
    char c_roseFalls = sfFalse;
    
    /* Arrow */
    sfSprite * spr_arrow
        = sfSyS_sfSpriteDeclare
            (img, "data/arrow.png", sfTrue,
            sfColor_FromRGB (96,200,63), 
            sfFalse, 0.f, 0.f);
    sfSprite_SetPosition (spr_arrow,
        cui_renderWindowWidth * .0333f, cui_renderWindowHeight * .0333f);
    sfSprite_FlipY (spr_arrow, sfTrue);
    // 0 is stable situation, 1 is good situation, -1 is bad situation
    char c_arrowState = 0;
    
    
    /* Intro text */
    sfFont * font = NULL;
    sfString * str_notice
        = sfSyS_sfStringDeclare
            (font, "data/Isabella.ttf", 64,
            NULL, "Hold spacebar not to dance!",
            sfColor_FromRGBA (255,255,255,127), 
            sfTrue,
            0.f, 0.f);
    sfString_SetPosition (str_notice, 
        cui_renderWindowWidth / 2.f, cui_renderWindowHeight * .8f);
    
    /* Fader */
    sfShape * shp_fader
        = sfSyS_sfShapeRectOrLineDeclare
            ('r',
            0.f, 0.f, cui_renderWindowWidth, cui_renderWindowHeight,
            0.f, sfColor_FromRGBA (0,0,0, 127),
            0.f, sfGreen,
            sfTrue, sfFalse,
            sfFalse, 0.f, 0.f);
    
    //* Music *//
    /* Lost game */
    sfMusic * mus_gameLost
        = sfMusic_CreateFromFile ("data/DotG - out of tune sound effect.oga");
    /* Background theme */
    sfMusic * * musp2 = NULL;
    musp2 = malloc (I_NB_MUSIC_LAYERS * sizeof (sfMusic *));
    for (i = 0; i < I_NB_MUSIC_LAYERS; i++)
    {   *(musp2 + i) = NULL;
    }
    if (sfRandom_Int (0, 1))
    {   puts ("Debug: Choosen music: La Madeline au Truffe.");
        *(musp2 + 0)
            = sfMusic_CreateFromFile ("data/La Madeline au Truffe 1.oga");
        *(musp2 + 1)
            = sfMusic_CreateFromFile ("data/La Madeline au Truffe 1.oga");
    }
    else
    {   puts ("Debug: Choosen music: Fuego.");
        *(musp2 + 0)
            = sfMusic_CreateFromFile ("data/Fuego 1.oga");
        *(musp2 + 1)
            = sfMusic_CreateFromFile ("data/Fuego 2.oga");
    }
    float f_mus1Vol = 5.f;
    sfMusic_SetVolume (*(musp2 + 0), 4.f * f_mus1Vol);
    sfMusic_SetVolume (*(musp2 + 1), f_mus1Vol);
    for (i = 0; i < I_NB_MUSIC_LAYERS; i++)
    {   sfMusic_SetLoop (*(musp2 + i), sfTrue);
    }
    for (i = 0; i < I_NB_MUSIC_LAYERS; i++)
    {   sfMusic_Play (*(musp2 + i));
    }
    
    /* Score var */
    * d_score                   = 0.0;
    
    /* Clocks */
    sfClock * clock             = sfClock_Create ();
    
    /* Others */
    char c_state                = 0;
    
    
    sfRenderWindow_SetFramerateLimit (windowMain, I_FRAMERATE);
    
    ////////////////////////////////////////////////////////////////////
    // MAIN LOOP ///////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////
    while (c_running)
    {
        while (sfRenderWindow_GetEvent (windowMain, event))
        {   if (c_state == 0
                && (*event).Type == sfEvtKeyPressed)
            {   c_state = 1;
            }
            else if ((*event).Type == sfEvtKeyReleased)
            {   if ((*event).Key.Code == sfKeyEscape)
                {   c_nextMod = 'Q';
                    c_running = sfFalse;
                }
            }
        }
        
        if (c_state == 2)
        {
            /* Retrieves things */
            f_mus1Vol            = sfMusic_GetVolume (*(musp2 + 1));
            
            /* Setting things */
            sfShape_SetColor 
                ( shp_fader, sfColor_FromRGBA (163,33,98, 2 * f_mus1Vol) );
            c_JuanDancesNot = sfFalse;
            if (sfInput_IsKeyDown (input, sfKeySpace))
            {   c_JuanDancesNot     = sfTrue;
            }
            
            /* Printing things */
            puts ("");
            printf ("Score: %.0f\n",                        * d_score);
            printf ("Music 2 volume: %.0f\n",               f_mus1Vol);
            printf ("Carlita sight rotat: %.0f\n",          f_CarlitaSightRotat);
            printf ("Carlita sight rotat offset: %.3f\n",   f_CarlitaSightRotatOffset);
            printf ("Carlita looks at Juan: %d\n",          c_CarlitaLooksAtJuan);
            printf ("Juan doesn't dance: %d\n",             c_JuanDancesNot);
            printf ("Juan health: %f\n",                    f_JuanHealth);
            printf ("Juan is ashamed of himself: %d\n",     c_JuanIsSoShameful);
            printf ("A rose go through da screen: %d\n",    c_roseFalls);
            puts ("");
            
            //* Animation *//
            /* Carlita */
            if (fnGame_IsItTimeToAnimCarlitaFeet (sfClock_GetTime (clock), & d_CarlitaAnimFeetStepTime))
            {   fnGame_CarlitaAnimateFeet (spr_Carlita, & irect_CarlitaSpr, & i_CarlitaFeetAnimStep);
            }
            
            /* Falling rose */
            if (f_mus1Vol > 75.f)
            {   if (sfRandom_Int (0,1) == sfTrue)
                {   sfSprite_SetPosition (spr_rose,
                        sfRandom_Float (.333f * cui_renderWindowWidth, cui_renderWindowWidth * .666f), 
                        - (cui_renderWindowHeight / 2.f));
                    c_roseFalls = sfTrue;
                }
                printf ("Rose position: %f %f\n", 
                    sfSprite_GetX (spr_rose), sfSprite_GetY (spr_rose));
            }
            if (c_roseFalls == sfTrue)
            {   sfSprite_Move   (spr_rose, 0.f, 5.f);
                sfSprite_Rotate (spr_rose, 5.f);
                if (sfSprite_GetY (spr_rose) > 1.5f * cui_renderWindowHeight)
                {   c_roseFalls = sfFalse;
                }
            }
            
            /* Juan Carlos is shameful */
            if (c_JuanIsSoShameful > 0)
            {   switch (c_JuanIsSoShameful)
                {
                    case 1:
                        // They're making fun of you now!
                        c_arrowState = sfFalse;
                        sfString_SetText    (str_notice, "They're making fun of you now!");
                        break;
                    case 2:
                        // Don't waste your energy!
                        c_arrowState = sfFalse;
                        sfString_SetText    (str_notice, "Don't waste your energy!");
                        break;
                    case 3:
                        // She is watching! What are you doing?
                        sfString_SetText    (str_notice, "She is watching! What are you doing Juan?");
                        break;
                }
                c_state = 3;
            }
            
            /* Juan Carlos dance */
            if (! c_JuanDancesNot)
            {   c_arrowState = sfTrue;
                fnGame_ArrowPositive (spr_arrow, f_JuanHealth);
                
                if (fnGame_IsItTimeToAnimJuanDance (sfClock_GetTime (clock), & d_JuanDanceAnimStep))
                {   fnGame_JuanAnimateDance (spr_JuanCarlos, & irect_JuanCarlos, & i_JuanDanceAnimStep);
                }
                
                if (f_mus1Vol < 98.f)
                {   sfMusic_SetVolume (*(musp2 + 0), f_mus1Vol + 1.f);
                    sfMusic_SetVolume (*(musp2 + 1), f_mus1Vol + .5f);
                }
                * d_score 
                    = *(d_score) + (10.0 *  sfRenderWindow_GetFrameTime (windowMain));
                f_JuanHealth += (f_JuanHealth < F_JUAN_HEALTH_MAX) ? 
                    sfRenderWindow_GetFrameTime (windowMain) : 0;
                c_JuanIsSoShameful = sfFalse;
                
                if (sfSyS_sfSpriteAreWeInside 
                        (f_JuanPositionXY [0], f_JuanPositionXY [1],
                        spr_CarlitaSight, F_SIGHT_WIDTH, F_SIGHT_HEIGHT)
                    == 'y')
                {   for (i = 0; i < I_NB_PEOPLE; i++)
                    {   if (sfSyS_sfSpriteAreWeInside 
                            (f_JuanPositionXY [0], f_JuanPositionXY [1],
                            *(sprpX_peopleSight + i), F_SIGHT_WIDTH, F_SIGHT_HEIGHT)
                        == 'y')
                        {   c_JuanIsSoShameful = 1;
                        }
                    }
                }
                else
                {   c_JuanIsSoShameful = 2;
                }
            }
            else
            {   c_arrowState = sfFalse;
                fnGame_JuanDoesNotDance (spr_JuanCarlos, & irect_JuanCarlos);
                // Decreases volume of each parts slowly
                if (f_mus1Vol > 2.f)
                {   if (f_mus1Vol > 33.333f)
                        sfMusic_SetVolume (*(musp2 + 0), f_mus1Vol);
                    sfMusic_SetVolume (*(musp2 + 1), f_mus1Vol - 0.15f);
                }
                
                if (sfSyS_sfSpriteAreWeInside 
                        (f_JuanPositionXY [0], f_JuanPositionXY [1],
                        spr_CarlitaSight, F_SIGHT_WIDTH, F_SIGHT_HEIGHT)
                    == 'y')
                {   * d_score = *(d_score) - (2.0 *  sfRenderWindow_GetFrameTime (windowMain));
                    for (i = 0; i < I_NB_PEOPLE; i++)
                    {   if (sfSyS_sfSpriteAreWeInside 
                            (f_JuanPositionXY [0], f_JuanPositionXY [1],
                            *(sprpX_peopleSight + i), F_SIGHT_WIDTH, F_SIGHT_HEIGHT)
                        == 'y')
                        {   c_arrowState = -2;
                        }
                    }
                    
                    if (c_arrowState != -2)
                    {   if (f_JuanHealth > 0.f)
                        {   f_JuanHealth -= sfRenderWindow_GetFrameTime (windowMain);
                        }
                    }
                    c_arrowState = -1;
                    fnGame_ArrowNegative (spr_arrow, f_JuanHealth);
                }
                else if (f_JuanHealth < 0.f)
                {   c_JuanIsSoShameful = 3;
                }
            }
            
            /* People */
            for (i = 0; i < I_NB_PEOPLE; i++)
            {
                // Sight
                if (ca_peopleLooksElsewhere [i] == sfFalse)
                {   if (sfRandom_Int (0, 127) == sfTrue)
                    {   fa_peopleSightRotatOffset [i] 
                            = sfRandom_Float (F_PEOPLE_SIGHT_ROTAT_OFFSET_MIN, F_PEOPLE_SIGHT_ROTAT_OFFSET_MAX);
                        if (sfRandom_Int (0, 1))
                        {   fa_peopleSightRotatOffset [i] *= -1.f;
                        }
                        ca_peopleLooksElsewhere [i] = sfTrue;
                    }
                }
                else if (sfRandom_Int (0, 255) == sfTrue)
                {   ca_peopleLooksElsewhere [i] = sfFalse;
                }
                else
                {   sfSprite_Rotate (*(sprpX_peopleSight + i), fa_peopleSightRotatOffset [i]);
                }
                
                // Sprite change
                if (sfSprite_GetRotation (*(sprpX_peopleSight + i)) > 180.f)
                {   fnGame_PeopleLooksDown  
                        (*(sprpX_people + i), & irect_people [i]);
                }
                else
                {   fnGame_PeopleLooksUp    
                        (*(sprpX_people + i), & irect_people [i]);
                }
            }
            
            /* Carlita sight */
            if (c_CarlitaLooksElsewhere == sfFalse)
            {   if (sfRandom_Int (0, 127) == sfTrue)
                {   if ( ! c_CarlitaLooksAtJuan
                        && sfRandom_Int (0, 1) == sfTrue)
                    {   c_CarlitaLooksAtJuan = sfTrue;
                    }
                    else
                    {   f_CarlitaSightRotatOffset = sfRandom_Float (F_CARLITA_SIGHT_ROTAT_OFFSET_MIN, F_CARLITA_SIGHT_ROTAT_OFFSET_MAX);
                        if (sfRandom_Int (0, 1))
                        {   f_CarlitaSightRotatOffset *= -1.f;
                        }
                    }
                    c_CarlitaLooksElsewhere = 2;
                }
            }
            else if (c_CarlitaLooksElsewhere == sfTrue)
            {   f_CarlitaSightRotat = sfSprite_GetRotation (spr_CarlitaSight) + f_CarlitaSightRotatOffset;
                if ((f_CarlitaSightRotat > F_CARLITA_SIGHT_LIM_MIN)
                    &&
                    (f_CarlitaSightRotat < F_CARLITA_SIGHT_LIM_MAX))
                {       sfSprite_Rotate (spr_CarlitaSight, f_CarlitaSightRotatOffset);
                        if (c_CarlitaLooksAtJuan)
                        {   if (f_CarlitaSightRotat > 89.f
                                && f_CarlitaSightRotat < 91.f)
                            {   f_CarlitaSightRotatOffset   = 0.f;
                                c_CarlitaLooksElsewhere     = sfFalse;
                                c_CarlitaLooksAtJuan        = sfFalse;
                            }
                        }
                        else if (sfRandom_Int (0, 127) == sfTrue)        c_CarlitaLooksElsewhere = sfFalse;
                }
                else        c_CarlitaLooksElsewhere = sfFalse;
            }
            else
            {   if (fnGame_IsItTimeToAnimCarlitaSmile (sfClock_GetTime (clock), & d_CarlitaAnimSmileStepTime))
                {   if ((I_CARLITA_SPR_SMILE_ANIM_STEPS_TOTAL - 1) 
                            == fnGame_CarlitaAnimateSmile (spr_Carlita, & irect_CarlitaSpr, & i_CarlitaSmileAnimStep))
                    {   c_CarlitaLooksElsewhere = sfTrue;
                    }
                }
            }
        }
        else if (c_state == 1)
        {   sfString_SetY 
                (str_notice, cui_renderWindowHeight * 0.9f);
            sfString_SetScale (str_notice, 0.666f, 0.666f);
            
            c_state = 2;
        }
        else if (c_state == 3)
        {   if (c_arrowState != 3)
            {   c_arrowState = sfFalse;
            }
            sfShape_SetColor 
                (shp_fader, sfColor_FromRGBA (0,0,0, 127));
            sfString_SetY 
                (str_notice, cui_renderWindowHeight * .666f);
            sfString_SetScale   (str_notice, 1.f, 1.f);
            sfString_SetCenter  (str_notice,
                sfSyS_sfStringGetWidth  (str_notice) / 2.f, 
                sfSyS_sfStringGetHeight (str_notice) / 2.f);
            
            for (i = 0; i < I_NB_MUSIC_LAYERS; i++)
            {   sfMusic_Stop       (*(musp2 + i));
            }
            sfMusic_Play (mus_gameLost);
            
            c_state = 4;
        }
        else if (c_state == 4)
        {   if (sfMusic_GetStatus (mus_gameLost) == sfStopped)
                c_running = sfFalse;
        }
        
        
        ///* Drawing *///
        sfRenderWindow_Clear      (windowMain,  sfBlack);
        sfRenderWindow_DrawSprite (windowMain,  spr_playground);
        sfRenderWindow_DrawSprite (windowMain,  spr_CarlitaSight);
        for (i = 0; i < (I_NB_PEOPLE * 2); i++)
        {   if (i < I_NB_PEOPLE)
            {   sfRenderWindow_DrawSprite 
                    (windowMain, *(sprpX_peopleSight + i));
            }
            else
            {   sfRenderWindow_DrawSprite 
                    (windowMain, *(sprpX_people + (i - I_NB_PEOPLE)));
            }
        }
        sfRenderWindow_DrawShape  (windowMain,  shp_fader);
        sfRenderWindow_DrawSprite (windowMain,  spr_Carlita);
        sfRenderWindow_DrawSprite (windowMain,  spr_JuanCarlos);
        if (c_arrowState != sfFalse)
        {   sfRenderWindow_DrawSprite (windowMain,  spr_arrow);
        }
        sfRenderWindow_DrawSprite (windowMain,  spr_rose);
        sfRenderWindow_DrawString (windowMain,  str_notice);
        sfRenderWindow_Display    (windowMain);
    }
    
    
    /* Cleanup resources */
    puts ("Debug: Freeing ().");
    //sfSoundBuffer_Destroy     (sndbuff);
    //sfSound_Destroy           (snd);
    //sfImage_Destroy     (img);
    sfFont_Destroy      (font);
    
    sfImage_Destroy     (sfSprite_GetImage (spr_playground));
    sfSprite_Destroy    (spr_playground);
    sfImage_Destroy     (sfSprite_GetImage (spr_playgroundMask));
    sfSprite_Destroy    (spr_playgroundMask);
    sfImage_Destroy     (sfSprite_GetImage (spr_JuanCarlos));
    sfSprite_Destroy    (spr_JuanCarlos);
    sfImage_Destroy     (sfSprite_GetImage (spr_Carlita));
    sfSprite_Destroy    (spr_Carlita);
    sfImage_Destroy     (sfSprite_GetImage (spr_CarlitaSight));
    sfSprite_Destroy    (spr_CarlitaSight);
    sfImage_Destroy     (sfSprite_GetImage (*(sprpX_people + 0)));
    //sfImage_Destroy     (sfSprite_GetImage (*(sprpX_peopleSight + 0)));
    for (i = 0; i < I_NB_PEOPLE; i++)
    {   sfSprite_Destroy    (*(sprpX_people + i));
        sfSprite_Destroy    (*(sprpX_peopleSight + i));
    }
    sfImage_Destroy     (sfSprite_GetImage (spr_rose));
    sfSprite_Destroy    (spr_rose);
    sfImage_Destroy     (sfSprite_GetImage (spr_arrow));
    sfSprite_Destroy    (spr_arrow);
    sfFont_Destroy      (sfString_GetFont (str_notice));
    sfString_Destroy    (str_notice);
    sfShape_Destroy     (shp_fader);
    sfMusic_Stop        (mus_gameLost);
    sfMusic_Destroy     (mus_gameLost);
    for (i = 0; i < I_NB_MUSIC_LAYERS; i++)
    {   sfMusic_Stop    (*(musp2 + i));
        sfMusic_Destroy (*(musp2 + i));
    }
    free (musp2);
    sfClock_Destroy (clock);
    
    
    return c_nextMod;
}



char mod_RetryR 
    (sfRenderWindow * windowMain, sfEvent * event, sfInput * input, double d_score)
{
    /* Usual variables */
    char c_running = sfTrue;
    char c_nextMod = 'G';
    const unsigned int      cui_renderWindowWidth     = sfRenderWindow_GetWidth (windowMain),
                            cui_renderWindowHeight    = sfRenderWindow_GetHeight (windowMain);
    
    sfFont * font = NULL;
    
    /* Noise layer */
    sfImage * img = NULL;
    sfSprite * spr_noise 
        = sfSyS_sfSpriteDeclare 
            (img, "data/noise.png", sfTrue, 
            sfColor_FromRGBA (255,255,255, 196), sfFalse, 
            cui_renderWindowWidth, cui_renderWindowHeight);
    sfSprite_SetBlendMode (spr_noise, sfBlendAdd);
    
    sfString * str_tipOrJoke = NULL;
    switch (sfRandom_Int (0,4))
    {
        case 0:
            str_tipOrJoke =
                sfSyS_sfStringDeclare
                    (font, "data/Isabella.ttf", 31,
                    NULL, "She is the Juan . . .",
                    sfColor_FromRGBA (255,255,255,255), 
                    sfTrue,
                    0.f, 0.f);
            break;
        case 1:
            str_tipOrJoke =
                sfSyS_sfStringDeclare
                    (font, "data/Isabella.ttf", 31,
                    NULL, "Tip: she happens to smile . . .",
                    sfColor_FromRGBA (255,255,255,255), 
                    sfTrue,
                    0.f, 0.f);
            break;
        case 2:
            str_tipOrJoke =
                sfSyS_sfStringDeclare
                    (font, "data/Isabella.ttf", 31,
                    NULL, "Tip: dancing while she isn't watching is way more exhausting . . .",
                    sfColor_FromRGBA (255,255,255,255), 
                    sfTrue,
                    0.f, 0.f);
            break;
        case 3:
            str_tipOrJoke =
                sfSyS_sfStringDeclare
                    (font, "data/Isabella.ttf", 31,
                    NULL, "Tip: don't miss any opportunity to show her your skill . . .",
                    sfColor_FromRGBA (255,255,255,255), 
                    sfTrue,
                    0.f, 0.f);
            break;
        case 4:
            str_tipOrJoke =
                sfSyS_sfStringDeclare
                    (font, "data/Isabella.ttf", 31,
                    NULL, "Tip: if people see you dancing, they will make fun of you . . .",
                    sfColor_FromRGBA (255,255,255,255), 
                    sfTrue,
                    0.f, 0.f);
            break;
    }
    sfString_SetPosition (str_tipOrJoke, 
        cui_renderWindowWidth / 2.f, cui_renderWindowHeight * .2f);
    
    /* Score text */
    char * cp_score 
        = malloc (strlen ("Score: XXXXX") * sizeof (char));
    snprintf (cp_score, strlen ("Score: XXXXX"), 
        "Score: %d", (int) d_score);
    sfString * str_score =
        sfSyS_sfStringDeclare
            (font, "data/Isabella.ttf", 47,
            NULL, (const char *) cp_score,
            sfColor_FromRGBA (255,255,255,255), 
            sfTrue,
            0.f, 0.f);
    free (cp_score);
    sfString_SetPosition (str_score, 
        cui_renderWindowWidth / 2.f, cui_renderWindowHeight * .333f);
    
    sfString * str_retry =
        sfSyS_sfStringDeclare
            (font, "data/Isabella.ttf", 63,
            NULL, "Retry Juance again?",
            sfColor_FromRGBA (255,255,255,255), 
            sfTrue,
            0.f, 0.f);
    sfString_SetPosition (str_retry, 
        cui_renderWindowWidth / 2.f, cui_renderWindowHeight / 2.f);
    sfString * str_retry2 =
        sfSyS_sfStringDeclare
            (font, "data/Isabella.ttf", 47,
            NULL, "[ Y | N ]",
            sfColor_FromRGBA (255,255,255,255), 
            sfTrue,
            0.f, 0.f);
    sfString_SetPosition (str_retry2, 
        cui_renderWindowWidth / 2.f, cui_renderWindowHeight * .6f);
    
    
    while (c_running)
    {
        // Quit if Return is not pressed
        while (sfRenderWindow_GetEvent (windowMain, event))
        {   if ((*event).Type == sfEvtKeyReleased)
            {   if ((*event).Key.Code       == sfKeyY)
                {   c_nextMod = 'G';
                    c_running = sfFalse;
                }
                else if ((*event).Key.Code  == sfKeyN)  
                {   c_nextMod = 'Q';
                    c_running = sfFalse;
                }
            }
        }
        
        
        /* Drawing */
        sfRenderWindow_Clear        (windowMain, sfColor_FromRGBA (164,32,32, 255));
        sfRenderWindow_DrawSprite   (windowMain, spr_noise);
        sfRenderWindow_DrawString   (windowMain, str_tipOrJoke);
        sfRenderWindow_DrawString   (windowMain, str_score);
        sfRenderWindow_DrawString   (windowMain, str_retry);
        sfRenderWindow_DrawString   (windowMain, str_retry2);
        sfRenderWindow_Display      (windowMain);
    }
    
    
    /* Cleanup resources */
    //sfMusic_Destroy   (music);
    sfImage_Destroy     (img);
    sfFont_Destroy      (font);
    
    sfImage_Destroy     (sfSprite_GetImage (spr_noise));
    sfSprite_Destroy    (spr_noise);
    sfFont_Destroy      (sfString_GetFont (str_tipOrJoke));
    sfString_Destroy    (str_tipOrJoke);
    sfFont_Destroy      (sfString_GetFont (str_score));
    sfString_Destroy    (str_score);
    sfFont_Destroy      (sfString_GetFont (str_retry));
    sfString_Destroy    (str_retry);
    sfFont_Destroy      (sfString_GetFont (str_retry2));
    sfString_Destroy    (str_retry2);
    
    
    if (c_nextMod == 'Q')
    {   puts ("BYE BYE JUAN\nTHE NEXT GIRL WILL BE THE REAL JUAN, TRUST ME!");
    }
    
    return c_nextMod;
}
