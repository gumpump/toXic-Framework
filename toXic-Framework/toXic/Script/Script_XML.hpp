#ifndef SCRIPT_XML_IS_DEFINED
#define SCRIPT_XML_IS_DEFINED

#include "TinyXML/tinyxml.h"
#include "../Common/Common.hpp"

using namespace std;

#include "Script_XML_Types.hpp"

// Mesh-Daten laden
bool LoadMeshScript (tX_XML_Mesh *Data,
					 string Filename);

// Fensterdaten laden
bool LoadWndScript	(tX_XML_Wnd *Data,
					 string Filename);

// Texte laden
bool LoadTxtScript	(tX_XML_Txt *Data,
					 string Filename);
#endif