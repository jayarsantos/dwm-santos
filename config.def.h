/* See LICENSE file for copyright and license details. */

static const char *const autostart[] = {
	"wal", "-R", NULL,
	"slstatus", NULL,
	"/usr/lib/polkit-gnome/polkit-gnome-authentication-agent-1", NULL,
	"xfce4-power-manager", NULL,
	"picom", "--config", "~/.config/picom.conf", "--animations", "-b", NULL,
	"nm-applet", NULL,
	"keepassxc"
	"udiskie", "-as", "--appindicator", NULL,
	"light-locker", NULL,
	"thunar", "--daemon", NULL,
	"sh", "-c", "~/.config/pywal/wallpaperchanger.sh update", NULL,
	NULL /* terminate */
};

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int gappih    = 20;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 10;       /* vert inner gap between windows */
static const unsigned int gappoh    = 10;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 30;       /* vert outer gap between windows and screen edge */
static       int smartgaps          = 1;        /* 1 means no outer gap when there is only one window */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "MesloLGS Nerd Font Mono:size=10", "NotoColorEmoji:pixelsize=10:antialias=true:autohint=true"  };
static const char dmenufont[]       = "FiraCode Nerd Font:size=10";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
static const char col_urgborder[]   = "#ff0000";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
	[SchemeUrg]  = { col_gray4, col_cyan,  col_urgborder  },
};

typedef struct {
	const char *name;
	const void *cmd;
} Sp;
const char *spcmd1[] = {"st", "-n", "spterm", "-g", "120x30", NULL };
const char *spcmd2[] = {"st", "-n", "spfm", "-g", "120x30", "-e", "ranger", NULL };
const char *spcmd3[] = {"keepassxc", NULL };
const char *spcmd4[] = {"pavucontrol", NULL };
const char *spcmd5[] = {"pcmanfm", NULL };
const char *spcmd6[] = {"st", "-n", "sptop", "-g", "120x30", "-e", "btop", NULL };
static Sp scratchpads[] = {
	/* name          cmd  */
	{"spterm",      spcmd1},
	{"spranger",    spcmd2},
	{"keepassxc",   spcmd3},
	{"pavucontrol", spcmd4},
	{"pcmanfm", 		spcmd5},
	{"sptop", 	  	spcmd6},
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };
static const int taglayouts[] = { 11, 6, 1, 13, 6, 0, 0, 0, 0 };
static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",	       NULL,			   NULL,		   0,				       1,			     -1 },
	{ NULL,          NULL,   "Picture-in-Picture", 7, 				 1, 				 -1 },    
	{ "firefox",     NULL,			   NULL,		   1 << 1,			   0,			     -1 },
	{ "Chromium",    NULL,			   NULL,		   1 << 1,			   0,			     -1 },
	{ "qutebrowser", NULL,			   NULL,		   1 << 1,			   0,			     -1 },
	{ "Thunar",      NULL,			   NULL,		   1 << 2,			   1,			     -1 },
	{ "thunderbird", NULL,   			 NULL,  		 1 << 4, 				 0, 				 -1 },
	{ "steam", 			 NULL,			   NULL,		   1 << 4,			   1,			     -1 },
	{ "Clementine",  NULL,			   NULL,		   1 << 5,			   1,			     -1 },
	{ NULL,		     "spterm",		   NULL,		   SPTAG(0),		   1,			     -1 },
	{ NULL,		     "spfm",		     NULL,		   SPTAG(1),		   1,			     -1 },
	{ NULL,		     "keepassxc",    NULL,		   SPTAG(2),		   1,			     -1 },
	{ NULL,		     "pavucontrol",  NULL,		   SPTAG(3),		   1,			     -1 },
	{ NULL,		     "pcmanfm",      NULL,		   SPTAG(4),		   1,			     -1 },
	{ NULL,		     "sptop",        NULL,		   SPTAG(5),		   1,			     -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 0; /* 1 will force focus on the fullscreen window */

#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",  	/* 0 */    tile },    /* first entry is default */
	{ "[M]",    /* 1 */ 	 monocle },
	{ "[@]",    /* 2 */ 	 spiral },
	{ "[\\]",   /* 3 */ 	 dwindle },
	{ "H[]",    /* 4 */ 	 deck },
	{ "TTT",    /* 5 */    bstack },
	{ "===",    /* 6 */  	 bstackhoriz },
	{ "HHH",    /* 7 */  	 grid },
	{ "###",    /* 8 */  	 nrowgrid },
	{ "---",    /* 9 */  	 horizgrid },
	{ ":::",    /* 10 */   gaplessgrid },
	{ "|M|",    /* 11 */   centeredmaster },
	{ ">M>",    /* 12 */   centeredfloatingmaster },
	{ "><>",    /* 13 */   NULL },    /* no layout function means floating behavior */
	{ NULL,       				 NULL },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *launchercmd[] = { "rofi", "-show", "drun", NULL };
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, NULL };
static const char *termcmd[]  = { "st", NULL };
static const char *webcmd[]  = { "qutebrowser", NULL };

#include "movestack.c"
static const Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_r,      spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_y,      spawn,          {.v = launchercmd} }, // spawn rofi for launching other programs
	{ MODKEY|ControlMask,           XK_b,      spawn,          {.v = webcmd } },
	{ MODKEY,    					          XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_j,      movestack,      {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_k,      movestack,      {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_h,      setcfact,       {.f = +0.25} },
	{ MODKEY|ShiftMask,             XK_l,      setcfact,       {.f = -0.25} },
	{ MODKEY|ShiftMask,             XK_o,      setcfact,       {.f =  0.00} },
	{ MODKEY|ControlMask,           XK_Return, zoom,           {0} },
	{ MODKEY|Mod1Mask,              XK_u,      incrgaps,       {.i = +1 } },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_u,      incrgaps,       {.i = -1 } },
	{ MODKEY|Mod1Mask,              XK_i,      incrigaps,      {.i = +1 } },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_i,      incrigaps,      {.i = -1 } },
	{ MODKEY|Mod1Mask,              XK_o,      incrogaps,      {.i = +1 } },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_o,      incrogaps,      {.i = -1 } },
	{ MODKEY|Mod1Mask,              XK_6,      incrihgaps,     {.i = +1 } },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_6,      incrihgaps,     {.i = -1 } },
	{ MODKEY|Mod1Mask,              XK_7,      incrivgaps,     {.i = +1 } },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_7,      incrivgaps,     {.i = -1 } },
	{ MODKEY|Mod1Mask,              XK_8,      incrohgaps,     {.i = +1 } },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_8,      incrohgaps,     {.i = -1 } },
	{ MODKEY|Mod1Mask,              XK_9,      incrovgaps,     {.i = +1 } },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_9,      incrovgaps,     {.i = -1 } },
	{ MODKEY|Mod1Mask,              XK_0,      togglegaps,     {0} },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_0,      defaultgaps,    {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
 	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
 	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_g,      setlayout,      {.v = &layouts[10]} },
	{ MODKEY,                       XK_c,      setlayout,      {.v = &layouts[11]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY|ShiftMask,             XK_f,      togglefullscr,  {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ MODKEY,                       XK_Right,  viewnext,       {0} },
	{ MODKEY,                       XK_Left,   viewprev,       {0} },
	{ MODKEY|ShiftMask,             XK_Right,  tagtonext,      {0} },
	{ MODKEY|ShiftMask,             XK_Left,   tagtoprev,      {0} },
	{ 0,            								XK_F12,  	 togglescratch,  {.ui = 0 } },
	{ 0,            								XK_F11,	   togglescratch,  {.ui = 1 } },
	{ 0, 			           						XK_F9,	   togglescratch,  {.ui = 2 } },
	{ 0,            								XK_F5,	   togglescratch,  {.ui = 3 } },
	{ 0,            								XK_F10,	   togglescratch,  {.ui = 4 } },
	{ 0,            								XK_F1,	   togglescratch,  {.ui = 5 } },
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
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button1,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

