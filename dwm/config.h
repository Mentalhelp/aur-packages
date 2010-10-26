#include <X11/XF86keysym.h>

/* appearance */
static const char font[]            = "-*-terminus-medium-*-*-*-12-*-*-*-*-*-*-*";
static const char normbordercolor[] = "#cccccc";
static const char normbgcolor[]     = "#cccccc";
static const char normfgcolor[]     = "#000000";
static const char selbordercolor[]  = "#305FA5";
static const char selbgcolor[]      = "#305FA5";
static const char selfgcolor[]      = "#ffffff";
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const Bool showbar           = True;     /* False means no bar */
static const Bool topbar            = True;     /* False means bottom bar */

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6" };

static const Rule rules[] = {
	/* class           instance    title       tags mask     isfloating   monitor */
	{ "Chromium",      NULL,       NULL,       1 << 1,       False,       -1 },
	{ "Namoroka",      NULL,       NULL,       1 << 1,       False,       -1 },
	{ "Firefox",       NULL,       NULL,       1 << 1,       False,       -1 },
	{ "Gmpc",          NULL,       NULL,       1 << 2,       False,       -1 },
	{ "Gxmessage",     NULL,       NULL,       0,            True,        -1 },
	{ "MPlayer",       NULL,       NULL,       0,            True,        -1 },
	{ "Truecrypt",     NULL,       NULL,       0,            True,        -1 },
	{ "Pidgin",        NULL,       NULL,       1 << 4,       False,       -1 },
	{ "Sonata",        NULL,       NULL,       1 << 2,       False,       -1 },
	{ "jd-Main",       NULL,       NULL,       1 << 5,       False,       -1 },
};

/* layout(s) */
static const float mfact      = 0.60;  /* factor of master area size [0.05..0.95] */
static const Bool resizehints = False; /* False means respect size hints in tiled resizals */

#include "bstack.c"
#include "bstackhoriz.c"
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
	{ "TTT",      bstack },
	{ "===",      bstackhoriz },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* commands */
//static const char *cmd[]  = { , NULL };
static const char *fileman[]  = { "tuxcmd", NULL };
static const char *browser[]  = { "chromium", NULL };
static const char *runcmd[] = { "dmenu_run", "-fn", font, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbgcolor, "-sf", selfgcolor, NULL };
static const char *terminal[]  = { "terminal-screen", NULL };

static const char *audiomute[]  = { "amixer","set","Master","togglemute",NULL };
static const char *audiovoldown[]  = { "amixer","set","Master","4%-",NULL };
static const char *audiovolup[]  = { "amixer","set","Master","4%+",NULL };
static const char *mpcnext[]  = { "mpc","next",NULL };
static const char *mpcprev[]  = { "mpc","prev",NULL };
static const char *mpcstop[]  = { "mpc","stop",NULL };
static const char *mpctoggle[]  = { "mpc","toggle",NULL };
static const char *mpcnp[]  = { "mpd-np-xsel",NULL };

static const char *lock[]  = { "slock",NULL };
static const char *suspend[]  = { "lock",NULL };

static const char *dmenushutdown[]  = { "dmenu_shutdown", "-fn", font, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbgcolor, "-sf", selfgcolor, NULL };
static const char *dmenumpd[]  = { "dmenu_mpd", "-fn", font, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbgcolor, "-sf", selfgcolor, NULL };
static const char *dmenupowerman[]  = { "dmenu_powerman", "-fn", font, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbgcolor, "-sf", selfgcolor, NULL };
static const char *dmenustats[]  = { "dmenu_stats", "-fn", font, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbgcolor, "-sf", selfgcolor, NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */

	{ MODKEY,                       XK_e,      spawn,          {.v = fileman } },
	{ MODKEY,                       XK_r,      spawn,          {.v = runcmd } },
	{ MODKEY,                       XK_q,      spawn,          {.v = terminal } },
	{ MODKEY,                       XK_w,      spawn,          {.v = browser } },

	{ Mod5Mask,                     XK_F11,    spawn,          {.v = lock } },
	{ Mod5Mask,                     XK_F12,    spawn,          {.v = suspend } },

	{ MODKEY,                       XK_y,      spawn,          {.v = dmenushutdown } },
	{ MODKEY,                       XK_x,      spawn,          {.v = dmenumpd } },
	{ MODKEY,                       XK_c,      spawn,          {.v = dmenupowerman } },
	{ MODKEY,                       XK_v,      spawn,          {.v = dmenustats } },

	{ 0, XF86XK_AudioMute,        spawn,        { .v = audiomute } },
	{ 0, XF86XK_AudioLowerVolume, spawn,        { .v = audiovoldown } },
	{ 0, XF86XK_AudioRaiseVolume, spawn,        { .v = audiovolup } },
	{ 0, XF86XK_AudioNext,        spawn,        { .v = mpcnext } },
	{ Mod5Mask, XK_F9,            spawn,        { .v = mpcnext } },
	{ 0, XF86XK_AudioPrev,        spawn,        { .v = mpcprev  } },
	{ Mod5Mask, XK_F8,            spawn,        { .v = mpcprev  } },
	{ 0, XF86XK_AudioStop,        spawn,        { .v = mpcstop } },
	{ Mod5Mask, XK_F11,           spawn,        { .v = mpcstop } },
	{ 0, XF86XK_AudioPlay,        spawn,        { .v = mpctoggle } },
	{ Mod5Mask, XK_F10,           spawn,        { .v = mpctoggle } },
	{ Mod5Mask, XK_n,             spawn,        { .v = mpcnp } },

	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.03} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.03} },
	{ MODKEY,                       XK_s,      zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_z,      setlayout,      {.v = &layouts[3]} },
	{ MODKEY,                       XK_n,      setlayout,      {.v = &layouts[4]} },
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
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};
