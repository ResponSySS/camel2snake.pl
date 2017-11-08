#include "libcsfml-sys.h"


/* WELCOME TO AMYSAH'S VERY PERSONAL LIBRARY! */

// Pattern: 		sfSyS_[related_type_what_it_does]_[paramlist]_[return_type] ()
// e.g.:	sf_bool 	sfSyS_sfViewAreYouInside_1r2i_b
//			int sfSyS_sfRenderWindowInWhichPartOfAreYou_1pw2i1r_i


/* sf_render_window-related */

sf_render_window * sfSyS_sfRenderWindowReadCmdArgs 
    (const char * ccp_title, int argc, char * argv [])
/* Read the following cmd line args:
 *      nothing:            auto-detect resolution, windowed mode
 *      "--resolution X Y": resolution (X width by Y height)
 *      "--fullscreen":     fullscreen mode
 *      "--version":        show version
 *      "--help" (same behavior as if wrong args)
 */
{
    sf_video_mode vid_mode             = sfVideoMode_GetDesktopMode ();
    unsigned long win_style          = sf_titlebar;
    sf_window_settings win_settings    = {24, 8, 8};
    
    if (argc == 1)
    {   return (sfRenderWindow_Create (vid_mode, ccp_title, win_style, win_settings));
    }
    
    int i; 
    for (i = 1; i < argc; i++)
    {   if (strncmp ("--fullscreen", argv [i], strlen (argv [i])) == 0)
        {   win_style = sf_fullscreen;
        }
        else if (strncmp ("--resolution", argv [i], strlen (argv [i])) == 0)
        {   if ( isdigit (*(argv [++i] + 0)) )
                vid_mode.Width    = atoi (argv [i]);
            else    goto Label_ShowUsage;
            
            if ( isdigit (*(argv [++i] + 0)) )
                vid_mode.Height   = atoi (argv [i]);
            else    goto Label_ShowUsage;
        }
        else if (strncmp ("--version", argv [i], strlen (argv [i])) == 0)
        {   puts ("Version:");
            printf ("%40s\n", STR_VERSION);
            return NULL;
        }
        else
        {   puts ("Error:");
            printf ("%40s:  Wrong argument.\n\n", argv [i]);
            goto Label_ShowUsage;
        }
    }
    return (sfRenderWindow_Create (vid_mode, ccp_title, win_style, win_settings));
    
    Label_ShowUsage:
    puts   ("Usage:");
    printf ("%40s:  Juan in fullscreen\n", "--fullscreen");
    printf ("%40s:  Juan in [width] by [height] resolution\n", "--resolution [width] [height]");
    printf ("%40s:  Show version\n", "--version");
    printf ("%40s:  Show this very help\n", "--help");
    printf ("\nExamples:\n        %s --fullscreen --resolution 800 600\n", argv [0]);
    return NULL;
}

sf_bool sfSyS_sfRenderWindowFramerateAsking 
	(sf_render_window * window_main)
{
	puts ("Framerate, sir?");
	printf ("\t");
	int dat_framerate; 
	if (scanf ("%d", &dat_framerate) > 0)
		sfRenderWindow_SetFramerateLimit (window_main, dat_framerate);
	
	if (dat_framerate > 0)
		return sf_true;
	else
		return sf_false;
}

int sfSyS_sfRenderWindowInWhichPartOfAreYou
	(sf_render_window * window_main,
	const int cint_mouseX, const int cint_mouseY,
	const sf_float_rect view_float_rect)
/* First, check if you're above 
 * the line from 0,0 to window_width,window_height;
 * then, check if you're below 
 * the line from 0,0 to window_width,window_height.
 * 
 * \xxxx			   /x			\xx/o
 *  \xxx   	then	  /xx	 to		 \/oo
 *   \xx			 /xxx			 /\oo
 *    \x			/xxxx			/xx\o
 * 
 * 
 * \  0 /
 *  \  /
 *   \/
 * 3 /\  1
 *  /  \
 * /  2 \
 * 
 * 
 * */
{
	sf_bool 	upper_right = sf_false, 
			bottom_right = sf_false;
	int returnedint;
	
	const float window_width = (view_float_rect.Right - view_float_rect.Left);
	const float window_height = (view_float_rect.Bottom - view_float_rect.Top);
	
	const float window_ratio = window_width / window_height;
	
	
	const float ratio_x_out_of_y = (float) cint_mouseX / (float) cint_mouseY;
	printf ("\t\tratio 1: %f\n", ratioXOutOfY);
	/* The first ratio is mouse_x/mouse_y, will be compared
	 * with the line from 0,0 to window_width,window_height
	 * \xxxx
	 *  \xxx
	 *   \xx
	 *    \x
	 */
	
	/* First test */
	if (ratio_x_out_of_y > (window_ratio))
	{
		printf ("\t\t\tMouse in the upper right corner.\n");
		upper_right = sf_true;
	}
	
	
	const int mouse_x_less_zero 			= cint_mouseX - 0;
	const int mouse_y_less_window_height 	= cint_mouseY - window_height;
	
	
	float ratioXLessZeroOutOfYLessWindowHeight 	= 
		(float) mouse_x_less_zero / (float) mouse_y_less_window_height;
	printf ("\t\tratio 2: %f\n", ratioXLessZeroOutOfYLessWindowHeight);
	/* The second ratio is mouse_x/mouse_y, will be compared
	 * with the line from 0,window_height to window_width,0
	 *    /x
	 *   /xx
	 *  /xxx
	 * /xxxx
	 */
	
	/* Second and final test */
	if (ratioXLessZeroOutOfYLessWindowHeight < (- window_ratio))
	{
		printf ("\t\t\tMouse in the bottom right corner.\n");
		bottom_right = sf_true;
	}
	
	
	/* Results */
	if (upper_right)
	{
		if (bottom_right)
			returnedint = 1;
		else
			returnedint = 0;
	}
	else
	{
		if (bottom_right)
			returnedint = 2;
		else
			returnedint = 3;
	}
	
	printf ("\t\tReturns '%d'", returnedint);
	return returnedint;
}


/* sf_input-related */

sf_bool sfSyS_sfInputIsMouseButtonReleased 
	(sf_input * input, sf_mouse_button button, sf_bool mouse_button_previous_state)
/* needs an external sf_bool mouse_button_previous_state 
 * 
 * loop:
 * 		this ();
 * 		mouse_button_previous_state = sfInput_IsMouseButtonDown (input, button);*/
{
	if (mouse_button_previous_state == sf_true)
	{
		if (sfInput_IsMouseButtonDown (input, button) == sf_false)
			return sf_true;
	}
	
	return sf_false;
}


/* sf_view-related */

sf_bool sfSyS_sfViewAreYouInside
//sf_bool sfSyS_sfViewAreYouInside_1r2i_b
	(sf_float_rect view_float_rect,
	const int x_coordinate_to_test, const int y_coordinate_to_test)
{
	if (
		view_float_rect.Bottom < y_coordinate_to_test
		|| 
		view_float_rect.Top > y_coordinate_to_test
		||
		view_float_rect.Left > x_coordinate_to_test
		||
		view_float_rect.Right < x_coordinate_to_test
		)
			return sf_false; //Out of the view
	else
			return sf_true;	//In the view
}


/* sf_thread-related */

void fn_thrdClock (void * arg)
{
	unsigned long int i = 0;
	
	for (; ; i++)
	{
		sleep (1);
		printf ("Time: %ld s.\n", i);
	}
}

/* sf_sprite-related */

inline sf_sprite * sfSyS_sfSpriteDeclare 
	(sf_image * img, 
	const char * ccp_pathToImage, const sf_bool bl_smoothImage,
	sf_color clr_spr, const sf_bool bl_centerSpr,
	const float cflt_resizeWidth, const float cflt_resizeHeight)
/* The sf_image * used in this function is not exclusive to the
 * sf_sprite * declared and you should re-use it for all the other
 * declarations made with this function.
 * Don't forget to free it once declared sprites are no longer needed */
/* RESIZING SPRITES IS NOT GOOD FOR COLLISION */
{
	if ( ! ccp_pathToImage)
	{	//puts ("\t\tDebug: No path to image provided. Assuming the sfImage * is ready or intentionally not present.");
	}
	else
		img = sfImage_CreateFromFile (ccp_pathToImage);
	
	if ( ! img)
	{	//puts ("\t\tDebug: Image not found or not ready (be it intentional or not).\n\t\tDebug: Returning empty sfSprite *.");
		//return sfSprite_Create ();
		//puts ("\t\tERROR: Image not found or not ready (be it intentional or not).\n\t\tDebug: Returning NULL.");
		return NULL;
	}
	
	sfImage_SetSmooth (img, bl_smoothImage);
	
	sf_sprite * spr = sfSprite_Create ();
	sfSprite_SetImage (spr, img);
	sfSprite_SetColor (spr, sf_white); sfSprite_SetColor (spr, clr_spr);
	//Resize only happens when strictly positive arguments:
	sfSprite_Resize (spr, cflt_resizeWidth, cflt_resizeHeight);
	
	if (bl_centerSpr)
	{
		//~ /* IS THIS PROBLEMATIC? */ /* YES IT IS */
		//~ if ((resize_width > 0) && (resize_height > 0))
			//~ sfSprite_SetCenter (sprite, 
				//~ resize_width / 2, resize_height / 2);
		//~ else
		sfSprite_SetCenter (spr, 
			sfImage_GetWidth (img) / 2.f, sfImage_GetHeight (img) / 2.f);
	}
	
	return spr;
}

void sfSyS_sfSpritePrintPosAndCenter
	(sf_sprite * sfsprite, const char * str_name_of_sfstring)
{
	printf ("\tDimension of %s: %5d, %5d.\n", strNameOfSfstring,
		(int)sfSprite_GetWidth (sfsprite), (int)sfSprite_GetHeight (sfsprite) );
	printf ("\tCenter of %s: %5d, %5d.\n", strNameOfSfstring,
		(int)sfSprite_GetCenterX (sfsprite), (int)sfSprite_GetCenterY (sfsprite) );
	printf ("\tPosition of %s: %5d, %5d.\n", strNameOfSfstring,
		(int)sfSprite_GetX (sfsprite), (int)sfSprite_GetY (sfsprite) );
}


inline sfUint8 sfSyS_sfSpriteAlphaIncDec
	(sf_sprite * sprite, int intensity,
	const int min, const int max)
/* Returns uint alpha after modification */
{
	int sign = 1;
	sfUint8 alpha 	= (sfSprite_GetColor (sprite).a);
	sfUint8 red 	= (sfSprite_GetColor (sprite).r);
	sfUint8 green 	= (sfSprite_GetColor (sprite).g);
	sfUint8 blue 	= (sfSprite_GetColor (sprite).b);
	int i = 0; 
	
	if (intensity < 0)
	{
		sign = - sign;
		intensity = - intensity;
	}
	
	for (i = 0; (i < intensity); i++)
	{	
		if ( ((sign > 0) && (alpha < max))
			||
			((sign < 0) && (alpha > min)) )
		{
				alpha = (sfSprite_GetColor (sprite).a) + sign;
				sfSprite_SetColor (sprite, sfColor_FromRGBA (red,green,blue, alpha));
		}
	}
	
	return alpha;
};

void sfSyS_sfSpriteColorIncDec
	(sf_sprite * sprite,
	const int red_increase_intensity, 
	const int green_increase_intensity, 
	const int blue_increase_intensity,
	const int alpha_increase_intensity)
/* INTENSITIES MUST BE MULTIPLE OF 5 (TO REACH EXACTLY 255)
 * OMG THE WORLD IS SO WRONG SOMETIMES!!111§!!!111 */
{
//////////////////////////////////* !!!!!ALGORYTHM NOT OPTIMISED!!!!! */
	int red = (sfSprite_GetColor (sprite).r);
		if ( (red != 255) || (red != 0) )
			red = red + red_increase_intensity;
	int green = (sfSprite_GetColor (sprite).g);
		if ( (green != 255) || (green != 0) )
			green = green + green_increase_intensity;
	int blue = (sfSprite_GetColor (sprite).b);
		if ( (blue != 255) || (blue != 0) )
			blue = blue + blue_increase_intensity;
	int alpha = (sfSprite_GetColor (sprite).a);
		if ( (alpha != 255) || (alpha != 0) )
			alpha = alpha + alpha_increase_intensity;
	
	sfSprite_SetColor (sprite, sfColor_FromRGBA (red,green,blue,alpha));
};


char sfSyS_sfSpriteAreWeInside 
	(const float cflt_globalX, const float cflt_globalY, 
	sf_sprite * sprite_to_test,
	const float width_sprite_to_test, const float height_sprite_to_test)
/* Returns:
 * 		'y' if Yes, in da sprite
 * 		'n' if Na, nat in da sprite
 * 		't' if in da sprite and it's Transparent */
{
	float local_coord_x_to_test = 0.f, local_coord_y_to_test = 0.f;
	sfSprite_TransformToLocal 
		(sprite_to_test, 
		cflt_globalX, cflt_globalY,
		&local_coord_x_to_test, &local_coord_y_to_test);
	
	if ((0.f <= local_coord_x_to_test) && (local_coord_x_to_test < width_sprite_to_test))
	{	if ((0.f <= local_coord_y_to_test) && (local_coord_y_to_test < height_sprite_to_test))
		{	if (
				(sfSprite_GetPixel 
					(sprite_to_test, 
					(unsigned int) local_coord_x_to_test, (unsigned int) local_coord_y_to_test)
				).a == 0
				)
				goto weAreInDaSpriteAndItsAlphaIsZero;
			else
				goto we_are_in_da_sprite;
		}
	}
	//weAreNOTInDaSprite:
	//puts ("\t\tNot in da sprite!");
	return 'n';
	
	we_are_in_da_sprite:
	//puts ("\t\tIn da sprite!");
	return 'y';
	
	weAreInDaSpriteAndItsAlphaIsZero:
	//puts ("\t\tIn da sprite! ALPHA IS ZERO HERE!");
	return 't';
}

sf_bool sfSyS_sfSpritePutOnGroundProperly
	(sf_sprite * sprite_to_put_on_the_ground,
	sf_sprite * sprite_to_test, 
	const float width_sprite_to_test, const float height_sprite_to_test,
	const sf_float_rect view_float_rect, const sf_bool caring_about_the_view)
{
	float flt_globalX = 
		sfSprite_GetX (sprite_to_put_on_the_ground);
	float flt_globalY = 
		sfSprite_GetY (sprite_to_put_on_the_ground);
	
	char * initial_pixel_state = malloc (sizeof(char));
	* initial_pixel_state = sfSyS_sfSpriteAreWeInside 
			(flt_globalX, 
			flt_globalY,
			sprite_to_test,
			width_sprite_to_test, height_sprite_to_test);
	
	char pixel_state_y_to_reach;
	int direction = 1;
	
	if (*initial_pixel_state == 'y')
	{
		/* means sprite is below surface of the ground */
		pixel_state_y_to_reach = sf_false;
		direction = - direction;
	}
	else
	{
		/* means sprite is above surface of the ground */
		pixel_state_y_to_reach = sf_true;
	}
	
	free (initial_pixel_state);
	
	for (;;)
	{
		char are_we_in_da_sprite = sfSyS_sfSpriteAreWeInside 
				(flt_globalX, 
				flt_globalY,
				sprite_to_test,
				width_sprite_to_test, height_sprite_to_test);
		
		
		if ((pixel_state_y_to_reach) && are_we_in_da_sprite == 'y')
			break;
		else if ((pixel_state_y_to_reach == sf_false) && are_we_in_da_sprite != 'y')
			break;
		
		if (! caring_about_the_view)
			goto jumping_view_checking;
		
		if ( ! sfSyS_sfViewAreYouInside (view_float_rect, 
			flt_globalX, flt_globalY) )
					goto out_of_the_view;
		else
		{
			jumping_view_checking:
			sfSprite_Move (sprite_to_put_on_the_ground, 
										0., (float) direction);
			flt_globalX = sfSprite_GetX (sprite_to_put_on_the_ground);
			flt_globalY = sfSprite_GetY (sprite_to_put_on_the_ground);
			//printf ("\t\tPixel sprite being tested: %f, %f.\n", 
				//flt_globalX, flt_globalY);			
		}
	}
	
	
	/* If sprite was below surface, it now is on a 't' (transparent) pixel,
	 * which means it's in the air above a solid pixel; consequently,
	 * you need to put it on that solid pixel */
	if (pixel_state_y_to_reach == sf_false)
		sfSprite_Move (sprite_to_put_on_the_ground, 0., (float) -direction);
	
	
	return sf_true;
	
	out_of_the_view:
	//puts ("Can't put sprite on the ground: out of the view");
	return sf_false;
}

sf_bool sfSyS_sfSpritePutOnGroundFromBottom
	(sf_sprite * sprite_to_put_on_the_ground,
	sf_sprite * sprite_to_test, 
	const int width_sprite_to_test, const int height_sprite_to_test,
	const sf_float_rect view_float_rect, const sf_bool caring_about_the_view)
{
	sfSprite_SetY (sprite_to_put_on_the_ground, 
		view_float_rect.Bottom - 5);
	
	sf_bool returned_bool = 
		(sfSyS_sfSpritePutOnGroundProperly
			(sprite_to_put_on_the_ground,
			sprite_to_test,
			width_sprite_to_test, height_sprite_to_test,
			view_float_rect, caring_about_the_view)	);
	
	return returned_bool;
}


sf_bool sfSyS_sfSpriteAnimate 
	(sf_sprite * * sprite, const char * direction_of_the_last_move, 
	char * beginning_of_path_to_image, int * current_animation_step, 
	const int max_number_of_animation_step, sf_bool bl_smoothImage, 
	sf_bool time_to_change_animation_sprite)
/* Reads direction_of_the_last_move provided by *_DirectionOfTheLastMove and iterates in the series of animation images accordingly
 *
 * e.g.:
 * 		char * path_t_i = "Sprite walking "
 * 		switch (direction_o_t_l_m)
 * 			case 'u':
 * 				path_t_i = "Sprite walking up"
 * 				break;
 * 			case ...
 * 		
 * 		current_animation_step++;
 * 		if current_animation_step > max_number_of_animation_step
 * 			current_animation_step = 1;
 * 		
 * 		path_t_i = "Lucas walking down %d.png", c_s_o_a
 * 
 * 		sfSprite_SetImage (sprite, path_t_i);
 * 		 */
{
	if ( ! time_to_change_animation_sprite)
		puts ("\t\t\tIt's not time to change anim sprite, bro."); return sfFalse;
	
	if (strcmp (direction_of_the_last_move, "\0") == 0)
		puts ("\t\t\tSprite unchanged."); return sfFalse;
	
	char * path_to_image  = malloc ((strlen(beginning_of_path_to_image) + strlen(" xx 0.png")) * sizeof(char)); 
	char number_of_frame_and_dot_png [6];
	/* strlen(" 0.png") == 6 */
	
	
	printf ("\t\t\tdOTLM: \"%s\"\n", directionOfTheLastMove);
	
	
	strcpy (path_to_image, beginning_of_path_to_image);
	strcat (path_to_image, " ");
	strcat (path_to_image, direction_of_the_last_move);
	
	
	*current_animation_step = *current_animation_step % max_number_of_animation_step;
	*current_animation_step = *current_animation_step + 1;	
	
	sprintf (numberOfFrameAndDotPng, " %d.png", *currentAnimationStep);
	strcat (path_to_image, number_of_frame_and_dot_png);
	/* ^ DUNNO WHY BUT DOTLM AND NOFADP ARE THE SAME AFTER THAT */
	
	
	printf ("\t\t\tdOTLM: \"%s\"\n", directionOfTheLastMove);
	printf ("\t\t\tnOFADP: \"%s\"\n", numberOfFrameAndDotPng);
	
	
	printf ("\t\t\tpathToImage: \"%s\", currentAnimationStep: %d\n", pathToImage,
		*current_animation_step);
	
	sf_image * image = sfImage_CreateFromFile (path_to_image);
	if (! image)
		puts ("\t\t\tPath no good :("); return sfFalse;
	
	sfImage_SetSmooth (image, bl_smoothImage);
	sfSprite_SetImage (*sprite, image);
	puts ("\t\t\tSprite has been changed.");
	
	free (path_to_image);
	
	return sf_true;
}




/* sf_shape-related */

sf_shape * sfSyS_sfShapeCircleDeclaration
	(const float flt_center_x, const float flt_center_y,
	const float flt_radius,
	sf_color color_fill,
	float flt_outline_thickness,
	sf_color color_outline,
	const sf_bool bool_enable_fill, const sf_bool bool_enable_outline,
	const sf_bool bool_center_sprite_on_itself,
	const float flt_scale_x, const float flt_scale_y)
/* BE CAREFUL WITH COLORS, OUTLINE AND SHIT */
{
	sf_shape * shape = sfShape_Create ();
	if (bool_enable_outline)
	{	shape = sfShape_CreateCircle 
			(0.f, 0.f, flt_radius, color_fill, 
			flt_outline_thickness, color_outline);
	}
	else
	{	shape = sfShape_CreateCircle 
			(0.f, 0.f, flt_radius, sf_white, 
			flt_outline_thickness, color_outline);
		sfShape_SetColor (shape, color_fill);
	}
	sfShape_SetPosition 	(shape, flt_center_x, flt_center_y);
	sfShape_EnableFill 		(shape, bool_enable_fill);
	sfShape_EnableOutline 	(shape, bool_enable_outline);
	//if (bool_center_sprite_on_itself)
		//automatically done lol
	sfShape_SetScale (shape, flt_scale_x, flt_scale_y);
	
	return shape;
}

sf_shape * * sfSyS_sfShapeCircleSmoothDeclare
	(const int cint_arrSize, const float flt_ratio_concentric_cirlces,
	const float flt_center_x, const float flt_center_y,
	float flt_radius_fill, sf_color color_fill,
	sf_bool bool_enable_fill,
	const sf_bool bool_center_sprite_on_itself,
	const float flt_scale_x, const float flt_scale_y)
/* sf_shape * arrays from smallest circle to biggest circle */
/* First, creates the base shape with fill and no outline,
 * then creates circles with outline only */
{
	sf_shape * * shape_circle_smooth 
		= malloc (cint_arrSize * sizeof (sf_shape *) );
	//
	float flt_outline_thickness = 0.f;
	sf_bool bool_enable_outline = sf_false;
	
	//printf ("\nDeclaring an array of smooth circles.\nfltRatioConcentricCirlces: %.2f\t", fltRatioConcentricCirlces);
	int i; for (i = 0; i < cint_arrSize; i++)
	{
		//printf ("i: %d, ", i);
		//
		//printf ("Outline width: %.2f\t", fltRatioConcentricCirlces);
		*(shape_circle_smooth + i) = sfSyS_sfShapeCircleDeclaration
			(flt_center_x, flt_center_y,
			flt_radius_fill, color_fill,
			flt_outline_thickness, color_fill,
			bool_enable_fill, bool_enable_outline,
			bool_center_sprite_on_itself,
			flt_scale_x, flt_scale_y);
		
		bool_enable_fill = sf_false;
		bool_enable_outline = sf_true;
		//
		color_fill = sfColor_FromRGBA (
			(color_fill.r),
			(color_fill.g),
			(color_fill.b), 
			(color_fill.a / (i+1) ) );
		//printf ("alpha: %d.\t", (sfShape_GetPointOutlineColor (shapeCircleSmooth[0], 0)).a / (i+1) );
		//
		flt_outline_thickness 
			= (flt_radius_fill * pow(flt_ratio_concentric_cirlces, i+1) ) - flt_radius_fill;
		// ^ pow() NEED <math.h>
	}
	//puts ("");
	return shape_circle_smooth;
}

sf_shape * * sfSyS_sfShapeCircleSmoothDeclareWithOutline
	(const int int_arrSize, const float flt_ratio_concentric_cirlces,
	const float flt_center_x, const float flt_center_y,
	float flt_radius,
	sf_color color_fill,
	float flt_outline_thickness,
	sf_color color_outline,
	const sf_bool bool_enable_fill,
	const sf_bool bool_center_sprite_on_itself,
	const float flt_scale_x, const float flt_scale_y)
{
	sf_shape * * shape_circle_smooth = malloc (int_arrSize * sizeof (sf_shape *) );
	
	if (int_arrSize > 1)
		(shape_circle_smooth) = sfSyS_sfShapeCircleSmoothDeclare
			(int_arrSize, flt_ratio_concentric_cirlces,
			flt_center_x, flt_center_y,
			flt_radius + flt_outline_thickness, color_outline,
			bool_enable_fill,
			bool_center_sprite_on_itself,
			flt_scale_x, flt_scale_y);
	//
	*(shape_circle_smooth) = sfSyS_sfShapeCircleDeclaration
		(flt_center_x, flt_center_y,
		flt_radius, color_fill,
		0.f, color_outline,
		bool_enable_fill, sf_true,
		bool_center_sprite_on_itself,
		flt_scale_x, flt_scale_y);
	
	puts ("");
	return shape_circle_smooth;
}

sf_shape * sfSyS_sfShapeRectOrLineDeclare
	(const char char_type_of_shape,
	float P1X, float P1Y, float P2X, float P2Y,
	const float flt_thickness,
	sf_color color_fill,
	float flt_outline_thickness,
	sf_color color_outline,
	const sf_bool bool_enable_fill, const sf_bool bool_enable_outline,
	const sf_bool bool_center_sprite_on_itself,
	const float flt_scale_x, const float flt_scale_y)
/* FOR BETTER RESULTS, PUT THE CENTER AT 0;0 WHEN YOU CREATE THE SHAPE, AND THEN DO YA THINGS */
/* 2013/11/14: changed the coloring method (color_fill to sf_white THEN color_fill) */
{
	sf_shape * shape = sfShape_Create ();
	
	switch (char_type_of_shape)
	{
		case 'r':
			//shape = sfShape_CreateRectangle
				//( P1X, P1Y, P2X, P2Y, 
				//color_fill, flt_outline_thickness, color_outline);
			shape = sfShape_CreateRectangle
				( P1X, P1Y, P2X, P2Y, 
				sf_white, flt_outline_thickness, color_outline);
			sfShape_SetColor (shape, color_fill);
			break;
		case 'l':
			//shape = sfShape_CreateLine
				//( P1X, P1Y, P2X, P2Y, 
				//flt_thickness, color_fill,
				//flt_outline_thickness, color_outline);
			shape = sfShape_CreateLine
				( P1X, P1Y, P2X, P2Y, 
				flt_thickness, sf_white,
				flt_outline_thickness, color_outline);
			sfShape_SetColor (shape, color_fill);
			break;
		default:
			puts ("\tcharTypeOfShape IS NOT A VALID ONE, BITCHES.");
			return NULL;
	}
	
	sfShape_EnableFill (shape, bool_enable_fill);
	sfShape_EnableOutline (shape, bool_enable_outline);
	if (bool_center_sprite_on_itself)
		sfShape_SetCenter ( shape, 
			(P2X / 2.f), (P2Y / 2.f) );
	sfShape_SetScale (shape, 
		flt_scale_x, flt_scale_y);
	
	return shape;
}

inline sfUint8 sfSyS_sfShapeAlphaIncDec 
	(sf_shape * shape, int intensity,
	const int min, const int max)
/* Returns uint alpha after modification */
{
	int sign = 1;
	sfUint8 red 	= (sfShape_GetColor (shape).r);
	sfUint8 green 	= (sfShape_GetColor (shape).g);
	sfUint8 blue 	= (sfShape_GetColor (shape).b);
	sfUint8 alpha 	= (sfShape_GetColor (shape).a);
	int i = 0; 
	
	if (intensity < 0)
	{
		sign = - sign;
		intensity = - intensity;
	}
	
	for (i = 0; (i < intensity); i++)
	{
		if (
			((sign > 0) && (alpha < max))
			||
			((sign < 0) && (alpha > min))
			)
		{
				alpha = (sfShape_GetColor (shape).a) + sign;
				sfShape_SetColor (shape, sfColor_FromRGBA (red,green,blue, alpha));
		}
	}
	
	return alpha;
};


///* WHY THIS FUNCTION IS USELESS *///
/* 		When creating a sf_shape, the color set when creating it with sfShape_Create* ()
 * 		is multiplied by sf_white to produce the final RGBA values.
 * 		So if you sfShape_Create* () a sf_red shape, all its RGBA values will be 255 (INCLUDING ALPHA)
 * 		but the actual visible color of the shape will be sf_red, like a sf_white red sprite. */
/* 		As a consequence, fading them -in and -out is actually very simple as
 * 		you don't have to worry about the Alpha value of each layer individually.
 * 		WHAT A WANDERFAL WARLD!!!!!!!! */
//sfUint8 sfSyS_sfShapeCircleSmoothAlphaIncDec 
	//(sf_shape * * shp_circleSmooth, int shrt_arraySize,
	//const sfUint8 sfuint8_intensity,
	//int shrt_minTopLayer, int shrt_maxTopLayer,
	//const sf_bool bl_hasOutline,
	//const int cshrt_minOutLayer, const int cshrt_maxOutLayer)
///* The top layer being the first, we use a reverse for loop */
///* If no outline, alpha values for out(line) layers are set to < 0 */
///* OH GAWD SO INCOMPLETE... I BELIEVE... */
//{
	
	//if (shrt_arraySize > 0)
	//{
		//shrt_arraySize--;
		//// proceed for top layer (i == shrt_arraySize)
		//sfUint8 sfuint8_alphaTopLayer 
			//= sfSyS_sfShapeAlphaIncDec (*(shp_circleSmooth + shrt_arraySize),
				//sfuint8_intensity, shrt_minTopLayer, shrt_maxTopLayer);
		////shrt_arraySize--;
		
		////~ if (bl_hasOutline)
		////~ {
			////~ shrt_minTopLayer = cshrt_minOutLayer;
			////~ shrt_minTopLayer = cshrt_minOutLayer;
		////~ }
		////~ //proceed for remaining layers using i
		////~ int i; for (i = (shrt_arraySize - 1); i > 0; i--)
			////~ sfSyS_sfShapeAlphaIncDec (*(shp_circleSmooth + i), 
				////~ (sfuint8_intensity / (shrt_arraySize - i)), shrt_minTopLayer, shrt_maxTopLayer);
		
		//printf ("RETARNING: %d\n", sfuint8_alphaTopLayer);
		//return sfuint8_alphaTopLayer;
		////~ return 127;
	//}
	//else
	//{
		//puts ("Smooth circle shape has a size of 0, can't inc/dec alpha");
		//return 127;
	//}
//}

inline void sfSyS_sfShapeCircleSmoothDraw 
	(sf_render_window * window_main, sf_shape * * shape_circle_smooth, const int int_arrSize)
{
	int i;
	for (i = (int_arrSize - 1); i >= 0; i--)
		sfRenderWindow_DrawShape (window_main, *(shape_circle_smooth + i));
}

inline void sfSyS_sfShapeCircleSmoothMove
	(sf_shape * * shape_circle_smooth, int int_arrSize,
	 float flt_offset_x, float flt_offset_y)
{
	int i;
	for (i = (int_arrSize - 1); i >= 0; i--)
		sfShape_Move 
			(shape_circle_smooth [i],
			flt_offset_x, flt_offset_y);
}

inline void sfSyS_sfShapeCircleSmoothSetPosition
	(sf_shape * * shape_circle_smooth, int int_arrSize,
	 float flt_X, float flt_Y)
{
	int i;
	for (i = (int_arrSize - 1); i >= 0; i--)
		sfShape_SetPosition 
			(shape_circle_smooth [i],
			flt_X, flt_Y);
}

void sfSyS_sfShapeCircleSmoothSetColor
	(sf_shape * * shape_circle_smooth, int int_arrSize,
	sf_color color_new)
{
	int int_red = color_new.r;
	int int_green = color_new.g;
	int int_blue = color_new.b;
	//
	int i; 
	for (i = (int_arrSize - 1); i >= 0; i--)
		sfShape_SetColor 
			( *(shape_circle_smooth + i),
			sfColor_FromRGBA 
				(int_red,int_green,int_blue,
				sfShape_GetColor (*(shape_circle_smooth + i)).a )
			);
}


/* sf_string-related */

inline sf_string * sfSyS_sfStringDeclare
	(sf_font * font, const char * path_to_font, 
	unsigned int uint_char_size, const sfUint32 * ptr_uint_charset,
	const char * str_text, sf_color color_string,
	const sf_bool bool_center_sprite_on_itself,
	const float flt_scale_x, const float flt_scale_y)
// ^^ Cause valgrind memcheck errors
{
	font = sfFont_CreateFromFile 
			(path_to_font, uint_char_size, ptr_uint_charset);
	sf_string * sfstr = sfString_Create ();
	sfString_SetFont 	(sfstr, font);
	sfString_SetSize 	(sfstr, uint_char_size);
	sfString_SetColor 	(sfstr, color_string);
	sfString_SetText 	(sfstr, str_text);
	// ^^ Valgrind memcheck "Invalid read of size 8" x2
	
	if (bool_center_sprite_on_itself)
	{
		sf_float_rect flt_rect_string = sfString_GetRect (sfstr);
		//
		sfString_SetCenter
			(sfstr,
			(flt_rect_string.Right - flt_rect_string.Left) / 2.f,
			(flt_rect_string.Bottom - flt_rect_string.Top) / 2.f
			);
	}
	
	sfString_SetScale 
		(sfstr, flt_scale_x, flt_scale_y);
	
	//printf ("\t\tCenter of created sfString: %f, %f\n",
		//sfString_GetCenterX (sfstr), sfString_GetCenterY (sfstr));
	return sfstr;
}

float sfSyS_sfStringGetHeight
	(sf_string * sfstr)
{
	sf_float_rect flt_rect_sfstring = sfString_GetRect (sfstr);
	return (flt_rect_sfstring.Bottom - flt_rect_sfstring.Top);
}

float sfSyS_sfStringGetWidth
	(sf_string * sfstring)
{
	sf_float_rect flt_rect_sfstring = sfString_GetRect (sfstring);
	return (flt_rect_sfstring.Right - flt_rect_sfstring.Left);
}

inline void sfSyS_sfStringCenter
    (sf_string * str)
{   sfString_SetCenter  (str,
        sfSyS_sfStringGetWidth  (str) / 2.f, 
        sfSyS_sfStringGetHeight (str) / 2.f);
}

void sfSyS_sfStringPrintPosAndCenter
	(sf_string * sfstring, const char * str_name_of_sfstring)
{
	printf ("\tPosition of %s: %5d, %5d.\n", strNameOfSfstring,
		(int)sfString_GetX (sfstring), (int)sfString_GetY (sfstring) );
	printf ("\tCenter of %s: %5d, %5d.\n", strNameOfSfstring,
		(int)sfString_GetCenterX (sfstring), (int)sfString_GetCenterY (sfstring) );
}

inline sfUint8 sfSyS_sfStringAlphaIncDec 
	(sf_string * sfstring, int intensity,
	const int min, const int max)
/* Returns uint alpha after modification */
{
	int sign = 1;
	sfUint8 alpha 	= (sfString_GetColor (sfstring).a);
	sfUint8 red 	= (sfString_GetColor (sfstring).r);
	sfUint8 green 	= (sfString_GetColor (sfstring).g);
	sfUint8 blue 	= (sfString_GetColor (sfstring).b);
	int i = 0; 
	
	if (intensity < 0)
	{
		sign = - sign;
		intensity = - intensity;
	}
	
	for (i = 0; (i < intensity); i++)
	{	
		if ( 	((sign > 0) && (alpha < max))
				||
				((sign < 0) && (alpha > min)) 	)
		{		
				alpha = (sfString_GetColor (sfstring).a) + sign;
				sfString_SetColor (sfstring, sfColor_FromRGBA (red,green,blue, alpha));
		}
	}
	
	return alpha;
};


/* sf_sound-related */

inline sf_sound * sfSyS_sfSoundDeclare_sfSnd
	(sf_sound_buffer * sndbuff, const char * str_pathToSound, 
	const sf_bool cbl_loop,
	const float cflt_pitch, const float cflt_vol)
{
	if ( ! str_pathToSound)
		puts ("\t\tDebug: No path to sound provided. Assuming the sfSoundBuffer * is ready or intentionally not present.");
	else
		sndbuff = sfSoundBuffer_CreateFromFile (str_pathToSound);
	
	if ( ! sndbuff)
	{
		puts ("\t\tDebug: Sound not found or not ready (be it intentional or not).\
		\n\t\t_debug: Returning empty sf_sound *.");
		return sfSound_Create ();
	}
	
	sf_sound * snd = sfSound_Create ();
	sfSound_SetBuffer (snd, sndbuff);
	sfSound_SetLoop (snd, cbl_loop);
	sfSound_SetPitch (snd, cflt_pitch);
	sfSound_SetVolume (snd, cflt_vol);
	
	return snd;
}


/* Others */



///* Template *///

/* ------------------------------------------------------------------ */
inline sf_bool sfSyS_IsItTimeToAnim
    (double d_time, double * d_nextAnimTime)
{
	// IF FOR DEBUG PURPOSE ONLY
	if (d_nextAnimTime != NULL)
	{	if (d_time > (*d_nextAnimTime))
		{	*(d_nextAnimTime) = d_time + D_ANIM_STEP_TIME;
			return sf_true;
		}
	}
	return sf_false;
}


//char * sfSyS_DirectionOfTheLastMove (sf_input * input, sf_sprite ** sprite)
///* Reads input and returns:
 //* 		"u" if has gone up
 //* 		"d" if has gone down
 //* 		"l" if has gone left
 //* 		"r" if has gone right
 //* 		"ul" if has gone up and left at the same time
 //* 		...
 //* 		"\0" if has done nothing
 //*
 //*
 //* Needs to be coupled with *_Animate () in order to finish the animation.
 //*/
//{
	//char direction [2] = "\0";
	
	//if (sfInput_IsKeyDown (input, sf_key_z) || sfInput_IsKeyDown (input, sf_key_up))
	//{
		//sfSprite_Move (*sprite, 0., -2.);
		//puts ("\t\tSprite has gone up!");
		//strcat (direction, "u");
	//}
	//if (sfInput_IsKeyDown (input, sf_key_s) || sfInput_IsKeyDown (input, sf_key_down))
	//{
		//sfSprite_Move (*sprite, 0., 2.);
		//puts ("\t\tSprite has gone down!");
		//if (strlen(direction) == 1)
			//strcpy (direction, "\0");
		//else
			//strcat (direction, "d");
	//}
	//if (sfInput_IsKeyDown (input, sf_key_q) || sfInput_IsKeyDown (input, sf_key_left))
	//{
		//sfSprite_Move (*sprite, -2., 0.);
		//puts ("\t\tSprite has gone left!");
		//strcat (direction, "l");
	//}
	//if (sfInput_IsKeyDown (input, sf_key_d) || sfInput_IsKeyDown (input, sf_key_right))
	//{
		//sfSprite_Move (*sprite, 2., 0.);
		//puts ("\t\tSprite has gone right!");
		//if (strchr(direction, 'l'))
			//*(strchr(direction, 'l')) = '\0';
		//else
			//strcat (direction, "r");
	//}
	
	
	//printf ("\n\t\tDirection: \"%s\"\n", direction);
	
	//return direction;
//}

