/*
Bot Game Options menu - server rules + bot settings for browser CS bot game
*/

#include "Framework.h"
#include "keydefs.h"
#include "Bitmap.h"
#include "Field.h"
#include "CheckBox.h"
#include "PicButton.h"
#include "SpinControl.h"
#include "model/StringArrayModel.h"
#include "Action.h"

#define ART_BANNER "gfx/shell/head_advoptions"

static const char *difficultyNames[] = {
	"Newbie", "Average", "Normal", "Professional", "Godlike"
};

static CStringArrayModel g_difficultyModel( difficultyNames, 5 );

class CMenuBotGameOptions : public CMenuFramework
{
public:
	CMenuBotGameOptions() : CMenuFramework( "CMenuBotGameOptions" ) { }

	// Bot settings
	CMenuField       botQuota;
	CMenuSpinControl botDifficulty;

	// Server rules
	CMenuField    startMoney;
	CMenuField    roundTime;
	CMenuField    buyTime;
	CMenuField    freezeTime;
	CMenuField    c4Timer;
	CMenuField    maxRounds;
	CMenuCheckBox friendlyFire;

private:
	void _Init() override;
	void _VidInit() override;
};

void CMenuBotGameOptions::_Init( void )
{
	banner.SetPicture( ART_BANNER );
	AddItem( banner );

	AddButton( L( "GameUI_OK" ), nullptr, PC_OK, VoidCb( &CMenuBotGameOptions::Hide ) );

	// --- Bot Settings ---

	// Bot count (1-9)
	botQuota.iMaxLength = 2;
	botQuota.bNumbersOnly = true;
	botQuota.szName = L( "Bot Count (1-9)" );
	botQuota.LinkCvar( "yb_quota" );

	// Bot difficulty (Newbie / Average / Normal / Professional / Godlike)
	botDifficulty.SetNameAndStatus( L( "Bot Difficulty" ), L( "0=Newbie  1=Average  2=Normal  3=Professional  4=Godlike" ) );
	botDifficulty.Setup( &g_difficultyModel );
	botDifficulty.LinkCvar( "yb_difficulty", CMenuEditable::CVAR_VALUE );

	// --- Server Rules ---

	startMoney.iMaxLength = 5;
	startMoney.bNumbersOnly = true;
	startMoney.szName = L( "Start Money" );
	startMoney.LinkCvar( "mp_startmoney" );

	roundTime.iMaxLength = 4;
	roundTime.szName = L( "Round Time (min)" );
	roundTime.LinkCvar( "mp_roundtime" );

	buyTime.iMaxLength = 4;
	buyTime.szName = L( "Buy Time (min)" );
	buyTime.LinkCvar( "mp_buytime" );

	freezeTime.iMaxLength = 3;
	freezeTime.bNumbersOnly = true;
	freezeTime.szName = L( "Freeze Time (sec)" );
	freezeTime.LinkCvar( "mp_freezetime" );

	c4Timer.iMaxLength = 3;
	c4Timer.bNumbersOnly = true;
	c4Timer.szName = L( "Bomb Timer (sec)" );
	c4Timer.LinkCvar( "mp_c4timer" );

	maxRounds.iMaxLength = 3;
	maxRounds.bNumbersOnly = true;
	maxRounds.szName = L( "Max Rounds" );
	maxRounds.LinkCvar( "mp_maxrounds" );

	friendlyFire.szName = L( "Friendly Fire" );
	friendlyFire.LinkCvar( "mp_friendlyfire" );

	AddItem( botQuota );
	AddItem( botDifficulty );
	AddItem( startMoney );
	AddItem( roundTime );
	AddItem( buyTime );
	AddItem( freezeTime );
	AddItem( c4Timer );
	AddItem( maxRounds );
	AddItem( friendlyFire );
}

void CMenuBotGameOptions::_VidInit( void )
{
	// Two columns: left (bot settings), right (server rules)
	int fieldW = 210;
	int fieldH = 32;
	int gap    = 65;

	int xL = 72,  yL = 260;  // left column: bot settings
	int xR = 350, yR = 260;  // right column: server rules

	botQuota.SetRect(     xL, yL, fieldW, fieldH ); yL += gap;
	botDifficulty.SetRect( xL, yL, fieldW, fieldH );

	startMoney.SetRect(   xR, yR, fieldW, fieldH ); yR += gap;
	roundTime.SetRect(    xR, yR, fieldW, fieldH ); yR += gap;
	buyTime.SetRect(      xR, yR, fieldW, fieldH ); yR += gap;
	freezeTime.SetRect(   xR, yR, fieldW, fieldH ); yR += gap;
	c4Timer.SetRect(      xR, yR, fieldW, fieldH ); yR += gap;
	maxRounds.SetRect(    xR, yR, fieldW, fieldH ); yR += gap;
	friendlyFire.SetCoord( xR, yR );
}

ADD_MENU( menu_botgameoptions, CMenuBotGameOptions, UI_BotGameOptions_Menu );
