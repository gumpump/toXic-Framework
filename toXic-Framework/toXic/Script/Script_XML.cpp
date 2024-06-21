#include "Script_XML.hpp"

bool LoadMeshScript (tX_XML_Mesh *Data,
					 string Filename)
{
	// Hier wird irgendwas gemacht,
	// aber wir haben jetzt 23:52
	// und ich hab jetzt grad keinen Bock mehr.

	// So, wir haben jetzt zwar auch schon wieder 00:28
	// aber ich mach den Teil hier trotzdem noch.

	// Jetzt bin ich hier auf Bug-Suche und wir haben
	// schon wieder 23:55 und Morgen ist der
	// beschissene letzte Tag meines Urlaubs.

	// Bug gefunden:
	// LPCSTR musste durch string ersetzt werden.

	TiXmlDocument Doc (Filename.c_str ());

	if (Doc.LoadFile () == false)
	{
		return false;
	}

	else
	{
		TiXmlElement *Root = Doc.RootElement ();
		TiXmlElement *Sub;

		string Type = Root->Attribute ("Type");

		if (Type != "Mesh")
		{
			return false;
		}

		else
		{
			Sub = Root->FirstChildElement ("Load");
			Data->Path = Sub->Attribute ("Path");
			Data->Filename = Sub->Attribute ("File");

			Sub = Root->FirstChildElement ("Pos");
			Sub->Attribute ("X", &Data->PosX);
			Sub->Attribute ("Y", &Data->PosY);
			Sub->Attribute ("Z", &Data->PosZ);

			Sub = Root->FirstChildElement ("Rot");
			Sub->Attribute ("X", &Data->RotX);
			Sub->Attribute ("Y", &Data->RotY);
			Sub->Attribute ("Z", &Data->RotZ);
		}
	}

	return true;
}

bool LoadWndScript (tX_XML_Wnd *Data,
					string Filename)
{
	TiXmlDocument Doc (Filename.c_str ());

	if (Doc.LoadFile () == false)
	{
		return false;
	}

	else
	{
		TiXmlElement *Root = Doc.RootElement ();
		TiXmlElement *Sub;

		string Type = Root->Attribute ("Type");

		if (Type != "Wnd")
		{
			return false;
		}

		else
		{
			Sub = Root->FirstChildElement ("Size");
			Sub->Attribute ("Width", &Data->Width);
			Sub->Attribute ("Height", &Data->Height);

			Sub = Root->FirstChildElement ("Window");
			int IsWindowed;
			Sub->Attribute ("Mode", &IsWindowed);
			if (IsWindowed == 1)
			{
				Data->Windowed = true;
			}

			else
			{
				Data->Windowed = false;
			}

			Sub = Root->FirstChildElement ("Color");
			Sub->Attribute ("R", &Data->R);
			Sub->Attribute ("G", &Data->G);
			Sub->Attribute ("B", &Data->B);
		}
	}

	return true;
}

bool LoadTxtScript (tX_XML_Txt *Data,
					string Filename)
{
	TiXmlDocument Doc (Filename.c_str ());

	if (Doc.LoadFile () == false)
	{
		return false;
	}

	else
	{
		TiXmlElement *Root = Doc.RootElement ();
		TiXmlElement *Sub;

		string Type = Root->Attribute ("Type");

		if (Type != "Txt")
		{
			return false;
		}

		else
		{
			Sub = Root->FirstChildElement ("Font");
			const char *Tmp = Sub->Attribute ("Name");
			Data->Name.append (Tmp);
			Sub->Attribute ("Large", &Data->Large);

			Sub = Root->FirstChildElement ("Pos");
			Sub->Attribute ("X", &Data->PosX);
			Sub->Attribute ("Y", &Data->PosY);

			Sub = Root->FirstChildElement ("Color");
			Sub->Attribute ("R", &Data->R);
			Sub->Attribute ("G", &Data->G);
			Sub->Attribute ("B", &Data->B);

			Sub = Root->FirstChildElement ("Text");
			Tmp = Sub->FirstChild ()->ToText ()->Value ();
			Data->Text.append (Tmp);
			ReplaceCodes (&Data->Text);
		}
	}

	return true;
}

bool ReplaceCodes (string *str)
{
	const int Count = 7;
	string Codes[Count];
	Codes[0] = "-RET-";
	Codes[1] = "-AE-";
	Codes[2] = "-OE-";
	Codes[3] = "-UE-";
	Codes[4] = "-ae-";
	Codes[5] = "-oe-";
	Codes[6] = "-ue-";

	string RPC[Count];
	RPC[0] = "\n";
	RPC[1] = "Ä";
	RPC[2] = "Ö";
	RPC[3] = "Ü";
	RPC[4] = "ä";
	RPC[5] = "ö";
	RPC[6] = "ü";

	if (!str)
	{
		return false;
	}

	else
	{
		int j = 0;

		while (j <= Count)
		{
			int i = 0;

			while (str->find (Codes[j], i) != string::npos)
			{
				i = static_cast<int>(str->find (Codes[j], i));

				str->replace (i, Codes[j].size (), RPC[j], 0, RPC[j].size ());
			}

			j++;
		}
		return true;
	}
}