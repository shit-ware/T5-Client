// ==========================================================
// Project T5
// 
// Component: t5code
// Sub-component: clientdll
// Purpose: ISteamFriends007 implementation
//
// Initial author: NTAuthority
// Started: 2011-03-31
// ==========================================================

#include "stdinc.h"
#include "SteamFriends007.h"
#include <Winsock2.h>

static bool didRichPresence = false;
const char *CSteamFriends007::GetPersonaName()
{
	if (!didRichPresence)
	{
		if (*(DWORD*)0xA566A0 == 152) // T5 SP 7.0.152
		{

			NP_SetRichPresence("game", "t5s");
			NP_SetRichPresence("hostname", "Black Ops: Single player");
		
		} else {
		
			NP_SetRichPresence("game", "t5m");
			NP_SetRichPresence("hostname", "Black Ops: Multiplayer");
		
		}

		NP_StoreRichPresence();
		didRichPresence = true;
	}

	if (GAME_FLAG(GAME_FLAG_DEDICATED))
	{
		return "rzo Dedicated Server";
	}

	return Auth_GetUsername();
}

void CSteamFriends007::SetPersonaName( const char *pchPersonaName )
{
}

EPersonaState CSteamFriends007::GetPersonaState()
{
	return k_EPersonaStateOnline;
}

int CSteamFriends007::GetFriendCount( EFriendFlags iFriendFlags )
{
	return NP_GetNumFriends();
}

CSteamID CSteamFriends007::GetFriendByIndex( int iFriend, int iFriendFlags )
{
	return CSteamID(NP_GetFriend(iFriend));
}

EFriendRelationship CSteamFriends007::GetFriendRelationship( CSteamID steamIDFriend )
{
	if (NP_GetFriendName(steamIDFriend.ConvertToUint64()) != NULL)
	{
		return k_EFriendRelationshipFriend;
	}

	return k_EFriendRelationshipNone;
}

EPersonaState CSteamFriends007::GetFriendPersonaState( CSteamID steamIDFriend )
{

	switch (NP_GetFriendPresence(steamIDFriend.ConvertToUint64()))
	{
		case PresenceStateOnline:
			return k_EPersonaStateOnline;
		case PresenceStateAway:
			return k_EPersonaStateAway;
		case PresenceStateExtendedAway:
			return k_EPersonaStateSnooze;
	}

	return k_EPersonaStateOffline;
}

const char *CSteamFriends007::GetFriendPersonaName( CSteamID steamIDFriend )
{
	//return steamIDFriend.Render();

	const char* username = NP_GetFriendName(steamIDFriend.ConvertToUint64());
	if (username == NULL) {
		return "Unkown soldier:";
	} else {
		return username;
	}
}

int CSteamFriends007::GetSmallFriendAvatar( CSteamID steamIDFriend )
{
	return 0;
}

int CSteamFriends007::GetMediumFriendAvatar( CSteamID steamIDFriend )
{
	return 0;
}

int CSteamFriends007::GetLargeFriendAvatar( CSteamID steamIDFriend )
{
	return 0;
}

int GetLocalPort(int sockfd, unsigned short& port)
{
	struct sockaddr_in sin;
	int sinlen = sizeof(sin);

	memset(&sin, 0, sizeof(sin));

	if (getsockname(sockfd, (struct sockaddr*) &sin, &sinlen) == 0 && sin.sin_family == AF_INET)
	{
		port = ntohs(sin.sin_port);
		return 0;
	}

	return 4;
}

bool CSteamFriends007::GetFriendGamePlayed( CSteamID steamIDFriend, FriendGameInfo_t *pFriendGameInfo )
{
	const char* friendGame = NP_GetFriendRichPresence(steamIDFriend.ConvertToUint64(), "game");

	if (friendGame && !stricmp(friendGame, "t5m"))
	{
		pFriendGameInfo->m_gameID = CGameID(42710);
		pFriendGameInfo->m_steamIDLobby = CSteamID(steamIDFriend.GetAccountID(), 0x40000, k_EUniversePublic, k_EAccountTypeChat);
		pFriendGameInfo->m_unGameIP = inet_addr(NP_GetFriendRichPresence(steamIDFriend.ConvertToUint64(), "current_server"));
		GetLocalPort(pFriendGameInfo->m_unGameIP, pFriendGameInfo->m_usGamePort);
		pFriendGameInfo->m_usQueryPort = pFriendGameInfo->m_usGamePort;
		Com_Printf(0, "m_unGameIP: %d, m_usGamePort: %d", pFriendGameInfo->m_unGameIP, pFriendGameInfo->m_usGamePort);
	}

	if (friendGame && !stricmp(friendGame, "t5s"))
	{
		pFriendGameInfo->m_gameID = CGameID(42700);
		pFriendGameInfo->m_steamIDLobby = CSteamID(steamIDFriend.GetAccountID(), 0x40000, k_EUniversePublic, k_EAccountTypeChat);
		pFriendGameInfo->m_unGameIP = inet_addr(NP_GetFriendRichPresence(steamIDFriend.ConvertToUint64(), "current_server"));
		GetLocalPort(pFriendGameInfo->m_unGameIP, pFriendGameInfo->m_usGamePort);
		pFriendGameInfo->m_usQueryPort = pFriendGameInfo->m_usGamePort;
		Com_Printf(0, "m_unGameIP: %d, m_usGamePort: %d", pFriendGameInfo->m_unGameIP, pFriendGameInfo->m_usGamePort);
	}
	return true;
}

const char *CSteamFriends007::GetFriendPersonaNameHistory( CSteamID steamIDFriend, int iPersonaName )
{
	return "";
}

bool CSteamFriends007::HasFriend( CSteamID steamIDFriend, EFriendFlags iFriendFlags )
{
	return true;
}

int CSteamFriends007::GetClanCount()
{
	return 0;
}

CSteamID CSteamFriends007::GetClanByIndex( int iClan )
{
	return CSteamID();
}

const char *CSteamFriends007::GetClanName( CSteamID steamIDClan )
{
	return "RepZ";
}

const char *CSteamFriends007::GetClanTag( CSteamID steamIDClan )
{
	return "RepZ";
}

int CSteamFriends007::GetFriendCountFromSource( CSteamID steamIDSource )
{
	return 0;
}

CSteamID CSteamFriends007::GetFriendFromSourceByIndex( CSteamID steamIDSource, int iFriend )
{
	return CSteamID();
}

bool CSteamFriends007::IsUserInSource( CSteamID steamIDUser, CSteamID steamIDSource )
{
	return false;
}

void CSteamFriends007::SetInGameVoiceSpeaking( CSteamID steamIDUser, bool bSpeaking )
{

}

void CSteamFriends007::ActivateGameOverlay( const char *pchDialog )
{

}

void CSteamFriends007::ActivateGameOverlayToUser( const char *pchDialog, CSteamID steamID )
{

}

void CSteamFriends007::ActivateGameOverlayToWebPage( const char *pchURL )
{

}

void CSteamFriends007::ActivateGameOverlayToStore( AppId_t nAppID )
{

}

void CSteamFriends007::SetPlayedWith( CSteamID steamIDUserPlayedWith )
{

}

void CSteamFriends007::ActivateGameOverlayInviteDialog( CSteamID steamIDLobby ) {}