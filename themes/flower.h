static const char norm_fg[] = "#83cfe2";
static const char norm_bg[] = "#06080E";
static const char norm_border[] = "#5b909e";

static const char sel_fg[] = "#83cfe2";
static const char sel_bg[] = "#AF4322";
static const char sel_border[] = "#83cfe2";

static const char urg_fg[] = "#83cfe2";
static const char urg_bg[] = "#604C4D";
static const char urg_border[] = "#604C4D";

static const char *colors[][3]      = {
    /*               fg           bg         border                         */
    [SchemeNorm] = { norm_fg,     norm_bg,   norm_border }, // unfocused wins
    [SchemeSel]  = { sel_fg,      sel_bg,    sel_border },  // the focused win
    [SchemeHid] =  { urg_fg,      urg_bg,    urg_border },  // Tab Colorschemes (awesomebar)
    [SchemeUrg] =  { urg_fg,      urg_bg,    urg_border },
};

static const char *wallpaper[] = {"feh", "--no-fehbg", "--bg-fill", "/home/jayar/.config/wall/flower.jpg", NULL };
