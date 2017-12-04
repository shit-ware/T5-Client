#include "stdinc.h"
#include <fstream>
#include <string>

char* botsNames[20];

void PatchT5_Bots()
{
	char** combatTraining = (char**)0xBFD4B0;

	std::ifstream file("bots.txt");
	std::string str;
	if (file)
	{
		while (std::getline(file, str))
		{
			for (int i = 0; i < 20; i++)
			{
				strcpy(botsNames[i], str.c_str());
			}
		}

		for (int i2 = 0; i2 < 20; i2++)
		{
			combatTraining[i2] = botsNames[i2];
		}
	}
	else
	{
		combatTraining[0] = "RepZ Ta$y";
		combatTraining[1] = "Fragz";
		combatTraining[2] = "RZT";
		combatTraining[3] = "WildHOG";
		combatTraining[4] = "Dualtorch";
		combatTraining[5] = "Alex";
		combatTraining[6] = "Fl0w";
	}

	strcpy((char*)0xA78F98, "connect \"\\cg_predictItems\\1\\cl_punkbuster\\0\\cl_anonymous\\0\\color\\4\\head\\default\\model\\multi\\snaps\\20\\rate\\25000\\name\\%s\\clanAbbrev\\iNT\\bdOnlineUserID\\%s\\protocol\\%d\\qport\\%d\"");
}