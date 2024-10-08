static const char norm_fg[]       = "#f8f8f2";
static const char norm_bg[]       = "#282a36";
static const char norm_border[] = "#404040";

static const char sel_fg[]       = "#f8f8f2";
static const char sel_bg[]       = "#a272a4";
static const char sel_border[]       = "#644475";

static const char urg_fg[] = "#f8f8f2";
static const char urg_bg[] = "#604C4D";
static const char urg_border[] = "#604C4D";

static const char *colors[][3]      = {
    /*               fg           bg         border                         */
    [SchemeNorm] = { norm_fg,     norm_bg,   norm_border }, // unfocused wins
    [SchemeSel]  = { sel_fg,      sel_bg,    sel_border },  // the focused win
    [SchemeHid] =  { urg_fg,      urg_bg,    urg_border },  // Tab Colorschemes (awesomebar)
    [SchemeUrg] =  { urg_fg,      urg_bg,    urg_border },
};


static const char *wallpaper[] = {"feh", "--no-fehbg", "--bg-fill", "/home/jayar/.config/wall/dracula.jpg", NULL };
