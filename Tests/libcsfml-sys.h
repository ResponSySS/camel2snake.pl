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


/* sfRenderWindow-related */

#define STR_VERSION                 "Juan version 2013.12"

sfRenderWindow * sfSyS_sfRenderWindowReadCmdArgs 
    (const char * ccp_title, int argc, char * argv []);

sfBool sfSyS_sfRenderWindowFramerateAsk 
    (sfRenderWindow * windowMain);

int sfSyS_sfRenderWindowInWhichPartOfAreYou
	(sfRenderWindow * windowMain,
	const int mouseX, const int mouseY,
	const sfFloatRect viewFloatRect);


/* sfInput-related */

sfBool sfSyS_sfInputIsMouseButtonReleased 
    (sfInput * input, sfMouseButton button, 
    sfBool mouseButtonPreviousState);


/* sfView-related */

sfBool sfSyS_sfViewAreYouInside
	(sfFloatRect viewFloatRect,
	const int xCoordinateToTest, const int yCoordinateToTest);


/* sfThread-related */

// Requirement for sleep ()
#include <unistd.h>
void fn_thrdClock (void * arg);


/* sfSprite-related */

inline sfSprite * sfSyS_sfSpriteDeclare 
	(sfImage * img, const char * str_pathToImage, const sfBool bl_smoothImage,
	sfColor clr_spr, const sfBool bl_centerSpr,
	const float cflt_resizeWidth, const float cflt_resizeHeight);

void sfSyS_sfSpritePrintPosAndCenter
	(sfSprite * sfsprite, const char * strNameOfSfstring);

inline sfUint8 sfSyS_sfSpriteAlphaIncDec 
	(sfSprite * sprite, int intensity,
	const int min, const int max);

void sfSyS_sfSpriteColorIncDec 
	(sfSprite * sprite,
	const int redIncreaseIntensity, 
	const int greenIncreaseIntensity, 
	const int blueIncreaseIntensity,
	const int alphaIncreaseIntensity);

char sfSyS_sfSpriteAreWeInside 
	(const float cflt_globalX, const float cflt_globalY, 
	sfSprite * spriteToTest,
	const float widthSpriteToTest, const float heightSpriteToTest);

sfBool sfSyS_sfSpritePutOnGroundProperly
	(sfSprite * spriteToPutOnTheGround,
	sfSprite * spriteToTest, 
	const float widthSpriteToTest, const float heightSpriteToTest,
	const sfFloatRect viewFloatRect, const sfBool caringAboutTheView);

sfBool sfSyS_sfSpritePutOnGroundFromBottom
	(sfSprite * spriteToPutOnTheGround,
	sfSprite * spriteToTest, 
	const int widthSpriteToTest, const int heightSpriteToTest,
	const sfFloatRect viewFloatRect, const sfBool caringAboutTheView);

sfBool sfSyS_sfSpriteAnimate 
	(sfSprite ** sprite, const char * directionOfTheLastMove, 
	char * beginningOfPathToImage, int * currentAnimationStep, 
	const int maxNumberOfAnimationStep, sfBool smoothImage, 
	sfBool timeToChangeAnimationSprite);


/* sfShape-related */

sfShape * sfSyS_sfShapeCircleDeclaration
	(const float fltCenterX, const float fltCenterY,
	const float fltRadius,
	sfColor colorFill,
	float fltOutlineThickness,
	sfColor colorOutline,
	const sfBool boolEnableFill, const sfBool boolEnableOutline,
	const sfBool boolCenterSpriteOnItself,
	const float fltScaleX, const float fltScaleY);

#include <math.h>

sfShape * * sfSyS_sfShapeCircleSmoothDeclare
	(const int cint_arrSize, const float fltRatioConcentricCirlces,
	const float fltCenterX, const float fltCenterY,
	float fltRadius, sfColor colorFill,
	const sfBool boolEnableFill,
	const sfBool boolCenterSpriteOnItself,
	const float fltScaleX, const float fltScaleY);

sfShape * * sfSyS_sfShapeCircleSmoothDeclareWithOutline
	(const int cint_arrSize, const float fltRatioConcentricCirlces,
	const float fltCenterX, const float fltCenterY,
	float fltRadius,
	sfColor colorFill,
	float fltOutlineThickness,
	sfColor colorOutline,
	const sfBool boolEnableFill,
	const sfBool boolCenterSpriteOnItself,
	const float fltScaleX, const float fltScaleY);

sfShape * sfSyS_sfShapeRectOrLineDeclare
	(const char charTypeOfShape,
	float P1X, float P1Y, float P2X, float P2Y,
	const float fltThickness,
	sfColor colorFill,
	float fltOutlineThickness,
	sfColor colorOutline,
	const sfBool boolEnableFill, const sfBool boolEnableOutline,
	const sfBool boolCenterSpriteOnItself,
	const float fltScaleX, const float fltScaleY);

inline sfUint8 sfSyS_sfShapeAlphaIncDec 
	(sfShape * shape, int intensity,
	const int min, const int max);

//sfUint8 sfSyS_sfShapeCircleSmoothAlphaIncDec 
	//(sfShape * * shp_circleSmooth, int shrt_arraySize,
	//const sfUint8 sfuint8_intensity,
	//int shrt_minTopLayer, int shrt_maxTopLayer,
	//const sfBool bl_hasOutline,
	//const int cshrt_minOutLayer, const int cshrt_maxOutLayer);

inline void sfSyS_sfShapeCircleSmoothDraw 
	(sfRenderWindow * windowMain, 
	sfShape * * shapeCircleSmooth, int int_arrSize);

inline void sfSyS_sfShapeCircleSmoothMove
	(sfShape * * shapeCircleSmooth, int int_arrSize,
	float fltOffsetX, float fltOffsetY);

inline void sfSyS_sfShapeCircleSmoothSetPosition
	(sfShape * * shapeCircleSmooth, int int_arrSize,
	 float flt_X, float flt_Y);

void sfSyS_sfShapeCircleSmoothSetColor
	(sfShape * * shapeCircleSmooth, int int_arrSize,
	sfColor color_new);


/* sfString-related */

inline sfString * sfSyS_sfStringDeclare
	(sfFont * font, const char * pathToFont, 
	unsigned int uintCharSize, const sfUint32 * ptrUintCharset,
	const char * strText, sfColor colorString,
	const sfBool boolCenterSpriteOnItself,
	const float fltScaleX, const float fltScaleY);

float sfSyS_sfStringGetHeight
	(sfString * sfstring);

float sfSyS_sfStringGetWidth
	(sfString * sfstring);

inline void sfSyS_sfStringCenter
    (sfString * str);

void sfSyS_sfStringPrintPosAndCenter
	(sfString * sfstring, const char * strNameOfSfstring);

inline sfUint8 sfSyS_sfStringAlphaIncDec 
	(sfString * sfstring, int intensity,
	const int min, const int max);


/* sfSound-related */

inline sfSound * sfSyS_sfSoundDeclare_sfSnd
	(sfSoundBuffer * sndbuff, const char * str_pathToSound, 
	const sfBool cbl_loop,
	const float cflt_pitch, const float cflt_vol);


/* Others */

///* Template *///

// Change this value according to your needs
#define     D_ANIM_STEP_TIME            0.5
inline sfBool sfSyS_IsItTimeToAnim 
	(double d_time, double * d_nextAnimTime);


#endif
