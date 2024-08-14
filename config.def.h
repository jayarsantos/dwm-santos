/* See LICENSE file for copyright and license details. */

#define SESSION_FILE "/tmp/dwm-session"

/* appearance */
static const unsigned int borderpx  = 4;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int gappih    = 16;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 16;       /* vert inner gap between windows */
static const unsigned int gappoh    = 16;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 16;       /* vert outer gap between windows and screen edge */
static       int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static const int swallowfloating    = 0;        /* 1 means swallow floating windows by default */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int user_bh            = 8;        /* 2 is the default spacing around the bar's font */
static const char *fonts[]          = { "JetBrainsMonoNF:pixelsize=12:antialias=true:autohint=true:style=Bold" };
static const char dmenufont[]       = "JetBrainsMonoNF:size=12";
static unsigned int baralpha        = 0xd0;
static unsigned int borderalpha     = OPAQUE;

#include "themes/dracula.h"
// #include "themes/flower.h"
// #include "themes/music.h"

static const char *const autostart[] = {
	"/usr/lib/policykit-1-gnome/polkit-gnome-authentication-agent-1", NULL,
	// "slstatus", NULL,
	"dwmblocks", NULL,
	"picom", "--animations", "-b", NULL,
	"fehbg", NULL,
	"/opt/apps/keepassxc", NULL,
	"udiskie", "-Ans", NULL,
	"numlockx", NULL,
	NULL /* terminate */
};

typedef struct {
	const char *name;
	const void *cmd;
} Sp;
const char *spcmd1[] = {"st", "-n", "spterm", "-g", "120x30", NULL };
const char *spcmd2[] = {"st", "-n", "spfm", "-g", "120x30", "-e", "ranger", NULL };
const char *spcmd3[] = {"/opt/apps/keepassxc", NULL };
const char *spcmd4[] = {"pavucontrol", NULL };
const char *spcmd5[] = {"thunar", NULL };
const char *spcmd6[] = {"st", "-n", "sptop", "-g", "120x30", "-e", "btop", NULL };
const char *spcmd7[] = {"st", "-n", "smusic", "-g", "150x20", "-e", "ncmpcpp", NULL };
static Sp scratchpads[] = {
	/* name          cmd  */
	{"spterm",      spcmd1},
	{"spranger",    spcmd2},
	{"keepassxc",   spcmd3},
	{"pavucontrol", spcmd4},
	{"thunar", 		spcmd5},
	{"sptop", 	  	spcmd6},
	{"smusic", 	  	spcmd7},
};

/* tagging */
static const char *tags[] = { "", "", "", "", "", "", "7" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class     instance  title           tags mask  isfloating  isterminal  noswallow  monitor */
	{ "Gimp",    NULL,     NULL,           0,         1,          0,           0,        -1 },
	{ "firefox", NULL,     NULL,           1 << 1,    0,          0,          -1,        -1 },
	{ "St",      NULL,     NULL,           0,         0,          1,           0,        -1 },
	{ "Alacritty", NULL,   NULL,           0,         0,          1,           0,        -1 },
	{ NULL,      NULL,     "Event Tester", 0,         0,          0,           1,        -1 }, /* xev */
	{ NULL,		     "spterm",		   NULL,	 SPTAG(0),  1,			     1,          0,        -1 },
	{ NULL,		     "spfm",		     NULL,	 SPTAG(1),  1,			     1,          1,        -1 },
	{ NULL,		     "keepassxc",    NULL,	 SPTAG(2),  1,			    -1,         -1,        -1 },
	{ NULL,		     "pavucontrol",  NULL,	 SPTAG(3),  1,			    -1,         -1,        -1 },
	{ "Thunar",	 NULL,             NULL,	 SPTAG(4),  1,			    -1,         -1,        -1 },
	{ NULL,		     "sptop",        NULL,	 SPTAG(5),  1,			     1,          1,        -1 },
	{ NULL,		     "smusic",       NULL,	 SPTAG(6),  1,			     1,          1,        -1 },
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
  { "[]=",   /* 0 */   tile },    /* first entry is default */
  { "[M]",   /* 1 */   monocle },
	{ "[@]",   /* 2 */   spiral },
	{ "[\\]",  /* 3 */   dwindle },
	{ "H[]",   /* 4 */   deck },
	{ "TTT",   /* 5 */   bstack },
	{ "===",   /* 6 */   bstackhoriz },
	{ "HHH",   /* 7 */   grid },
	{ "###",   /* 8 */   nrowgrid },
	{ "---",   /* 9 */   horizgrid },
	{ ":::",   /* 10 */   gaplessgrid },
	{ "|M|",   /* 11 */   centeredmaster },
	{ ">M>",   /* 12 */  centeredfloatingmaster },
	{ "><>",   /* 13 */  NULL },    /* no layout function means floating behavior */
	{ NULL,       NULL },
};

/* key definitions */
#define MODKEY Mod4Mask
#define MODALT Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, NULL };
static const char *termcmd[]  = { "st", "-e", "fish", NULL };

static const char *launchercmd[] = { "rofi", "-show", "drun", NULL };
static const char *mutecmd[] = { "pactl", "set-sink-mute", "0", "toggle", NULL };
static const char *volupcmd[] = { "pactl", "set-sink-volume", "0", "+5%", NULL };
static const char *voldowncmd[] = { "pactl", "set-sink-volume", "0", "-5%", NULL };

static const char *browsercmd[] = {"firefox", NULL};

Autostarttag autostarttaglist[] = {
	{.cmd = browsercmd, .tags = 1 << 1 },
	{.cmd = wallpaper, .tags = 0 },
	{.cmd = NULL, .tags = 0 },
};

#include "exitdwm.c"
static const Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_y,      spawn,          {.v = launchercmd} }, // spawn rofi for launching other programs
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstackvis,  {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstackvis,  {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_j,      focusstackhid,  {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_k,      focusstackhid,  {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_h,      setcfact,       {.f = +0.25} },
	{ MODKEY|ShiftMask,             XK_l,      setcfact,       {.f = -0.25} },
	{ MODKEY|ShiftMask,             XK_o,      setcfact,       {.f =  0.00} },
	{ MODALT,                       XK_Return, zoom,           {0} },
	{ MODKEY|Mod4Mask,              XK_u,      incrgaps,       {.i = +1 } },
	{ MODKEY|Mod4Mask|ShiftMask,    XK_u,      incrgaps,       {.i = -1 } },
	{ MODKEY|Mod4Mask,              XK_i,      incrigaps,      {.i = +1 } },
	{ MODKEY|Mod4Mask|ShiftMask,    XK_i,      incrigaps,      {.i = -1 } },
	{ MODKEY|Mod4Mask,              XK_o,      incrogaps,      {.i = +1 } },
	{ MODKEY|Mod4Mask|ShiftMask,    XK_o,      incrogaps,      {.i = -1 } },
	{ MODKEY|Mod4Mask,              XK_6,      incrihgaps,     {.i = +1 } },
	{ MODKEY|Mod4Mask|ShiftMask,    XK_6,      incrihgaps,     {.i = -1 } },
	{ MODKEY|Mod4Mask,              XK_7,      incrivgaps,     {.i = +1 } },
	{ MODKEY|Mod4Mask|ShiftMask,    XK_7,      incrivgaps,     {.i = -1 } },
	{ MODKEY|Mod4Mask,              XK_8,      incrohgaps,     {.i = +1 } },
	{ MODKEY|Mod4Mask|ShiftMask,    XK_8,      incrohgaps,     {.i = -1 } },
	{ MODKEY|Mod4Mask,              XK_9,      incrovgaps,     {.i = +1 } },
	{ MODKEY|Mod4Mask|ShiftMask,    XK_9,      incrovgaps,     {.i = -1 } },
	{ MODKEY|Mod4Mask,              XK_0,      togglegaps,     {0} },
	{ MODKEY|Mod4Mask|ShiftMask,    XK_0,      defaultgaps,    {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ControlMask,           XK_x,      killclient,     {0} },
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
	{ 0,            								XK_F12,  	 togglescratch,  {.ui = 0 } },
	{ 0,            								XK_F11,	   togglescratch,  {.ui = 1 } },
	{ 0,            								XK_F10,	   togglescratch,  {.ui = 4 } },
	{ 0, 			           						XK_F9,	   togglescratch,  {.ui = 2 } },
	{ 0,            								XK_F8,	   togglescratch,  {.ui = 6 } },
  { 0,                            XK_F7,     spawn,          {.v = volupcmd } },
  { 0,                            XK_F6,     spawn,          {.v = voldowncmd } },
	{ 0,                            XK_F5,     spawn,          {.v = mutecmd } },
	{ 0,            								XK_F4,	   togglescratch,  {.ui = 3 } },
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
	{ MODKEY,                       XK_s,      show,           {0} },
	{ MODKEY|ShiftMask,             XK_s,      showall,        {0} },
	{ MODKEY,                       XK_m,      hide,           {0} },
	{ MODKEY|ControlMask,           XK_r,      quit,           {1} }, 
	{ MODKEY|ShiftMask,             XK_e,      exitdwm,        {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button1,        togglewin,      {0} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button1,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

