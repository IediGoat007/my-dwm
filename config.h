/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int refresh_rate = 165;    /* Matches dwm's mouse event processing to your monitor's refresh rate for smoother window interactions. */
static const unsigned int borderpx  = 0;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int swallowfloating    = 1;        /* 1 means swallow floating windows by default */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayonleft = 0;    /* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systrayspacing = 1;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;        /* 0 means no systray */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const Bool viewontag         = True;     /* Switch view on tag switch */
static const char *fonts[]          = { "DepartureMono Nerd Font:size=10" };
static const char dmenufont[]       = "DepartureMono Nerd Font:size=10";
static const char col_gray1[]       = "#1e1e2e";
static const char col_gray2[]       = "#1e1e2e";
static const char col_gray3[]       = "#d9e0ee";
static const char col_gray4[]       = "#d9e0ee";
static const char col_cyan[]        = "#f28fad";
static const char col_pink[]        = "#dc6578";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_pink,  col_cyan  },
};

static const char *const autostart[] = {
	"polkit-gnome-authentication-agent-1", NULL,
	"qbittorrent", NULL,
        "dunst", NULL,
	"picom", NULL,
	"xset", "s", "off", "-dpms", "s", "noblank", "b", "off", NULL,
	"sh", "-c", "~/github/my-dwm/status", NULL,
	"sh", "-c", "~/github/my-dwm/fehbg", NULL,
	NULL /* terminate */
};

/* tagging */
/* static const char *tags[] = { "1", "2", "3", "4", "5" }; */
static const char *tags[] = { "Primary", "Secondary", "Games", "Chat", "Music" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class        instance  title           tags mask  isfloating  isterminal  noswallow  monitor */
        { "steam",       NULL,     NULL,           1 << 2,    0,          0,           0,        -1 },
        { "discord",     NULL,     NULL,           1 << 3,    0,          0,           0,        -1 },
        { "spotify",     NULL,     NULL,           1 << 4,    0,          0,           0,        -1 },
	{ "kitty",       NULL,     NULL,           0,         0,          1,           0,        -1 },
	{ NULL,          NULL,     "Event Tester", 0,         0,          0,           1,        -1 }, /* xev */
};

/* layout(s) */
static const float mfact     = 0.60; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 0; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
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
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_pink, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "kitty", NULL };

static const Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_r,      spawn,          {.v = dmenucmd } },
	{ MODKEY|ControlMask,           XK_x,      spawn,          {.v = termcmd } },
	{ MODKEY|ShiftMask,             XK_z,      spawn,          SHCMD ("thunar")},
	{ MODKEY|ShiftMask,             XK_s,      spawn,          SHCMD ("flameshot gui --clipboard")},
	{ MODKEY|ControlMask,           XK_z,      spawn,          SHCMD ("firefox")},
  { MODKEY|ControlMask,           XK_d,      spawn,          SHCMD ("discord")},
  { MODKEY|ControlMask,           XK_s,      spawn,          SHCMD ("steam")},
	{ MODKEY|ControlMask,           XK_equal,  spawn,          SHCMD ("pactl set-sink-volume @DEFAULT_SINK@ +5% && pkill -RTMIN+1 -f ~/github/my-dwm/status")},
	{ MODKEY|ControlMask,           XK_minus,  spawn,          SHCMD ("pactl set-sink-volume @DEFAULT_SINK@ -5% && pkill -RTMIN+1 -f ~/github/my-dwm/status")},
	{ MODKEY|ShiftMask,             XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_h,      setcfact,       {.f = +0.25} },
	{ MODKEY|ShiftMask,             XK_l,      setcfact,       {.f = -0.25} },
	{ MODKEY|ShiftMask,             XK_o,      setcfact,       {.f =  0.00} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,                       XK_q,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_m,      togglefloating, {0} },
	{ MODKEY|ShiftMask,             XK_f,      togglefullscr,  {0} },
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
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
	{ MODKEY|ControlMask|ShiftMask, XK_r,      spawn,          SHCMD("sudo /usr/bin/openrc-shutdown --reboot now")},
	{ MODKEY|ControlMask|ShiftMask, XK_s,      spawn,          SHCMD("sudo /usr/bin/openrc-shutdown --poweroff now")},
	{ MODKEY|ControlMask|ShiftMask, XK_u,      spawn,          SHCMD("pkill -u $USER")},
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {.i = 2} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

