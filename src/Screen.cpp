#define GLFW_DLL

#include "Screen.h"
#include "utils.h"

Screen* screen;

void Screen::run(double deltaTime)
{
	//glLoadIdentity();
}

int GLFWCALL Close()
{
	glfwCloseWindow();
	glfwTerminate();
	exit(0);
	return 0;
}

bool isInString(char *string, const char *search) 
{
	int pos=0;
	int maxpos=strlen(search)-1;
	int len=strlen(string);	
	char *other;
	for (int i=0; i<len; i++) {
		if ((i==0) || ((i>1) && string[i-1]=='\n')) {				// New Extension Begins Here!
			other=&string[i];			
			pos=0;													// Begin New Search
			while (string[i]!='\n') {								// Search Whole Extension-String
				if (string[i]==search[pos]) pos++;					// Next Position
				if ((pos>maxpos) && string[i+1]=='\n') return true; // We Have A Winner!
				i++;
			}			
		}
	}	
	return false;													// Sorry, Not Found!
}

GLint maxTexelUnits=1;

bool initMultitexture(void) 
{
	char *extensions;	
	extensions=_strdup((char *) glGetString(GL_EXTENSIONS));			// Fetch Extension String
	int len=strlen(extensions);
	for (int i=0; i<len; i++)										// Separate It By Newline Instead Of Blank
		if (extensions[i]==' ') extensions[i]='\n';

#ifdef EXT_INFO
	MessageBox(hWnd,extensions,"supported GL extensions",MB_OK | MB_ICONINFORMATION);
#endif

	if (isInString(extensions,"GL_ARB_multitexture")				// Is Multitexturing Supported?
		&& true												// Override-Flag
		&& isInString(extensions,"GL_EXT_texture_env_combine"))		// Is texture_env_combining Supported?
	{	
		glGetIntegerv(GL_MAX_TEXTURE_UNITS_ARB,&maxTexelUnits);
		glBlendEquationSeparate = (PFNGLBLENDEQUATIONSEPARATEPROC)  wglGetProcAddress("glBlendEquationSeparate");
		glBlendFuncSeparate     = (PFNGLBLENDFUNCSEPARATEPROC)      wglGetProcAddress("glBlendFuncSeparate");
		glBlendEquation         = (PFNGLBLENDEQUATIONPROC)          wglGetProcAddress("glBlendEquation");
		glMultiTexCoord1fARB	= (PFNGLMULTITEXCOORD1FARBPROC)		wglGetProcAddress("glMultiTexCoord1fARB");
		glMultiTexCoord2fARB	= (PFNGLMULTITEXCOORD2FARBPROC)		wglGetProcAddress("glMultiTexCoord2fARB");
		glMultiTexCoord3fARB	= (PFNGLMULTITEXCOORD3FARBPROC)		wglGetProcAddress("glMultiTexCoord3fARB");
		glMultiTexCoord4fARB	= (PFNGLMULTITEXCOORD4FARBPROC)		wglGetProcAddress("glMultiTexCoord4fARB");
		glActiveTextureARB		= (PFNGLACTIVETEXTUREARBPROC)		wglGetProcAddress("glActiveTextureARB");
		glClientActiveTextureARB= (PFNGLCLIENTACTIVETEXTUREARBPROC)	wglGetProcAddress("glClientActiveTextureARB");		
#ifdef EXT_INFO
	MessageBox(hWnd,"The GL_ARB_multitexture extension will be used.","feature supported!",MB_OK | MB_ICONINFORMATION);
#endif
		return true;
	}
	return false;
}

void GLFWCALL Screen::ReSizeGLScene(int w, int h)
{
	//GLfloat aspectRatio;
	// Zabezpieczenie przed dzieleniem przez zero
	if(h == 0)
		h = 1;
	// Ustawienie wielkoci widoku na równ wielkoci okna
	glViewport(0, 0, w, h);
	// Ustalenie uk³adu wspó³rzdnych
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	glOrtho(0,w,0,h,-1,1);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	if(!screen)
		return;
	screen->setWidth(w);
	screen->setHeight(h);
	
	glfwSwapBuffers();
}

Screen::Screen(int width, int height)
{
	Width = width;
	Height = height;

	glfwInit();
	glfwOpenWindow(width,height,8,8,8,0,0,0,GLFW_WINDOW);
	glfwSetWindowTitle("Projekt");
	glfwSetWindowCloseCallback(Close);
	glfwSetKeyCallback(Input::InputManager::KeyCallback);
	glfwSetWindowSizeCallback(Screen::ReSizeGLScene);
	glfwSetMousePosCallback(Input::InputManager::MouseCallback);
	glfwSetMouseButtonCallback(Input::InputManager::MouseButtonCallback);
	glfwSetCharCallback(Input::InputManager::CharCallback);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0,width,0,height,-1,1);
	glMatrixMode(GL_MODELVIEW);
	
	glEnable(GL_TEXTURE_2D);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glClearColor(0.0, 0.0, 0.0, 0.0);
	if(initMultitexture()) cout << "Udalo sie! Jest Multi Textururing!\n"; else cout << "Tia no nie wyszlo z multi texturingiem...\n";
}