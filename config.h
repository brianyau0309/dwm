/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = {
  "CascadiaCode:pixelsize=18:antialias=true:autohint=true",
  "NotoSansCJKHK:pixelsize=18:antialias=true:autohint=true",
  "JoyPixels:pixelsize=16:antialias=true:autohint=true",
  "Symbola:pixelsize=16:antialias=true:autohint=true",
  "Symbols Nerd Font:pixelsize=18:antialias=true:autohint=true"
};
static const char dmenufont[]       = "CascadiaCode:pixelsize=18:antialias=true:autohint=true";
static const char col_black[]       = "#000000";
static const char col_gray0[]       = "#161B1D";
static const char col_gray1[]       = "#202020";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#006688";
static const char col_green0[]      = "#226655";
static const char col_green[]       = "#44bbaa";
static const unsigned int baralpha = 0x90;
static const unsigned int borderalpha = OPAQUE;
static const char *colors[][3]      = {
	/*               fg         bg          border   */
	[SchemeNorm] = { col_gray3, col_black,  col_gray2   },
	[SchemeSel]  = { col_gray4, col_green0, col_green0  },
	[SchemeSelW] = { col_gray4, col_black,  col_gray2   },
};
static const unsigned int alphas[][3]      = {
	/*               fg      bg        border     */
	[SchemeNorm] = { OPAQUE, baralpha, borderalpha },
	[SchemeSel]  = { OPAQUE, baralpha, borderalpha },
	[SchemeSelW] = { OPAQUE, baralpha, borderalpha },
};

/* tagging */
static const char *tags[] = { "🐧","🌏","📬","💬","📝","🖼","📽","🎮","🚫" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class           instance         title       tags mask   switchtotag   switchtourgent   isfloating   monitor */
  { "Thunderbird",   "Mail",          NULL,       1 << 2,     0,            0,               0,           -1 },
  { "Thunderbird",   "Calendar",      NULL,       0,          0,            0,               1,           -1 },
  { "Thunderbird",   "Msgcompose",    NULL,       0,          0,            0,               1,           -1 },
  { "thunderbird",   "Mail",          NULL,       1 << 2,     0,            0,               0,           -1 },
  { "thunderbird",   "Calendar",      NULL,       0,          0,            0,               1,           -1 },
  { "thunderbird",   "Msgcompose",    NULL,       0,          0,            0,               1,           -1 },
  { "Google-chrome", "google-chrome", NULL,       1 << 1,     1,            1,               0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "[M]",      monocle },
	{ "><>",      NULL },    /* no layout function means floating behavior */
};

/* key definitions */
#define MODKEY Mod4Mask
#define AltMask Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_green, "-sf", col_gray1, NULL };
static const char *termcmd[]  = { "alacritty", NULL };

static const StatusCmd statuscmds[] = {
	{ "moc.statuscmd",            1 },
  { "wkon.statuscmd",           2 },
  { "storage.statuscmd",        3 },
  { "date.statuscmd",           4 },
  { "battery.statuscmd",        5 },
  { "keyboard.statuscmd",       6 },
  { "syncthing.statuscmd",      7 },
  { "bluetooth.statuscmd",      8 },
  { "notify.statuscmd",         9 },
  { "audio.statuscmd",          11 },
  { "internet.statuscmd",       12 },
};
static const char *statuscmd[] = { "/bin/sh", "-c", NULL, NULL };

#include <X11/XF86keysym.h>
#include "focusurgent.c"
static const Key keys[] = {
	/* modifier                     key                        function           argument */

  { MODKEY,                       XK_semicolon,              spawn,             {.v = dmenucmd } },
  { MODKEY,                       XK_t,                      spawn,             {.v = termcmd } },

  // Open
  { MODKEY,                       XK_w,                      spawn,             SHCMD("$BROWSER") },
  { MODKEY|ShiftMask,             XK_w,                      spawn,             SHCMD("$WBROWSER") },

  { MODKEY,                       XK_Return,                 spawn,             SHCMD("alacritty -t nnn -e nnn -erx ~") },
  { MODKEY,                       XK_n,                      spawn,             SHCMD("dunstctl set-paused toggle && refstatus") },
  { MODKEY,                       XK_v,                      spawn,             SHCMD("alacritty -t pulsemixer -e pulsemixer") },
  { MODKEY,                       XK_c,                      spawn,             SHCMD("clipmenu -i 2>/dev/null") },
  { 0,                            XK_Pause,                  spawn,             SHCMD("betterlockscreen -l >/dev/null") },

  // Script
  { MODKEY,                       XK_e,                      spawn,             SHCMD("emoji") },
  { MODKEY,                       XK_r,                      spawn,             SHCMD("refstatus") },
  { MODKEY,                       XK_s,                      spawn,             SHCMD("dmenussh") },
  { MODKEY,                       XK_i,                      spawn,             SHCMD("dmenuwifi") },
  { MODKEY,                       XK_d,                      spawn,             SHCMD("dmenudisplay") },
  { MODKEY,                       XK_m,                      spawn,             SHCMD("dmenumount mount") },
  { MODKEY,                       XK_u,                      spawn,             SHCMD("dmenumount umount") },
  { MODKEY,                       XK_b,                      spawn,             SHCMD("dmenublue >/dev/null") },
  { 0,                            XK_Print,                  spawn,             SHCMD("screenshot full") },
  { ShiftMask,                    XK_Print,                  spawn,             SHCMD("screenshot select") },
  { MODKEY,                       XK_Right,                  spawn,             SHCMD("brightness up && xobctl show brightness") },
  { MODKEY,                       XK_Left,                   spawn,             SHCMD("brightness down && xobctl show brightness") },
  { MODKEY,                       XK_Up,                     spawn,             SHCMD("audio up && xobctl show volume") },
  { MODKEY,                       XK_Down,                   spawn,             SHCMD("audio down && xobctl show volume") },
  { MODKEY|ShiftMask,             XK_p,                      spawn,             SHCMD("genurlqr") },

  // XF86 keys
  { 0,                            XF86XK_MonBrightnessUp,    spawn,             SHCMD("brightness up && xobctl show brightness") },
  { 0,                            XF86XK_MonBrightnessDown,  spawn,             SHCMD("brightness down && xobctl show brightness") },
  { 0,                            XF86XK_AudioMute,          spawn,             SHCMD("audio toggle && xobctl show volume") },
  { 0,                            XF86XK_AudioRaiseVolume,   spawn,             SHCMD("audio up && xobctl show volume") },
  { 0,                            XF86XK_AudioLowerVolume,   spawn,             SHCMD("audio down && xobctl show volume") },
  { 0,                            XF86XK_AudioPlay,          spawn,             SHCMD("playerctl play-pause") },
  { 0,                            XF86XK_AudioPause,         spawn,             SHCMD("playerctl pause") },
  { 0,                            XF86XK_AudioNext,          spawn,             SHCMD("playerctl next") },
  { 0,                            XF86XK_AudioPrev,          spawn,             SHCMD("playerctl previous") },

	{ MODKEY,                       XK_b,                      togglebar,         {0} },
	{ MODKEY,                       XK_j,                      focusstack,        {.i = +1 } },
	{ MODKEY,                       XK_k,                      focusstack,        {.i = -1 } },
	{ MODKEY,                       XK_i,                      incnmaster,        {.i = +1 } },
	{ MODKEY,                       XK_d,                      incnmaster,        {.i = -1 } },
	{ MODKEY,                       XK_h,                      setmfact,          {.f = -0.05} },
	{ MODKEY,                       XK_l,                      setmfact,          {.f = +0.05} },
	{ MODKEY,                       XK_z,                      zoom,              {0} },

  // Window Movement
 	{ MODKEY|ShiftMask,             XK_j,                      moveresize,        {.v = "0x 25y 0w 0h" } },
 	{ MODKEY|ShiftMask,             XK_k,                      moveresize,        {.v = "0x -25y 0w 0h" } },
 	{ MODKEY|ShiftMask,             XK_l,                      moveresize,        {.v = "25x 0y 0w 0h" } },
 	{ MODKEY|ShiftMask,             XK_h,                      moveresize,        {.v = "-25x 0y 0w 0h" } },
 	{ MODKEY|ControlMask,           XK_j,                      moveresize,        {.v = "0x 0y 0w 25h" } },
 	{ MODKEY|ControlMask,           XK_k,                      moveresize,        {.v = "0x 0y 0w -25h" } },
 	{ MODKEY|ControlMask,           XK_l,                      moveresize,        {.v = "0x 0y 25w 0h" } },
 	{ MODKEY|ControlMask,           XK_h,                      moveresize,        {.v = "0x 0y -25w 0h" } },

	{ AltMask,                      XK_Tab,                    view,              {0} },
	{ MODKEY,                       XK_Tab,                    shiftviewclients,  { .i = +1 } },
	{ MODKEY|ShiftMask,             XK_Tab,                    shiftviewclients,  { .i = -1 } },
	{ AltMask|ShiftMask,            XK_Tab,                    focusurgent,       {0} },

	{ MODKEY|ShiftMask,             XK_t,                      setlayout,         {.v = &layouts[0]} },
	{ MODKEY|ShiftMask,             XK_m,                      setlayout,         {.v = &layouts[1]} },
	{ MODKEY|ShiftMask,             XK_f,                      setlayout,         {.v = &layouts[2]} },
	{ MODKEY|ShiftMask,             XK_space,                  setlayout,         {0} },
	{ MODKEY,                       XK_space,                  togglefloating,    {0} },
	{ MODKEY,                       XK_0,                      view,              {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,                      tag,               {.ui = ~0 } },
	{ MODKEY,                       XK_comma,                  focusmon,          {.i = -1 } },
	{ MODKEY,                       XK_period,                 focusmon,          {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,                  tagmon,            {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period,                 tagmon,            {.i = +1 } },
	TAGKEYS(                        XK_1,                                         0)
	TAGKEYS(                        XK_2,                                         1)
	TAGKEYS(                        XK_3,                                         2)
	TAGKEYS(                        XK_4,                                         3)
	TAGKEYS(                        XK_5,                                         4)
	TAGKEYS(                        XK_6,                                         5)
	TAGKEYS(                        XK_7,                                         6)
	TAGKEYS(                        XK_8,                                         7)
	TAGKEYS(                        XK_9,                                         8)

	// Quit
	{ MODKEY,                       XK_q,                      killclient,        {0} },
	{ MODKEY|ShiftMask,             XK_q,                      spawn,             SHCMD("power") },
  { MODKEY|ShiftMask,             XK_F12,                    quit,              {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientW  in, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argu  ment */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button1,        spawn,          {.v = statuscmd } },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = statuscmd } },
	{ ClkStatusText,        0,              Button3,        spawn,          {.v = statuscmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

