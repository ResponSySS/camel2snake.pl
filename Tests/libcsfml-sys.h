#ifndef HEADER_SFML_CONFIG_H
#define HEADER_SFML_CONFIG_H

#include <SFML/Config.h>

#endif


#ifndef HEADER_SySLIB_H
#define HEADER_SySLIB_H

//#include <SFML/System.h>
#include <SFML/Audio.h>
//#include <SFML/Window.h>
#include <SFML/Graphics.h>
#include <SFML/Graphics/Font.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <ctype.h>

/* WELCOME TO MY VERY PERSONAL LIBRARY! */


/* sf_render_window-related */

#define STR_VERSION                 "Juan version 2013.12"

sf_render_window * sfSyS_sfRenderWindowReadCmdArgs 
    (const char * ccp_title, int argc, char * argv []);

sf_bool sfSyS_sfRenderWindowFramerateAsk 
    (sf_render_window * window_main);

int sfSyS_sfRenderWindowInWhichPartOfAreYou
	(sf_render_window * window_main,
	const int mouse_x, const int mouse_y,
	const sf_float_rect view_float_rect);


/* sf_input-related */

sf_bool sfSyS_sfInputIsMouseButtonReleased 
    (sf_input * input, sf_mouse_button button, 
    sf_bool mouse_button_previous_state);


/* sf_view-related */

sf_bool sfSyS_sfViewAreYouInside
	(sf_float_rect view_float_rect,
	const int x_coordinate_to_test, const int y_coordinate_to_test);


/* sf_thread-related */

// Requirement for sleep ()
#include <unistd.h>
void fn_thrdClock (void * arg);


/* sf_sprite-related */

inline sf_sprite * sfSyS_sfSpriteDeclare 
	(sf_image * img, const char * str_pathToImage, const sf_bool bl_smoothImage,
	sf_color clr_spr, const sf_bool bl_centerSpr,
	const float cflt_resizeWidth, const float cflt_resizeHeight);

void sfSyS_sfSpritePrintPosAndCenter
	(sf_sprite * sfsprite, const char * str_name_of_sfstring);

inline sfUint8 sfSyS_sfSpriteAlphaIncDec 
	(sf_sprite * sprite, int intensity,
	const int min, const int max);

void sfSyS_sfSpriteColorIncDec 
	(sf_sprite * sprite,
	const int red_increase_intensity, 
	const int green_increase_intensity, 
	const int blue_increase_intensity,
	const int alpha_increase_intensity);

char sfSyS_sfSpriteAreWeInside 
	(const float cflt_globalX, const float cflt_globalY, 
	sf_sprite * sprite_to_test,
	const float width_sprite_to_test, const float height_sprite_to_test);

sf_bool sfSyS_sfSpritePutOnGroundProperly
	(sf_sprite * sprite_to_put_on_the_ground,
	sf_sprite * sprite_to_test, 
	const float width_sprite_to_test, const float height_sprite_to_test,
	const sf_float_rect view_float_rect, const sf_bool caring_about_the_view);

sf_bool sfSyS_sfSpritePutOnGroundFromBottom
	(sf_sprite * sprite_to_put_on_the_ground,
	sf_sprite * sprite_to_test, 
	const int width_sprite_to_test, const int height_sprite_to_test,
	const sf_float_rect view_float_rect, const sf_bool caring_about_the_view);

sf_bool sfSyS_sfSpriteAnimate 
	(sf_sprite ** sprite, const char * direction_of_the_last_move, 
	char * beginning_of_path_to_image, int * current_animation_step, 
	const int max_number_of_animation_step, sf_bool smooth_image, 
	sf_bool time_to_change_animation_sprite);


/* sf_shape-related */

sf_shape * sfSyS_sfShapeCircleDeclaration
	(const float flt_center_x, const float flt_center_y,
	const float flt_radius,
	sf_color color_fill,
	float flt_outline_thickness,
	sf_color color_outline,
	const sf_bool bool_enable_fill, const sf_bool bool_enable_outline,
	const sf_bool bool_center_sprite_on_itself,
	const float flt_scale_x, const float flt_scale_y);

#include <math.h>

sf_shape * * sfSyS_sfShapeCircleSmoothDeclare
	(const int cint_arrSize, const float flt_ratio_concentric_cirlces,
	const float flt_center_x, const float flt_center_y,
	float flt_radius, sf_color color_fill,
	const sf_bool bool_enable_fill,
	const sf_bool bool_center_sprite_on_itself,
	const float flt_scale_x, const float flt_scale_y);

sf_shape * * sfSyS_sfShapeCircleSmoothDeclareWithOutline
	(const int cint_arrSize, const float flt_ratio_concentric_cirlces,
	const float flt_center_x, const float flt_center_y,
	float flt_radius,
	sf_color color_fill,
	float flt_outline_thickness,
	sf_color color_outline,
	const sf_bool bool_enable_fill,
	const sf_bool bool_center_sprite_on_itself,
	const float flt_scale_x, const float flt_scale_y);

sf_shape * sfSyS_sfShapeRectOrLineDeclare
	(const char char_type_of_shape,
	float P1X, float P1Y, float P2X, float P2Y,
	const float flt_thickness,
	sf_color color_fill,
	float flt_outline_thickness,
	sf_color color_outline,
	const sf_bool bool_enable_fill, const sf_bool bool_enable_outline,
	const sf_bool bool_center_sprite_on_itself,
	const float flt_scale_x, const float flt_scale_y);

inline sfUint8 sfSyS_sfShapeAlphaIncDec 
	(sf_shape * shape, int intensity,
	const int min, const int max);

//sfUint8 sfSyS_sfShapeCircleSmoothAlphaIncDec 
	//(sf_shape * * shp_circleSmooth, int shrt_arraySize,
	//const sfUint8 sfuint8_intensity,
	//int shrt_minTopLayer, int shrt_maxTopLayer,
	//const sf_bool bl_hasOutline,
	//const int cshrt_minOutLayer, const int cshrt_maxOutLayer);

inline void sfSyS_sfShapeCircleSmoothDraw 
	(sf_render_window * window_main, 
	sf_shape * * shape_circle_smooth, int int_arrSize);

inline void sfSyS_sfShapeCircleSmoothMove
	(sf_shape * * shape_circle_smooth, int int_arrSize,
	float flt_offset_x, float flt_offset_y);

inline void sfSyS_sfShapeCircleSmoothSetPosition
	(sf_shape * * shape_circle_smooth, int int_arrSize,
	 float flt_X, float flt_Y);

void sfSyS_sfShapeCircleSmoothSetColor
	(sf_shape * * shape_circle_smooth, int int_arrSize,
	sf_color color_new);


/* sf_string-related */

inline sf_string * sfSyS_sfStringDeclare
	(sf_font * font, const char * path_to_font, 
	unsigned int uint_char_size, const sfUint32 * ptr_uint_charset,
	const char * str_text, sf_color color_string,
	const sf_bool bool_center_sprite_on_itself,
	const float flt_scale_x, const float flt_scale_y);

float sfSyS_sfStringGetHeight
	(sf_string * sfstring);

float sfSyS_sfStringGetWidth
	(sf_string * sfstring);

inline void sfSyS_sfStringCenter
    (sf_string * str);

void sfSyS_sfStringPrintPosAndCenter
	(sf_string * sfstring, const char * str_name_of_sfstring);

inline sfUint8 sfSyS_sfStringAlphaIncDec 
	(sf_string * sfstring, int intensity,
	const int min, const int max);


/* sf_sound-related */

inline sf_sound * sfSyS_sfSoundDeclare_sfSnd
	(sf_sound_buffer * sndbuff, const char * str_pathToSound, 
	const sf_bool cbl_loop,
	const float cflt_pitch, const float cflt_vol);


/* Others */

///* Template *///

// Change this value according to your needs
#define     D_ANIM_STEP_TIME            0.5
inline sf_bool sfSyS_IsItTimeToAnim 
	(double d_time, double * d_nextAnimTime);


#endif
