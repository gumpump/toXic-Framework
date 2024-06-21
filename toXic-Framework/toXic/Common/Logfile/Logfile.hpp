#ifndef __CLOGFILE
#define __CLOGFILE

// Includes
//
#include <windows.h>
#include <stdio.h>
#include <string>
#include "Singleton.hpp"

using namespace std;

// Defines
#define MAX_BUFFER 1024             // Maximale Größe für den Buffer
#define L_FAIL false                // Funktion war erfolgreich
#define L_OK   true                 // Funktion ist fehlgeschlagen
#define g_pLogfile CLogfile::Get () // Makro zur einfachen Verwendung

// Farben für den Text
enum FONTCOLORS
{
	BLACK,
	RED,
	GREEN,
	BLUE,
	PURPLE
};

// Klassendeklaration
//
class CLogfile : public TSingleton<CLogfile>
{
	// Memberfunktionen
	public:

		CLogfile       ();
		~CLogfile      ();
		void CreateLogfile  (string LogName);
		void WriteTopic     (string Topic, int Size);
		void Textout        (string Text);
		void Textout        (int Color, string Text);
		void Textout        (int Color, bool List, string Text);
		void fTextout       (string Text, ...);
		void fTextout       (int Color, string Text, ...);
		void fTextout       (int Color, bool List, string Text, ...);
		void FunctionResult (string Name, bool Result);

		// Membervariablen
		private:

		FILE *m_Logfile;

};

#endif
