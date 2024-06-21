/*
* Als erstes kommt der Include-W�chter.
* Mit #ifndef wird �berpr�ft, ob tX_PROCESS_BASE bereits definiert wurde.
* ifndef => if not defined
* Falls tX_PROCESS_BASE noch nicht definiert wurde, wird der Begriff jetzt definiert
* und alles, was darauf folgt, bis mit #endif die if-Bedingung geschlossen wird.
* Alle Befehle, die mit # anfangen, sind Pr�prozessoranweisungen.
* Sie werden ausgef�hrt, bevor der Code aktiviert wird.
* Wenn diese Datei mehrmals geladen wird, kommt es nicht zu Problemen,
* da der Include-W�chter verhindert, dass der eigentliche Code in dieser Datei
* mehrmals erscheint.
*/
#ifndef tX_PROCESS_BASE
#define tX_PROCESS_BASE

/*
* Mit namespace tX wird der Namensbereich "tX" deklariert.
* Namensbereiche werden benutzt, um Namen von Variablen, Funktionen und Klassen,
* die woanders eventuell bereits auftauchen k�nnten, eindeutig zu kennzeichnen.
* Ausserhalb des Namensbereichs wird z.B. auf die Klasse "Process_Base"
* mittels "tX::Process_Base" zugegriffen.
*/
namespace tX
{
	// Klassendeklaration und -definition
	/*
	* Diese Klasse dient als Basisklasse, die selbst nicht benutzt wird.
	* Eine Basisklasse vererbt ihre Funktionen und Variablen an ihre Kinderklassen
	* Nur Funktionen und Variablen, die public oder protected sind, werden vererbt.
	* Warum die Vererbung in diesem Fall Sinn macht, siehst du sp�ter beim Prozessmanager
	*/
	class Process_Base
	{
		/*
		* Auf Funktionen und Variablen, die public sind,
		* kann man auch au�erhalb der Klasse zugreifen.
		*/
		public:
			// Konstruktor
			Process_Base() { this->m_bActive = false; this->m_pNext = NULL; this->m_nNextValue = 0; }

			// Destruktor
			/*
			* Die Funktion, in diesem Fall der Destruktor, wird als virtual deklariert.
			* Wenn die Instanz einer Kinderklasse eine Funktion aufruft,
			* die durch die Basisklasse vererbt wurde, wird als erstes die Funktion
			* der Basisklasse aufgerufen, dann erst die eigene Funktion mit dem gleichen Namen.
			* Wenn die Funktion in der Basisklasse als virtual deklariert wurde,
			* wird sie innerhalb der Kinderklasse durch die eigene Funktion ersetzt.
			*/
			virtual ~Process_Base() {}

			/*
			* Die Funktion "Start" soll den Prozess starten.
			* Die Variable "Value" kann benutzt werden, um Werte zu �bergeben.
			* Diese Variable ist hier deklariert worden,
			* damit sie in allen Kinderklassen verf�gbar ist.
			*/
			virtual void Start(int Value) {} // Some classes don't need the parameter

			/*
			* Die Funktion "Update" soll den Prozess aktualisieren.
			* Die Variable "Elapsed" wird benutzt, um dem Prozess die Zeit mitzuteilen,
			* die seit der letzten Aktualisierung des Prozesses vergangen ist.
			*/
			virtual void Update(float Elapsed) {}

			/*
			* Prozess festlegen, der nach Beendigung dieses Prozesses gestartet werden soll.
			*/
			void SetNext(Process_Base* Process, int Value) { m_pNext = Process; m_nNextValue = Value; }

			/*
			* Die Funktion "GetNext" gibt als R�ckgabewert den Prozess zur�ck,
			* der nach diesem Prozess gestartet werden soll.
			*/
			Process_Base* const GetNext() { return m_pNext; }

			/*
			* Die Funktion "GetNextValue" gibt als R�ckgabewert den Wert zur�ck,
			* mit dem der n�chste Prozess gestartet werden soll (siehe Start(int Value)).
			*/
			int GetNextValue() { return m_nNextValue; }

			/*
			* Die Funktion "IsActive" gibt als R�ckgabewert den Zustand des Prozesses zur�ck.
			*/
			bool IsActive() { return m_bActive; }

			/*
			* Die Funktion "HasNext" gibt als R�ckgabewert zur�ck, ob dieser Prozess
			* einen ihm zugewiesenen Nachfolgeprozess besitzt.
			*/
			bool HasNext() { return m_pNext != 0 ? true : false; }

			/*
			* Die Funktion "Kill" soll Prozesse stoppen k�nnen.
			*/
			virtual void Kill() {}

		/*
		* Auf Funktionen und Variablen, die protected sind,
		* kann man nur innerhalb der Basis- und der Kinderklasse zugreifen.
		*/
		protected:
			/*
			* Die Variable "m_bActive" repr�sentiert den Zustand des Prozesses.
			* Aktiv => true
			* Nicht aktiv => false
			*/
			bool m_bActive;

			/*
			* Die Variable "m_pNext" ist der Nachfolgeprozess.
			* Falls kein Nachfolgeprozess zugewiesen wurde, ist die Variable,
			* bzw. der Zeiger leer.
			*/
			Process_Base* m_pNext;

			/*
			* Die Variable "m_nNextValue" enth�lt den Wert, der dem Nachfolgeprozess
			* beim Start �bergeben werden soll.
			*/
			int m_nNextValue;
	};
}
/* Ende des Include-W�chters */
#endif