//Задание: Во входном файле содержится некоторый текст.
//Преобразовать данный текст в код HTML, вывести его в выходной файл и возвратить файл с расширением .htm.
//******* Болдырев Александр 13501/3 *******

#include <fstream>
#include <iostream>
#include <stdio.h>

using namespace std;

//==== Main function decomposition ====

void MainGen	();
void HeadGen	();
void BodyGen	();
void TextGen	();
void H1Gen	();
void H2Gen	();
void SimpListGen();
void NumListGen	();
void ListItemGen();
void TabGen	();
void Enters	();
void ItGen	();
void BItGen	();
void Closer	();

//==== Files which we are using ====

ifstream iFile("Input.txt");
ofstream oFile("Result.htm");

//==== Global variables ====

char sym[1];
char lists[50];					//ul = "u", ol = "o". Oh yes, Cap! ;)
bool hdrsng 	= false;
bool hdrdbl 	= false;
int  tabs 	= 0;
bool aftertab 	= false;
int  inlist 	= 0;
int  inlistp 	= 0;
bool inli 	= false;
bool index 	= false;
bool inpar 	= false;
bool first 	= true;
bool it 	= false;
bool bit 	= false;

//==== The main program ====

int main()
{
    //==== Input/output setup ====
    
    if (!iFile)
    {
        cout << "Error: input file does not exist!" << endl;
        return 1;
    }
    if (!oFile)
    {
        cout << "Error: output file is unavailable!" << endl;
        return 2;
    }

    //==== Main algorithm ====
    
    MainGen();
    return 0;
}

//============ AUXILARY FUNCTIONS ============

//==== The main function ====

void MainGen()
{
    oFile << "<!DOCTYPE html>\n";
    oFile << "<HTML>\n";
    HeadGen();
    BodyGen();
    oFile << "\n</HTML>\n";
}

//==== The header creating function ====

void HeadGen()
{
    oFile << "\n<HEAD>\n";
    oFile << "\t<meta charset = \"utf-8\">\n";
    oFile << "\t<title>==== HTMLer Results ====</title>\n";
    oFile << "</HEAD>\n";
}

//==== The body creating function ====

void BodyGen()
{
    oFile << "\n<BODY bgcolor = \"#000000\" text = \"#00FF00\">\n";
    sym[1] = '\0';
    TextGen();
    oFile << "\n</BODY>\n";
}

//==== The inner component of the body ====

void TextGen()
{
    iFile.get(sym[0]);
    if (!iFile.eof())
    {
       if (first)
       {
            first = false;
            aftertab = false;
	    switch (sym[0])
            {
                case '\"':
                    inlist = 0;
                    if (inlist < inlistp) Closer();
                    hdrdbl = true;
                    H1Gen();
                    break;
                case '\'':
                    inlist = 0;
                    if (inlist < inlistp) Closer();
                    hdrsng = true;
                    H2Gen();
                    break;
                case '*':
                case '-':
                case '+':
                    SimpListGen();
                    break;
                case '0'...'9':
                	index = true;
                	TextGen();
                    break;
                case '\x09':
                    TabGen();
                    break;
                case '\x0A':
                    Enters();
                    break;
                default:
                    inlist = 0;
                    if (inlist < inlistp) Closer();
                    oFile << "\n<p>" << sym[0];
                    inpar = true;
                    TextGen();
            }
        }
        else
        {
            switch (sym[0])
            {
                case '\"':
                    aftertab = false;
                    if (hdrdbl)
                    {
                        hdrdbl = false;
                        H1Gen();
                    }
		    else BItGen();
                    break;
                case '\'':
                    aftertab = false;
                    if (hdrsng)
                    {
                        hdrsng = false;
                        H2Gen();
                    }
                    else ItGen();
                    break;
                case '*':
                case '-':
                case '+':
                    if (aftertab) SimpListGen();
                    else
                    {
                        oFile << sym[0];
                        TextGen();
                    }
                    break;
                case '0'...'9':
		    if (aftertab)
		    {
			index = true;
			TextGen();
		    }
                    if (!index)
	    	    {
			aftertab = false;
			oFile << sym[0];
			TextGen();
	       	    }
                    break;
		case '.':
	    	    if (index)
	 	    {
			index = false;
			NumListGen();
		    }
		    else
		    {
			aftertab = false;
			oFile << sym[0];
			TextGen();
		    }
		    break;
                case '\x09':
                    TabGen();
                    break;
                case '\x0A':
                    aftertab = false;
                    Enters();
                    break;
                default:
                    aftertab = false;
                    oFile << sym[0];
                    TextGen();
            }
        }
    }
}

//==== Wraps a header in the 1 level "<h1></h1>" tags ====

void H1Gen()
{
    if (hdrdbl) oFile << "<h1>";
    else oFile << "</h1>";
    TextGen();
}

//==== Wraps a header in the 2 level "<h2></h2>" tags ====

void H2Gen()
{
    if (hdrsng) oFile << "<h2>";
    else oFile << "</h2>";
    TextGen();
}

//==== Treatment of the italic text placed in the unary quotes ====

void ItGen()
{
    it = !it;
    if (it)  oFile << "<i>";
    oFile << sym[0];
    if (!it) oFile << "</i>";
    TextGen();
}

//==== Treatment of the italic text placed in the double quotes ====

void BItGen()
{
    bit = !bit;
    if (bit) oFile << "<b><i>";
    oFile << sym[0];
    if(!bit) oFile << "</i></b>";
    TextGen();
}

//==== Wraps a list in the "<ul></ul>" tags ====

void SimpListGen()
{
    inlistp = inlist;
    inlist  = tabs + 1;
    int i   = inlist;
    if (inlist > inlistp)
    {
    	lists[inlist] = 'u';
    	oFile << '\n';
    	for (i; i != 0; i--) oFile << '\t';
    	oFile << "<ul>";
    }
	if (inlist < inlistp) Closer();
    ListItemGen();
}

//==== Wraps a list in the "<ol></ol>" tags ====

void NumListGen()
{
    inlistp = inlist;
    inlist  = tabs + 1;
    int i   = inlist;
    if (inlist > inlistp)
    {
    	lists[inlist] = 'o';
    	oFile << '\n';
    	for (i; i != 0; i--) oFile << '\t';
    	oFile << "<ol>";
    }
	if (inlist < inlistp) Closer();
    ListItemGen();
}

//==== Adds a tag to an element of the list ====

void ListItemGen()
{
    int i = inlist;
    oFile << '\n';
    for (i; i != 0; i--) oFile << '\t';
    oFile << "<li>";
    inli  = true;
    TextGen();
}

//==== Treatment of the tabs ====

void TabGen()
{
    if (inlist <= 0)
    {
    	if (tabs == 0) oFile << "<br />\n";
    	oFile << "&nbsp; &nbsp; &nbsp; &nbsp;";
    }
    tabs++;
    aftertab = true;
    TextGen();
}

//==== Treatment of the enters ====

void Enters()
{
    if (inli)
    {
    	oFile << "</li>";
    	inli = false;
    }
    if (inpar)
    {
	oFile << "</p>\n";
	inpar = false;
    }
    first = true;
    oFile << " E[" << inlist << "_" << inlistp << "; type = " << lists[inlist] << "]";    	//==== Trace for the Enters() ====
    tabs = 0;
    TextGen();
}

//==== Putting of the closer tags ====

void Closer()
{
    oFile << " C[" << inlist << "_" << inlistp << "]";                                    	//==== Trace for the Closer() ====
    int inls = inlistp;
    for (inls; inls != inlist; inls--)
    {
	oFile << '\n';
	int i = inls;
	for (i; i != 0; i--) oFile << '\t';
	switch (lists[inls])
	{
	case 'u':
	    oFile << "</ul>\n";
	    break;
	case 'o':
	    oFile << "</ol>\n";
	    break;
	default: oFile << "Cthulhu has devoured thy brainz s0m3h0w... h0w?... ";
        }
    inlistp--;
    }
}
