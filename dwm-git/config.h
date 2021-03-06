/* See LICENSE file for copyright and license details. */

/* appearance */
static const char font[]            = "-*-terminus-medium-*-*-*-12-*-*-*-*-*-*-*";
static const char normbordercolor[] = "#000000";
static const char normbgcolor[]     = "#393939";
static const char normfgcolor[]     = "#dddddd";
static const char selbordercolor[]  = "#494949";
//static const char selbgcolor[]      = "#222222";
static const char selbgcolor[]      = "#494949";
static const char selfgcolor[]      = "#dddddd";
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const Bool showbar           = True;     /* False means no bar */
static const Bool topbar            = True;     /* False means bottom bar */

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Chromium", NULL,       NULL,       1 << 1,       False,       -1 },
	{ "Ario",     NULL,       NULL,       1 << 2,       False,       -1 },
	{ "Firefox",  NULL,       NULL,       1 << 5,       False,       -1 },
	{ "Gxmessage",NULL,       NULL,       0,            True,        -1 },
	{ "MPlayer",  NULL,       NULL,       0,            True,        -1 },
	{ "trayer",   NULL,       NULL,       1 << 5,       False,       -1 },
};

/* layout(s) */
static const float mfact      = 0.60;  /* factor of master area size [0.05..0.95] */
static const int nmaster      = 1;    /* number of clients in master area */
static const Bool resizehints = False; /* True means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#include <X11/XF86keysym.h>
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static const char *terminal[]  = { "terminal-tmux", NULL };
static const char *fileman[]  = { "thunar", NULL };
static const char *browser[]  = { "chromium", NULL };
static const char *runcmd[] = { "dmenu_run", "-fn", font, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbgcolor, "-sf", selfgcolor, NULL };

static const char *mpcnext[]  = { "mpc","next",NULL };
static const char *mpcprev[]  = { "mpc","prev",NULL };
static const char *mpcstop[]  = { "mpc","stop",NULL };
static const char *mpctoggle[]  = { "mpc","toggle",NULL };

static const char *voldown[]  = { "amixer","-D","pulse","set","Master","2%-",NULL };
static const char *volup[]  = { "amixer","-D","pulse","set","Master","2%+",NULL };
static const char *volmute[]  = { "amixer","-D","pulse","set","Master","togglemute",NULL };

static const char *suspend[]  = { "lock-suspend",NULL };
static const char *hibernate[]  = { "lock-hibernate",NULL };
static const char *lock[]  = { "lock",NULL };

static const char *dmenunetcfg[]  = { "dmenu_netcfg", "-fn", font, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbgcolor, "-sf", selfgcolor, NULL };
static const char *dmenumpd[]  = { "dmenu_mpd", "-fn", font, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbgcolor, "-sf", selfgcolor, NULL };
static const char *dmenupowerman[]  = { "dmenu_powerman", "-fn", font, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbgcolor, "-sf", selfgcolor, NULL };
static const char *dmenustats[]  = { "dmenu_stats", "-fn", font, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbgcolor, "-sf", selfgcolor, NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_q,      spawn,          {.v = terminal } },
	{ MODKEY,                       XK_w,      spawn,          {.v = browser } },
	{ MODKEY,                       XK_e,      spawn,          {.v = fileman } },
	{ MODKEY,                       XK_r,      spawn,          {.v = runcmd } },
	{ Mod5Mask,                     XK_F3,     spawn,          {.v = suspend } },
	{ Mod5Mask,                     XK_F4,     spawn,          {.v = hibernate } },
	{ Mod5Mask,                     XK_F12,    spawn,          {.v = lock } },
	{ MODKEY,                       XK_y,      spawn,          {.v = dmenunetcfg } },
	{ MODKEY,                       XK_x,      spawn,          {.v = dmenumpd } },
	{ MODKEY,                       XK_c,      spawn,          {.v = dmenupowerman } },
	{ MODKEY,                       XK_v,      spawn,          {.v = dmenustats } },
	{ 0, XF86XK_AudioNext, spawn, { .v = mpcnext } },
	{ 0, XF86XK_AudioPrev, spawn, { .v = mpcprev } },
	{ 0, XF86XK_AudioStop, spawn, { .v = mpcstop } },
	{ 0, XF86XK_AudioPlay, spawn, { .v = mpctoggle } },
	{ 0, XF86XK_AudioLowerVolume, spawn, { .v = voldown } },
	{ 0, XF86XK_AudioRaiseVolume, spawn, { .v = volup } },
	{ 0, XF86XK_AudioMute, spawn, { .v = volmute } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.03} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.03} },
	{ MODKEY,                       XK_s,      zoom,           {0} },
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
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
};

/* button definitions */
/* click can be ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = terminal } },
	{ ClkStatusText,        0,              Button3,        spawn,          {.v = volmute } },
	{ ClkStatusText,        0,              Button4,        spawn,          {.v = volup } },
	{ ClkStatusText,        0,              Button5,        spawn,          {.v = voldown } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

