#include "Controlka.h"


void Controlka::BuildFont()								// Build Our Bitmap Font
{

	HFONT	Font;										// Windows Font ID

	base = glGenLists(256);								// Storage For 256 Characters

	Font = CreateFont(	-12,							// Height Of Font
						0,								// Width Of Font
						0,								// Angle Of Escapement
						0,								// Orientation Angle
						FW_NORMAL,						// Font Weight
						FALSE,							// Italic
						FALSE,							// Underline
						FALSE,							// Strikeout
						ANSI_CHARSET,					// Character Set Identifier
						OUT_TT_ONLY_PRECIS,					// Output Precision
						CLIP_DEFAULT_PRECIS,			// Clipping Precision
						CLEARTYPE_QUALITY,			// Output Quality
						FF_DONTCARE|DEFAULT_PITCH,		// Family And Pitch
						"Cambria");				// Font Name

	//HWND hWND = GetForegroundWindow();
	HDC hdc = GetDC(nullptr);
	SelectObject(hdc, Font);							// Selects The Font We Created

	wglUseFontOutlines(hdc,							// Select The Current DC
						0,								// Starting Character
						255,							// Number Of Display Lists To Build
						base,							// Starting Display Lists
						0.0f,							// Deviation From The True Outlines
						0.0f,							// Font Thickness In The Z Direction
						WGL_FONT_POLYGONS,				// Use Polygons, Not Lines
						gmf);							// Address Of Buffer To Recieve Data
}

//GLvoid KillFont(GLvoid)									// Delete The Font
//{
//  glDeleteLists(base, 256);								// Delete All 256 Characters
//}

float Controlka::GetTextLength(const char* text)
{
	float length = 0;
	for (unsigned int i = 0; i < (strlen(text)); i++)
	{
		length+=gmf[text[i]].gmfCellIncX;			// Increase Length By Each Characters Width
	}
	return length;
}

void Controlka::glPrint(float x, float y, const char *fmt, ...)					// Custom GL "Print" Routine
{
	char		text[256];								// Holds Our String
	va_list		ap;										// Pointer To List Of Arguments

	if (fmt == NULL)									// If There's No Text
		return;											// Do Nothing

	va_start(ap, fmt);									// Parses The String For Variables
	    vsprintf(text, fmt, ap);						// And Converts Symbols To Actual Numbers
	va_end(ap);				// Results Are Stored In Text

	glEnable(GL_POLYGON_SMOOTH);
	glDisable(GL_TEXTURE_2D);


	glPushMatrix();
	glTranslatef(x,y,0);					// Center Our Text On The Screen
	glScalef(scale*20,scale*20,0);
	
	glPushAttrib(GL_LIST_BIT);							// Pushes The Display List Bits
	glListBase(base);									// Sets The Base Character to 0
	glCallLists(strlen(text), GL_UNSIGNED_BYTE, text);	// Draws The Display List Text
	glPopAttrib();				// Pops The Display List Bits
	glEnable(GL_TEXTURE_2D);
	glDisable(GL_POLYGON_SMOOTH);
	glPopMatrix();
}

void Controlka::glPrint(float x, float y, float scale, const char *fmt, ...)					// Custom GL "Print" Routine
{
	char		text[256];								// Holds Our String
	va_list		ap;										// Pointer To List Of Arguments

	if (fmt == NULL)									// If There's No Text
		return;											// Do Nothing

	va_start(ap, fmt);									// Parses The String For Variables
	    vsprintf(text, fmt, ap);						// And Converts Symbols To Actual Numbers
	va_end(ap);				// Results Are Stored In Text

	glEnable(GL_POLYGON_SMOOTH);
	glDisable(GL_TEXTURE_2D);


	glPushMatrix();
	glTranslatef(x,y,0);					// Center Our Text On The Screen
	glScalef(scale*20,scale*20,0);
	
	glPushAttrib(GL_LIST_BIT);							// Pushes The Display List Bits
	glListBase(base);									// Sets The Base Character to 0
	glCallLists(strlen(text), GL_UNSIGNED_BYTE, text);	// Draws The Display List Text
	glPopAttrib();				// Pops The Display List Bits
	glEnable(GL_TEXTURE_2D);
	glDisable(GL_POLYGON_SMOOTH);
	glPopMatrix();
}

//////////////////////
Texture* Controlka::font = nullptr;
unsigned int Controlka::base;
GLYPHMETRICSFLOAT Controlka::gmf[256];