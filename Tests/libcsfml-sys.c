#include "libcsfml-sys.h"


/* WELCOME TO AMYSAH'S VERY PERSONAL LIBRARY! */

// Pattern: 		sfSyS_[relatedTypeWhatItDoes]_[paramlist]_[returnType] ()
// e.g.:	sfBool 	sfSyS_sfViewAreYouInside_1r2i_b
//			int sfSyS_sfRenderWindowInWhichPartOfAreYou_1pw2i1r_i


/* sfRenderWindow-related */

sfRenderWindow * sfSyS_sfRenderWindowReadCmdArgs 
    (const char * ccp_title, int argc, char * argv [])
/* Read the following cmd line args:
 *      nothing:            auto-detect resolution, windowed mode
 *      "--resolution X Y": resolution (X width by Y height)
 *      "--fullscreen":     fullscreen mode
 *      "--version":        show version
 *      "--help" (same behavior as if wrong args)
 */
{
    sfVideoMode vidMode             = sfVideoMode_GetDesktopMode ();
    unsigned long winStyle          = sfTitlebar;
    sfWindowSettings winSettings    = {24, 8, 8};
    
    if (argc == 1)
    {   return (sfRenderWindow_Create (vidMode, ccp_title, winStyle, winSettings));
    }
    
    int i; 
    for (i = 1; i < argc; i++)
    {   if (strncmp ("--fullscreen", argv [i], strlen (argv [i])) == 0)
        {   winStyle = sfFullscreen;
        }
        else if (strncmp ("--resolution", argv [i], strlen (argv [i])) == 0)
        {   if ( isdigit (*(argv [++i] + 0)) )
                vidMode.Width    = atoi (argv [i]);
            else    goto Label_ShowUsage;
            
            if ( isdigit (*(argv [++i] + 0)) )
                vidMode.Height   = atoi (argv [i]);
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
    return (sfRenderWindow_Create (vidMode, ccp_title, winStyle, winSettings));
    
    Label_ShowUsage:
    puts   ("Usage:");
    printf ("%40s:  Juan in fullscreen\n", "--fullscreen");
    printf ("%40s:  Juan in [width] by [height] resolution\n", "--resolution [width] [height]");
    printf ("%40s:  Show version\n", "--version");
    printf ("%40s:  Show this very help\n", "--help");
    printf ("\nExamples:\n        %s --fullscreen --resolution 800 600\n", argv [0]);
    return NULL;
}

sfBool sfSyS_sfRenderWindowFramerateAsking 
	(sfRenderWindow * windowMain)
{
	puts ("Framerate, sir?");
	printf ("\t");
	int datFramerate; 
	if (scanf ("%d", &datFramerate) > 0)
		sfRenderWindow_SetFramerateLimit (windowMain, datFramerate);
	
	if (datFramerate > 0)
		return sfTrue;
	else
		return sfFalse;
}

int sfSyS_sfRenderWindowInWhichPartOfAreYou
	(sfRenderWindow * windowMain,
	const int cint_mouseX, const int cint_mouseY,
	const sfFloatRect viewFloatRect)
/* First, check if you're above 
 * the line from 0,0 to windowWidth,windowHeight;
 * then, check if you're below 
 * the line from 0,0 to windowWidth,windowHeight.
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
	sfBool 	upperRight = sfFalse, 
			bottomRight = sfFalse;
	int returnedint;
	
	const float windowWidth = (viewFloatRect.Right - viewFloatRect.Left);
	const float windowHeight = (viewFloatRect.Bottom - viewFloatRect.Top);
	
	const float windowRatio = windowWidth / windowHeight;
	
	
	const float ratioXOutOfY = (float) cint_mouseX / (float) cint_mouseY;
	printf ("\t\tratio 1: %f\n", ratioXOutOfY);
	/* The first ratio is mouseX/mouseY, will be compared
	 * with the line from 0,0 to windowWidth,windowHeight
	 * \xxxx
	 *  \xxx
	 *   \xx
	 *    \x
	 */
	
	/* First test */
	if (ratioXOutOfY > (windowRatio))
	{
		printf ("\t\t\tMouse in the upper right corner.\n");
		upperRight = sfTrue;
	}
	
	
	const int mouseXLessZero 			= cint_mouseX - 0;
	const int mouseYLessWindowHeight 	= cint_mouseY - windowHeight;
	
	
	float ratioXLessZeroOutOfYLessWindowHeight 	= 
		(float) mouseXLessZero / (float) mouseYLessWindowHeight;
	printf ("\t\tratio 2: %f\n", ratioXLessZeroOutOfYLessWindowHeight);
	/* The second ratio is mouseX/mouseY, will be compared
	 * with the line from 0,windowHeight to windowWidth,0
	 *    /x
	 *   /xx
	 *  /xxx
	 * /xxxx
	 */
	
	/* Second and final test */
	if (ratioXLessZeroOutOfYLessWindowHeight < (- windowRatio))
	{
		printf ("\t\t\tMouse in the bottom right corner.\n");
		bottomRight = sfTrue;
	}
	
	
	/* Results */
	if (upperRight)
	{
		if (bottomRight)
			returnedint = 1;
		else
			returnedint = 0;
	}
	else
	{
		if (bottomRight)
			returnedint = 2;
		else
			returnedint = 3;
	}
	
	printf ("\t\tReturns '%d'", returnedint);
	return returnedint;
}


/* sfInput-related */

sfBool sfSyS_sfInputIsMouseButtonReleased 
	(sfInput * input, sfMouseButton button, sfBool mouseButtonPreviousState)
/* needs an external sfBool mouseButtonPreviousState 
 * 
 * loop:
 * 		this ();
 * 		mouseButtonPreviousState = sfInput_IsMouseButtonDown (input, button);*/
{
	if (mouseButtonPreviousState == sfTrue)
	{
		if (sfInput_IsMouseButtonDown (input, button) == sfFalse)
			return sfTrue;
	}
	
	return sfFalse;
}


/* sfView-related */

sfBool sfSyS_sfViewAreYouInside
//sfBool sfSyS_sfViewAreYouInside_1r2i_b
	(sfFloatRect viewFloatRect,
	const int xCoordinateToTest, const int yCoordinateToTest)
{
	if (
		viewFloatRect.Bottom < yCoordinateToTest
		|| 
		viewFloatRect.Top > yCoordinateToTest
		||
		viewFloatRect.Left > xCoordinateToTest
		||
		viewFloatRect.Right < xCoordinateToTest
		)
			return sfFalse; //Out of the view
	else
			return sfTrue;	//In the view
}


/* sfThread-related */

void fn_thrdClock (void * arg)
{
	unsigned long int i = 0;
	
	for (; ; i++)
	{
		sleep (1);
		printf ("Time: %ld s.\n", i);
	}
}

/* sfSprite-related */

inline sfSprite * sfSyS_sfSpriteDeclare 
	(sfImage * img, 
	const char * ccp_pathToImage, const sfBool bl_smoothImage,
	sfColor clr_spr, const sfBool bl_centerSpr,
	const float cflt_resizeWidth, const float cflt_resizeHeight)
/* The sfImage * used in this function is not exclusive to the
 * sfSprite * declared and you should re-use it for all the other
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
	
	sfSprite * spr = sfSprite_Create ();
	sfSprite_SetImage (spr, img);
	sfSprite_SetColor (spr, sfWhite); sfSprite_SetColor (spr, clr_spr);
	//Resize only happens when strictly positive arguments:
	sfSprite_Resize (spr, cflt_resizeWidth, cflt_resizeHeight);
	
	if (bl_centerSpr)
	{
		//~ /* IS THIS PROBLEMATIC? */ /* YES IT IS */
		//~ if ((resizeWidth > 0) && (resizeHeight > 0))
			//~ sfSprite_SetCenter (sprite, 
				//~ resizeWidth / 2, resizeHeight / 2);
		//~ else
		sfSprite_SetCenter (spr, 
			sfImage_GetWidth (img) / 2.f, sfImage_GetHeight (img) / 2.f);
	}
	
	return spr;
}

void sfSyS_sfSpritePrintPosAndCenter
	(sfSprite * sfsprite, const char * strNameOfSfstring)
{
	printf ("\tDimension of %s: %5d, %5d.\n", strNameOfSfstring,
		(int)sfSprite_GetWidth (sfsprite), (int)sfSprite_GetHeight (sfsprite) );
	printf ("\tCenter of %s: %5d, %5d.\n", strNameOfSfstring,
		(int)sfSprite_GetCenterX (sfsprite), (int)sfSprite_GetCenterY (sfsprite) );
	printf ("\tPosition of %s: %5d, %5d.\n", strNameOfSfstring,
		(int)sfSprite_GetX (sfsprite), (int)sfSprite_GetY (sfsprite) );
}


inline sfUint8 sfSyS_sfSpriteAlphaIncDec
	(sfSprite * sprite, int intensity,
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
	(sfSprite * sprite,
	const int redIncreaseIntensity, 
	const int greenIncreaseIntensity, 
	const int blueIncreaseIntensity,
	const int alphaIncreaseIntensity)
/* INTENSITIES MUST BE MULTIPLE OF 5 (TO REACH EXACTLY 255)
 * OMG THE WORLD IS SO WRONG SOMETIMES!!111§!!!111 */
{
//////////////////////////////////* !!!!!ALGORYTHM NOT OPTIMISED!!!!! */
	int red = (sfSprite_GetColor (sprite).r);
		if ( (red != 255) || (red != 0) )
			red = red + redIncreaseIntensity;
	int green = (sfSprite_GetColor (sprite).g);
		if ( (green != 255) || (green != 0) )
			green = green + greenIncreaseIntensity;
	int blue = (sfSprite_GetColor (sprite).b);
		if ( (blue != 255) || (blue != 0) )
			blue = blue + blueIncreaseIntensity;
	int alpha = (sfSprite_GetColor (sprite).a);
		if ( (alpha != 255) || (alpha != 0) )
			alpha = alpha + alphaIncreaseIntensity;
	
	sfSprite_SetColor (sprite, sfColor_FromRGBA (red,green,blue,alpha));
};


char sfSyS_sfSpriteAreWeInside 
	(const float cflt_globalX, const float cflt_globalY, 
	sfSprite * spriteToTest,
	const float widthSpriteToTest, const float heightSpriteToTest)
/* Returns:
 * 		'y' if Yes, in da sprite
 * 		'n' if Na, nat in da sprite
 * 		't' if in da sprite and it's Transparent */
{
	float localCoordXToTest = 0.f, localCoordYToTest = 0.f;
	sfSprite_TransformToLocal 
		(spriteToTest, 
		cflt_globalX, cflt_globalY,
		&localCoordXToTest, &localCoordYToTest);
	
	if ((0.f <= localCoordXToTest) && (localCoordXToTest < widthSpriteToTest))
	{	if ((0.f <= localCoordYToTest) && (localCoordYToTest < heightSpriteToTest))
		{	if (
				(sfSprite_GetPixel 
					(spriteToTest, 
					(unsigned int) localCoordXToTest, (unsigned int) localCoordYToTest)
				).a == 0
				)
				goto weAreInDaSpriteAndItsAlphaIsZero;
			else
				goto weAreInDaSprite;
		}
	}
	//weAreNOTInDaSprite:
	//puts ("\t\tNot in da sprite!");
	return 'n';
	
	weAreInDaSprite:
	//puts ("\t\tIn da sprite!");
	return 'y';
	
	weAreInDaSpriteAndItsAlphaIsZero:
	//puts ("\t\tIn da sprite! ALPHA IS ZERO HERE!");
	return 't';
}

sfBool sfSyS_sfSpritePutOnGroundProperly
	(sfSprite * spriteToPutOnTheGround,
	sfSprite * spriteToTest, 
	const float widthSpriteToTest, const float heightSpriteToTest,
	const sfFloatRect viewFloatRect, const sfBool caringAboutTheView)
{
	float flt_globalX = 
		sfSprite_GetX (spriteToPutOnTheGround);
	float flt_globalY = 
		sfSprite_GetY (spriteToPutOnTheGround);
	
	char * initialPixelState = malloc (sizeof(char));
	* initialPixelState = sfSyS_sfSpriteAreWeInside 
			(flt_globalX, 
			flt_globalY,
			spriteToTest,
			widthSpriteToTest, heightSpriteToTest);
	
	char pixelStateYToReach;
	int direction = 1;
	
	if (*initialPixelState == 'y')
	{
		/* means sprite is below surface of the ground */
		pixelStateYToReach = sfFalse;
		direction = - direction;
	}
	else
	{
		/* means sprite is above surface of the ground */
		pixelStateYToReach = sfTrue;
	}
	
	free (initialPixelState);
	
	for (;;)
	{
		char areWeInDaSprite = sfSyS_sfSpriteAreWeInside 
				(flt_globalX, 
				flt_globalY,
				spriteToTest,
				widthSpriteToTest, heightSpriteToTest);
		
		
		if ((pixelStateYToReach) && areWeInDaSprite == 'y')
			break;
		else if ((pixelStateYToReach == sfFalse) && areWeInDaSprite != 'y')
			break;
		
		if (! caringAboutTheView)
			goto jumpingViewChecking;
		
		if ( ! sfSyS_sfViewAreYouInside (viewFloatRect, 
			flt_globalX, flt_globalY) )
					goto outOfTheView;
		else
		{
			jumpingViewChecking:
			sfSprite_Move (spriteToPutOnTheGround, 
										0., (float) direction);
			flt_globalX = sfSprite_GetX (spriteToPutOnTheGround);
			flt_globalY = sfSprite_GetY (spriteToPutOnTheGround);
			//printf ("\t\tPixel sprite being tested: %f, %f.\n", 
				//flt_globalX, flt_globalY);			
		}
	}
	
	
	/* If sprite was below surface, it now is on a 't' (transparent) pixel,
	 * which means it's in the air above a solid pixel; consequently,
	 * you need to put it on that solid pixel */
	if (pixelStateYToReach == sfFalse)
		sfSprite_Move (spriteToPutOnTheGround, 0., (float) -direction);
	
	
	return sfTrue;
	
	outOfTheView:
	//puts ("Can't put sprite on the ground: out of the view");
	return sfFalse;
}

sfBool sfSyS_sfSpritePutOnGroundFromBottom
	(sfSprite * spriteToPutOnTheGround,
	sfSprite * spriteToTest, 
	const int widthSpriteToTest, const int heightSpriteToTest,
	const sfFloatRect viewFloatRect, const sfBool caringAboutTheView)
{
	sfSprite_SetY (spriteToPutOnTheGround, 
		viewFloatRect.Bottom - 5);
	
	sfBool returnedBool = 
		(sfSyS_sfSpritePutOnGroundProperly
			(spriteToPutOnTheGround,
			spriteToTest,
			widthSpriteToTest, heightSpriteToTest,
			viewFloatRect, caringAboutTheView)	);
	
	return returnedBool;
}


sfBool sfSyS_sfSpriteAnimate 
	(sfSprite * * sprite, const char * directionOfTheLastMove, 
	char * beginningOfPathToImage, int * currentAnimationStep, 
	const int maxNumberOfAnimationStep, sfBool bl_smoothImage, 
	sfBool timeToChangeAnimationSprite)
/* Reads directionOfTheLastMove provided by *_DirectionOfTheLastMove and iterates in the series of animation images accordingly
 *
 * e.g.:
 * 		char * pathTI = "Sprite walking "
 * 		switch (directionOTLM)
 * 			case 'u':
 * 				pathTI = "Sprite walking up"
 * 				break;
 * 			case ...
 * 		
 * 		currentAnimationStep++;
 * 		if currentAnimationStep > maxNumberOfAnimationStep
 * 			currentAnimationStep = 1;
 * 		
 * 		pathTI = "Lucas walking down %d.png", cSOA
 * 
 * 		sfSprite_SetImage (sprite, pathTI);
 * 		 */
{
	if ( ! timeToChangeAnimationSprite)
		puts ("\t\t\tIt's not time to change anim sprite, bro."); return sfFalse;
	
	if (strcmp (directionOfTheLastMove, "\0") == 0)
		puts ("\t\t\tSprite unchanged."); return sfFalse;
	
	char * pathToImage  = malloc ((strlen(beginningOfPathToImage) + strlen(" xx 0.png")) * sizeof(char)); 
	char numberOfFrameAndDotPng [6];
	/* strlen(" 0.png") == 6 */
	
	
	printf ("\t\t\tdOTLM: \"%s\"\n", directionOfTheLastMove);
	
	
	strcpy (pathToImage, beginningOfPathToImage);
	strcat (pathToImage, " ");
	strcat (pathToImage, directionOfTheLastMove);
	
	
	*currentAnimationStep = *currentAnimationStep % maxNumberOfAnimationStep;
	*currentAnimationStep = *currentAnimationStep + 1;	
	
	sprintf (numberOfFrameAndDotPng, " %d.png", *currentAnimationStep);
	strcat (pathToImage, numberOfFrameAndDotPng);
	/* ^ DUNNO WHY BUT DOTLM AND NOFADP ARE THE SAME AFTER THAT */
	
	
	printf ("\t\t\tdOTLM: \"%s\"\n", directionOfTheLastMove);
	printf ("\t\t\tnOFADP: \"%s\"\n", numberOfFrameAndDotPng);
	
	
	printf ("\t\t\tpathToImage: \"%s\", currentAnimationStep: %d\n", pathToImage,
		*currentAnimationStep);
	
	sfImage * image = sfImage_CreateFromFile (pathToImage);
	if (! image)
		puts ("\t\t\tPath no good :("); return sfFalse;
	
	sfImage_SetSmooth (image, bl_smoothImage);
	sfSprite_SetImage (*sprite, image);
	puts ("\t\t\tSprite has been changed.");
	
	free (pathToImage);
	
	return sfTrue;
}




/* sfShape-related */

sfShape * sfSyS_sfShapeCircleDeclaration
	(const float fltCenterX, const float fltCenterY,
	const float fltRadius,
	sfColor colorFill,
	float fltOutlineThickness,
	sfColor colorOutline,
	const sfBool boolEnableFill, const sfBool boolEnableOutline,
	const sfBool boolCenterSpriteOnItself,
	const float fltScaleX, const float fltScaleY)
/* BE CAREFUL WITH COLORS, OUTLINE AND SHIT */
{
	sfShape * shape = sfShape_Create ();
	if (boolEnableOutline)
	{	shape = sfShape_CreateCircle 
			(0.f, 0.f, fltRadius, colorFill, 
			fltOutlineThickness, colorOutline);
	}
	else
	{	shape = sfShape_CreateCircle 
			(0.f, 0.f, fltRadius, sfWhite, 
			fltOutlineThickness, colorOutline);
		sfShape_SetColor (shape, colorFill);
	}
	sfShape_SetPosition 	(shape, fltCenterX, fltCenterY);
	sfShape_EnableFill 		(shape, boolEnableFill);
	sfShape_EnableOutline 	(shape, boolEnableOutline);
	//if (boolCenterSpriteOnItself)
		//automatically done lol
	sfShape_SetScale (shape, fltScaleX, fltScaleY);
	
	return shape;
}

sfShape * * sfSyS_sfShapeCircleSmoothDeclare
	(const int cint_arrSize, const float fltRatioConcentricCirlces,
	const float fltCenterX, const float fltCenterY,
	float fltRadiusFill, sfColor colorFill,
	sfBool boolEnableFill,
	const sfBool boolCenterSpriteOnItself,
	const float fltScaleX, const float fltScaleY)
/* sfShape * arrays from smallest circle to biggest circle */
/* First, creates the base shape with fill and no outline,
 * then creates circles with outline only */
{
	sfShape * * shapeCircleSmooth 
		= malloc (cint_arrSize * sizeof (sfShape *) );
	//
	float fltOutlineThickness = 0.f;
	sfBool boolEnableOutline = sfFalse;
	
	//printf ("\nDeclaring an array of smooth circles.\nfltRatioConcentricCirlces: %.2f\t", fltRatioConcentricCirlces);
	int i; for (i = 0; i < cint_arrSize; i++)
	{
		//printf ("i: %d, ", i);
		//
		//printf ("Outline width: %.2f\t", fltRatioConcentricCirlces);
		*(shapeCircleSmooth + i) = sfSyS_sfShapeCircleDeclaration
			(fltCenterX, fltCenterY,
			fltRadiusFill, colorFill,
			fltOutlineThickness, colorFill,
			boolEnableFill, boolEnableOutline,
			boolCenterSpriteOnItself,
			fltScaleX, fltScaleY);
		
		boolEnableFill = sfFalse;
		boolEnableOutline = sfTrue;
		//
		colorFill = sfColor_FromRGBA (
			(colorFill.r),
			(colorFill.g),
			(colorFill.b), 
			(colorFill.a / (i+1) ) );
		//printf ("alpha: %d.\t", (sfShape_GetPointOutlineColor (shapeCircleSmooth[0], 0)).a / (i+1) );
		//
		fltOutlineThickness 
			= (fltRadiusFill * pow(fltRatioConcentricCirlces, i+1) ) - fltRadiusFill;
		// ^ pow() NEED <math.h>
	}
	//puts ("");
	return shapeCircleSmooth;
}

sfShape * * sfSyS_sfShapeCircleSmoothDeclareWithOutline
	(const int int_arrSize, const float fltRatioConcentricCirlces,
	const float fltCenterX, const float fltCenterY,
	float fltRadius,
	sfColor colorFill,
	float fltOutlineThickness,
	sfColor colorOutline,
	const sfBool boolEnableFill,
	const sfBool boolCenterSpriteOnItself,
	const float fltScaleX, const float fltScaleY)
{
	sfShape * * shapeCircleSmooth = malloc (int_arrSize * sizeof (sfShape *) );
	
	if (int_arrSize > 1)
		(shapeCircleSmooth) = sfSyS_sfShapeCircleSmoothDeclare
			(int_arrSize, fltRatioConcentricCirlces,
			fltCenterX, fltCenterY,
			fltRadius + fltOutlineThickness, colorOutline,
			boolEnableFill,
			boolCenterSpriteOnItself,
			fltScaleX, fltScaleY);
	//
	*(shapeCircleSmooth) = sfSyS_sfShapeCircleDeclaration
		(fltCenterX, fltCenterY,
		fltRadius, colorFill,
		0.f, colorOutline,
		boolEnableFill, sfTrue,
		boolCenterSpriteOnItself,
		fltScaleX, fltScaleY);
	
	puts ("");
	return shapeCircleSmooth;
}

sfShape * sfSyS_sfShapeRectOrLineDeclare
	(const char charTypeOfShape,
	float P1X, float P1Y, float P2X, float P2Y,
	const float fltThickness,
	sfColor colorFill,
	float fltOutlineThickness,
	sfColor colorOutline,
	const sfBool boolEnableFill, const sfBool boolEnableOutline,
	const sfBool boolCenterSpriteOnItself,
	const float fltScaleX, const float fltScaleY)
/* FOR BETTER RESULTS, PUT THE CENTER AT 0;0 WHEN YOU CREATE THE SHAPE, AND THEN DO YA THINGS */
/* 2013/11/14: changed the coloring method (colorFill to sfWhite THEN colorFill) */
{
	sfShape * shape = sfShape_Create ();
	
	switch (charTypeOfShape)
	{
		case 'r':
			//shape = sfShape_CreateRectangle
				//( P1X, P1Y, P2X, P2Y, 
				//colorFill, fltOutlineThickness, colorOutline);
			shape = sfShape_CreateRectangle
				( P1X, P1Y, P2X, P2Y, 
				sfWhite, fltOutlineThickness, colorOutline);
			sfShape_SetColor (shape, colorFill);
			break;
		case 'l':
			//shape = sfShape_CreateLine
				//( P1X, P1Y, P2X, P2Y, 
				//fltThickness, colorFill,
				//fltOutlineThickness, colorOutline);
			shape = sfShape_CreateLine
				( P1X, P1Y, P2X, P2Y, 
				fltThickness, sfWhite,
				fltOutlineThickness, colorOutline);
			sfShape_SetColor (shape, colorFill);
			break;
		default:
			puts ("\tcharTypeOfShape IS NOT A VALID ONE, BITCHES.");
			return NULL;
	}
	
	sfShape_EnableFill (shape, boolEnableFill);
	sfShape_EnableOutline (shape, boolEnableOutline);
	if (boolCenterSpriteOnItself)
		sfShape_SetCenter ( shape, 
			(P2X / 2.f), (P2Y / 2.f) );
	sfShape_SetScale (shape, 
		fltScaleX, fltScaleY);
	
	return shape;
}

inline sfUint8 sfSyS_sfShapeAlphaIncDec 
	(sfShape * shape, int intensity,
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
/* 		When creating a sfShape, the color set when creating it with sfShape_Create* ()
 * 		is multiplied by sfWhite to produce the final RGBA values.
 * 		So if you sfShape_Create* () a sfRed shape, all its RGBA values will be 255 (INCLUDING ALPHA)
 * 		but the actual visible color of the shape will be sfRed, like a sfWhite red sprite. */
/* 		As a consequence, fading them -in and -out is actually very simple as
 * 		you don't have to worry about the Alpha value of each layer individually.
 * 		WHAT A WANDERFAL WARLD!!!!!!!! */
//sfUint8 sfSyS_sfShapeCircleSmoothAlphaIncDec 
	//(sfShape * * shp_circleSmooth, int shrt_arraySize,
	//const sfUint8 sfuint8_intensity,
	//int shrt_minTopLayer, int shrt_maxTopLayer,
	//const sfBool bl_hasOutline,
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
	(sfRenderWindow * windowMain, sfShape * * shapeCircleSmooth, const int int_arrSize)
{
	int i;
	for (i = (int_arrSize - 1); i >= 0; i--)
		sfRenderWindow_DrawShape (windowMain, *(shapeCircleSmooth + i));
}

inline void sfSyS_sfShapeCircleSmoothMove
	(sfShape * * shapeCircleSmooth, int int_arrSize,
	 float fltOffsetX, float fltOffsetY)
{
	int i;
	for (i = (int_arrSize - 1); i >= 0; i--)
		sfShape_Move 
			(shapeCircleSmooth [i],
			fltOffsetX, fltOffsetY);
}

inline void sfSyS_sfShapeCircleSmoothSetPosition
	(sfShape * * shapeCircleSmooth, int int_arrSize,
	 float flt_X, float flt_Y)
{
	int i;
	for (i = (int_arrSize - 1); i >= 0; i--)
		sfShape_SetPosition 
			(shapeCircleSmooth [i],
			flt_X, flt_Y);
}

void sfSyS_sfShapeCircleSmoothSetColor
	(sfShape * * shapeCircleSmooth, int int_arrSize,
	sfColor color_new)
{
	int int_red = color_new.r;
	int int_green = color_new.g;
	int int_blue = color_new.b;
	//
	int i; 
	for (i = (int_arrSize - 1); i >= 0; i--)
		sfShape_SetColor 
			( *(shapeCircleSmooth + i),
			sfColor_FromRGBA 
				(int_red,int_green,int_blue,
				sfShape_GetColor (*(shapeCircleSmooth + i)).a )
			);
}


/* sfString-related */

inline sfString * sfSyS_sfStringDeclare
	(sfFont * font, const char * pathToFont, 
	unsigned int uintCharSize, const sfUint32 * ptrUintCharset,
	const char * strText, sfColor colorString,
	const sfBool boolCenterSpriteOnItself,
	const float fltScaleX, const float fltScaleY)
// ^^ Cause valgrind memcheck errors
{
	font = sfFont_CreateFromFile 
			(pathToFont, uintCharSize, ptrUintCharset);
	sfString * sfstr = sfString_Create ();
	sfString_SetFont 	(sfstr, font);
	sfString_SetSize 	(sfstr, uintCharSize);
	sfString_SetColor 	(sfstr, colorString);
	sfString_SetText 	(sfstr, strText);
	// ^^ Valgrind memcheck "Invalid read of size 8" x2
	
	if (boolCenterSpriteOnItself)
	{
		sfFloatRect fltRectString = sfString_GetRect (sfstr);
		//
		sfString_SetCenter
			(sfstr,
			(fltRectString.Right - fltRectString.Left) / 2.f,
			(fltRectString.Bottom - fltRectString.Top) / 2.f
			);
	}
	
	sfString_SetScale 
		(sfstr, fltScaleX, fltScaleY);
	
	//printf ("\t\tCenter of created sfString: %f, %f\n",
		//sfString_GetCenterX (sfstr), sfString_GetCenterY (sfstr));
	return sfstr;
}

float sfSyS_sfStringGetHeight
	(sfString * sfstr)
{
	sfFloatRect fltRectSfstring = sfString_GetRect (sfstr);
	return (fltRectSfstring.Bottom - fltRectSfstring.Top);
}

float sfSyS_sfStringGetWidth
	(sfString * sfstring)
{
	sfFloatRect fltRectSfstring = sfString_GetRect (sfstring);
	return (fltRectSfstring.Right - fltRectSfstring.Left);
}

inline void sfSyS_sfStringCenter
    (sfString * str)
{   sfString_SetCenter  (str,
        sfSyS_sfStringGetWidth  (str) / 2.f, 
        sfSyS_sfStringGetHeight (str) / 2.f);
}

void sfSyS_sfStringPrintPosAndCenter
	(sfString * sfstring, const char * strNameOfSfstring)
{
	printf ("\tPosition of %s: %5d, %5d.\n", strNameOfSfstring,
		(int)sfString_GetX (sfstring), (int)sfString_GetY (sfstring) );
	printf ("\tCenter of %s: %5d, %5d.\n", strNameOfSfstring,
		(int)sfString_GetCenterX (sfstring), (int)sfString_GetCenterY (sfstring) );
}

inline sfUint8 sfSyS_sfStringAlphaIncDec 
	(sfString * sfstring, int intensity,
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


/* sfSound-related */

inline sfSound * sfSyS_sfSoundDeclare_sfSnd
	(sfSoundBuffer * sndbuff, const char * str_pathToSound, 
	const sfBool cbl_loop,
	const float cflt_pitch, const float cflt_vol)
{
	if ( ! str_pathToSound)
		puts ("\t\tDebug: No path to sound provided. Assuming the sfSoundBuffer * is ready or intentionally not present.");
	else
		sndbuff = sfSoundBuffer_CreateFromFile (str_pathToSound);
	
	if ( ! sndbuff)
	{
		puts ("\t\tDebug: Sound not found or not ready (be it intentional or not).\
		\n\t\tDebug: Returning empty sfSound *.");
		return sfSound_Create ();
	}
	
	sfSound * snd = sfSound_Create ();
	sfSound_SetBuffer (snd, sndbuff);
	sfSound_SetLoop (snd, cbl_loop);
	sfSound_SetPitch (snd, cflt_pitch);
	sfSound_SetVolume (snd, cflt_vol);
	
	return snd;
}


/* Others */



///* Template *///

/* ------------------------------------------------------------------ */
inline sfBool sfSyS_IsItTimeToAnim
    (double d_time, double * d_nextAnimTime)
{
	// IF FOR DEBUG PURPOSE ONLY
	if (d_nextAnimTime != NULL)
	{	if (d_time > (*d_nextAnimTime))
		{	*(d_nextAnimTime) = d_time + D_ANIM_STEP_TIME;
			return sfTrue;
		}
	}
	return sfFalse;
}


//char * sfSyS_DirectionOfTheLastMove (sfInput * input, sfSprite ** sprite)
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
	
	//if (sfInput_IsKeyDown (input, sfKeyZ) || sfInput_IsKeyDown (input, sfKeyUp))
	//{
		//sfSprite_Move (*sprite, 0., -2.);
		//puts ("\t\tSprite has gone up!");
		//strcat (direction, "u");
	//}
	//if (sfInput_IsKeyDown (input, sfKeyS) || sfInput_IsKeyDown (input, sfKeyDown))
	//{
		//sfSprite_Move (*sprite, 0., 2.);
		//puts ("\t\tSprite has gone down!");
		//if (strlen(direction) == 1)
			//strcpy (direction, "\0");
		//else
			//strcat (direction, "d");
	//}
	//if (sfInput_IsKeyDown (input, sfKeyQ) || sfInput_IsKeyDown (input, sfKeyLeft))
	//{
		//sfSprite_Move (*sprite, -2., 0.);
		//puts ("\t\tSprite has gone left!");
		//strcat (direction, "l");
	//}
	//if (sfInput_IsKeyDown (input, sfKeyD) || sfInput_IsKeyDown (input, sfKeyRight))
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

