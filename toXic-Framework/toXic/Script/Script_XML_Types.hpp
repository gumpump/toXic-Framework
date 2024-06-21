#ifndef SCRIPT_XML_TYPES_IS_DEFINED
#define SCRIPT_XML_TYPES_IS_DEFINED

////////tX_XML_Mesh - Struktur////////
//////////////////////////////////////
struct tX_XML_Mesh
{
	// Pfade
	string Path;
	string Filename;

	// Positionsangaben
	double PosX;
	double PosY;
	double PosZ;

	// Roationswinkel
	double RotX;
	double RotY;
	double RotZ;

	// Konstruktor
	tX_XML_Mesh ()
	{
		PosX = PosY = PosZ = ZERO;
		RotX = RotY = RotZ = ZERO;
	}
};


////////tX_XML_Wnd////////
//////////////////////////
struct tX_XML_Wnd
{
	// Fensterauflösung
	int Width;
	int Height;

	// Fenstermodus
	bool Windowed;

	// Fensterfarbe
	int R;
	int G;
	int B;

	// Konstruktor
	tX_XML_Wnd ()
	{
		Width = 0;
		Height = 0;

		Windowed = true;

		R = 0;
		G = 0;
		B = 0;
	}
};


////////tX_XML_Txt////////
//////////////////////////
struct tX_XML_Txt
{
	// Schriftart
	string Name;

	// Schriftgröße
	int Large;

	// Position
	int PosX;
	int PosY;

	// Schriftfarbe
	int R;
	int G;
	int B;

	// Text
	string Text;

	// Konstruktor
	tX_XML_Txt ()
	{
		Large = 0;
		
		PosX = PosY = 0;

		R = 0;
		G = 0;
		B = 0;
	}
};

bool ReplaceCodes (string *str);
#endif