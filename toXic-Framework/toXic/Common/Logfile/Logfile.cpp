#include "Logfile.hpp"

// Konstruktor
//
// Aufgabe: Bisher noch keine
//
CLogfile::CLogfile ()
{

} // Konstruktor

// Destruktor
//
// Aufgabe: Gibt Ende-Meldung aus und schließ das Logfile
//
CLogfile::~CLogfile ()
{
	// Logfile-Ende schreiben und Datei schließen
	Textout ("<br><br>End of logfile</font></body></html>");
	fclose (m_Logfile);

} // Destruktor

// CreateLogfile
//
// Aufgabe: Logfile erstellen und Kopf schreiben
//
void CLogfile::CreateLogfile (string LogName)
{
	// Logfile leeren und Kopf schreiben
	m_Logfile = fopen (LogName.c_str (), "w");
	Textout ("<html><head><title>Logfile</title></head>");
	Textout ("<body><font face='courier new'>");
	WriteTopic ("Logfile", 3);

	// Aktuelle Build-Konfiguration ausgeben
	#ifdef _DEBUG
	Textout ("BUILD: DEBUG<br>");
	#else
	Textout ("BUILD: RELEASE<br>");
	#endif

	// Link für E-Mail-Adresse schreiben
	Textout ("<a href='mailto:wolfgang_neue@toxic-coding.de?subject=Logfile'>");
	Textout ("Send E-Mail to me</a><br><br>");

	// Logfile schließen und mit append wieder öffnen
	fclose (m_Logfile);
	m_Logfile = fopen (LogName.c_str (), "a");

} // CreateLogfile

// WriteTopic
//
// Aufgabe: Überschrift erzeugen
//
void CLogfile::WriteTopic (string Topic, int Size)
{
	// Überschrift schreiben und flushen
	Textout ("<table cellspacing='0' cellpadding='0' width='100%%' ");
	Textout ("bgcolor='#DFDFE5'>\n<tr>\n<td>\n<font face='arial' ");
	fTextout ("size='+%i'>\n", Size);
	Textout (Topic.c_str ());
	Textout ("</font>\n</td>\n</tr>\n</table>\n<br>");
	fflush (m_Logfile);

} // WriteTopic

// Textout
//
// Aufgabe: Text ins Logfile schreiben (schwarz)
//
void CLogfile::Textout (string Text)
{
	// Text schreiben und flushen
	fprintf (m_Logfile, Text.c_str ());
	fflush (m_Logfile);

} // Textout (schwarz)

// Textout
//
// Aufgabe: Text ins Logfile schreiben (farbig)
//
void CLogfile::Textout (int Color, string Text)
{
	Textout (Color, false, Text.c_str ());

} // Textout (farbig)

// Textout
//
// Aufgabe: Text ins Logfile schreiben (farbig, Liste)
//
void CLogfile::Textout (int Color, bool List, string Text)
{
	// Listen-Tag schreiben
	if (List == true)
	Textout ("<li>");

	// Farbtag schreiben
	switch (Color)
	{
		case BLACK:
			Textout ("<font color=black>");  break;
		case RED:
			Textout ("<font color=red>");    break;
		case GREEN:
			Textout ("<font color=green>");  break;
		case BLUE:
			Textout ("<font color=blue>");   break;
		case PURPLE:
			Textout ("<font color=purple>"); break;
	};

	// Text schreiben
	Textout (Text.c_str ());
	Textout ("</font>");

	if (List == false)
		Textout ("<br>");
	else
		Textout ("</li>");

} // Textout (farbig, liste)

// fTextout
//
// Aufgabe: formatierten Text ins Logfile schreiben (schwarz)
//
void CLogfile::fTextout (string Text, ...)
{
	char buffer[MAX_BUFFER];  // char-Buffer
	const char *Tmp = Text.c_str ();
	va_list pArgList;          // Liste der übergebenen Argumente

	// String aus den Argumenten erstellen
	va_start (pArgList, Tmp);
	vsprintf (buffer, Text.c_str (), pArgList);
	va_end (pArgList);

	// Erzeugten String schreiben
	Textout (buffer);

} // fTextout (schwarz)

// fTextout
//
// Aufgabe: formatierten Text ins Logfile schreiben (farbig)
//
void CLogfile::fTextout (int Color, string Text, ...)
{
	char buffer[MAX_BUFFER];  // char-Buffer
	const char *Tmp = Text.c_str ();
	va_list pArgList;          // Liste der übergebenen Argumente

	// String aus den Argumenten erstellen
	va_start (pArgList, Tmp);
	vsprintf (buffer, Text.c_str (), pArgList);
	va_end (pArgList);

	// Erzeugten String schreiben
	Textout (Color, buffer);

} // fTextout (farbig)

// fTextout
//
// Aufgabe: formatierten Text ins Logfile schreiben (farbig, Liste)
//
void CLogfile::fTextout (int Color, bool List, string Text, ...)
{
	char buffer[MAX_BUFFER];  // char-Buffer
	const char *Tmp = Text.c_str ();
	va_list pArgList;          // Liste der übergebenen Argumente

	// String aus den Argumenten erstellen
	va_start (pArgList, Tmp);
	vsprintf (buffer, Text.c_str (), pArgList);
	va_end (pArgList);

	// Erzeugten String schreiben
	Textout (Color, List, buffer);

} // fTextout (farbig, Liste)

// FunctionResult
//
// Aufgabe: OK oder ERROR für Funktionsaufruf ausgeben
//
void CLogfile::FunctionResult (string Name, bool Result)
{
	if (L_OK == Result)
	{
		Textout("<table width='100%%' cellSpacing='1' cellPadding='5'");
		Textout(" border='0' bgcolor='#C0C0C0'><tr><td bgcolor=");
		fTextout("'#FFFFFF' width='35%%'>%s</TD>", Name.c_str ());
		Textout("<td bgcolor='#FFFFFF' width='30%%'><font color =");
		Textout("'green'>OK</FONT></TD><td bgcolor='#FFFFFF' ");
		Textout("width='35%%'>-/-</TD></tr></table>");
	}
	else
	{
		Textout("<table width='100%%' cellSpacing='1' cellPadding='5'");
		Textout(" border='0' bgcolor='#C0C0C0'><tr><td bgcolor=");
		fTextout("'#FFFFFF' width='35%%'>%s</TD>", Name.c_str ());
		Textout("<td bgcolor='#FFFFFF' width='30%%'><font color =");
		Textout("'red'>ERROR</FONT></TD><td bgcolor='#FFFFFF' ");
		Textout("width='35%%'>-/-</TD></tr></table>");
	}

} // FunctionResult
