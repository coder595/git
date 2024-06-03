/* See LICENSE file for copyright and license details. */

/* appearance */
static unsigned int borderpx  = 1;        /* border pixel of windows */
static unsigned int snap      = 32;       /* snap pixel */
static int showbar            = 1;        /* 0 means no bar */
static int topbar             = 0;        /* 0 means bottom bar */

static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayonleft = 0;    /* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;        /* 0 means no systray */

static const char *fonts[]          = { "FontAwesome:size=14", "monospace:size=14" };
//static const char *fonts[] = { "monospace:size=10", "FontAwesome:size=14" };
static const char dmenufont[]       = "monospace:size=14";

static char normbgcolor[]           = "black";
static char normbordercolor[]       = "blue";
static char normfgcolor[]           = "lightgreen";
static char selfgcolor[]            = "white";
static char selbordercolor[]        = "yellow";
static char selbgcolor[]            = "red";
static char *colors[][3] = {
       /*               fg           bg           border   */
       [SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor },
       [SchemeSel]  = { selfgcolor,  selbgcolor,  selbordercolor  },
};

/* Extra Colors */
static char extra_1[]            = "red";

/*screenshot */
static const char *screenshot[] = {"scrot", "/home/muhammad/Pictures/Screenshots/%Y-%m-%d-%T-screenshot.png",NULL};

/* tagging */
static const char *tags[] = { "", "2", "3", "4", "5", "6" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static int nmaster     = 0;    /* number of clients in master area */
static int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "",        tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define ALTKEY Mod1Mask  // Alt key
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/bash", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", extra_1, "-sf", selfgcolor, NULL };
static const char *termcmd[]  = { "alacritty", NULL };
/* Extra Commands */
static const char *firefoxcmd[]  = { "firefox-esr", NULL };
static const char *slockcmd[]    = { "slock", NULL };
static const char *chatgptcmd[]  = { "thorium-browser", "--profile-directory=Profile 3",  "--app=https://chat.openai.com", NULL };
static const char *whatsapp[]  = { "thorium-browser", "--profile-directory=Profile 3", "--app=https://web.whatsapp.com", NULL };
static const char *filemanager[]  = { "pcmanfm", NULL };
static const char *my_github[]  = { "brave-browser-nightly", "--app=https://github.com/", NULL };
static const char *discordcmd[]  = { "brave-browser-nightly", "--app=https://discord.com/channels/@me", NULL };
//static const char *discordcmd[]  = { "flatpak", "run", "com.discordapp.Discord", NULL };
/* volume controls */
static const char *upvol[]   = { "amixer", "-q", "sset", "Master", "5%+", NULL };
static const char *downvol[] = { "amixer", "-q", "sset", "Master", "5%-", NULL };
static const char *mutevol[] = { "amixer", "-q", "sset", "Master", "toggle", NULL };
static const char *unmutevol[] = { "amixer", "-q", "sset", "Master", "unmute", NULL };

/*
 * Xresources preferences to load at startup
 */
ResourcePref resources[] = {
		{ "normbgcolor",        STRING,  &normbgcolor },
		{ "normbordercolor",    STRING,  &normbordercolor },
		{ "normfgcolor",        STRING,  &normfgcolor },
		{ "selbgcolor",         STRING,  &selbgcolor },
		{ "selbordercolor",     STRING,  &selbordercolor },
		{ "selfgcolor",         STRING,  &selfgcolor },
		{ "borderpx",          	INTEGER, &borderpx },
		{ "snap",          	INTEGER, &snap },
		{ "showbar",          	INTEGER, &showbar },
		{ "topbar",          	INTEGER, &topbar },
		{ "nmaster",          	INTEGER, &nmaster },
		{ "resizehints",       	INTEGER, &resizehints },
		{ "mfact",      	 	FLOAT,   &mfact },
};

static const Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_a,      spawn,          {.v = dmenucmd } },
	/* Keybindings for Extra Commands/Apps ------------------------------------- */
	{ MODKEY,                	XK_q,      spawn,          {.v = firefoxcmd } },
	{ MODKEY, 			XK_l,      spawn, 	   {.v = slockcmd } },
	{ MODKEY, 			XK_g, 	   spawn, 	   {.v = chatgptcmd } },
	{ MODKEY, 			XK_w, 	   spawn, 	   {.v = whatsapp } },
	{ MODKEY, 			XK_e, 	   spawn, 	   {.v = filemanager } },
	{ MODKEY|ShiftMask, 		XK_g, 	   spawn, 	   {.v = my_github } },
	{ MODKEY|ShiftMask,             XK_d,      spawn,          {.v = discordcmd } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_F8,     spawn,          {.v = upvol   } },
        { MODKEY,                       XK_F7,     spawn,          {.v = downvol } },
        { MODKEY,                       XK_F5,     spawn,          {.v = mutevol } },
	{ MODKEY,                       XK_F6,     spawn,          {.v = unmutevol } },
	/* ------------------------------------------------------------------------- */
	{0,                             XK_Print,  spawn,	   {.v = screenshot } },
  	{ MODKEY,                       XK_p,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};


